#include <stdlib.h>
#include "audiofile.h"

int main()
{
    Audio file;
    readAudioFile("bitch.wav", file);
    for(int i = 0; i < file.getSize()/file.getSampleSize(); i++)
	file.set(-file.get(i, 0), i, 0);
    writeAudioFile("out.wav", file);
 }
 
