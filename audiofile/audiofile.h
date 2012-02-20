#pragma once
#include <fstream>
#include <iostream>
#include <string.h>
#include "wav.h"
#include "audio.h"


class AudioFile : public Audio
{
public:
    AudioFile();
//    AudioFile(const char *fn); /* fuck it */
//    ~AudioFile();
    /* Reads audio from file specified by /fn/ to Audio object /audio/ */
    void readAudioFile(const char *fn);
/* Writes audio from /audio/ to file specified by /fn/ in WAVE format */
    void writeAudioFile(const char *fn);
};
