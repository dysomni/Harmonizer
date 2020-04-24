/*
  ==============================================================================

    KeyInfo.h
    Created: 24 Apr 2020 4:10:39am
    Author:  James Brock

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

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
