/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Use: Creates the controller
 *
 * Last Modified: Feb 1, 2013
 *
 */

#include <gtkmm/application.h>
#include "controller.h"
using namespace std;


int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  Controller controller(app);
  
  return 0;
}
