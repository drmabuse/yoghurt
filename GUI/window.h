#pragma once

#include <gtkmm.h>
#include <string>
#include "screen.h"

class GUI : public Gtk::Window
{
	public:
		GUI(void (*_on_command_passed_listener)(std::string),
				void (*_on_file_opened_listener)(std::string),
				bool (*_on_draw_listener)
				(const Cairo::RefPtr<Cairo::Context>& cr,
				 const Gtk::Allocation& allocation));

		virtual ~GUI();

		std::string get_filename() const
		{ return filename; }

		void set_on_command_passed_listener(
				void (*_on_command_passed_listener)(std::string));
		void set_on_file_opened_listener(
				void (*_on_file_opened_listener)(std::string));
		void set_on_draw_listener(bool (*_on_draw_listener)
				(const Cairo::RefPtr<Cairo::Context>& cr,
				 const Gtk::Allocation& allocation));

	protected:
		//Signal listeners:
		void on_open_clicked();
		void on_command_passed();

		//Child widgets:
		Gtk::Box main_unit;
		Gtk::Box file_propeties;
		Gtk::Box command_box;
		Gtk::Button open_button, apply_button;
		Gtk::Label current_file_label;
		Gtk::Entry console;
		Screen scr;

	private:
		std::string filename;
		std::stack<std::string> command_stack;
		void (*on_command_passed_listener)(std::string);
		void (*on_file_opened_listener)(std::string);
};
