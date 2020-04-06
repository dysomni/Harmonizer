//
//  PitchDelay.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "PitchDelay.h"


PitchDelay::PitchDelay(){
}

// Destructor
PitchDelay::~PitchDelay(){
}


float PitchDelay::processSample(float x) {
    shiftPitch();
        
    delay += delta;
    if (delta <= 0.f && delay < 2.f){
        delay = MAX_DELAY_SAMPLES;
    }
    if (delta >= 0.f && delay > MAX_DELAY_SAMPLES){
        delay = 2.0f;
    }
    
    // Delay Buffer
    // "delay" can be fraction
    int d1 = floor(delay);
    int d2 = d1 + 1;
    float g2 = delay - (float)d1;
    float g1 = 1.0f - g2;
    
    int indexD1 = index - d1;
    if (indexD1 < 0){
        indexD1 += MAX_BUFFER_SIZE;
    }
    
    int indexD2 = index - d2;
    if (indexD2 < 0){
        indexD2 += MAX_BUFFER_SIZE;
    }
    
    float y = g1 * delayBuffer[indexD1] + g2 * delayBuffer[indexD2];
    
    delayBuffer[index] = x;
    
    if (index < MAX_BUFFER_SIZE - 1){
        index++;
    }
    else{
        index = 0;
    }
    
    return y;
}

void PitchDelay::setFs(float Fs){
    this->Fs = Fs;
    this->MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
}

void PitchDelay::shiftPitch() {
    semitone = (goalTone - semitone) * shift + semitone;
    tr = powf(2.f,semitone/12.f);
    delta = 1.f - tr;
}

void PitchDelay::setPitch(float goal){
    this->goalTone = goal;
}

void PitchDelay::setShift(float shift) {
    this->shift = shift;
}
