TARGET = test
OBJS   = test.o audio.o audiofile.o wav.o
CFLAGS = -g
CC     = g++

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)	

test.o:
	$(CC)  $(CFLAGS) -c test.cpp 

audio.o:
	$(CC)  $(CFLAGS) -c audio.cpp

audiofile.o:
	$(CC) $(CFLAGS) -c audiofile.cpp

wav.o:
	$(CC) $(CFLAGS) -c wav.cpp

clean:
	touch $(OBJS)
	rm $(OBJS)
	touch $(TARGET)
	rm $(TARGET)
