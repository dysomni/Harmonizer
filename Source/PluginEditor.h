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
using namespace std;

//==============================================================================
/**
*/

class KeyInfo {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    bool on = false;
    Colour onColour = Colours::aqua;
    Colour offColour = Colours::white;
    bool white = true;
    KeyInfo(int X, int Y, int W, int H, bool On, Colour OnColour, Colour OffColour, bool White) {
        x = X; y = Y; w = W; h = H; on = On; onColour = OnColour; offColour = OffColour; white = White;
    };
};

class KeyboardComponent : public Component
{
public:
    void paint (Graphics& g) override {
        drawKeys(g);
    }
    
    void drawKeys(Graphics& g) {
        for (int i = 0; i < processor.notes.size(); i++) {
            int num = processor.notes[i]->num;
            keys[num]->on = processor.notes[i]->on;
            if (keys[num]->white) {
                drawKey(keys[num], g);
                if (num - 1 >= 0 && !keys[num - 1]->white) drawKey(keys[num-1], g);
                if (num + 1 < keys.size() && !keys[num + 1]->white) drawKey(keys[num+1], g);
            } else {
                drawKey(keys[num], g);
            }
        }
        cout << processor.notes.size() << endl;
        processor.notes.clear();
    }
    
    void drawKey(KeyInfo* key, Graphics& g) {
        if (key->on) {
            g.setColour(key->onColour);
        } else {
            g.setColour(key->offColour);
        }
        g.fillRect(key->x, key->y, key->w, key->h);
    }
    
    HarmonizerAudioProcessor& processor;
    std::vector<KeyInfo*>& keys;
    std::vector<Note*>& notes;
    
    KeyboardComponent(HarmonizerAudioProcessor& processor, std::vector<KeyInfo*>& keys, std::vector<Note*>& notes) : processor(processor), keys(keys), notes(notes) {
//        setOpaque(true);
        setSize(500,400);
    }
};

class HarmonizerAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Timer
{
public:
    HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor&);
    ~HarmonizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void changeMidiDisplay(String input);
    
    void sliderValueChanged(Slider* slider) override;
    
    void drawKeys(Graphics& g);
    void drawKey(KeyInfo* key, Graphics& g);
    
    void timerCallback() override;
    
//    void audioProcessorChanged(AudioProcessor * processor) override;
    
//    Listener midiListener;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HarmonizerAudioProcessor& processor;
    
    Label currentMidiLabel;
    Slider dryWetSlider;
    Slider attackSlider;

    std::vector<KeyInfo*> keys;
    
    KeyboardComponent keyboardComponent{processor, keys, processor.notes};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessorEditor)
};
