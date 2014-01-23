/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Controller takes care of event handlers and the different views.
 *
 * Last Modified: Mar 22, 2013
 *
 */

#include "controller.h"
#include <iostream>

Controller::Controller(Glib::RefPtr<Gtk::Application> a)
: view(this),
  stuWindow(this),
  appWindow(this),
  sumWindow(this),
  io()
{
  app = NULL;
  stu = NULL;
  application = a;
  startEvents();
  application->run(view);
}

Controller::~Controller()
{
  if(app != NULL) 
  {
    delete(app);
  }
  if(stu != NULL)
  {
    delete(stu);
  }
}

void Controller::getIO(IO* i)
{
  i = &io;
}

void Controller::startEvents()
{
  // StuWindow
  stuWindow.canButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::canButtonClicked));

  // AppWindow
  appWindow.canButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::canButtonClicked));
  appWindow.appButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::awpButtonClicked));
  appWindow.subButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::subButtonClicked));
  appWindow.subButton2.signal_clicked().connect( sigc::mem_fun(*this, &Controller::subButton2Clicked));
  appWindow.subButton3.signal_clicked().connect( sigc::mem_fun(*this, &Controller::subButton3Clicked));
  appWindow.delButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::delButtonClicked));
  appWindow.delButton2.signal_clicked().connect( sigc::mem_fun(*this, &Controller::delButton2Clicked));
  appWindow.delButton3.signal_clicked().connect( sigc::mem_fun(*this, &Controller::delButton3Clicked));
  appWindow.closeButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::closeButtonClicked));
  appWindow.nextButton4.signal_clicked().connect( sigc::mem_fun(*this, &Controller::viewNextApplication));
  appWindow.prevButton4.signal_clicked().connect( sigc::mem_fun(*this, &Controller::viewPrevApplication));

  // MainWindow
  view.genButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::genButtonClicked));
  view.modButton.signal_clicked().connect( sigc::mem_fun(*this, &Controller::modButtonClicked));

}

// Button Student section
void Controller::stuButtonClicked()
{
  stuWindow.popUp();
}

// View all applications
void Controller::selButtonClicked()
{
  string z = "applications/";
  string file = "data/courses";
  int fileLength = io.getFileLength(file);
  string s[fileLength];
  sumWindow.clear();
  io.getFromFile(file, s, fileLength);
  for(int i = 0; i < fileLength; i++) 
  {
    if(s[i].compare("/0") == 0)
      break;
    sumWindow.list.getApplications(&io, z+s[i]);
  }
    Glib::ustring u = "all courses";
    sumWindow.popUp(u);
}

// View selected applications
void Controller::viewButtonClicked()
{
  Glib::ustring s;
  view.list.getSelection(s);
  string z = "applications/"; 
  z.append(s.c_str());
  sumWindow.clear();
  sumWindow.list.getApplications(&io, z);

  if (s != "")
    sumWindow.popUp(s);
}

// Apply button
void Controller::appButtonClicked()
{
  Glib::ustring s;
  view.list.getSelection(s);

  if (s != "") {
    appWindow.popUp(s);
    if(app == NULL)
      app = new UApplication(s, stu);
  }
}

// Cancel button
void Controller::canButtonClicked()
{
  if(stuWindow.get_visible()) {
    if(!stuWindow.editing)
    {
      view.bacButtonClicked();
    }
    stuWindow.hide();
    stuWindow.clear();
  }
  if(appWindow.get_visible()) {
    appWindow.hide();
    appWindow.clear();
    if(app != NULL) {
      delete(app);
      app = NULL;
    }
  }
}

// Edit General Info Button
void Controller::genButtonClicked()
{
  int size;
  std::string* s;

  // File the student form with information for editing
  if (isGrad)
  {
    size = GRAD_NUM_ATTRIBUTES;
    s = new string[size];
    Grad* g = ((Grad*)stu);
    g->toStrings(s, size);
  }
  else
  {
    size = UNDERGRAD_NUM_ATTRIBUTES;
    s = new string[size];
    Undergrad* u = ((Undergrad*)stu);
    u->toStrings(s, size);
  }

  stuWindow.popUp(s, size);
  delete[] s;
}

