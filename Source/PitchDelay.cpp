//
//  PitchDelay.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "PitchDelay.h"


PitchDelay::PitchDelay(int phaseChoice){
    this->phaseChoice = phaseChoice;
    calcDelay();
}

// Destructor
PitchDelay::~PitchDelay(){
}


float PitchDelay::processSample(float x, float& angle){
    addToBuffer(x);
    incDelay(angle);
    return calcFractionalDelay();
}

void PitchDelay::setFs(float Fs){
    this->Fs = Fs;
    MAX_DELAY_SAMPLES = MAX_DELAY_SEC * Fs;
    calcDelay();
}

void PitchDelay::setPitch(float semitone){
    this->semitone = semitone;
    tr = powf(2.f,semitone/12.f);
    delta = 1.f - tr;
}

void PitchDelay::addToBuffer(float& sample) {
    delayBuffer[index] = sample;

    // Increment buffer
    if (index < MAX_BUFFER_SIZE - 1) { index++; }
    else { index = 0; }
}

void PitchDelay::calcDelay() {
    switch(phaseChoice) {
        case 1: delay = 2.f;                                break;
        case 2: delay = (float)MAX_DELAY_SAMPLES/3.0f;      break;
        case 3: delay = 2.f*(float)MAX_DELAY_SAMPLES/3.0f;  break;
    }
}

void PitchDelay::incDelay(float& angle) {
    delay += delta;
    if (delta <= 0.f && delay < 2.f){
        delay = MAX_DELAY_SAMPLES;
        angle = 1.5f*M_PI;
    }
    if (delta > 0.f && delay > MAX_DELAY_SAMPLES){
        delay = 2.0f;
        angle = 1.5f*M_PI;
    }
}

float PitchDelay::calcFractionalDelay() {
    int d1 = floor(delay);
    int d2 = d1 + 1;
    
    float g2 = delay - (float)d1;
    float g1 = 1.0f  - g2;
    
    int indexD1 = index - d1;
    if (indexD1 < 0){ indexD1 += MAX_BUFFER_SIZE; }
    
    int indexD2 = index - d2;
    if (indexD2 < 0){ indexD2 += MAX_BUFFER_SIZE; }
    
    return g1 * delayBuffer[indexD1] + g2 * delayBuffer[indexD2];
}
