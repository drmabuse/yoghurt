////
// Copyright (c) 2012 Yoghurt Inc. All rights reserved.
////

#include "gui.h"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>

#include <iostream>
#include <vector>

yoghurt::GUI::GUI(void (*_on_file_opened_listener)(std::string),
		void (*_on_command_passed_listener)(std::string),
		bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		 const size_t width, const size_t height),
		const size_t _command_stack_size)

	: main_unit(Gtk::ORIENTATION_VERTICAL, 20),
	file_propeties(Gtk::ORIENTATION_HORIZONTAL, 15),
	command_box(Gtk::ORIENTATION_HORIZONTAL, 15),
	open_button("Open"),
	current_file_label("No file chousen"),
	apply_button("Apply"),
	command_stack_size(_command_stack_size),
	cur_command(command_stack.begin())
{
	set_title("yoghurt");

	set_icon_from_file("stuff/icon128.png");
	set_border_width(10);
	set_size_request(500, 500);

	open_button.signal_clicked().connect(sigc::mem_fun(*this, &GUI::on_open_clicked));

	apply_button.signal_clicked().connect(sigc::mem_fun(*this, &GUI::on_command_passed));

	console.signal_activate().connect(sigc::mem_fun(*this, &GUI::on_command_passed));

	command_box.signal_key_press_event().connect(
			sigc::mem_fun(*this, &GUI::on_key_released));
	command_box.add_events(Gdk::KEY_PRESS_MASK);

	
	add(main_unit);
	main_unit.pack_start(file_propeties, Gtk::PACK_SHRINK);
	main_unit.pack_start(scr);
	main_unit.pack_start(command_box, Gtk::PACK_SHRINK);
	file_propeties.pack_start(current_file_label);
	file_propeties.pack_end(open_button, Gtk::PACK_SHRINK);
	command_box.pack_start(console);
	command_box.pack_end(apply_button, Gtk::PACK_SHRINK);

	on_command_passed_listener = _on_command_passed_listener;
	on_file_opened_listener = _on_file_opened_listener;
	scr.set_on_draw_listener(_on_draw_listener);

	show_all_children();
}

yoghurt::GUI::~GUI() {};

void yoghurt::GUI::set_on_command_passed_listener(
		void (*_on_command_passed_listener)(std::string))
{ on_command_passed_listener = _on_command_passed_listener; }

void yoghurt::GUI::set_on_file_opened_listener(
		void (*_on_file_opened_listener)(std::string))
{ on_file_opened_listener = _on_file_opened_listener; }

void yoghurt::GUI::set_on_draw_listener(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		 const size_t width, const size_t height))
{ scr.set_on_draw_listener(_on_draw_listener); }

void yoghurt::GUI::on_open_clicked()
{
	Gtk::FileChooserDialog dialog("Please choose a file",
			Gtk::FILE_CHOOSER_ACTION_OPEN);	
	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	if(result == Gtk::RESPONSE_OK)
	{
		filename = dialog.get_filename();
		current_file_label.set_text(filename);
		if(on_file_opened_listener != NULL)
			on_file_opened_listener(filename);
	}
}

void yoghurt::GUI::on_command_passed()
{
	if(command_stack.size() >= command_stack_size)
		command_stack.pop_back();

	command_stack.push_front(console.get_text());

	if(on_command_passed_listener != NULL)
		on_command_passed_listener(console.get_text());

	console.set_text("");
	cur_command = --command_stack.begin();
}

bool yoghurt::GUI::on_key_released(GdkEventKey* event)
{
	if(event->type == GDK_KEY_PRESS)
	{
		if(event->keyval == GDK_KEY_Up)
		{
			if(++cur_command != command_stack.end())
				console.set_text(*(cur_command));
			else
				--cur_command;
		}
		if(event->keyval == GDK_KEY_Down)
		{
			if(cur_command == --command_stack.begin())
				return true;

			if(cur_command == command_stack.begin())
			{
				--cur_command;
				console.set_text("");
				return true;
			}

			console.set_text(*(--cur_command));
		}
	}
	return true;
}