void Controller::modButtonClicked()
{
  if(stu == 0)
    return;

  Glib::ustring s;
  view.list.getSelection(s);
  DIR           *d;
  std::string    q;
  struct dirent *dir;
  std::string path = "applications/";
  path.append(s.c_str());
  path.append("/");
  d = opendir(path.c_str());
  std::string studentUID;
  stu->getIDStr(studentUID);
  bool foundApplication = false;

  if (s != "") {
    // Iterate over all the files in the selected course
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        q = dir->d_name;
        if(q.find(".") == -1)
        {
          // Look into every file to see if student id is there and if application is pending
          std::string temp = path + q;
          std::string pending = "Pending";
          if(io.findWord(temp, studentUID) > 0 && io.findWord(temp, pending) > 0) 
          {
            // Get the file length and get the file content
            int fileLength = io.getFileLength(temp);
            string z[fileLength];
            io.getFromFile(temp, z, fileLength);
            
            if(app == NULL)
               app = new UApplication(s, stu);

            // Create the application from the file content
            app->createFromStrings(z, fileLength);
            appWindow.popUp(s, true);

            foundApplication = true;

            break;
          }
        }
      }

      if(!foundApplication) 
      {
        Gtk::MessageDialog message(view, 
          "Either the application does not exist or it is closed!", false, Gtk::MESSAGE_ERROR );
        message.run();
      }

      closedir(d);
    }
  }
}

void Controller::closeButtonClicked()
{
  submitApplication(1);
}

void Controller::awpButtonClicked()
{
  submitApplication(0);
}

// Undergrad general information submission and error messages
void Controller::createUndergrad(int t) {
  int num = UNDERGRAD_NUM_ATTRIBUTES;
  std::string s[num];
  Undergrad* u;

  u = new Undergrad();

  // Get the entries from the form
  stuWindow.undergradForm.getEntries(s, &num);

  int i = u->createFromStrings(s, num);
  if(checkStudent(i))
  {
    delete(u);
  }
  else
  { 
    if(stu != NULL) 
    {
      delete(stu);
      stu = NULL;
    }
    stu = u;
    isGrad = false;

    if(t)
      studentToFile();
  }
}

// Graduate general information submission and error messages
void Controller::createGrad(int t) {
  int num = GRAD_NUM_ATTRIBUTES;
  std::string s[num];
  std::string z;
  Grad* u;

  u = new Grad();

  // Get the entries from the form
  stuWindow.gradForm.getEntries(s, &num);
  num++;
  
  stuWindow.getComboText(z);
  s[num-1] = z;

  int i = u->createFromStrings(s, num);
  if(checkStudent(i))
  {
    delete(u);
  }
  else
  { 
    if(stu != NULL) 
    {
      delete(stu);
    }
    stu = u;
    isGrad = true;

    if(t)
      studentToFile();
  }
}

void Controller::studentToFile()
{
  std::string s[10];
  std::string id;
  stu->getIDStr(id);
  std::string file = "students/" + id;

  // Send student to file
  if(stu != 0)
  {
    if(isGrad) 
    {
      s[0] = "grad";
      static_cast<Grad*>(stu)->toStrings(&s[1], GRAD_NUM_ATTRIBUTES);
      io.sendToFile(file, s, GRAD_NUM_ATTRIBUTES+1);
    }
    else
    {
      s[0] = "undergrad";
      static_cast<Undergrad*>(stu)->toStrings(&s[1], UNDERGRAD_NUM_ATTRIBUTES);
      io.sendToFile(file, s, UNDERGRAD_NUM_ATTRIBUTES+1);
    }
    stu->setCreated();
  }

  
}

// Student Error Checking
int Controller::checkStudent(int i) 
{
  std::string err;

  if(i == 0) {
    stuWindow.hide();
    stuWindow.clear();
    Gtk::MessageDialog message(view, 
      "Information has been saved! You may now apply.", false, Gtk::MESSAGE_INFO );
    message.run();
  }
  else {
    switch (i)
      {
        case 1: err = "Invalid Student Number!"; break;
        case 2: err = "First Name cannot be left blank!"; break;
        case 3: err = "Last Name cannot be left blank!"; break;
        case 4: err = "Invalid Email! (e.g. @cmail.carleton.ca)"; break;
        case 5: err = "Invalid Year Standing!"; break;
        case 6: err = "Major cannot be left blank!"; break;
        case 7: err = "Invalid CGPA!"; break;
        case 8: err = "Invalid Major GPA!"; break;
        case 9: err = "Select Research Area from combo box!"; break;
        case 10: err = "Program must be either PhD or MCS!"; break;
        case 11: err = "Supervisor cannot be left blank!"; break;
        default: err = "Incorrect Fields!"; break;
      }
    Gtk::MessageDialog message(stuWindow, 
      "Error: " + err, false, Gtk::MESSAGE_ERROR );
    message.run();
    return 1;
  }
  return 0;
}

