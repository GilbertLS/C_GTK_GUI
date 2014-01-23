#ifndef UNDERGRAD_H
#define UNDERGRAD_H

#include "student.h"
#include <string>
#include <stdlib.h>
#include <sstream>

#define UNDERGRAD_NUM_ATTRIBUTES 8

class Undergrad : public Student
{

  public:
    Undergrad();
    Undergrad(std::string*, int);
    int createFromStrings(std::string*, int);
    int setYearStanding(int);
    int setMajor(const std::string&);
    int setCgpa(int);
    int setGpa(int);
    int toStrings(std::string*, int);

  private:
    int         yearStanding;
    std::string major;
    int         cgpa;
    int         gpa;
    
};

#endif
