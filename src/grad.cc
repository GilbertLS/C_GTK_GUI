/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Grad derived from student class. Models a grad student.
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "grad.h"

Grad::Grad()
{

}

Grad::Grad(std::string s[], int n)
{
  createFromStrings(s, n);
}

int Grad::setResearchArea(const std::string& s)
{
  if (s.length() == 0 || s.compare("Research Area") == 0)
    return 1;
  researchArea = s;
  return 0;
}

int Grad::setProgram(const std::string& s)
{
  std::string str = s;

  //To lower case
  for (int i=0;i<str.length();i++)
  if (str[i] >= 0x41 && str[i] <= 0x5A)
    str[i] = str[i] + 0x20;

  if (str.compare("phd") != 0 && str.compare("mcs") != 0)
    return 1;
  program = str;
  return 0;
}

int Grad::setSupervisor(const std::string& s)
{
  if (s.length() == 0)
    return 1;
  supervisor = s;
  return 0;
}

int Grad::createFromStrings(std::string s[], int n)
{
  if(n >= GRAD_NUM_ATTRIBUTES) {
    int i = Student::createFromStrings(s, STUDENT_NUM_ATTRIBUTES);
    
    if(i != 0)
      return i;

    if(setResearchArea(s[6])) {return 9;}
    if(setProgram(s[4])) {return 10;}
    if(setSupervisor(s[5])) {return 11;}

    setUniqueID();

    return 0;
  }
  else
    return -1;
}

int Grad::toStrings(std::string s[], int n) {
  if(n < GRAD_NUM_ATTRIBUTES)
    return 1;

  Student::toStrings(s, n);

  std::stringstream stream;

  s[6] = researchArea;
  s[4] = program;
  s[5] = supervisor;

  return 0;
}
