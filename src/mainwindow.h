#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <string>
#include "selectlist.h"
#include "io.h"
#include "Queue.h"
#include "application.h"
#include "gapplication.h"
#include "uapplication.h"
#include "student.h"
#include "grad.h"
#include "undergrad.h"

class Controller;

class MainWindow : public Gtk::Window
{
  friend class Controller;

  public:
    MainWindow(Controller*);
    virtual ~MainWindow();

  private:
    //Functions
    void startEvents();
    void stuButtonClicked();
    void facButtonClicked();
    void appButtonClicked();
    void bacButtonClicked();
    void selButtonClicked();
    void viewButtonClicked();
    void button1();
    void button2();
    void findPopUp();
    void findApplications(std::string& find, Student* stu=NULL);
    Student* findStudent(std::string& find, bool one = false);
    Application* getApplication(int);

    //Variables
    Controller*  controller;
    IO*          io;

    //Child widgets:
    Gtk::Button  stuButton;
    Gtk::Button  facButton;
    Gtk::Button  appButton;
    Gtk::Button  bacButton;
    Gtk::Button  selButton;
    Gtk::Button  viewButton;
    Gtk::Button  genButton;
    Gtk::Button  modButton;
    Gtk::Button  viewAppButton;
    Gtk::Box     box;
    Gtk::Box     homeBox;
    Gtk::Box     classBox;
    Gtk::Box     buttonBox;
    Gtk::Image   cuLogo;
    SelectList   list;

    Gtk::Window  findWindow;
    Gtk::Label	 label1;
    Gtk::Label	 label2;
    Gtk::Label	 label3;
    Gtk::Button  findButton1;
    Gtk::Button  findButton2;
    Gtk::Button  findButton3;
    Gtk::Entry   entry1;
    Gtk::Entry   entry2;
    Gtk::Entry   entry3;
    Gtk::Grid    findGrid;

    Queue<Application> applications;
    Queue<Student> students;
};

#endif
