#include <fstream>
#include <iostream>
#include <string.h>
#include "wav.h"
#include "audio.h"

void readAudioFile(const char *fn, Audio &audio)
{
    struct fmt_chunk fmt;
    struct data_chunk data;
    try
    {
	readWAVFile(fn, fmt, data);    
	audio.setSize(data.size);
	audio.setData(data.data, data.size);
	audio.setSampleRate(fmt.sample_rate);
	audio.setSampleSize(fmt.significant_bits_ps / 8);
	audio.setNumberOfChannels(fmt.number_of_channels);
	if(data.size)
	    delete [] data.data;
	if(fmt.extra_fmt_bytes_size)
	    delete [] fmt.extra_fmt_bytes;
    }
    catch(const char *e)
    {
	std::cout << e << std::endl;
    }
}

void writeAudioFile(const char *fn, Audio &audio)
{
    struct fmt_chunk fmt;
    struct data_chunk data;
    fmt.size = 16;             
    fmt.compression = 1;     //raw PCM
    fmt.number_of_channels = audio.getNumberOfChannels();
    fmt.sample_rate = audio.getSampleRate();
    fmt.block_align = audio.getSampleSize() * audio.getNumberOfChannels();
    fmt.av_bytes_ps = fmt.sample_rate * fmt.block_align;
    fmt.significant_bits_ps = audio.getSampleSize() / 8;
    fmt.extra_fmt_bytes_size = 0;
    data.size = audio.getSize();
    data.data = audio.getData();
    writeWAVFile(fn, fmt, data);
}
