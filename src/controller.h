#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <gtkmm.h>
#include "mainwindow.h"
#include "stuwindow.h"
#include "appwindow.h"
#include "sumwindow.h"
#include "student.h"
#include "undergrad.h"
#include "grad.h"
#include "application.h"
#include "uapplication.h"
#include "io.h"
#include <string>

class MainWindow;

class Controller
{

  public:
    Controller(Glib::RefPtr<Gtk::Application>);
    ~Controller();

    // Get functions
    void getIO(IO*);

    void stuButtonClicked();
    void appButtonClicked();
    void selButtonClicked();
    void viewButtonClicked();
    void createUndergrad(int);
    void createGrad(int);
    bool getIsGrad();
    int acceptApplication(std::string&);
    void closeApplication(const std::string&);
    void studentToFile();
    void viewApplications(Application* a);
    void viewNextApplication();
    void viewPrevApplication();
    void viewApplication(int);
    Application* app;

  private:
    Glib::RefPtr<Gtk::Application> application;
    MainWindow   view;
    StuWindow    stuWindow;
    AppWindow    appWindow;
    SumWindow    sumWindow;
    IO           io;
    Student*     stu;
    bool isGrad;

    // Signal handlers:
    void canButtonClicked();
    void awpButtonClicked();
    void submitApplication(int);
    void subButtonClicked();
    void subButton2Clicked();
    void subButton3Clicked();
    void startEvents();
    void subErrors(int);
    void genButtonClicked();
    void modButtonClicked();
    void delButtonClicked();
    void delButton2Clicked();
    void delButton3Clicked();
    void closeButtonClicked();
    int  checkStudent(int);
    void closeApplications(const std::string&);

};

#endif
