/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "KeyInfo.h"
#include "KeyboardComponent.h"
using namespace std;

//==============================================================================

class HarmonizerAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer
{
public:
    HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor&);
    ~HarmonizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HarmonizerAudioProcessor& processor;
    Slider wetnessSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    
    std::vector<KeyInfo*> keys;
    KeyboardComponent keyboardComponent{processor, keys, processor.notes};
    
    void createVectorOfKeys();
    void drawAllKeys(Graphics& g);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessorEditor)
};
