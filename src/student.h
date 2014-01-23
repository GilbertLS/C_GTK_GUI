#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>

#define STUDENT_NUM_ATTRIBUTES 4

class Student
{

  public:
    Student();
    Student(std::string*, int);
    int  createFromStrings(std::string*, int);
    int  setStudentNum(int);
    int  setFirstName(const std::string&);
    int  setLastName(const std::string&);
    int  setEmail(const std::string&);
    bool isCreated();
    void setCreated();
    virtual int  toStrings(std::string*, int);

    int getIDStr(std::string&);

  protected:
    bool        created;
    int         studentNum;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string uniqueID;

    void setUniqueID();
    
};

#endif
