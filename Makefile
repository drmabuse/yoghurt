all:
	g++ -c audio.cpp -g
	g++ -c wav.cpp -g
	g++ -c audiofile.cpp -g
	g++ -c test.cpp -g
	g++ -o test test.o audiofile.o audio.o wav.o -g