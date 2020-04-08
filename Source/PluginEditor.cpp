/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarmonizerAudioProcessorEditor::HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    currentMidiLabel.setBounds(50,225,100,100);
    currentMidiLabel.setText("No MIDI yet...", NotificationType::dontSendNotification);
    addAndMakeVisible(currentMidiLabel);
    
    dryWetSlider.addListener(this);
    dryWetSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetSlider.setBounds(200,55,125,125);
    dryWetSlider.setRange(0.0f,1.0f);
    dryWetSlider.setValue(processor.dryWetValue);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxRight, false, 70, 30);
    addAndMakeVisible(dryWetSlider);
    
    attackSlider.addListener(this);
    attackSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setBounds(200,155,125,125);
    attackSlider.setRange(0.0f,1000.0f);
    attackSlider.setValue(processor.attackValue);
    attackSlider.setTextBoxStyle(Slider::TextBoxRight, false, 70, 30);
    addAndMakeVisible(attackSlider);
    
//    processor.addListener(this);
}

HarmonizerAudioProcessorEditor::~HarmonizerAudioProcessorEditor()
{
}

//==============================================================================
void HarmonizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (50.0f);
    g.drawFittedText("HARMONIZER", 50, 20, 200, 60, Justification::centred, 1);
    g.setFont (20.0f);
    g.drawFittedText("Dry/Wet", 100, 100, 60, 30, Justification::left, 1);
    g.drawFittedText("Attack", 110, 200, 60, 30, Justification::left, 1);
}

void HarmonizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void HarmonizerAudioProcessorEditor::changeMidiDisplay(String input) {
    currentMidiLabel.setText(input, NotificationType::dontSendNotification);
}

void HarmonizerAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    
    if(slider == &dryWetSlider) {
        processor.dryWetValue = dryWetSlider.getValue();
    }
    
    if(slider == &attackSlider) {
        processor.attackValue = attackSlider.getValue();
    }
    
}

//void HarmonizerAudioProcessorEditor::audioProcessorChanged(AudioProcessor * processor) {
//
//}
