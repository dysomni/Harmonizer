//
//  PitchDelay.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "PitchDelay.h"


PitchDelay::PitchDelay(int phaseChoice){
    this->phaseChoice = phaseChoice;
    if (phaseChoice == 1){
        delay[0] = 2.f; delay[1] = 2.f;
    }
    if (phaseChoice == 2){
        delay[0] = (float)MAX_DELAY_SAMPLES/3.0f;
        delay[1] = (float)MAX_DELAY_SAMPLES/3.0f;
    }
    if (phaseChoice == 3){
        delay[0] = 2.f*(float)MAX_DELAY_SAMPLES/3.0f;
        delay[1] = 2.f*(float)MAX_DELAY_SAMPLES/3.0f;
    }
}

// Destructor
PitchDelay::~PitchDelay(){
}


float PitchDelay::processSample(float x, int channel, float & angle){
    
//    if (delay[channel] < 1.f){
//        return x;
//    }
//    else{
        
        delay[channel] += delta;
        if (delta <= 0.f && delay[channel] < 2.f){
            delay[channel] = MAX_DELAY_SAMPLES;
            angle = 1.5f*M_PI;
        }
        if (delta > 0.f && delay[channel] > MAX_DELAY_SAMPLES){
            delay[channel] = 2.0f;
            angle = 1.5f*M_PI;
        }
        
        // Delay Buffer
        // "delay" can be fraction
        int d1 = floor(delay[channel]);
        int d2 = d1 + 1;
        float g2 = delay[channel] - (float)d1;
        float g1 = 1.0f - g2;
        
        int indexD1 = index[channel] - d1;
        if (indexD1 < 0){
            indexD1 += MAX_BUFFER_SIZE;
        }
        
        int indexD2 = index[channel] - d2;
        if (indexD2 < 0){
            indexD2 += MAX_BUFFER_SIZE;
        }
        
        float y = g1 * delayBuffer[indexD1][channel] + g2 * delayBuffer[indexD2][channel];
        
        delayBuffer[index[channel]][channel] = x;
        
        if (index[channel] < MAX_BUFFER_SIZE - 1){
            index[channel]++;
        }
        else{
            index[channel] = 0;
        }
        
        return y;
    //}
}

void PitchDelay::setFs(float Fs){
    this->Fs = Fs;
    this->MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
    
    if (phaseChoice == 1){
        delay[0] = 2.f; delay[1] = 2.f;
    }
    if (phaseChoice == 2){
        delay[0] = (float)MAX_DELAY_SAMPLES/3.0f;
        delay[1] = (float)MAX_DELAY_SAMPLES/3.0f;
    }
    if (phaseChoice == 3){
        delay[0] = 2.f*(float)MAX_DELAY_SAMPLES/3.0f;
        delay[1] = 2.f*(float)MAX_DELAY_SAMPLES/3.0f;
    }
}


void PitchDelay::setPitch(float semitone){
    this->semitone = semitone;
    tr = powf(2.f,semitone/12.f);
    delta = 1.f - tr;
}
