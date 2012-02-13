#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "wav.h"


/* 
 * Reads /n/ bytes from /in/ and compiles an integer from them
 * e.g. FF 03 AC becomes 0xAC03FF
 */
int WAVfile::read_data(std::ifstream& in, int n)
{
    int res = 0;
    for(int i = 0; i < n; i++)
    {
	char ch;
	in.get(ch);
	res |= (int)((ch & 0xFF) << i*8);
    }
    return res;
}

/*
 * Writes /value/ to /out/ as /n/ bytes
 * e.g. 0x03B0AF becomes AF B0 03
 */
void WAVfile::write_data(std::ofstream& out, int value, int n)
{
    for(int i = 0; i < n; i++)
    {
	char ch = (value >> i*8);
	out.put(ch);
    }
}

/* Constructor
 * reads file /file/ which stores WAV
 */    
WAVfile::WAVfile(const char *file)
{
    std::ifstream in;
    in.open(file, std::ifstream::binary);
    char* str = new char[5];
    //read RIFF header
    in.read(str, 4);
    str[4] = '\0';
    if(strcmp(str, "RIFF"))
    {
	throw("No RIFF format!");
    }
    riff_size = 0;
    riff_size = read_data(in, 4);
    in.read(str, 4);
    str[4] = '\0';
    if(strcmp(str, "WAVE"))
    {
	throw("No WAVE format!");
    }
    bool fmt_read = false, data_read = false;
    while(!(fmt_read && data_read)){
	if(!data_read || !fmt_read) //read chunk header
	{
	    in.read(str, 4);
	    str[4] = '\0';	
	}
	if(!strcmp(str, "fmt ")) //read "fmt " chunk
	{
	    read_fmt_chunk(in);
	    fmt_read = true;
	}
	else if(!strcmp(str, "data")) //read "data" chunk
	{
	    read_data_chunk(in);
	    data_read = true;
	}
	else
	{
	    //no support for other chunks yet
	}
    }
    in.close();
}


/* Destructor */
WAVfile::~WAVfile()
{
    if(data.size)
	delete[] data.data;
    if(fmt.extra_fmt_bytes_size)
	delete[] fmt.extra_fmt_bytes;
}
    
/*
 * writes down WAV to /file/
 */
void WAVfile::write(const char *file)
{
    std::ofstream out(file, std::ofstream::binary);
    //write RIFF header
    out.write("RIFF", 4);
    write_data(out, riff_size, 4);
    out.write("WAVE", 4);
    //write "fmt " chunk
    out.write("fmt ", 4);
    write_data(out, fmt.size, 4);
    write_data(out, fmt.compression, 2);
    write_data(out, fmt.number_of_channels, 2);
    write_data(out, fmt.sample_rate, 4);
    write_data(out, fmt.av_bytes_ps, 4);
    write_data(out, fmt.block_align, 2);
    write_data(out, fmt.significant_bits_ps, 2);
    if(fmt.size > 16) // there exist extra fmt bytes
    {
	write_data(out, fmt.extra_fmt_bytes_size, 2);
	out.write(fmt.extra_fmt_bytes, fmt.extra_fmt_bytes_size);
    }
    //write "data" chunk
    out.write("data",4);
    write_data(out, data.size, 4);
    out.write(data.data, data.size);
    out.close();
}


/* Function
 * reads "fmt " chunk from /in/ to fmt
 * checking that there actually IS "fmt " chunk to read should be done outside
 */
void WAVfile::read_fmt_chunk(std::ifstream &in)
{
    fmt.size = 0;
    fmt.compression = 0;
    fmt.number_of_channels = 0;
    fmt.sample_rate  = 0;
    fmt.av_bytes_ps  = 0;
    fmt.block_align  = 0;
    fmt.significant_bits_ps = 0;
    fmt.extra_fmt_bytes_size = 0;
    fmt.size = read_data(in, 4);
    fmt.compression = read_data(in, 2);
    if(fmt.compression!=1)
    {
	throw("No compressed support!");
    }
    fmt.number_of_channels = read_data(in, 2);
    fmt.sample_rate = read_data(in, 4);
    fmt.av_bytes_ps = read_data(in, 4);
    fmt.block_align = read_data(in, 2);
    fmt.significant_bits_ps = read_data(in, 2);
    if(fmt.size > 16) // there exist extra fmt bytes 
    {
	fmt.extra_fmt_bytes_size = read_data(in, 2);
	fmt.extra_fmt_bytes = new char[fmt.extra_fmt_bytes_size];
	in.read(fmt.extra_fmt_bytes, fmt.extra_fmt_bytes_size);
    }
}


/*
 * reads "data" chunk from /in/ to /data/
 * checking that there actually IS "data" chunk to read should be done outside
 */
void WAVfile::read_data_chunk(std::ifstream &in)
{
    data.size = read_data(in, 4);
    data.data = new char[data.size];
    in.read(data.data, data.size);
    /* 
       What the fuck this shit is of no need why have i put it here?
       for(int i = 0; i < data.size; i+= fmt.significant_bits_ps/8)
       {
       int d = 0;
       for(int j = 0; j < fmt.significant_bits_ps/8; j++)
       {
       d |= (int) ((data.data[i+j] & 0xFF) << j*8);
       }
       for(int j = 0; j < fmt.significant_bits_ps/8; j++)
       data.data[i+j] = ((d >> 8*j) & 0xFF);
       }
    */
}

/* Operator []
 * provides access to /n/th sample of data
 * note that it does NOT return data.data[n] (unless samples are 8bit)
 */
int WAVfile::operator[] (unsigned int n)
{
    if(n > data.size)
	throw("no shit man");
    int d = 0;
    int offset = n * fmt.significant_bits_ps/8;
    for(int i = 0; i < fmt.significant_bits_ps/8; i++)
	d |= ((int)data.data[offset+i] & 0xFF) << i*8;
    return d;
}
