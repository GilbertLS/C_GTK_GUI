#ifndef SUMWINDOW_H
#define SUMWINDOW_H

#include <gtkmm.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "sumlist.h"

class Controller;

class SumWindow : public Gtk::Window
{
  friend class Controller;

  public:
    SumWindow(Controller*);
    virtual ~SumWindow();
    void popUp(Glib::ustring&);
    void clear();

  private:
    // Variables
    Controller* controller;

    // Member widgets
    Glib::ustring course;
    Gtk::Button   printButton;
    Gtk::Button   acceptButton;
    Gtk::Label    labels[9];
    Gtk::Label	  title;
    Gtk::Box      box;
    Gtk::Box      buttonBox;
    SumList       list;
 
    IO* io;
    
    //Functions
    void acceptApplication();
    void printToFile();
};

#endif
