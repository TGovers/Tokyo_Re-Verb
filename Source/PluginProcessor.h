/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Reverb_Edit.h"

//==============================================================================
/**
*/
class TokyoRe_verbAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TokyoRe_verbAudioProcessor();
    ~TokyoRe_verbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState& getValueTreeState();
    
    void updateFilter();
    
    //void updateParameters();
    
    //void updateReverb();
    
    // TAYLOR COMMENT:
    // CANT REMEMBER IF I EVER USED THIS, DONT THINK I DID BUT MIGHT AS WELL ADD ANYWAY
    SmoothedValue<float>mixLevel;
    
    //SmoothedValue<float>freqLevel;
    //SmoothedValue<float>resLevel;
    
    AudioProcessorValueTreeState mState;
    
    //void updatedPara (float p1, float p2, float p3, float p4, float p5);

private:
    
    float currentSampleRate;
    //float lastSampleRate;
    
    // TAYLOR COMMENT:
    // THIS IS DEFINING THE DIFFERENT PARAMETERS, CHANGE FOR WHAT EFFECT YOU DO (FILTER ONES SHOULD BE PRETTY SIMILAR)
    AudioParameterFloat* cutoff;
    AudioParameterFloat* resonance;
    
    /*AudioParameterFloat* drive;
    AudioParameterFloat* range;
    AudioParameterFloat* blend;
    AudioParameterFloat* volume;
    
    float*driveParameter = nullptr;
    float*rangeParameter = nullptr;
    float*blendParameter = nullptr;
    float*volumeParameter = nullptr;*/
    
    float*cutoffParameter = nullptr;
    float*resParameter = nullptr;
    
   // float* dry = nullptr;
   // float* wet = nullptr;
    float *room = 0;
    float *damp = 0;
    float *width = 0;
    float *mix = 0;
    
    
    //Reverb tokyoReverb;
    //Reverb::Parameters tokyoReverbParameters;
    EditReverb tokyoReverb;
    EditReverb::Parameters tokyoReverbParameters;
    
    //juce::dsp::ProcessorChain<juce::dsp::Reverb> tokyoReverb;
    
    enum
    {
        reverbIndex
    };
    
    
    // TAYLOR COMMENTS
    // NOT SURE WHAT THESE NEXT TWO DO, BUT ARE NEEDED
    UndoManager mUndoManager;
    
    Random random;
    
    // THIS IS SETTING UP THE LOWPASS FILTER, WILL NEED TO CHANGE FOR WHAT FILTER YOU DO (PROBS JUST CHANGING THE IIR PART TO WHATEVER KIND OF FILTER YOU DO)
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients<float>> lowPassFilter;
    //dsp::ProcessorChain<juce::dsp::Reverb> tokyoReverb;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TokyoRe_verbAudioProcessor)
};
