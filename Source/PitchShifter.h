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
    PitchShifter();
    ~PitchShifter();
    
    float processSample(float x);
    float kindaProcessSample(float x);
    void setFs(float Fs);
    void setPitch(float semitone);
    void actualSetPitch(float semitone);
    void validateChange(bool on);

private:
    float changeGain    = 0.f;
    float pitchBuffer   = 0.f;
    float changeGainInc = 0.f;
    float GAIN_CHANGE_SPEED = 0.05f;
    
    const float M2_PI = 2.f * M_PI;
    
    float Fs = 48000.f;
    
    PitchDelay pitchDelay1{1};
    PitchDelay pitchDelay2{2};
    PitchDelay pitchDelay3{3};

    float a1 = (1.5f*M_PI);
    float a2 = (1.5f*M_PI) + (M2_PI/3.f);
    float a3 = (1.5f*M_PI) + (2.f*M2_PI/3.f);
    
    float angleChange;
    float freq;
    
    const float MAX_DELAY_SEC = .1f;
    float MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
    
    float semitone = 0.f;
    float tr = 1.f; // momentary trasposition
    float delta = 0.f; // rate of change for delay (samples)
    
    void  calcDelta();
    void  calcAngleChange();
    float calcGain(float& angle);
    void  validateAngleBounds(float& angle);
};



#endif /* PitchShifter_h */
