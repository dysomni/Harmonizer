/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

bool keyCompare(KeyInfo* one, KeyInfo* two) { return one->x < two->x; }

//==============================================================================
HarmonizerAudioProcessorEditor::HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 275);
    
    dryWetSlider.addListener(this);
    dryWetSlider.setSliderStyle(Slider::LinearHorizontal);
    dryWetSlider.setBounds(100,200,300,30);
    dryWetSlider.setRange(0.0f,1.0f);
    dryWetSlider.setValue(processor.dryWetValue);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 40);
    addAndMakeVisible(dryWetSlider);
    
    createVectorOfKeys();
    startTimerHz(10);
    
    addAndMakeVisible(keyboardComponent);
}

HarmonizerAudioProcessorEditor::~HarmonizerAudioProcessorEditor(){}

void HarmonizerAudioProcessorEditor::createVectorOfKeys() {
    for (int i = 0; i < 29; i++) { // white keys
        KeyInfo* key = new KeyInfo((14*i) + 45, 105, 12, 28, false, Colours::aqua, Colours::white, true);
        keys.push_back(key);
    }
    for (int i = 0; i < 28; i++) { // black keys
        int mod = i % 7;
        if ( mod == 2 || mod == 6 ) continue;
        KeyInfo* key = new KeyInfo((14*i) + 53, 102, 11, 19, false, Colours::aqua, Colours::black, false);
        keys.push_back(key);
    }
    sort(keys.begin(), keys.end(), keyCompare); // sort them in order of appearence
}

void HarmonizerAudioProcessorEditor::paint (Graphics& g){
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    Image logo = ImageCache::getFromMemory(BinaryData::harmonizerlogo_png, BinaryData::harmonizerlogo_pngSize);
    g.drawImageAt(logo, 50, 50);

    drawAllKeys(g);
    
    g.setColour(Colours::white);
    g.setFont (20.0f);
    g.drawFittedText("~ wetness ~", 100, 165, 300, 30, Justification::centred, 1);
}

void HarmonizerAudioProcessorEditor::drawAllKeys(Graphics& g) {
    for (int i = 0; i < keys.size(); i++) { // draw white keys first
        if (keys[i]->white) {
            if (keys[i]->on) g.setColour(keys[i]->onColour);
            else g.setColour(keys[i]->offColour);
            g.fillRect(keys[i]->x, keys[i]->y, keys[i]->w, keys[i]->h);
        }
    }
    for (int i = 0; i < keys.size(); i++) { // draw black keys second (black are ontop)
        if (!keys[i]->white) {
            if (keys[i]->on) g.setColour(keys[i]->onColour);
            else g.setColour(keys[i]->offColour);
            g.fillRect(keys[i]->x, keys[i]->y, keys[i]->w, keys[i]->h);
        }
    }
}

void HarmonizerAudioProcessorEditor::resized(){}

void HarmonizerAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if(slider == &dryWetSlider) processor.dryWetValue = dryWetSlider.getValue();
}

void HarmonizerAudioProcessorEditor::timerCallback() {
    keyboardComponent.repaint();
}
