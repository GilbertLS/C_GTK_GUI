#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <stdlib.h>
#include <sstream>

#define COURSE_NUM_ATTRIBUTES 6

class Course
{

  public:
    Course();
    Course(std::string*, int);
    ~Course();
    int createFromStrings(std::string*, int);
    int setName(const std::string&);
    int setTerm(const std::string&);
    int setYear(int);
    int setGrade(const std::string&);
    int setSupervisor(const std::string&);
    int setLecturer(const std::string&);
    int toStrings(std::string* s, int);

  private:
    std::string name;
    std::string term;
    int         year;
    std::string grade;
    std::string supervisor;
    std::string lecturer;
};

#endif
