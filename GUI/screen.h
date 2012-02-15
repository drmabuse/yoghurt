#pragma once

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

class Screen : public Gtk::DrawingArea
{
	public:
		Screen();

		Screen(bool (*_on_draw_listener)
				(const Cairo::RefPtr<Cairo::Context>& cr,
				 const Gtk::Allocation& allocation));

		virtual ~Screen();

		void set_on_draw_listener(bool (*_on_draw_listener)
				(const Cairo::RefPtr<Cairo::Context>& cr,
				 const Gtk::Allocation& allocation));

	protected:
		// Override default signal listener:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

	private:
		bool (*on_draw_listener)(const Cairo::RefPtr<Cairo::Context>& cr,
				const Gtk::Allocation& allocation);
};
