#include <stdlib.h>
#include "audiofile.h"

int main()
{
    AudioFile file;
    file.readAudioFile("bitch.wav");
    for(int i = 0; i < file.getSize()/file.getSampleSize(); i++)
	file.set(-file.get(i, 0), i, 0);
    file.writeAudioFile("out.wav");
 }
 
