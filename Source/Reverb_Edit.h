/*
 ==============================================================================
 
 This file is part of the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004-11 by Raw Material Software Ltd.
 
 ------------------------------------------------------------------------------
 
 JUCE can be redistributed and/or modified under the terms of the GNU General
 Public License (Version 2), as published by the Free Software Foundation.
 A copy of the license is included in the JUCE distribution, or can be found
 online at www.gnu.org/licenses.
 
 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.rawmaterialsoftware.com/juce for more information.
 
 ==============================================================================
 */

#ifndef __REVERB_EDIT__
#define __REVERB_EDIT__


//==============================================================================
/**
 Performs a simple reverb effect on a stream of audio data.
 
 This is a simple stereo reverb, based on the technique and tunings used in FreeVerb.
 Use setSampleRate() to prepare it, and then call processStereo() or processMono() to
 apply the reverb to your audio data.
 
 @see ReverbAudioSource
 */
class EditReverb
{
public:
    //==============================================================================
    EditReverb()
    {
        setParameters (Parameters());
        setSampleRate (44100.0);
    }
    
    //==============================================================================
    /** Holds the parameters being used by a Reverb object. */
    struct Parameters
    {
        Parameters() noexcept
        : roomSize   (0.5f),
        damping    (0.5f),
        wetLevel   (0.33f),
        dryLevel   (0.4f),
        width      (1.0f),
        freezeMode (0)
        {}
        
        float roomSize;     /**< Room size, 0 to 1.0, where 1.0 is big, 0 is small. */
        float damping;      /**< Damping, 0 to 1.0, where 0 is not damped, 1.0 is fully damped. */
        float wetLevel;     /**< Wet level, 0 to 1.0 */
        float dryLevel;     /**< Dry level, 0 to 1.0 */
        float width;        /**< Reverb width, 0 to 1.0, where 1.0 is very wide. */
        float freezeMode;   /**< Freeze mode - values < 0.5 are "normal" mode, values > 0.5
                             put the reverb into a continuous feedback loop. */
    };
    
    //==============================================================================
    /** Returns the reverb's current parameters. */
    const Parameters& getParameters() const noexcept    { return parameters; }
    
    /** Applies a new set of parameters to the reverb.
     Note that this doesn't attempt to lock the reverb, so if you call this in parallel with
     the process method, you may get artifacts.
     */
    void setParameters (const Parameters& newParams)
    {
        const float wetScaleFactor = 3.0f;
        const float dryScaleFactor = 2.0f;
        
        const float wet = newParams.wetLevel * wetScaleFactor;
        wet1 = wet * (newParams.width * 0.5f + 0.5f);
        wet2 = wet * (1.0f - newParams.width) * 0.5f;
        dry = newParams.dryLevel * dryScaleFactor;
        gain = isFrozen (newParams.freezeMode) ? 0.0f : 0.015f;
        parameters = newParams;
        shouldUpdateDamping = true;
    }
    
    //==============================================================================
    /** Sets the sample rate that will be used for the reverb.
     You must call this before the process methods, in order to tell it the correct sample rate.
     */
    void setSampleRate (const double sampleRate)
    {
        jassert (sampleRate > 0);
        
        static const short combTunings[] = { 1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617 }; // (at 44100Hz)
        static const short allPassTunings[] = { 556, 441, 341, 225 };
        const int stereoSpread = 23;
        const int intSampleRate = (int) sampleRate;
        
        for (int i = 0; i < numCombs; ++i)
        {
            comb[0][i].setSize ((intSampleRate * combTunings[i]) / 44100);
            comb[1][i].setSize ((intSampleRate * (combTunings[i] + stereoSpread)) / 44100);
        }
        
        for (int i = 0; i < numAllPasses; ++i)
        {
            allPass[0][i].setSize ((intSampleRate * allPassTunings[i]) / 44100);
            allPass[1][i].setSize ((intSampleRate * (allPassTunings[i] + stereoSpread)) / 44100);
        }
        
        shouldUpdateDamping = true;
    }
    
    /** Clears the reverb's buffers. */
    void reset()
    {
        for (int j = 0; j < numChannels; ++j)
        {
            for (int i = 0; i < numCombs; ++i)
                comb[j][i].clear();
            
            for (int i = 0; i < numAllPasses; ++i)
                allPass[j][i].clear();
        }
    }
    
