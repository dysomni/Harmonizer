/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HarmonizerAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener
{
public:
    HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor&);
    ~HarmonizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void changeMidiDisplay(String input);
    
    void sliderValueChanged(Slider* slider) override;
    
//    Listener midiListener;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HarmonizerAudioProcessor& processor;
    
    Label currentMidiLabel;
    Slider dryWetSlider;
    Slider attackSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessorEditor)
};
