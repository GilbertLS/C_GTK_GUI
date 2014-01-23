/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Created by constructor. Displays different containers.
 *
 * Last Modified: Mar 22, 2013
 *
 */

#include "mainwindow.h"
#include "controller.h"
#include <iostream>

MainWindow::MainWindow(Controller *c)
: stuButton("Student"),
  facButton("Faculty"),
  appButton("Apply"),
  bacButton("Back"),
  selButton("View All"),
  genButton("Edit General Info"),
  modButton("Edit Application"),
  viewButton("View"),
  viewAppButton("Find Application"),
  box(Gtk::ORIENTATION_VERTICAL),
  homeBox(Gtk::ORIENTATION_HORIZONTAL),
  classBox(Gtk::ORIENTATION_HORIZONTAL),
  buttonBox(Gtk::ORIENTATION_VERTICAL),
  cuLogo("images/logo1.png"),
  list("data/courses"),
  findWindow(),
  findButton1("Search"),
  findButton2("Search"),
  findButton3("Search"),
  label1("Find by application #:"),
  label2("Find by student #:"),
  label3("Find by student name:")
{
  controller = c;

  // Fill list from file of courses
  controller->getIO(io);
  list.getFromFile(io);

  // Window Properties
  set_title("cuTAES");
  set_default_size(400, 300);
  set_border_width(10);

  // homeBox
  homeBox.set_spacing(5);
  stuButton.set_size_request(50, 25);
  facButton.set_size_request(50, 25);
  homeBox.pack_start(stuButton);
  homeBox.pack_start(facButton);

  // classBox
  appButton.set_size_request(100, 50);
  bacButton.set_size_request(100, 50);
  selButton.set_size_request(100, 50);
  genButton.set_size_request(100, 50);
  viewButton.set_size_request(100, 50);
  modButton.set_size_request(100, 50);
  viewAppButton.set_size_request(100, 50);
  classBox.set_spacing(5);
  classBox.pack_start(list);
  classBox.pack_start(buttonBox, Gtk::PACK_SHRINK);
  buttonBox.set_spacing(5);
  buttonBox.pack_start(appButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(viewButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(selButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(genButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(modButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(viewAppButton, Gtk::PACK_SHRINK);
  buttonBox.pack_start(bacButton, Gtk::PACK_SHRINK);
  classBox.show_all();

  // The main box
  box.set_spacing(5);
  box.pack_start(cuLogo, Gtk::PACK_SHRINK);
  box.pack_start(homeBox);

  // Add Widgets to window
  add(box);

  // Show all widgets
  show_all();

  // Find window
  findWindow.set_title("View Application");
  findWindow.set_default_size(200, 100);
  findWindow.set_border_width(10);
  findWindow.set_modal(true);
  findWindow.set_resizable(false);
  findWindow.add(findGrid);
  findGrid.add(label1);
  findGrid.attach(entry1, 0, 1, 1, 1);
  findGrid.attach(findButton1, 1, 1, 1, 1);
  findGrid.attach(label2, 0, 2, 1, 1);
  findGrid.attach(entry2, 0, 3, 1, 1);
  findGrid.attach(findButton2, 1, 3 ,1 ,1);
  findGrid.attach(label3, 0, 4, 1, 1);
  findGrid.attach(entry3, 0, 5, 1, 1);
  findGrid.attach(findButton3, 1, 5, 1, 1);

  startEvents();
}

MainWindow::~MainWindow()
{
}

void MainWindow::startEvents()
{
    // MainWindow - Home screen signal handlers
  stuButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::stuButtonClicked));
  facButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::facButtonClicked));

  // MainWindow - course list screen signal handlers
  appButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::appButtonClicked));
  bacButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::bacButtonClicked));
  selButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::selButtonClicked));
  viewButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::viewButtonClicked));
  viewAppButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::findPopUp));

  // FindWindow
  findButton1.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::button1));
  findButton2.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::button2));
}

void MainWindow::stuButtonClicked()
{
  box.remove(homeBox);
  box.pack_start(classBox);
  selButton.hide();
  genButton.show();
  modButton.show();
  viewButton.hide();
  viewAppButton.hide();
  appButton.show();
  controller->stuButtonClicked();
}

