#include <iostream>
#include <fstream>
#include <string.h>
#include "audio.h"
#include "wav.h"

Audio::Audio(const char *_data, int _size, int _sampleRate, int _numberOfChannels , int _sampleSize)
{
    if(_size)
    {
	data = new char[size];
	memcpy(data, _data, _size);
    }
    size = _size;
    sampleRate = _sampleRate;
    numberOfChannels = _numberOfChannels;
    sampleSize = _sampleSize;
}

Audio::Audio()
{
    size = 0;
    sampleRate = 0;
    numberOfChannels = 0;
    sampleSize = 0;
    data = NULL;
}

Audio::~Audio()
{
    if(size)
	delete [] data;
}

int Audio::get(int n, int channel)
{
    int offset = sampleSize * (n * numberOfChannels + channel);
    int d = 0;
    for(int i = 0; i < sampleSize; i++)
	d |= (data[offset+i] & 0xFF) << i*8;
    return d;
}

void Audio::set(int value, int n, int channel)
{
    int offset = sampleSize * (n * numberOfChannels + channel);
    for(int i = 0; i < sampleSize; i++)
	data[offset+i] = (value >> i*8) & 0xFF;
}

void Audio::setSize(int _size)
{
    size = _size;
}

void Audio::setSampleRate(int _sampleRate)
{
    sampleRate = _sampleRate;
}

void Audio::setNumberOfChannels(int _numberOfChannels)
{
    numberOfChannels = _numberOfChannels;
}

void Audio::setSampleSize(int _sampleSize)
{
    sampleSize = _sampleSize;
}

void Audio::setData(char *_data, int _size)
{
    if(size)
	delete[]data;
    data = new char[size];
    memcpy(data, _data, size);
}

int Audio::getSize()
{
    return size;
}


int Audio::getSampleSize()
{
    return sampleSize;
}

int Audio::getNumberOfChannels()
{
    return numberOfChannels;
}

int Audio::getSampleRate()
{
    return sampleRate;
}

char* Audio::getData()
{
    return data;
}















