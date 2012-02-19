////
// Copyright (c) 2012 Yoghurt Inc. All rights reserved.
//
// This file describes main GUI class.
// Include it if you want to use GUI frontend.
//
// WARNING: You shouldn't include any other GUI files, this one provides
// all functionality.
//
// Example of use you can see in "gui_example.cpp".
////

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

#include <cairomm/context.h>

#include <string>
#include <list>

#include "screen.h"

namespace yoghurt
{
	////
	// The main GUI class.
	//
	// This class makes all work with GUI for you, one just need to
	// register some listeners:
	//
	// 1) On file opened listener:
	// Called when new file is opened from GUI, provides you filename string.
	//
	// You can set it using the "set_on_file_opened_listener" function,
	// or by passing it as the first argument of constructor.
	//
	// 2) On command passed listener:
	// Called when command is passed to the graphical console,
	// provides command string.
	//
	// You can set it using the "set_on_command_passed_listener" function,
	// or by passing it as the second argument of constructor.
	//
	// 3) On draw listener:
	// This one gives you an ability to visualize anything you want,
	// by drawing it using Cairo.
	// Provides const Cairo::RefPtr<Cairo::Context>& and canvas dimension.
	//
	// You can set it using the "set_on_draw_listener" function,
	// or by passing it as the third argument of constructor.
	//
	//
	// Thouse listeners will be called whenever the appropriate event happenes.
	// 
	// REMARK: If you prefer not to use one or another listener you can just
	// call the appropriate listener setter from NULL pointer. In fact, all
	// listeners are set to NULL by default, which gives you an ability to
	// omit some of them in the very beginning.
	//
	// After setting up listeners you can just run it as a normal window.
	////
	class GUI : public Gtk::Window
	{
		public:
			// First three parametres of this constructor described in the
			// class description.
			//
			// Fourth is for setting command stack size limit.
			// Graphical console saves some last commands user typed,
			// this value bounds the quantity of commands
			// console will remember.

			GUI(void (*_on_file_opened_listener)(std::string) = NULL,
					void (*_on_command_passed_listener)(std::string) = NULL,
					bool (*_on_draw_listener)
					(const Cairo::RefPtr<Cairo::Context>& cr,
					 const size_t width, const size_t height) = NULL,
					const size_t _command_stack_size = 30);

			virtual ~GUI();

			inline std::string get_filename() const
			{ return filename; }

			// On file opened listener setter.
			void set_on_file_opened_listener(
					void (*_on_file_opened_listener)(std::string));
			// On command passed listener setter.
			void set_on_command_passed_listener(
					void (*_on_command_passed_listener)(std::string));
			// On draw listener setter.
			void set_on_draw_listener(bool (*_on_draw_listener)
					(const Cairo::RefPtr<Cairo::Context>& cr,
					 const size_t width, const size_t height));

		protected:
			//Signal listeners:
			void on_open_clicked();
			void on_command_passed();
			bool on_key_released(GdkEventKey* event);

			//Child widgets:
			Gtk::Box main_unit;
			Gtk::Box file_propeties;
			Gtk::Box command_box;
			Gtk::Button open_button, apply_button;
			Gtk::Label current_file_label;
			Gtk::Entry console;
			Screen scr;

		private:
			// Holds the name of the currently opened file.
			// (it is empty if no file opened)
			std::string filename;
			// Command stack.
			// Size is bounded by command_stack_size
			std::list<std::string> command_stack;
			const size_t command_stack_size;
			std::list<std::string>::iterator cur_command;
			// Listeners:
			void (*on_command_passed_listener)(std::string);
			void (*on_file_opened_listener)(std::string); 
	};
}
