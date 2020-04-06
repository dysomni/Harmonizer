/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PitchDelay.h"

//==============================================================================
/**
*/
class HarmonizerAudioProcessor  : public AudioProcessor,
                                  public Timer
{
public:
    //==============================================================================
    HarmonizerAudioProcessor();
    ~HarmonizerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    float getBothChannels(AudioBuffer<float>&, int numChannels, int n);
    float getOneChannel(AudioBuffer<float>&, int channel, int n);
    void writeBothChannels(AudioBuffer<float>&, float s1, float s2, int n);
    
    void pushNextSampleIntoFFT (float sample) noexcept;
    void findPitch();
    
    float tuneSample(float sample);
    float createHarmonies(float sample);

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
    
    void timerCallback() override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float dryWetValue = 0.5f;
    float attackValue = 1.0f;
    
    enum {
        fftOrder = 12,
        fftSize = 1 << fftOrder
    };
    
//    ChangeBroadcaster midiBroadcaster;

private:
    
    PitchDelay correction;
    PitchDelay forFFT;
    PitchDelay harmony1;
    dsp::FFT fft;
    float fftInput[fftSize];
    float fftData[2 * fftSize];
    int fftIndex = 0;
    bool nextFFTBlockReady = false;
    int Fs = 48000;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessor)
    
    float inputSample;
};
