/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <algorithm>
using namespace std;

//==============================================================================
HarmonizerAudioProcessor::HarmonizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
//,
//    fft(fftOrder)
#endif
{
//    yin.setSampleRate(Fs);
//    startTimerHz(30);
}

HarmonizerAudioProcessor::~HarmonizerAudioProcessor()
{
}

//==============================================================================
const String HarmonizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HarmonizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HarmonizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HarmonizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HarmonizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HarmonizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HarmonizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HarmonizerAudioProcessor::setCurrentProgram (int index)
{
}

const String HarmonizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void HarmonizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HarmonizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Fs = sampleRate;
//    correction.setFs(sampleRate);
//    twoOctaves.setFs(sampleRate);
//    twoOctaves.setPitch(24.f);
//    yin.setSampleRate((unsigned int) sampleRate);
//    correction.setShift(0.25f);
    for(int i = 0; i < 5; i++) {
        harmonies[i].setFs(sampleRate);
        harmonies[i].setPitch(0.f);
    }
}

void HarmonizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HarmonizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HarmonizerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    processMidi(midiMessages);
    processAudio(buffer);

}

void HarmonizerAudioProcessor::processMidi(MidiBuffer& midiMessages) {
    MidiMessage midiMessage; int midiSample;
    
    MidiBuffer::Iterator midiIterator = MidiBuffer::Iterator(midiMessages);
    while(midiIterator.getNextEvent(midiMessage, midiSample)) {
        if      (midiMessage.isNoteOn())  {
            midiScheduler.noteOn(midiMessage.getNoteNumber());
            Note* note = new Note(true, midiMessage.getNoteNumber());
            notes.push_back(note);
        }
        else if (midiMessage.isNoteOff()) {
            midiScheduler.noteOff(midiMessage.getNoteNumber());
            Note* note = new Note(false, midiMessage.getNoteNumber());
            notes.push_back(note);
        }
    }
}

void HarmonizerAudioProcessor::processAudio(AudioBuffer<float>& buffer) {
    
    
    float inputSample; //float tunedSample;
    for (int sampleNumber = 0; sampleNumber < buffer.getNumSamples(); sampleNumber++) {
        inputSample = getBothChannels(buffer, buffer.getNumChannels(), sampleNumber);
//        pushNextSampleIntoFFT(inputSample);
//        pushNextSampleIntoYin(inputSample);
//        tunedSample = tuneSample(inputSample);
        
//        if (wantTuned) {
//            inputSample = ((1.f - dryWetValue) * tunedSample) + (dryWetValue * createHarmonies(tunedSample));
//        }
//        else {
//            inputSample = ((1.f - dryWetValue) * inputSample) + (dryWetValue * createHarmonies(tunedSample));
//        }
        inputSample = ((1.f - dryWetValue) * inputSample) + (dryWetValue * createHarmonies(inputSample));
        writeBothChannels(buffer, inputSample, inputSample, sampleNumber);
    }
}

float HarmonizerAudioProcessor::getOneChannel(AudioBuffer<float>& buffer, int channel, int n) {
    return buffer.getReadPointer(channel)[n];
}

float HarmonizerAudioProcessor::getBothChannels(AudioBuffer<float>& buffer, int numChannels, int n) {
    float sum = 0.f;
    for (int i = 0; i < numChannels; i++) {
        sum = sum + getOneChannel(buffer, i, n);
    }
    return sum / numChannels;
}

void HarmonizerAudioProcessor::writeBothChannels(AudioBuffer<float>& buffer, float s1, float s2, int n) {
    buffer.getWritePointer(0)[n] = s1;
    buffer.getWritePointer(1)[n] = s2;
}

//float HarmonizerAudioProcessor::tuneSample(float sample) {
//    return correction.processSample(sample);
//}

float HarmonizerAudioProcessor::createHarmonies(float sample) {
    // will be based on midi notes passed in
    float output = 0.f;
    int count = 0;
    for(int i = 0; i < 5; i++) {
        harmonies[i].setPitch(midiScheduler.getHarmonyInfo(i)[0]);
        if(midiScheduler.getHarmonyInfo(i)[1] == 0) {
            count++;
            output += harmonies[i].processSample(sample);
        }
    }
    
    return output;// / (float)count;
}

//==============================================================================
bool HarmonizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HarmonizerAudioProcessor::createEditor()
{
    return new HarmonizerAudioProcessorEditor (*this);
}

//==============================================================================
void HarmonizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HarmonizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HarmonizerAudioProcessor();
}

//void HarmonizerAudioProcessor::pushNextSampleIntoYin(float sample) {
//    if (yinIndex == yinSize) {
//        if (!nextYINBlockReady) {
////            cout << "The block is ready" << endl;
//            yinReadyBuffer.makeCopyOf(yinBuffer);
//            nextYINBlockReady = true;
//        }
//
//        yinIndex = 0;
//    }
//    yinBuffer.getWritePointer(0)[yinIndex++] = sample; //twoOctaves.processSample(sample);
//}

//void HarmonizerAudioProcessor::pushNextSampleIntoFFT (float sample) noexcept
//{
//    // if the fifo contains enough data, set a flag to say
//    // that the next frame should now be rendered..
//    if (fftIndex == fftSize)
//    {
//        if (!nextFFTBlockReady)
//        {
//            zeromem (fftData, sizeof (fftData));
//            memcpy (fftData, fftInput, sizeof (fftInput));
//            nextFFTBlockReady = true;
//        }
//
//        fftIndex = 0;
//    }
//
//    fftInput[fftIndex++] = sample;
//}

//void HarmonizerAudioProcessor::timerCallback() {
//    if (nextYINBlockReady) {
//        findPitch();
//        nextYINBlockReady = false;
//    }
////    if (nextFFTBlockReady)
////    {
//////        cout << "About to perform FFT" << endl;
////        findPitch();
////        nextFFTBlockReady = false;
////    }
//}

//void HarmonizerAudioProcessor::findPitch() {
//    float frequency = yin.getPitchInHz(yinReadyBuffer.getReadPointer(0));
//    fundamental = frequency;
////    fft.performFrequencyOnlyForwardTransform(fftData);
//////    float pitch = 0.f;
////    int maxInx = distance(fftData, max_element(fftData, fftData + fftSize));
////    float frequency = ((maxInx * Fs)/fftSize);
////    cout << frequency << endl;
//    float pitch;
//    if(frequency < 50.f || frequency > 1500.f) {
//        pitch = 0.f;
//    } else {
//        cout << frequency << endl;
//        pitch = 12 * log2(130.81f/frequency);
//    }
//
//    //get the dominant pitch
//
//    //find nearest semitone and find the pitch difference
//
//    correction.setPitch(pitch);
//}
