/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Created by constructor. Displays application form and outputs to file using the IO class passed by controller.
 *
 * Last Modified: March 22, 2013
 *
 */

#include "stuwindow.h"
#include "controller.h"
#include <iostream>

StuWindow::StuWindow(Controller *c)
: appButton("Submit"),
  canButton("Cancel"),
  box(Gtk::ORIENTATION_VERTICAL),
  box2(Gtk::ORIENTATION_VERTICAL),
  gradBox(Gtk::ORIENTATION_VERTICAL),
  radioBox(Gtk::ORIENTATION_HORIZONTAL),
  buttonBox(Gtk::ORIENTATION_HORIZONTAL),
  undergradForm("data/undergradForm.format"),
  gradForm("data/gradForm.format"),
  undergradButton("Undergraduate"),
  gradButton("Gradutate"),
  title("As a new user please fill in the information")
{
  controller = c;

  // Fill form from format file
  IO* io;
  controller->getIO(io);
  undergradForm.getFormatFile(io);
  gradForm.getFormatFile(io);

  // Window properties
  set_modal(true);
  set_title("cuTAES - Student Form");  
  set_border_width(10);
  set_size_request(270, 300);
  set_resizable (false);
  canClose = false;

  // Add Widgets to window
  add(box);

  // Main box
  box.pack_start(title, Gtk::PACK_SHRINK);
  box.pack_start(radioBox, Gtk::PACK_SHRINK);
  box.pack_start(box2);
  box.pack_start(buttonBox, Gtk::PACK_SHRINK);

  // Button Box
  appButton.set_size_request(50, 25);
  canButton.set_size_request(50, 25);
  buttonBox.set_spacing(5);
  buttonBox.pack_start(appButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(canButton, Gtk::PACK_SHRINK);

  // Radio Box
  radioBox.pack_start(undergradButton);
  radioBox.pack_start(gradButton);

  // Middle Box
  box2.pack_start(undergradForm);
  box2.pack_start(gradBox);

  // Graduate Box
  gradBox.pack_start(gradForm);
  gradBox.pack_start(combo, Gtk::PACK_SHRINK);
  initCombo();
  combo.set_active_text("Research Area");

  Gtk::RadioButton::Group group = undergradButton.get_group();
  gradButton.set_group(group);

  undergradButton.set_sensitive(false);
  undergradButton.activate();
  gradButton.set_sensitive(true);
  gradBox.hide();
  undergradForm.show();

  startEvents();

  editing = false;

}

StuWindow::~StuWindow()
{
}

void StuWindow::startEvents()
{
  undergradButton.signal_clicked().connect( sigc::mem_fun(*this, &StuWindow::switchContent));
  gradButton.signal_clicked().connect( sigc::mem_fun(*this, &StuWindow::switchContent));
  appButton.signal_clicked().connect( sigc::mem_fun(*this, &StuWindow::appButtonClicked));
}

void StuWindow::appButtonClicked()
{
  if(!gradButton.get_active())
  {
    if(editing)
     controller->createUndergrad(1);
    else
     controller->createUndergrad(0);
  }
  else
  {
    if(editing)
      controller->createGrad(1);
    else
      controller->createGrad(0);
  }
}

void StuWindow::initCombo()
{
  IO* i;
  controller->getIO(i);
  std::string s[100];
  std::string path = "data/research.format";

  i->getFromFile(path, s, 100);

  for(int i = 0; i < 100; i++) {
    if(s[i] == "/0")
      break;

    combo.append(s[i]);
  }

}

// Show window
void StuWindow::popUp() {
  if(!get_visible()) {
    show_all();
    gradBox.hide();

    if(canClose) {
      canButton.show();
      set_deletable(true);
    }
    else {
      //canButton.hide();
      set_deletable(false);
    }
  }
  editing = false;
}

// Show window for student info editing
void StuWindow::popUp(std::string* s, int size, bool view)
{
  if(!get_visible()) {
    show_all();

    if(controller->getIsGrad())
    {
      gradButton.set_active();
      gradForm.createFromStrings(s, size);
      combo.set_active_text(s[size-1]);
      gradForm.hideEntry(0);
    }
    else
    {
      gradBox.hide();
      undergradForm.createFromStrings(s, size);
      undergradForm.hideEntry(0);
    }
    radioBox.hide();
  }

  if(view)
  {
    show_all();
    radioBox.hide();
    appButton.hide();
    canButton.hide();
    title.hide();
  }

  editing = true;
}

bool StuWindow::on_delete_event(GdkEventAny* event)
{
  if(canClose)
    hide();
  else
    iconify();
 return true;
}

void StuWindow::switchContent()
{
  undergradForm.clear();
  gradForm.clear();
  if(undergradButton.get_active())
  {
    undergradButton.set_sensitive(false);
    gradButton.set_sensitive(true);
    gradBox.hide();
    undergradForm.show();
  }
  else if(gradButton.get_active())
  {
    gradButton.set_sensitive(false);
    undergradButton.set_sensitive(true);
    undergradForm.hide();
    gradBox.show();
  }
}

void StuWindow::clear()
{
  undergradButton.activate();
}

void StuWindow::getComboText(std::string& s)
{
  s = combo.get_active_text().c_str();
}
	

