#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>
#include "window.h"

bool on_draw_listener(const Cairo::RefPtr<Cairo::Context>& cr,
		const Gtk::Allocation& allocation)
{
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// coordinates for the center of the window
	int xc, yc;
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

void on_file_opened_listener(std::string filename)
{
	std::cout << "File " << filename << " opened" << std::endl;
}

void on_command_passed_listener(std::string command)
{
	std::cout << "Command " << command << " passed to console" << std::endl;
}

int main(int argc,char *argv[])
{ 
	Gtk::Main kit(argc, argv); 

	GUI gui(on_command_passed_listener, on_file_opened_listener, on_draw_listener);

	Gtk::Main::run(gui); 

	return 0;
}
