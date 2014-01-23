/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Work Model
 *
 * Last Modified: March 8, 2013
 *
 */

#include "work.h"

Work::Work() 
{

}

Work::Work(std::string s[], int n)
{
  createFromStrings(s, n);
}

int Work::createFromStrings(std::string s[], int n)
{
  if(n == WORK_NUM_ATTRIBUTES){
    if(setTitle(s[0])) return 1;
    if(setResponsibilities(s[1])) return 2;
    if(setStart(s[2])) return 3;
    if(setEnd(s[3])) return 4;
    return 0;
  }
  return 5;
}

int Work::setTitle(const std::string& s) 
{
  if(s.length() == 0)
    return 1;

  title = s;
  return 0;
}

int Work::setResponsibilities(const std::string& s) 
{
  if(s.length() == 0)
    return 1;

  responsibilities = s;
  return 0;
}

int Work::setStart(const std::string& s)
{
  if((int)s[0] <= 3)
    return 1;
  if((int)s[1] <= 9)
    return 1;
  if((int)s[3] <= 1)
    return 1;
  if((int)s[4] <= 9)
    return 1;
  if((int)s[6] <= 9)
    return 1;
  if((int)s[7] <= 9)
    return 1;
  if((int)s[8] <= 9)
    return 1;
  if((int)s[9] <= 9)
    return 1;
  startDate = s;
  return 0;
}

int Work::setEnd(const std::string& s)
{
  if((int)s[0] <= 3)
    return 1;
  if((int)s[1] <= 9)
    return 1;
  if((int)s[3] <= 1)
    return 1;
  if((int)s[4] <= 9)
    return 1;
  if((int)s[6] <= 9)
    return 1;
  if((int)s[7] <= 9)
    return 1;
  if((int)s[8] <= 9)
    return 1;
  if((int)s[9] <= 9)
    return 1;
  endDate = s;
  return 0;
}

int Work::toStrings(std::string s[], int n) {
  if(n < WORK_NUM_ATTRIBUTES)
    return 1;

  //std::stringstream stream;
  
  s[0] = title;
  s[1] = responsibilities;
  s[2] = startDate;
  s[3] = endDate;

  return 0;
}