void MainWindow::facButtonClicked()
{
  box.remove(homeBox);
  box.pack_start(classBox);
  selButton.show();
  viewButton.show();
  appButton.hide();
  viewAppButton.show();
  genButton.hide();
  modButton.hide();
}

void MainWindow::appButtonClicked()
{
  controller->appButtonClicked();
}

void MainWindow::bacButtonClicked()
{
    box.remove(classBox);
    box.pack_start(homeBox);
}

void MainWindow::selButtonClicked()
{
  controller->selButtonClicked();
}

void MainWindow::viewButtonClicked()
{
  controller->viewButtonClicked();
}

void MainWindow::findPopUp()
{
  findWindow.show_all();
  entry1.set_text("");
  entry2.set_text("");
  entry3.set_text("");
}

// Get applications by app#
void MainWindow::button1()
{
  !applications;
  !students;
  std::string s = entry1.get_text().c_str();


  findWindow.hide();
  findApplications(s);
  
  std::cout << students.getSize() << "/" << applications.getSize() << std::endl;

  if(applications.getSize() > 0)
    controller->viewApplication(0);
}

// get applications by student# or name
void MainWindow::button2()
{
  !applications;
  !students;
  std::string s = entry2.get_text().c_str();

  findWindow.hide();
  findStudent(s);
  for(int i = 0; i < students.getSize(); ++i)
  {
    std::string temp;
    students[i]->getIDStr(temp);
    std::cout << "ID " << temp << std::endl;
    findApplications(temp, students[i]);
  }

    std::cout << students.getSize() << ":" << applications.getSize() << std::endl;

  if(applications.getSize() > 0)
    controller->viewApplication(0);
}

void MainWindow::findApplications(std::string& find, Student* stu)
{
  std::string path = "applications/";
  DIR           *d;
  std::string    q;
  struct dirent *dir;
  d = opendir(path.c_str());

  if(find.length() == 0)
    return;

  int length = io->getFileLength("data/courses");
  std::string s[length];
  io->getFromFile("data/courses", s, length);

  // Iterate over every course folder
  for(int i = 0; i < length; ++i) {
    std::string file = path + s[i];
    d = opendir(file.c_str());

    // Iterate over every application
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        q = dir->d_name;
        if(q.find(".") == -1)
        {
         file = path + s[i] + "/";
         file.append(q);
         std::cout << file << std::endl;

         // Find reference in file and add application to list
         if(io->findWord(file, find) > 0) 
          {
            std::cout << "found " << q << std::endl;

            int appLength = io->getFileLength(file);
	    std::string z[appLength];
            io->getFromFile(file, z, appLength);

            if(stu == 0)
	    {
              stu = findStudent(z[1], true);
	    }

            if(stu != 0)
            {
              std::cout << "appLength: " << appLength << std::endl;
	      Application* app;
              Undergrad* u = dynamic_cast<Undergrad*> (stu);
              if(u != 0) 
              {
                app = new UApplication(z, appLength, stu);
              }
              else
                app = new GradApplication(z, appLength, stu);
              
              applications += app;
            }
          }
        }
      }
      closedir(d);
    }
  }
}

Student* MainWindow::findStudent(std::string& find, bool one)
{
  std::string path = "students/";
  Student       *stu = 0;
  DIR           *d;
  std::string    q;
  struct dirent *dir;
  d = opendir(path.c_str());

  if(find.length() == 0)
    return stu;

  // Iterate over every student
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      q = dir->d_name;
      if(q.find(".") == -1)
      {
       std::string file = path + q;
       std::cout << file << std::endl;

       int length = io->getFileLength(file);
       std::string s[length];

       io->getFromFile(file, s, length);

       // Search criteria is equal to student number, 1st name, last name, or both
       if(find.compare(q)==0 || find.compare(s[1])==0 || find.compare(s[2])==0 || find.compare(s[3])==0 || (find.find(s[2])!=-1 && find.find(s[3])!=-1)) 
        {
           std::cout << "found " << q << std::endl;
           if(s[0].compare("undergrad")==0)
           {
	     stu = new Undergrad(s+1, length-1);
           }
           else
             stu = new Grad(s+1, length-1);
     
           students += stu;

           if(one)
             return stu;
        }
      }
    }
    closedir(d);
  }

  return stu;
}

Application* MainWindow::getApplication(int i)
{
  return applications[i];
}
