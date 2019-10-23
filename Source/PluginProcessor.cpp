/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Reverb_Edit.h"

//==============================================================================
TokyoRe_verbAudioProcessor::TokyoRe_verbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mState(*this, &mUndoManager, "Summative", {
         
         std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 600.0f),
         std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 1.0f),
         /*std::make_unique<AudioParameterFloat>("drive", "Drive", NormalisableRange<float>(0.0f, 1.0f, 0.0001), 0.01f),
         std::make_unique<AudioParameterFloat>("range", "Range", NormalisableRange<float>(0.0f, 3000.0f, 0.0001), 0.01f),
         std::make_unique<AudioParameterFloat>("blend", "Blend", NormalisableRange<float>(0.1f, 1.0f, 0.0001), 0.1f),
         std::make_unique<AudioParameterFloat>("volume", "Volume", NormalisableRange<float>(0.0f, 3.0f, 0.0001), 0.01f),*/
         //std::make_unique<AudioParameterFloat>("dry", "Dry", 0.0f, 1.0f, 0.4f),
         //std::make_unique<AudioParameterFloat>("wet", "Wet", 0.0f, 1.0f, 0.33f),
         std::make_unique<AudioParameterFloat>("mix", "Mix", 0, 1, 0.5),
         std::make_unique<AudioParameterFloat>("room", "Room", 0, 1, 0.5),
         std::make_unique<AudioParameterFloat>("damp", "Damp", 0, 1, 0.5),
         std::make_unique<AudioParameterFloat>("width", "Width", 0, 1, 0),
         
     }), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))

#endif
{
    
    /*tokyoReverbParameters.dryLevel = 0.4f;
    tokyoReverbParameters.wetLevel = 0.33f;
    tokyoReverbParameters.roomSize = 0.5f;
    tokyoReverbParameters.damping = 0.5f;
    tokyoReverbParameters.width = 0.5f;
    tokyoReverbParameters.freezeMode = 0.0f;*/
    
    
    //dry = mState.getRawParameterValue("dry");
    //wet = mState.getRawParameterValue("wet");
    mix = mState.getRawParameterValue("mix");
    room = mState.getRawParameterValue("room");
    damp = mState.getRawParameterValue("damp");
    width = mState.getRawParameterValue("width");
    
    //updatedPara(0.4, 0.33, 05., 0.5, 0.5);
    
    
    
}

TokyoRe_verbAudioProcessor::~TokyoRe_verbAudioProcessor()
{
}

//==============================================================================
const String TokyoRe_verbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TokyoRe_verbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TokyoRe_verbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TokyoRe_verbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TokyoRe_verbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TokyoRe_verbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TokyoRe_verbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TokyoRe_verbAudioProcessor::setCurrentProgram (int index)
{
}

const String TokyoRe_verbAudioProcessor::getProgramName (int index)
{
    return {};
}

void TokyoRe_verbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TokyoRe_verbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    currentSampleRate = sampleRate;
    
    //tokyoReverb.reset();
    
    tokyoReverb.setSampleRate(sampleRate);
    tokyoReverb.setParameters(tokyoReverbParameters);
    
    //lastSampleRate = sampleRate;
    
    // TAYLOR COMMENT:
    // THIS IS WHERE THE GENERAL DSP IS SETUP
    // AFTER THAT YOU CAN SEE THE SETUP OF THE FILTER, WITH SPEC USED TO PASS THE SAMPLERATE TO THE FILTER DSP
    // RESET IS THEN CALLED TO MAKE SURE IT KEEPS CHECKING/RESETTING
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
    //tokyoReverb.prepare(spec);
   // tokyoReverb.reset();
    // tokyoReverb.setSampleRate(spec); THIS SHOULD BE HOW ITS DONE? MAYBE?
    
    //updatedPara(0.4, 0.33, 05., 0.5, 0.5);

}

void TokyoRe_verbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TokyoRe_verbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// TAYLOR COMMENT:
// THIS IS THE FUNCTION USED TO UPDATE THE FILTER WITH NEW SAMPLES
// THIS IS WHERE WE SETUP THE FUNCTION TO CALL LATER
// YOU CAN SEE THAT IT GETS ITS VALUES FROM THE PARAMETERS WE SET AT THE START/UP ABOVE (cutoff, resonance)

void TokyoRe_verbAudioProcessor::updateFilter()
{
    float freq = *mState.getRawParameterValue("cutoff");
    float res = *mState.getRawParameterValue("resonance");
    
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(currentSampleRate, freq, res);
}

