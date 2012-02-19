////
// Copyright (c) 2012 Yoghurt Inc. All rights reserved.
////

#include "screen.h"
#include <cairomm/context.h>

yoghurt::Screen::Screen(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		const size_t width, const size_t height))
	: on_draw_listener(_on_draw_listener)
{ /* Just use parent constructor */ }

yoghurt::Screen::~Screen(){ /* Just use parent destructor */}


void yoghurt::Screen::set_on_draw_listener(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		const size_t width, const size_t height))
{ on_draw_listener = _on_draw_listener; }

bool yoghurt::Screen::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	// Just call On draw listener(if it is not NULL, ofcourse).
	return (on_draw_listener == NULL) ? true :
		on_draw_listener(cr, get_allocated_width(), get_allocated_height());
}
