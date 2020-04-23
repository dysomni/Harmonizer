//
//  PitchDelay.hpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#ifndef PitchDelay_h
#define PitchDelay_h

#include <cmath>
using namespace std;

class PitchDelay {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    PitchDelay(int phaseChoice);
    
    // Destructor
    ~PitchDelay();
    
    float processSample(float x, float& angle);

    void setFs(float Fs);
    
    void setPitch(float semitone);

    
private:
    
    float Fs = 48000.f;
    int phaseChoice;
    
    const float MAX_DELAY_SEC = .03f;
    float MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
    float delay;// = {5.f}; // in samples
    
    const int MAX_BUFFER_SIZE = 96000;
    float delayBuffer[96000] = {0.0f};
    int index = {0};
    
    float semitone = 0.f;
    float tr = 1.f; // momentary trasposition
    float delta = 0.f; // rate of change for delay (samples)
    
    void  calcDelay();
    void  incDelay(float& angle);
    void  addToBuffer(float& sample);
    float calcFractionalDelay();
};



#endif /* PitchDelay_h */