// Submit Application
void Controller::submitApplication(int close) 
{
  std::string s[10];
  std::string id;
  std::string file;
  std::string err;

  //Make sure lists are not empty
  if(((UApplication*)app)->isCourseTakenEmpty() && !isGrad) {
    err = "You have not added any courses taken.";
  }

  if(err.length() > 0)
  {
    Gtk::MessageDialog message(appWindow, 
      err.c_str(), false, Gtk::MESSAGE_ERROR );
    message.run();
    return;
  }

  studentToFile();

  //Use the - operator to close application if specified
  if(close > 0)
    -(*app);

  // Send general App info to file
  std::string z[APP_NUM_ATTRIBUTES];
  app->toStrings(z, APP_NUM_ATTRIBUTES);
  app->getIDStr(id);

  file = "applications/";
  file.append(appWindow.course.c_str());
  file.append("/" + id);
  io.sendToFile(file, z, APP_NUM_ATTRIBUTES);
  
  // Send list of courses and work to file
  std::string emptyString = "";
  std::string seperator = "---";
  Course* c;
  Work* w;

  // Send Course Taken to file
  while(!((UApplication*)app)->isCourseTakenEmpty()) {
    io.appendToFile(file, &emptyString, 1);
    c = ((UApplication*)app)->popCourseTaken();
    c->toStrings(z, COURSE_NUM_ATTRIBUTES);
    delete(c);
    io.appendToFile(file, z, COURSE_NUM_ATTRIBUTES);
  }

  io.appendToFile(file, &seperator, 1);

  // Send Course TAed to file
  while(!app->isCourseTAEmpty()) {
    io.appendToFile(file, &emptyString, 1);
    c = app->popCourseTA();
    c->toStrings(z, COURSE_NUM_ATTRIBUTES);
    delete(c);
    io.appendToFile(file, z, COURSE_NUM_ATTRIBUTES);
  }

  io.appendToFile(file, &seperator, 1);

  // Send Work to file
  while(!app->isWorkEmpty()) {
    io.appendToFile(file, &emptyString, 1);
    w = app->popWork();
    w->toStrings(z, WORK_NUM_ATTRIBUTES);
    delete(w);
    io.appendToFile(file, z, WORK_NUM_ATTRIBUTES);
  }

  io.appendToFile(file, &seperator, 1);

  Gtk::MessageDialog message(view, 
    "Application has been sent!", false, Gtk::MESSAGE_INFO );
  message.run();

  if(app != NULL) {
    delete(app);
    app = NULL;
  }

  appWindow.hide();
  appWindow.clear();
}

// Submit course student has taken
void Controller::subButtonClicked() 
{
  int num = COURSE_NUM_ATTRIBUTES;
  std::string s[num];
  Course* c = new Course();
  appWindow.form.getEntries(s, &num);
  int i = c->createFromStrings(s, num);

  if(i == 0) {
    Gtk::MessageDialog message(appWindow, 
      "Class taken has been added to your application!", false, Gtk::MESSAGE_INFO );
    message.run();
    ((UApplication*)app)->pushCourseTaken(c);
  }
  else {
    subErrors(i);
    delete(c);
  }
}

// Remove class Taken from application
void Controller::delButtonClicked()
{
  std::string s;
  Course* c = ((UApplication*)app)->popCourseTaken();
  if(c != 0)
  {
    delete(c);
    s = "Oldest class taken has been removed from your application!";
  }
  else
    s = "There are no classes taken to remove!";

  Gtk::MessageDialog message(appWindow, 
    s, false, Gtk::MESSAGE_INFO );
  message.run();
}

// Submit course student has Taed
void Controller::subButton2Clicked() 
{
  int num = COURSE_NUM_ATTRIBUTES;
  std::string s[num];
  Course* c = new Course();
  appWindow.form2.getEntries(s, &num);
  int i = c->createFromStrings(s, num);

  if(i == 0) {
    Gtk::MessageDialog message(appWindow, 
      "Class TAed has been added to your application!", false, Gtk::MESSAGE_INFO );
    message.run();
    app->pushCourseTA(c);
  }
  else {
    subErrors(i);
    delete(c);
  }
}

// Remove class TAed from application
void Controller::delButton2Clicked()
{
  std::string s;
  Course* c = app->popCourseTA();
  if(c != 0)
  {
    delete(c);
    s = "Oldest class TAed has been removed from your application!";
  }
  else
    s = "There are no classes TAed to remove!";

  Gtk::MessageDialog message(appWindow, 
    s, false, Gtk::MESSAGE_INFO );
  message.run();
}

