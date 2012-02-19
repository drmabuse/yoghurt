////
// Copyright (c) 2012 Yoghurt Inc. All rights reserved.
//
// This file describes Screen class, which encapsulates some drawing work
// delegating it to specified listener.
////

#pragma once

#include <gtkmm/drawingarea.h>

#include <cairomm/context.h>

namespace yoghurt
{
	////
	// This class represents a simple drawing area.
	// 
	// To draw something here you must register a listener: a boolean fuction,
	// which takes const Cairo::RefPtr<Cairo::Context>& and canvas dimension.
	// 
	// Listener registration:
	// You can just pass a listener fuction to the constructor(you can not,
	// nothing will break, class has default constuctor, in that case drawing
	// area will be just clean).
	// If you want to set(or change) listener to an alrady constructed object,
	// you can just use "set_on_draw_listener" method, which does what you
	// think it does.
	////
	class Screen : public Gtk::DrawingArea
	{
		public:
			// Everything you should know about this constructor is
			// written in class description.
			Screen(bool (*_on_draw_listener)
					(const Cairo::RefPtr<Cairo::Context>& cr,
					 const size_t width, const size_t height) = NULL);

			virtual ~Screen();

			// On draw listener setter.
			void set_on_draw_listener(bool (*_on_draw_listener)
					(const Cairo::RefPtr<Cairo::Context>& cr,
					 const size_t width, const size_t height));

		protected:
			// Override default signal listener:
			virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

		private:
			// Listener:
			bool (*on_draw_listener)(const Cairo::RefPtr<Cairo::Context>& cr,
					const size_t width, const size_t height);
	};
}
