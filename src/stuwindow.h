#ifndef STUWINDOW_H
#define STUWINDOW_H

#include <gtkmm.h>
#include <stdlib.h>
#include <string>
#include "form.h"
#include "io.h"

class Controller;

class StuWindow : public Gtk::Window
{
  friend class Controller;

  public:
    StuWindow(Controller*);
    virtual ~StuWindow();
    void popUp();
    void popUp(std::string* s, int, bool=false);
    void clear();

    // Get
    void getCanButton(Gtk::Button*);
    void getComboText(std::string&);

    bool editing;

  private:
    // Variables
    Controller* controller;
    bool        canClose;

    // Member widgets
    Gtk::Button       appButton;
    Gtk::Button       canButton;
    Gtk::Label        labels[9];
    Gtk::Label	      title;
    Gtk::Box          box;
    Gtk::Box	      box2;
    Gtk::Box          gradBox;
    Gtk::Box          buttonBox;
    Gtk::Box          radioBox;
    Gtk::RadioButton undergradButton, gradButton;
    Gtk::ComboBoxText combo;
    Form              undergradForm;
    Form              gradForm;
  
    bool on_delete_event (GdkEventAny* event);
    void startEvents();
    void switchContent();
    void appButtonClicked();
    void initCombo();
};

#endif
