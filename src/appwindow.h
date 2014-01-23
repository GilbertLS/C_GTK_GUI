#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtkmm.h>
#include <stdlib.h>
#include <string>
#include "form.h"
#include "application.h"
#include "work.h"
#include "course.h"

class Controller;

class AppWindow : public Gtk::Window
{
  friend class Controller;

  public:
    AppWindow(Controller*);
    virtual ~AppWindow();
    void popUp(Glib::ustring&, bool edit = false, bool view = false);
    void clear();

    // Get
    void getCanButton(Gtk::Button*);

  private:
    // Variables
    Controller* controller;

    // Member widgets
    Glib::ustring course;
    Gtk::Button   appButton;
    Gtk::Button   canButton;
    Gtk::Button   subButton;
    Gtk::Button   subButton2;
    Gtk::Button   subButton3;
    Gtk::Button   delButton;
    Gtk::Button   delButton2;
    Gtk::Button   delButton3;
    Gtk::Button   closeButton;
    Gtk::Label    labels[9];
    Gtk::Label	  title;
    Gtk::Box      box;
    Gtk::Box      buttonBox;
    Form	  form;
    Form	  form2;
    Form	  form3;

    // Viewing
    Gtk::Button nextButton1;
    Gtk::Button prevButton1;
    Gtk::Button nextButton2;
    Gtk::Button prevButton2;
    Gtk::Button nextButton3;
    Gtk::Button prevButton3;
    Gtk::Button nextButton4;
    Gtk::Button prevButton4;
    int view1;
    int view2;
    int view3;
    int application;

    void next1();
    void next2();
    void next3();
    void next4();
    void prev1();
    void prev2();
    void prev3();
    void prev4();
    void fillWithTa();
    void fillWithTaken();
    void fillWithWork();

};

#endif
