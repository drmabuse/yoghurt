#pragma once
#include "audio.h"


struct fmt_chunk
{
    int riff_size;
    int size ;
    int compression ;
    int number_of_channels;
    int sample_rate ;
    int av_bytes_ps ;
    int block_align ;
    int significant_bits_ps ;
    int extra_fmt_bytes_size ;
    char *extra_fmt_bytes;
};

struct data_chunk
{
    int size;
    char *data;
};



int read_data(std::ifstream& in, int n);
void write_data(std::ofstream& out, int value, int n);
void readWAVFile(const char *filename, struct fmt_chunk &fmt, struct data_chunk &data);
void read_fmt_chunk(std::ifstream &in, struct fmt_chunk &fmt);
void read_data_chunk(std::ifstream &in, struct data_chunk &data);
void writeWAVFile(const char *file, struct fmt_chunk &fmt, struct data_chunk &data);
