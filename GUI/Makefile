
all:
	g++ -c -o screen.o screen.cpp `pkg-config gtkmm-3.0 --cflags --libs`
	g++ -c -o window.o window.cpp `pkg-config gtkmm-3.0 --cflags --libs`
	g++ -c -o main.o GUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`
	g++ -o sound_shayt screen.o window.o main.o `pkg-config gtkmm-3.0 --cflags --libs`
