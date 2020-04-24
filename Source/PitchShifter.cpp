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


float PitchShifter::processSample(float x) {
    x = x * changeGain;
    float x1 = pitchDelay1.processSample(x, a1);
    float x2 = pitchDelay2.processSample(x, a2);
    float x3 = pitchDelay3.processSample(x, a3);
    
    float g1 = calcGain(a1);
    float g2 = calcGain(a2);
    float g3 = calcGain(a3);
    
    validateAngleBounds(a1);
    validateAngleBounds(a2);
    validateAngleBounds(a3);
    
    validateChange(true);
    
    return (g1*x1 + g2*x2 + g3*x3) * (2.f/3.f) * changeGain;
}

float PitchShifter::kindaProcessSample(float x) {
    x = x * changeGain;
    
    float x1 = pitchDelay1.processSample(x, a1);
    float x2 = pitchDelay2.processSample(x, a2);
    float x3 = pitchDelay3.processSample(x, a3);
    
    float g1 = calcGain(a1);
    float g2 = calcGain(a2);
    float g3 = calcGain(a3);
    
    validateAngleBounds(a1);
    validateAngleBounds(a2);
    validateAngleBounds(a3);
    
    validateChange(false);
    
    return (g1*x1 + g2*x2 + g3*x3) * (2.f/3.f) * changeGain;
}

void PitchShifter::validateChange(bool on) {
    if (!on) {
        if (changeGain == 0.f && changeGainInc == 0.f) return;
        changeGainInc = -GAIN_CHANGE_SPEED;
        changeGain += changeGainInc;
        if(changeGain <= 0.f) {
            changeGain = 0.f;
            changeGainInc = 0.f;
        }
    } else {
        if (changeGainInc < 0) {
            changeGain += changeGainInc;
            if(changeGain <= 0.f) {
                changeGain = 0.f;
                changeGainInc = GAIN_CHANGE_SPEED;
                actualSetPitch(pitchBuffer);
            }
        } else if (changeGainInc > 0) {
            changeGain += changeGainInc;
            if(changeGain >= 1.f) {
                changeGain = 1.f;
                changeGainInc = 0.f;
            }
        } else if (changeGainInc == 0.f) {
            if (changeGain == 0.f) {
                changeGainInc = GAIN_CHANGE_SPEED;
                changeGain += changeGainInc;
            }
        }
    }
}

void PitchShifter::setFs(float Fs){
    this->Fs = Fs;
    pitchDelay1.setFs(Fs);
    pitchDelay2.setFs(Fs);
    pitchDelay3.setFs(Fs);
    
    calcAngleChange();
}

void PitchShifter::setPitch(float semitone) {
    if (this->semitone == semitone) return;
    pitchBuffer = semitone;
    changeGainInc = -GAIN_CHANGE_SPEED;
}

void PitchShifter::actualSetPitch(float semitone) {
    this->semitone = semitone;
    
    calcDelta();
    calcAngleChange();
    
    pitchDelay1.setPitch(semitone);
    pitchDelay2.setPitch(semitone);
    pitchDelay3.setPitch(semitone);
}

void PitchShifter::calcDelta() {
    tr = powf(2.f,semitone/12.f);
    delta = 1.f - tr;
}

void PitchShifter::calcAngleChange() {
    freq = 1.f/ ((MAX_DELAY_SAMPLES-1.f) / (delta*Fs));
    angleChange = freq * M2_PI / Fs;
}

float PitchShifter::calcGain(float& angle) {
    return 0.5f * sin(angle) + 0.5f;
}

void PitchShifter::validateAngleBounds(float& angle) {
    angle += angleChange;
    
    if      (angle > M2_PI) { angle -= M2_PI; }
    else if (angle < 0.f)   { angle += M2_PI; }
}
