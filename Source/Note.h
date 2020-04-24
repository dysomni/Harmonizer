/*
  ==============================================================================

    Note.h
    Created: 24 Apr 2020 4:10:03am
    Author:  James Brock

  ==============================================================================
*/

#pragma once

class Note {
public:
    bool on = false;
    int num = 0;
    Note(bool On, int Num) {
        on = On; num = Num;
    }
};
