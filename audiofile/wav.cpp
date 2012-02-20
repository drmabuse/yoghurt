#include <fstream>
#include <iostream>
#include "wav.h"
#include "audio.h"

int read_data(std::ifstream& in, int n)
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

void write_data(std::ofstream& out, int value, int n)
{
    for(int i = 0; i < n; i++)
    {
	char ch = (value >> i*8);
	out.put(ch);
    }
}

void readWAVFile(const char *filename, struct fmt_chunk &fmt, struct data_chunk &data)
{
    std::ifstream in;
    in.open(filename, std::ifstream::binary);
    int check = 0;
    //read RIFF header
    check = read_data(in, 4);
    if(check != 0x46464952) // "RIFF"
	throw("No RIFF format!");
    fmt.riff_size = 0;
    fmt.riff_size = read_data(in, 4);
    check = read_data(in, 4);
    if(check != 0x45564157) //"WAVE"
	throw("No WAVE format!");
    bool fmt_read = false, data_read = false;
    while(!(fmt_read && data_read))
    {
	if(!data_read || !fmt_read) //read chunk header
	    check = read_data(in, 4);	
	if(check == 0x20746D66) //read "fmt " chunk
	{
	    read_fmt_chunk(in,fmt);
	    fmt_read = true;
	}
	else if(check == 0x61746164) //read "data" chunk
	{
	    read_data_chunk(in, data);
	    data_read = true;
	}
	else
	{
	    //no support for other chunks yet
	}
    }
    in.close();
}

/* Function
 * reads "fmt " chunk from /in/ to fmt
 * checking that there actually IS "fmt " chunk to read should be done outside
 */
void read_fmt_chunk(std::ifstream &in, struct fmt_chunk &fmt)
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
void read_data_chunk(std::ifstream &in, struct data_chunk &data)
{
    data.size = read_data(in, 4);
    data.data = new char[data.size];
    in.read(data.data, data.size);
}


/*
 * writes down WAV to /file/
 */
void writeWAVFile(const char *file, struct fmt_chunk &fmt, struct data_chunk &data)
{
    std::ofstream out(file, std::ofstream::binary);
    //write RIFF header
    out.write("RIFF", 4);
    write_data(out, fmt.riff_size, 4);
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
