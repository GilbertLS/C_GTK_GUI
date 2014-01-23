/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Created by constructor. Displays summary of applications.
 *
 * Last Modified: March 22, 2013
 *
 */

#include "sumwindow.h"
#include "controller.h"

SumWindow::SumWindow(Controller *c)
: printButton("Print Summary"),
  acceptButton("Accept Application"),
  box(Gtk::ORIENTATION_VERTICAL),
  buttonBox(Gtk::ORIENTATION_HORIZONTAL),
  list("data/summary.format")
{
  controller = c;
  course = "";

  // Fill list from format file
  controller->getIO(io);
  list.getFormatFromFile(io);

  // Window properties
  set_modal(true);
  set_title("cuTAES - Application Form");  
  set_border_width(10);
  set_size_request(1000, 600);
  set_resizable (true);

  // Add Widgets to window
  add(box);
  box.set_spacing(5);
  box.pack_start(title, Gtk::PACK_SHRINK);
  box.pack_start(list);
  box.pack_start(buttonBox, Gtk::PACK_SHRINK);
  printButton.set_size_request(50, 25);
  buttonBox.set_spacing(5);
  buttonBox.pack_start(printButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(acceptButton, Gtk::PACK_SHRINK);

  printButton.signal_clicked().connect( sigc::mem_fun(*this, &SumWindow::printToFile));
  acceptButton.signal_clicked().connect( sigc::mem_fun(*this, &SumWindow::acceptApplication));
}

SumWindow::~SumWindow()
{
}

// Show window
void SumWindow::popUp(Glib::ustring& s) {
  if(!get_visible()) {
    course = s;
    title.set_text("Viewing applications for " + s);
    show_all();
  }
}

void SumWindow::clear()
{
  list.clear();
}

//print the summary to a file
void SumWindow::printToFile()
{
  char time_buf[21];
  time_t now;
  time(&now);
  strftime(time_buf, 21, "%Y-%m-%d-%H:%M:%S", gmtime(&now));
  std::string file = "summaryFile - ";
  file.append(time_buf);
  list.printToFile(io, file);
}

// Get information from application and send it to be accepted
void SumWindow::acceptApplication()
{
  Gtk::TreeModel::Row row = *list.treeView.get_selection()->get_selected();
  if(row) //If anything is selected
  {
  std::string pathToApp = "applications/";
  std::string studentReference;
  int i;

  std::string colD = row->get_value(list.columns.colD).c_str();
  std::string colA = row->get_value(list.columns.colA).c_str();

  if(colD.compare("Pending")==0)
  {
    pathToApp.append(row->get_value(list.columns.colA).c_str());
    pathToApp.append("/");
    pathToApp.append(row->get_value(list.columns.colB).c_str());
    if (controller->acceptApplication(pathToApp)==0)
    {
      Gtk::MessageDialog message(*this, 
        "Student application has been accepted!", false, Gtk::MESSAGE_INFO );
      message.run();
      hide();
    }
  }
}
}
