#pragma once


class Audio
{
protected:
    int size;                             
    int numberOfChannels;                 
    int sampleRate;                          /* number of samples per second */
    int sampleSize;                          /* number of bytes per sample   */
    char *data;
 
public:
    Audio(const char *_data, int _size, int _sampleRate, int _numberOfChannels = 1, int _sampleSize = 1);
    Audio();
    ~Audio();
    int get(int n, int channel);   
    void set(int value, int n, int channel);
    void setSize(int _size);
    void setSampleRate(int _sampleRate);
    void setNumberOfChannels(int _numberOfChannels);
    void setSampleSize(int _sampleSize);
    void setData(char *_data, int _size);
    int getSize();
    int getSampleRate();
    int getNumberOfChannels();
    int getSampleSize();
    char *getData();
};

