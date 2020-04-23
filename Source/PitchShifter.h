//
//  PitchShifter.hpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#ifndef PitchShifter_h
#define PitchShifter_h

#include <cmath>
#include "PitchDelay.h"

using namespace std;

class PitchShifter {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    PitchShifter();
    
    // Destructor
    ~PitchShifter();
    
    float processSample(float x,int channel);

    void setFs(float Fs);
    
    void setPitch(float semitone);

    
private:
    
    float Fs = 48000.f;
    
    PitchDelay pitchDelay1{1};
    PitchDelay pitchDelay2{2};
    PitchDelay pitchDelay3{3};

    float a1[2] = {1.5f*M_PI,1.5f*M_PI};
    float a2[2] = {(1.5f*M_PI) + 2.f*M_PI/3.f ,
                    (1.5f*M_PI) + 2.f*M_PI/3.f};
    float a3[2] = {(1.5f*M_PI) + 4.f*M_PI/3.f ,
                     (1.5f*M_PI) + 4.f*M_PI/3.f};
    float angleChange;
    float freq;
    
    const float MAX_DELAY_SEC = .03f;
    float MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
    
    float semitone = 0.f;
    float tr = 1.f; // momentary trasposition
    float delta = 0.f; // rate of change for delay (samples)
    
};



#endif /* PitchShifter_h */
