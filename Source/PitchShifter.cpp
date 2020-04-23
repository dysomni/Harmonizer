//
//  PitchShifter.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "PitchShifter.h"


PitchShifter::PitchShifter(){
}

// Destructor
PitchShifter::~PitchShifter(){
}


float PitchShifter::processSample(float x, int channel){
    
    
    float x1 = pitchDelay1.processSample(x, channel,a1[channel]);
    float x2 = pitchDelay2.processSample(x, channel,a2[channel]);
    float x3 = pitchDelay3.processSample(x, channel,a3[channel]);
    
    float g1 = 0.5f * sin(a1[channel]) + 0.5f;
    float g2 = 0.5f * sin(a2[channel]) + 0.5f;
    float g3 = 0.5f * sin(a3[channel]) + 0.5f;
    
    a1[channel] += angleChange;
    if (a1[channel] > 2.f*M_PI){
        a1[channel] -= 2.f*M_PI;
    }
    else if(a1[channel] < 0.f){
        a1[channel] += 2.f*M_PI;
    }
    
    a2[channel] += angleChange;
    if (a2[channel] > 2.f*M_PI){
        a2[channel] -= 2.f*M_PI;
    }
    else if(a2[channel] < 0.f){
        a2[channel] += 2.f*M_PI;
    }
    
    a3[channel] += angleChange;
    if (a3[channel] > 2.f*M_PI){
        a3[channel] -= 2.f*M_PI;
    }
    else if(a3[channel] < 0.f){
        a3[channel] += 2.f*M_PI;
    }
    
    return (g1*x1 + g2*x2 + g3*x3) * (2.f/3.f);
}

void PitchShifter::setFs(float Fs){
    this->Fs = Fs;
    pitchDelay1.setFs(Fs);
    pitchDelay2.setFs(Fs);
    pitchDelay3.setFs(Fs);
    
    float period = (MAX_DELAY_SAMPLES-1.f) / (delta*Fs);
    freq = 1.f/period;
    angleChange = freq * (2.f*M_PI) / Fs;
}


void PitchShifter::setPitch(float semitone){
    this->semitone = semitone;
    tr = powf(2.f,semitone/12.f);
    delta = 1.f - tr;
    
    float period = (MAX_DELAY_SAMPLES-1.f) / (delta*Fs);
    freq = 1.f/period;
    
    angleChange = freq * (2.f*M_PI) / Fs;
    
    pitchDelay1.setPitch(semitone);
    pitchDelay2.setPitch(semitone);
    pitchDelay3.setPitch(semitone);
}
