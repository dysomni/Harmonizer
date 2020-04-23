//
//  MidiScheduler.hpp
//  Harmonizer - VST3
//
//  Created by James Brock on 4/8/20.
//  Copyright © 2020 Dysomni. All rights reserved.
//

#ifndef MidiScheduler_hpp
#define MidiScheduler_hpp

#include <stdio.h>
#include <array>
#include <vector>
#include <chrono>
using namespace std;

class MidiScheduler {
    
public:
    
    MidiScheduler(){};
    ~MidiScheduler(){};
    
    vector<int> empty() {
        vector<int> indxs;
        for(int i = 0; i < 5; i++) {
            if(infos[i].empty) {
                indxs.push_back(i);
            }
        }
        return indxs;
    }
    
    int oldest() {
        int indx;
        auto now = std::chrono::steady_clock::now();
        int oldest = 0;
        for(int i = 0; i < 5; i++) {
            if(!infos[i].empty) {
                int amount = (int)chrono::duration_cast<chrono::nanoseconds> (now - infos[i].time).count();
                if (amount > oldest) {
                    indx = i;
                }
            }
        }
        return indx;
    }
    
    void noteOn(int note) {
        int insertIndex = 0;
        auto emptys = empty();
        if(emptys.size() == 0) {
            insertIndex = oldest();
        }
        else {
            insertIndex = emptys[0];
        }
        infos[insertIndex].time = std::chrono::steady_clock::now();
        infos[insertIndex].note = note;
        infos[insertIndex].empty = false;
    }
    
    void noteOff(int note) {
        for(int i = 0; i < 5; i++) {
            if(infos[i].note == note) {
                infos[i].empty = true;
            }
        }
    }
    
    vector<int> getHarmonyInfo(int indx) {
        vector<int> ret;
        ret.push_back(infos[indx].note);
        ret.push_back((int)infos[indx].empty);
        return ret;
    }
    
private:
    
    struct noteInfo {
        chrono::steady_clock::time_point time;
        int note = 0;
        bool empty = true;
    };
    
    struct noteInfo infos[5];
    
};

#endif /* MidiScheduler_h */
