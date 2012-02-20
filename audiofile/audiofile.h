#pragma once
#include "audio.h"


/* Reads audio from file specified by /fn/ to Audio object /audio/ */
void readAudioFile(const char *fn, Audio &audio);
/* Writes audio from /audio/ to file specified by /fn/ in WAVE format */
void writeAudioFile(const char *fn, Audio &audio);
