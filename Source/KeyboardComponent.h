/*
  ==============================================================================

    KeyboardComponent.h
    Created: 24 Apr 2020 4:10:55am
    Author:  James Brock

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <vector>

class KeyboardComponent : public Component
{
public:
    KeyboardComponent(HarmonizerAudioProcessor& processor, std::vector<KeyInfo*>& keys, std::vector<Note*>& notes) : processor(processor), keys(keys), notes(notes) {
        setSize(500,133);
    }
    
    void paint (Graphics& g) override { drawKeys(g); }
    
    void drawKeys(Graphics& g) {
        for (int i = 0; i < processor.notes.size(); i++) {
            int num = processor.notes[i]->num;
            if (num >= keys.size()) continue;
            
            cout << num << endl;
            keys[num]->on = processor.notes[i]->on;
            if (keys[num]->white) {
                drawKey(keys[num], g);
                if (num - 1 >= 0 && !keys[num - 1]->white)          drawKey(keys[num-1], g);
                if (num + 1 < keys.size() && !keys[num + 1]->white) drawKey(keys[num+1], g);
            }
            else drawKey(keys[num], g);
        }
        processor.notes.clear();
    }
    
    void drawKey(KeyInfo* key, Graphics& g) {
        if (key->on) g.setColour(key->onColour);
        else         g.setColour(key->offColour);
        g.fillRect(key->x, key->y, key->w, key->h);
    }
    
    HarmonizerAudioProcessor& processor;
    std::vector<KeyInfo*>& keys;
    std::vector<Note*>& notes;
};
