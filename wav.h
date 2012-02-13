#pragma once

#include <fstream>

struct fmt_chunk
{
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


class WAVfile
{
protected:
    int riff_size ;
    struct fmt_chunk fmt;
    struct data_chunk data;
    int read_data(std::ifstream &, int);
    void write_data(std::ofstream &, int, int);
    void read_fmt_chunk(std::ifstream &);
    void read_data_chunk(std::ifstream &);

public:
    WAVfile(const char *);
    ~WAVfile();
    int operator[](unsigned int);
    void write(const char *);
    
};
