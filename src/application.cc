/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Application Model
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "application.h"
#include <iostream>

Application::Application(const std::string& c, Student* s)
              : course(c), applicant(s), status(PENDING)
{
  setUniqueID();
}

Application::Application(std::string c[], int size, Student* s)
{
  createFromStrings(c, size);
  applicant = s;
}

Application::Application(Student* s)
{
  Application("course", s);
}

//Interfaces for the queue data members
void Application::pushCourseTA(Course* c)
{
  coursesTA.pushBack(c); 
}

Course* Application::popCourseTA()
{
  return coursesTA.popFront();
}

Course* Application::frontCourseTA()
{
  return coursesTA.front();
}

bool Application::isCourseTAEmpty()
{
  return coursesTA.empty();
}

void Application::pushWork(Work* w)
{
  work.pushBack(w); 
}

Work* Application::popWork()
{
  return work.popFront();
}

Work* Application::frontWork()
{
  return work.front();
}

bool Application::isWorkEmpty()
{
  return work.empty();
}

void Application::getStatusString(string* s)
{
  switch(status){
    //default:
    case PENDING:
      *s = "Pending";
      break;
    case REJECTED:
      *s = "Rejected";
      break;
    case CLOSED:
      *s = "Closed";
      break;
    case ACCEPTED:
      *s = "Accepted";
      break;
  }
}

Application& Application::operator-()
{
  status = CLOSED;
  return *this;
}

Application& Application::operator+()
{
  status = ACCEPTED;
  return *this;
}

void Application::setUniqueID() {
  std::stringstream stream;
  std::string s;
  int i;
  applicant->getIDStr(s);
  srand(atoi(course.c_str()));
  i = atoi(s.c_str());
  i *= rand() % 30 + 10000;
  stream << abs(i);
  appNum = stream.str();
}

void Application::setCourse(const std::string& s) 
{
  course = s;
}

int Application::getIDStr(std::string& s)
{
  s = appNum;

  return 0;
}

int Application::toStrings(std::string s[], int n)
{
  setUniqueID();
  std::string z;

  s[0] = appNum;
  applicant->getIDStr(z);
  s[1] = z;
  s[2] = course;
  getStatusString(&z);
  s[3] = z;
  
  n = 4;

  return 0;
}

void Application::createFromStrings(std::string s[], int n)
{
  std::cout << n << std::endl;

  if(n >= 4)
  {
    appNum    = s[0];
    course    = s[2];
    status    = PENDING;
  }

  createFromStringss(&s[4], n-4);
}

void Application::createFromStringss(std::string s[], int n)
{
  int i = 0;
  Course* c = 0;
  Work* w = 0;
  for(int k = 0; k < n; k++)
    std::cout << "printing: " << s[k] << std::endl;

  // Add courses TAed from file
  for(i = 0; i < n; ++i) {
        if(s[i].compare("---") == 0)
    {
      std::cout << "end of clases taed" << std::endl;
      i++;
      break;
    }

    if(s[i].compare("") != 0 && i + COURSE_NUM_ATTRIBUTES < n) 
    {
      std::cout << s[i] << "  in if" << std::endl;
      c = new Course();
      int j = c->createFromStrings(&s[i], COURSE_NUM_ATTRIBUTES);
      std::cout << "ERROR " << j << std::endl;
      pushCourseTA(c);
      c = 0;
      i += COURSE_NUM_ATTRIBUTES-1;
    }
  }

    // Add Work from file
  for(i; i < n; ++i) {
    if(s[i].compare("---") == 0)
    {
      std::cout << "end of work" << std::endl;
      i++;
      break;
    }

    if(s[i].compare("") != 0 && i + WORK_NUM_ATTRIBUTES < n) 
    {
      std::cout << s[i] << "  in if" << std::endl;
      w = new Work();
      int j = w->createFromStrings(&s[i], WORK_NUM_ATTRIBUTES);
      std::cout << "ERROR " << j << std::endl;
      pushWork(w);
      w = 0;
      i += WORK_NUM_ATTRIBUTES-1;
    }
  }

}

Student* Application::getApplicant()
{
  return applicant;
}

Course* Application::getCourseTA(int i)
{
  return coursesTA[i];
}

Work* Application::getWork(int i)
{
  return work[i];
}
