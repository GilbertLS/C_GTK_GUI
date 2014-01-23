/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Undergrad derived from student class. Models a undergrad student.
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "undergrad.h"

Undergrad::Undergrad()
{
}
Undergrad::Undergrad(std::string s[], int n)
{
  createFromStrings(s, n);
}

int Undergrad::setYearStanding(int i)
{
  if(i <= 0 || i > 4)
    return 1;
  else
    yearStanding = i;

  return 0;
}

int Undergrad::setMajor(const std::string& s)
{
  if(s.length() == 0)
    return 1;
  else
    major = s;
  return 0;
}

int Undergrad::setCgpa(int i)
{
  if(i <= 0)
    return 1;
  else
    cgpa = i;

  return 0;
}

int Undergrad::setGpa(int i)
{
  if(i <= 0 || i > 12)
    return 1;
  else
    gpa = i;
  
  return 0;
}

int Undergrad::createFromStrings(std::string s[], int n)
{
  if(n >= UNDERGRAD_NUM_ATTRIBUTES) {
    int i = Student::createFromStrings(s, STUDENT_NUM_ATTRIBUTES);

    if(i != 0)
      return i;

    if(setYearStanding(atoi(s[4].c_str()))) {return 5;}
    if(setMajor(s[5])) {return 6;}
    if(setCgpa(atoi(s[6].c_str()))) {return 7;}
    if(setGpa(atoi(s[7].c_str()))) {return 8;}

    setUniqueID();

    return 0;
  }
  else
    return -1;
}

int Undergrad::toStrings(std::string s[], int n) {
  if(n < UNDERGRAD_NUM_ATTRIBUTES)
    return 1;

  Student::toStrings(s, n);

  std::stringstream stream;

  stream << yearStanding;
  s[4] = stream.str();
  stream.str("");
  s[5] = major;
  stream << cgpa;
  s[6] = stream.str();
  stream.str("");
  stream << gpa;
  s[7] = stream.str();
  stream.str("");

  return 0;
}
