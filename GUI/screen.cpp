#include "screen.h"
#include <cairomm/context.h>

Screen::Screen() : on_draw_listener(NULL) { /* Just use parent constructor */ }

Screen::Screen(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		const Gtk::Allocation& allocation))
	: on_draw_listener(_on_draw_listener)
{ /* Just use parent constructor */ }

Screen::~Screen(){ /* Just use parent destructor */}


void Screen::set_on_draw_listener(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		const Gtk::Allocation& allocation))
{ on_draw_listener = _on_draw_listener; }

bool Screen::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{

	return (on_draw_listener == NULL) ? true : on_draw_listener(cr, get_allocation());
}