/*void TokyoRe_verbAudioProcessor::updateReverb()
{
    
    //float dryRev = *mState.getRawParameterValue("dry");
    //float wetRev = *mState.getRawParameterValue("wet");
    //float roomRev = *mState.getRawParameterValue("room");
    //float dampRev = *mState.getRawParameterValue("damp");
    //float widthRev = *mState.getRawParameterValue("width");
    
    tokyoReverbParameters.dryLevel = *dry;
    tokyoReverbParameters.wetLevel = *wet;
    tokyoReverbParameters.roomSize = *room;
    tokyoReverbParameters.damping = *damp;
    tokyoReverbParameters.width = *width;
    //tokyoReverb.reset();
    tokyoReverb.setParameters(tokyoReverbParameters);
    
    
}*/


void TokyoRe_verbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //updateReverb();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    tokyoReverbParameters.roomSize = *room;
    tokyoReverbParameters.width = *width;
    tokyoReverbParameters.damping = *damp;
    tokyoReverbParameters.dryLevel = 1 - *mix;
    tokyoReverbParameters.wetLevel = *mix;
    
    tokyoReverb.setParameters(tokyoReverbParameters);
    
    if (totalNumInputChannels == 1)
        tokyoReverb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    
    else
        tokyoReverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
    
    // TAYLOR COMMENT:
    // HERE IN THE PROCESS BLOCK IS WHERE EVERYTHING HAPPENS
    
    // WE CREATE "block" THAT TAKES THE AUDIO IN THE BUFFER
    //dsp::AudioBlock<float> block (buffer);
    
    // WE UPDATE THE FILTER TO GET CURRENT VALUES CONSTANTLY, YOU WOULD UPDATE WHATEVER EFFECT HERE AS WELL (UNLESS IT WAS IN A LATER LOOP LIKE THE DISTORTION YOU CAN SEE BELOW, DEPENDS ON THE EFFECT)
    //updateFilter();
    
    // THE FILTER THEN PROCESSES THE "block" WITH THE CURRENT PARAMETER VALUES
    //lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
    //updateReverb();
    
    //updateDistParameters();
    //overdrive.process(dsp::ProcessContextReplacing <float> (block));
    
    // THIS IS WHERE WE RETRIEVE THE MOST CURRENT VALUES FOR THE DISTORTION PARAMETERS (ITS A SLIGHTLY DIFFERENT PROCESS THAN WITH THE FILTER)
    // WE ARE THEN STORING THEM WITHIN THEIR OWN FLOATS. NOT NECESSARY I DONT THINK BUT MAKES IT EASIER TO WORK WITH
    //float mDrive = *mState.getRawParameterValue("drive");
    //float mRange = *mState.getRawParameterValue("range");
    //float mBlend = *mState.getRawParameterValue("blend");
    //float mVolume = *mState.getRawParameterValue("volume");
    
    //AudioBuffer<float> wetBuffer(getTotalNumInputChannels(), buffer.getNumSamples());
    //wetBuffer.makeCopyOf(buffer);
    
    
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        
       // auto* channelData = buffer.getWritePointer (channel);
       // auto* wetData = wetBuffer.getWritePointer (channel);

        //for (int sample = 0; sample < buffer.getNumSamples(); ++sample){
    
    //const auto numChannels = jmin(totalNumInputChannels, totalNumOutputChannels);
    
   /* if (numChannels == 1){
        //tokyoReverb.process(buffer.getWritePointer(0), buffer.getNumSamples());
        tokyoReverb.processMono(wetBuffer.getWritePointer(0), wetBuffer.getNumSamples());
        //channelData[sample] = ((channelData[sample] * 0.5) + (wetData[sample] * 0.5));
        }
    
    else if (numChannels == 2){
        tokyoReverb.processStereo(wetBuffer.getWritePointer(0), wetBuffer.getWritePointer(1), wetBuffer.getNumSamples());
        //channelData[sample] = ((channelData[sample] * 0.5) + (wetData[sample] * 0.5));
            }*/
            
       // }
        
    }
    
    dsp::AudioBlock<float> block (buffer);
    //updateReverb();
    //tokyoReverb.process(dsp::ProcessContextReplacing<float> (block));
    updateFilter();
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
    //tokyoReverb.reset();
    
}

//==============================================================================
bool TokyoRe_verbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TokyoRe_verbAudioProcessor::createEditor()
{
    return new TokyoRe_verbAudioProcessorEditor (*this);
}

//==============================================================================
void TokyoRe_verbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // TAYLOR COMMENT:
    // THIS AND THE NEXT SECTION IS SETTING THE PLUGIN UP TO REMEMBER PARAMETERS AND SAVE STATES
    // YOU CAN BASICALLY COPY THIS WHOLE getStateInformation AND setStateInformation SECTION DIRECT TO YOURS
    MemoryOutputStream stream(destData, false);
    mState.state.writeToStream(stream);
    
}

void TokyoRe_verbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // TAYLOR COMMENT:
    // LIKE I SAID ABOVE, YOU CAN STRAIGHT UP COPY THIS SECTION TO YOURS
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        mState.state = tree;
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TokyoRe_verbAudioProcessor();
}
