/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Student model class
 *
 * Last Modified: March 8, 2013
 *
 */

#include "student.h"

Student::Student() 
{
  created = false;
}

Student::Student(std::string s[], int n)
{
  Student();
  createFromStrings(s, n);
}

int Student::createFromStrings(std::string s[], int n)
{
  if(n == STUDENT_NUM_ATTRIBUTES) {
    if(setStudentNum(atoi(s[0].c_str()))) {return 1;}
    if(setFirstName(s[1])) {return 2;}
    if(setLastName(s[2])) {return 3;}
    if(setEmail(s[3])) {return 4;}

    setUniqueID();

    return 0;
  }
  else
    return -1;
}

int Student::setStudentNum(int i) 
{
  if(i < 100000000 || i > 200000000)
    return 1;
  else
    studentNum = i;

    setUniqueID();

  return 0;
}

int Student::setFirstName(const std::string& s)
{
  if (s.length() == 0)
    return 1;
  else
    firstName = s;
  return 0;
}

int Student::setLastName(const std::string& s) 
{
  if (s.length() == 0)
    return 1;
  else
    lastName = s;
  return 0;
}

int Student::setEmail(const std::string& s)
{
  int i = 0;
  i = s.find("@cmail.carleton.ca");
  i += s.find("@carleton.ca");
  if (i < -1)
    return 1;
  else
    email = s;
  return 0;
}

bool Student::isCreated()
{
  return created;
}

void Student::setCreated()
{
  created = true;
}

int Student::getIDStr(std::string& s)
{
  s = uniqueID;
  return 0;
}

void Student::setUniqueID() {
  std::stringstream stream;
  long i;

  srand(1892342);
  i = studentNum * 1000;
  i *= abs(rand() % 30 + 10000);
  stream << i;
  uniqueID = stream.str();
}

int Student::toStrings(std::string s[], int n) {
  if(n < STUDENT_NUM_ATTRIBUTES)
    return 1;

  std::stringstream stream;
  
  stream << studentNum;
  s[0] = stream.str();
  stream.str("");
  s[1] = firstName;
  s[2] = lastName;
  s[3] = email;

  return 0;
}
