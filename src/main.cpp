#include "../lib/window.hpp"

#include <gtkmm/application.h>

int main(int argc, char* argv[]){

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "utm.EZYSql");
    	Screen helloworld;

    	return app->run(helloworld);
}

