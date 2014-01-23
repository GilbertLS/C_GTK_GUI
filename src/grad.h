#ifndef GRAD_H
#define GRAD_H

#include "student.h"
#include <string>
#include <stdlib.h>
#include <sstream>

#define GRAD_NUM_ATTRIBUTES 7

class Grad : public Student
{

  public:
    Grad();
    Grad(std::string*, int);
    int createFromStrings(std::string*, int);
    int setResearchArea(const std::string&);
    int setProgram(const std::string&);
    int setSupervisor(const std::string&);
    int toStrings(std::string*, int);

  private:
    std::string researchArea;
    std::string program;
    std::string supervisor;
    
};

#endif