// Submit work
void Controller::subButton3Clicked() {
  int num = WORK_NUM_ATTRIBUTES;
  std::string s[num];
  std::string err;
  appWindow.form3.getEntries(s, &num);
  Work* work = new Work();
  int i = work->createFromStrings(s, num);

  if(i == 0) {
    Gtk::MessageDialog message(appWindow, 
      "Work experience has been added to your application!", false, Gtk::MESSAGE_INFO );
    message.run();
    app->pushWork(work);
  }
  else {
    if(i == 3 || i == 4)
      err = "Date format must be dd/mm/yyyy!";
    else
      err = "Cannot leave field blank!";
    Gtk::MessageDialog message(appWindow, 
    "Error: " + err, false, Gtk::MESSAGE_ERROR );
    message.run();
    delete(work);
  }
}

// Remove work from application
void Controller::delButton3Clicked()
{
  std::string s;
  Work* w = app->popWork();
  if(w != 0)
  {
    delete(w);
    s = "Oldest work entry has been removed from your application!";
  }
  else
    s = "There are no work entries to remove!";

  Gtk::MessageDialog message(appWindow, 
    s, false, Gtk::MESSAGE_INFO );
  message.run();
}

// Error messages for application class submission
void Controller::subErrors(int i) {
  std::string err;
  switch (i)
      {
      case 1: err = "Invalid Course Code!"; break;
      case 2: err = "Invalid Term!"; break;
      case 3: err = "Invalid Year! (ex: 2013)"; break;
      case 4: err = "Supervisor field cannot be left blank!"; break;
      case 5: err = "Invalid Grade! (ex: A+)"; break;
      case 6: err = "Lecturer field cannot be left blank!"; break;
      default: err = "Incorrect Fields!"; break;
    }
  Gtk::MessageDialog message(appWindow, 
    "Error: " + err, false, Gtk::MESSAGE_ERROR );
  message.run();
}

// Write to application file that it has been accepted
int Controller::acceptApplication(std::string& path)
{
  int         fileLength = io.getFileLength(path);
  std::string z[fileLength];
  std::string appRef;

  if(io.getFromFile(path, z, fileLength)==0)
  {
    appRef = z[0];
    std::string temp = "Accepted";
    z[3] = temp;
    
    io.sendToFile(path, z, fileLength);
    closeApplications(appRef);
    return 0;
  }
  return 1;
}

// Find all of the applicants other applications so we can close them
void Controller::closeApplications(const std::string& appRef)
{
  DIR           *d;
  std::string    q;
  std::string a = "applications/";
  string file = "data/courses";
  struct dirent *dir;

  int fileLength = io.getFileLength(file);
  std::string s[fileLength];
  sumWindow.clear();

  io.getFromFile(file, s, fileLength);

  for(int i = 0; i < fileLength; i++) 
  {
    if(s[i].compare("/0") == 0)
      break;
    std::string temp = ("applications/" + s[i]);
    d = opendir(temp.c_str());

    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        q = dir->d_name;
        if(q.compare(appRef) == 0) {

          temp = "applications/" + s[i] + "/" + q;    
          closeApplication(temp);

        }  
      }
      closedir(d);
    }
  }
}

// Close the application
void Controller::closeApplication(const std::string& path)
{
  int fileLength = io.getFileLength(path);
  if(fileLength == 0)
    return;

  std::string s[fileLength];
  io.getFromFile(path, s, fileLength);
  if(s[3].compare("Pending") == 0)
  {
    s[3] = "Closed";
    io.sendToFile(path, s, fileLength);
  }
}

bool Controller::getIsGrad() {return isGrad;}

void Controller::viewApplications(Application* a)
{
  if(a == 0)
    return;

  app = a;
  isGrad = false;
  Glib::ustring u = "";
  std::string s[8];
  a->getApplicant()->toStrings(s, 8);
  std::cout << s[0] << std::endl;
  stuWindow.popUp(s, 8, true);
  appWindow.popUp(u, true, true);
}

void Controller::viewNextApplication()
{
  Application* a = view.getApplication(++appWindow.application);
  
  if(a == 0)
  {
    --appWindow.application;
    return;
  }
  viewApplications(a);
}

void Controller::viewPrevApplication()
{
  if(appWindow.application > 0)
    viewApplications(view.getApplication(--appWindow.application));
}

void Controller::viewApplication(int i)
{
  appWindow.application = i;
  if(view.getApplication(i) != 0)
    viewApplications(view.getApplication(i));
}
