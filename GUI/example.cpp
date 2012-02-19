////
// Copyright (c) 2012 Yoghurt Inc. All rights reserved.
//
// This is the example of GUI class usage.
////

// This is needed to initialize gtkmm and then run GUI.
#include <gtkmm/main.h>

// Provides Cairo::Context for on_draw_listener.
#include <cairomm/context.h>

#include <iostream>

#include "gui.h"

// On draw listener.
// Just draws a couple of lines.
bool on_draw_listener(const Cairo::RefPtr<Cairo::Context>& cr,
		const size_t width, const size_t height)
{
	// coordinates for the center of the window
	size_t xc, yc;
	xc = width / 2;
	yc = height / 2;

	cr->set_line_width(10.0);

	// draw red lines out from the center of the window
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(xc, yc);
	cr->line_to(0, height);
	cr->move_to(xc, yc);
	cr->line_to(width, yc);
	cr->stroke();
}

// On file opened listener.
// Just prints opened file name to stdout.
void on_file_opened_listener(std::string filename)
{
	std::cout << "File " << filename << " opened" << std::endl;
}

// On command passed listener.
// Just prints typed commands to stdout.
void on_command_passed_listener(std::string command)
{
	std::cout << "Command " << command << " passed to console" << std::endl;
}

int main(int argc,char *argv[])
{ 
	// Next line initializes gtkmm.
	Gtk::Main kit(argc, argv); 
	
	// Than we construct GUI object, passing all three listeners
	// to constructor.
	yoghurt::GUI gui(on_file_opened_listener, on_command_passed_listener, on_draw_listener);

	// Finaly, we launch newly constructed gui.
	Gtk::Main::run(gui); 

	return 0;
}
