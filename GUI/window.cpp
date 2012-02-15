#include "window.h"
#include <iostream>

GUI::GUI(void (*_on_command_passed_listener)(std::string) = NULL,
		void (*_on_file_opened_listener)(std::string) = NULL,
		bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		 const Gtk::Allocation& allocation) = NULL)

	: main_unit(Gtk::ORIENTATION_VERTICAL, 20),
	file_propeties(Gtk::ORIENTATION_HORIZONTAL, 15),
	command_box(Gtk::ORIENTATION_HORIZONTAL, 15),
	open_button("Open"),
	current_file_label("No file chousen"),
	apply_button("Apply")
{
	set_title("Sound shayt");
	set_border_width(10);

	open_button.signal_clicked().connect(sigc::mem_fun(*this, &GUI::on_open_clicked));

	apply_button.signal_clicked().connect(sigc::mem_fun(*this, &GUI::on_command_passed));

	console.signal_activate().connect(sigc::mem_fun(*this, &GUI::on_command_passed));

	
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

GUI::~GUI() {};

void GUI::set_on_command_passed_listener(
		void (*_on_command_passed_listener)(std::string))
{ on_command_passed_listener = _on_command_passed_listener; }

void GUI::set_on_file_opened_listener(
		void (*_on_file_opened_listener)(std::string))
{ on_file_opened_listener = _on_file_opened_listener; }

void GUI::set_on_draw_listener(bool (*_on_draw_listener)
		(const Cairo::RefPtr<Cairo::Context>& cr,
		 const Gtk::Allocation& allocation))
{ scr.set_on_draw_listener(_on_draw_listener); }

void GUI::on_open_clicked()
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

void GUI::on_command_passed()
{
	std::cout << console.get_text() << std::endl;
	command_stack.push(console.get_text());
	if(on_command_passed_listener != NULL)
		on_command_passed_listener(console.get_text());
	console.set_text("");
}
