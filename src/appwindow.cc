/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Created by constructor. Displays application form and outputs to file using the IO class passed by controller.
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "appwindow.h"
#include "controller.h"

AppWindow::AppWindow(Controller *c)
: appButton("Submit"),
  canButton("Cancel"),
  subButton("Add"),
  subButton2("Add"),
  subButton3("Add"),
  delButton("Delete Oldest Entry"),
  delButton2("Delete Oldest Entry"),
  delButton3("Delete Oldest Entry"),
  closeButton("Close this application"),
  box(Gtk::ORIENTATION_VERTICAL),
  buttonBox(Gtk::ORIENTATION_HORIZONTAL),
  form("data/appForm.format"),
  form2("data/appForm2.format"),
  form3("data/appForm3.format"),
  nextButton1("Next >"),
  prevButton1("< Prev"),
  nextButton2("Next >"),
  prevButton2("< Prev"),
  nextButton3("Next >"),
  prevButton3("< Prev"),
  nextButton4("Next App"),
  prevButton4("Prev App")
{
  controller = c;
  course = "";
  application = 0;
  // Fill form from format file
  IO* io;
  controller->getIO(io);
  form.getFormatFile(io);
  form2.getFormatFile(io);
  form3.getFormatFile(io);

  // Window properties
  set_modal(true);
  set_title("cuTAES - Application Form");  
  set_border_width(10);
  set_size_request(270, 600);
  set_resizable (false);

  // Add Widgets to window
  add(box);
  box.set_spacing(5);
  subButton.set_size_request(50, 10);
  subButton2.set_size_request(50, 10);
  subButton3.set_size_request(50, 10);
  box.pack_start(title, Gtk::PACK_SHRINK);
  box.pack_start(form);
  box.pack_start(subButton, Gtk::PACK_SHRINK);
  box.pack_start(delButton, Gtk::PACK_SHRINK);
  box.pack_start(nextButton1, Gtk::PACK_SHRINK);
  box.pack_start(prevButton1, Gtk::PACK_SHRINK);
  box.pack_start(form2);
  box.pack_start(subButton2, Gtk::PACK_SHRINK);
  box.pack_start(delButton2, Gtk::PACK_SHRINK);
  box.pack_start(nextButton2, Gtk::PACK_SHRINK);
  box.pack_start(prevButton2, Gtk::PACK_SHRINK);
  box.pack_start(form3);
  box.pack_start(subButton3, Gtk::PACK_SHRINK);
  box.pack_start(delButton3, Gtk::PACK_SHRINK);
  box.pack_start(nextButton3, Gtk::PACK_SHRINK);
  box.pack_start(prevButton3, Gtk::PACK_SHRINK);
  box.pack_start(buttonBox, Gtk::PACK_SHRINK);
  appButton.set_size_request(50, 25);
  canButton.set_size_request(50, 25);
  buttonBox.set_spacing(5);
  buttonBox.pack_start(appButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(nextButton4, Gtk::PACK_SHRINK);
  buttonBox.pack_start(prevButton4, Gtk::PACK_SHRINK);
  buttonBox.pack_start(canButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(closeButton, Gtk::PACK_SHRINK);

  nextButton1.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::next1));
  nextButton2.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::next2));
  nextButton3.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::next3));
  prevButton1.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::prev1));
  prevButton2.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::prev2));
  prevButton3.signal_clicked().connect( sigc::mem_fun(*this, &AppWindow::prev3));
}

AppWindow::~AppWindow()
{
}

// Show window
void AppWindow::popUp(Glib::ustring& s, bool edit, bool view) 
{
  if(!get_visible()) {
    course = s;
    title.set_text("Applying for " + s);
    show_all();
  }
  if(!edit)
    closeButton.hide();
  if(controller->getIsGrad())
  {
    form.hide();
    subButton.hide();
    delButton.hide();
  }
  else 
  {
    form.show();
    subButton.show();
  }

  if(view)
  {
    subButton.hide();
    delButton.hide();
    subButton2.hide();
    delButton2.hide();
    subButton3.hide();
    delButton3.hide();
    appButton.hide();
    closeButton.hide();
    view1 = -1;
    view2 = -1;
    view3 = -1;
    
    //next1();
    next2();
    next3();
  }
  else
  {
    nextButton1.hide();
    prevButton1.hide();
    nextButton2.hide();
    prevButton2.hide();
    nextButton3.hide();
    prevButton3.hide();
    nextButton4.hide();
    prevButton4.hide();
  }
}

void AppWindow::clear() 
{
  form.clear();
  form2.clear();
  form3.clear();
}

void AppWindow::next1()
{
  ++view1;
  fillWithTaken();
}

void AppWindow::next2()
{
  ++view2;
  fillWithTa();
}

void AppWindow::next3()
{
  ++view3;
  fillWithWork();
}

void AppWindow::prev1()
{
  if(view1 > 0)
  {
    --view1;
    fillWithTaken();
  }
}

void AppWindow::prev2()
{
  if(view2 > 0)
  {
    --view2;
    fillWithTa();
  }
}

void AppWindow::prev3()
{
  if(view3 > 0)
  {
    --view3;
    fillWithWork();
  }
}

void AppWindow::fillWithTaken()
{
  Course* w = ((UApplication*)controller->app)->getCourseTaken(view1);

  if(w == 0)
  {
    if(view1 > 0)
      --view1;
    return;
  }

  std::string s[COURSE_NUM_ATTRIBUTES];
  w->toStrings(s, COURSE_NUM_ATTRIBUTES);
  std::string z[COURSE_NUM_ATTRIBUTES];
  z[0] = s[0];
  z[1] = s[1];
  z[2] = s[2];
  z[3] = s[3];
  z[4] = s[5];
  form.createFromStrings(z, COURSE_NUM_ATTRIBUTES);
}

void AppWindow::fillWithTa()
{
  Course* w = controller->app->getCourseTA(view2);

  if(w == 0)
  {
    if(view2 > 0)
      --view2;
    return;
  }

  std::string s[COURSE_NUM_ATTRIBUTES];
  w->toStrings(s, COURSE_NUM_ATTRIBUTES);
  std::string z[COURSE_NUM_ATTRIBUTES];
  z[0] = s[0];
  z[1] = s[1];
  z[2] = s[2];
  z[3] = s[4];
  form2.createFromStrings(z, COURSE_NUM_ATTRIBUTES);
}

void AppWindow::fillWithWork()
{
  Work* w = controller->app->getWork(view3);

  if(w == 0)
  {
    if(view3 > 0)
      --view3;
    return;
  }

  std::string s[WORK_NUM_ATTRIBUTES];
  w->toStrings(s, WORK_NUM_ATTRIBUTES);
  form3.createFromStrings(s, WORK_NUM_ATTRIBUTES);
}

