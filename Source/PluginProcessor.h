/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PitchShifter.h"
#include "MidiScheduler.h"
#include "PitchYIN.h"
#include <float.h>
#include <complex>
#include <vector>
#include "Note.h"

//==============================================================================

class HarmonizerAudioProcessor  : public AudioProcessor//,
                                  //public Timer
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
    
    void processMidi(MidiBuffer& midiMessages);
    void processAudio(AudioBuffer<float>& buffer);

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
//    void pushNextSampleIntoFFT (float sample) noexcept;
//    void pushNextSampleIntoYin(float sample);
//    void findPitch();
    
//    float tuneSample(float sample);
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
    
//    void timerCallback() override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float dryWetValue = 0.5f;
    float attackValue = 1.0f;
    
    std::vector<Note*> notes;
    
//    bool wantTuned = true;
    
//    enum {
//        fftOrder = 12,
//        fftSize = 1 << fftOrder
//    };

private:
    int   Fs = 48000;
    float inputSample;
    
    MidiScheduler midiScheduler;
    PitchShifter  harmonies[5] = {PitchShifter()};
//    PitchShifter correction;
    
    float getBothChannels  (AudioBuffer<float>&, int numChannels,    int n);
    float getOneChannel    (AudioBuffer<float>&, int channel,        int n);
    void  writeBothChannels(AudioBuffer<float>&, float s1, float s2, int n);
    
//    int yinSize = 8192;
//    int yinIndex = 0;
//    AudioBuffer<float> yinBuffer{1,8192};
//    AudioBuffer<float> yinReadyBuffer{1,8192};
//    PitchYIN yin{8192};
//    bool nextYINBlockReady = false;
//    float fundamental = 0;
    
//    dsp::FFT fft;
//    float fftInput[fftSize];
//    float fftData[2 * fftSize];
//    int fftIndex = 0;
//    bool nextFFTBlockReady = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessor)
};
