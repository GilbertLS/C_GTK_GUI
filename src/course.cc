/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Course Model
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "course.h"

Course::Course() 
{

}

Course::Course(std::string s[], int n)
{
  createFromStrings(s, n);
}

Course::~Course()
{
}

int Course::createFromStrings(std::string s[], int n)
{
  if(setName(s[0])){return 1;}
  if(setTerm(s[1])){return 2;}
  if(setYear(atoi(s[2].c_str()))){return 3;}

  if(n == 4) {
    if(setSupervisor(s[3])){return 4;}
  }
  else if (n == 5){
    if(setGrade(s[3])){return 5;}
    if(setLecturer(s[4])){return 6;}
  }
  else if (n == COURSE_NUM_ATTRIBUTES) {
    int i = 0;
    if(setSupervisor(s[4])){i = 4;}
    if(setGrade(s[3])){i =  5;}
    if(setLecturer(s[5])){i = 6;}

    if(i != 0)
      return i;
  }

  return 0;
}

int Course::setName(const std::string& s) 
{

  if(s.length() < 8 || s.length() > 9)
    return 1;

  name = s;
  return 0;
}

int Course::setTerm(const std::string& s) 
{
  if(s.length() == 0)
    return 1;

  term = s;
  return 0;
}

int Course::setYear(int i)
{
  if(i <= 1900)
    return 1;

  year = i;
  return 0;
}

int Course::setGrade(const std::string& s)
{
  if(s.length() == 0 || s.length() > 2 || (s[0]!='A' && s[0]!='B' && s[0]!='C' && s[0]!='D' && s[0]!='F'))
    return 1;

  grade = s;
  return 0;
}

int Course::setSupervisor(const std::string& s)
{
  if(s.length() == 0)
    return 1;

  supervisor = s;
  return 0;
}

int Course::setLecturer(const std::string& s) 
{
  if(s.length() == 0)
    return 1;

  lecturer = s;
  return 0;
}

int Course::toStrings(std::string s[], int n) {
  if(n < COURSE_NUM_ATTRIBUTES)
    return 1;

  std::stringstream stream;
  
  s[0] = name;
  s[1] = term;
  stream << year;
  s[2] = stream.str();
  stream.str("");
  s[3] = grade;
  s[4] = supervisor;
  s[5] = lecturer;


  return 0;
}
