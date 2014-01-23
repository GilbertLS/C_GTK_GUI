/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Application Model
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "uapplication.h"
#include <iostream>


UApplication::UApplication(std::string c[], int size, Student* s) : Application(s)
{
  applicant = s;
  createFromStrings(c, size);
}

UApplication::UApplication(const std::string& c, Student* s) : Application(c, s) { }

UApplication::~UApplication()
{
  while(!isCourseTakenEmpty())
    delete(popCourseTaken());
  while(!isCourseTAEmpty())
    delete(popCourseTA());
  while(!isWorkEmpty())
    delete(popWork());
}

//Interfaces for the queue data members
void UApplication::pushCourseTaken(Course* c)
{
  coursesTaken.pushBack(c); 
}

Course* UApplication::popCourseTaken()
{
  return coursesTaken.popFront();
}

Course* UApplication::frontCourseTaken()
{
  return coursesTaken.front();
}

bool UApplication::isCourseTakenEmpty()
{
  return coursesTaken.empty();
}

void UApplication::createFromStrings(std::string s[], int n)
{
  int i = 0;
  Course* c = 0;
  Work* w = 0;
  for(int k = 0; k < n; k++)
    std::cout << "uapp printing: " << s[k] << std::endl;

  // Add courses taken from file
  for(i = 4; i < n; ++i) {
    if(s[i].compare("---") == 0)
    {
      std::cout << "end of classes taken" << std::endl;
      i++;
      break;
    }

 std::cout << s[i] << "  out if" << std::endl;

    if(s[i].compare("") != 0) 
    {
      std::cout << s[i] << "  in if" << std::endl;
      c = new Course();
      int j = c->createFromStrings(&s[i], COURSE_NUM_ATTRIBUTES);
      std::cout << "ERROR " << j << std::endl;
      pushCourseTaken(c);
      c = 0;
      i += COURSE_NUM_ATTRIBUTES-1;
      std::cout << s[i] << "  is after class" << std::endl;
    }
  }

  Application::createFromStringss(&s[i], n-i);

}

Course* UApplication::getCourseTaken(int i)
{
  return coursesTaken[i];
}