    //==============================================================================
    /** Applies the reverb to two stereo channels of audio data. */
    void processStereo (float* const left, float* const right, const int numSamples) noexcept
    {
        jassert (left != nullptr && right != nullptr);
        
        if (shouldUpdateDamping)
            updateDamping();
        
        for (int i = 0; i < numSamples; ++i)
        {
            const float input = (left[i] + right[i]) * gain;
            float outL = 0, outR = 0;
            
            for (int j = 0; j < numCombs; ++j)  // accumulate the comb filters in parallel
            {
                outL += comb[0][j].process (input);
                outR += comb[1][j].process (input);
            }
            
            for (int j = 0; j < numAllPasses; ++j)  // run the allpass filters in series
            {
                outL = allPass[0][j].process (outL);
                outR = allPass[1][j].process (outR);
            }
            
            left[i]  = outL * wet1 + outR * wet2 + left[i]  * dry;
            right[i] = outR * wet1 + outL * wet2 + right[i] * dry;
        }
    }
    
    /** Applies the reverb to a single mono channel of audio data. */
    void processMono (float* const samples, const int numSamples) noexcept
    {
        jassert (samples != nullptr);
        
        if (shouldUpdateDamping)
            updateDamping();
        
        for (int i = 0; i < numSamples; ++i)
        {
            const float input = samples[i] * gain;
            float output = 0;
            
            for (int j = 0; j < numCombs; ++j)  // accumulate the comb filters in parallel
                output += comb[0][j].process (input);
            
            for (int j = 0; j < numAllPasses; ++j)  // run the allpass filters in series
                output = allPass[0][j].process (output);
            
            samples[i] = output * wet1 + input * dry;
        }
    }
    
private:
    //==============================================================================
    Parameters parameters;
    
    volatile bool shouldUpdateDamping;
    float gain, wet1, wet2, dry;
    
    inline static bool isFrozen (const float freezeMode) noexcept  { return freezeMode >= 0.5f; }
    
    void updateDamping() noexcept
    {
        const float roomScaleFactor = 0.28f;
        const float roomOffset = 0.7f;
        const float dampScaleFactor = 0.4f;
        
        shouldUpdateDamping = false;
        
        if (isFrozen (parameters.freezeMode))
            setDamping (0.0f, 1.0f);
        else
            setDamping (parameters.damping * dampScaleFactor,
                        parameters.roomSize * roomScaleFactor + roomOffset);
    }
    
    void setDamping (const float dampingToUse, const float roomSizeToUse) noexcept
    {
        for (int j = 0; j < numChannels; ++j)
            for (int i = numCombs; --i >= 0;)
                comb[j][i].setFeedbackAndDamp (roomSizeToUse, dampingToUse);
    }
    
    //==============================================================================
    class CombFilter
    {
    public:
        CombFilter() noexcept  : bufferSize (0), bufferIndex (0) {}
        
        void setSize (const int size)
        {
            if (size != bufferSize)
            {
                bufferIndex = 0;
                buffer.malloc ((size_t) size);
                bufferSize = size;
            }
            
            clear();
        }
        
        void clear() noexcept
        {
            last = 0;
            buffer.clear ((size_t) bufferSize);
        }
        
        void setFeedbackAndDamp (const float f, const float d) noexcept
        {
            damp1 = d;
            damp2 = 1.0f - d;
            feedback = f;
        }
        
        inline float process (const float input) noexcept
        {
            const float output = buffer [bufferIndex];
            last = (output * damp2) + (last * damp1);
            JUCE_UNDENORMALISE (last);
            
            float temp = input + (last * feedback);
            JUCE_UNDENORMALISE (temp);
            buffer [bufferIndex] = temp;
            bufferIndex = (bufferIndex + 1) % bufferSize;
            return output;
        }
        
    private:
        HeapBlock<float> buffer;
        int bufferSize, bufferIndex;
        float feedback, last, damp1, damp2;
        
        JUCE_DECLARE_NON_COPYABLE (CombFilter)
    };
    
    //==============================================================================
    class AllPassFilter
    {
    public:
        AllPassFilter() noexcept  : bufferSize (0), bufferIndex (0) {}
        
        void setSize (const int size)
        {
            if (size != bufferSize)
            {
                bufferIndex = 0;
                buffer.malloc ((size_t) size);
                bufferSize = size;
            }
            
            clear();
        }
        
        void clear() noexcept
        {
            buffer.clear ((size_t) bufferSize);
        }
        
        inline float process (const float input) noexcept
        {
            const float bufferedValue = buffer [bufferIndex];
            float temp = input + (bufferedValue * 0.5f);
            JUCE_UNDENORMALISE (temp);
            buffer [bufferIndex] = temp;
            bufferIndex = (bufferIndex + 1) % bufferSize;
            return bufferedValue - input;
        }
        
    private:
        HeapBlock<float> buffer;
        int bufferSize, bufferIndex;
        
        JUCE_DECLARE_NON_COPYABLE (AllPassFilter)
    };
    
    enum { numCombs = 8, numAllPasses = 4, numChannels = 2 };
    
    CombFilter comb [numChannels][numCombs];
    AllPassFilter allPass [numChannels][numAllPasses];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditReverb)
};


#endif   // __JUCE_REVERB_JUCEHEADER__
