#include "audiofile.h"

AudioFile::AudioFile()
{
    size = 0;
    sampleRate = 0;
    numberOfChannels = 0;
    sampleSize = 0;
    data = NULL;
}

void AudioFile::readAudioFile(const char *fn)
{
    struct fmt_chunk _fmt;
    struct data_chunk _data;
    try
    {
	readWAVFile(fn, _fmt, _data);    
	size = _data.size;
	data = new char[_data.size];
	memcpy(data, _data.data, _data.size);
	sampleRate = _fmt.sample_rate;
	sampleSize = _fmt.significant_bits_ps / 8;
	numberOfChannels = _fmt.number_of_channels;
	if(_data.size)
	    delete [] _data.data;
	if(_fmt.extra_fmt_bytes_size)
	    delete [] _fmt.extra_fmt_bytes;
    }
    catch(const char *e)
    {
	std::cout << e << std::endl;
    }
}

void AudioFile::writeAudioFile(const char *fn)
{
    struct fmt_chunk _fmt;
    struct data_chunk _data;
    _fmt.size = 16;             
    _fmt.compression = 1;     //raw PCM
    _fmt.number_of_channels = numberOfChannels;
    _fmt.sample_rate = sampleRate;
    _fmt.block_align = sampleSize * numberOfChannels;
    _fmt.av_bytes_ps = _fmt.sample_rate * _fmt.block_align;
    _fmt.significant_bits_ps = sampleSize / 8;
    _fmt.extra_fmt_bytes_size = 0;
    _data.size = size;
    _data.data = data;
    writeWAVFile(fn, _fmt, _data);
}
