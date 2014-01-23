#ifndef UAPPLICATION_H
#define UAPPLICATION_H

#define UAPP_NUM_ATTRIBUTES 4

#include "student.h"
#include "course.h"
#include "work.h"
#include "application.h"
#include "Queue.h"
#include <string>
#include <sstream>

class UApplication : public Application
{
  public:
    UApplication(const std::string&, Student*);
    UApplication(Student*);
    UApplication(std::string c[], int size, Student* s);
    ~UApplication();

    void    pushCourseTaken(Course*);
    Course* popCourseTaken();
    Course* frontCourseTaken();
    bool    isCourseTakenEmpty();

    //int     toStrings(std::string*, int);
    void    createFromStrings(std::string s[], int n);

    Course* getCourseTaken(int i);

  protected:
    Queue<Course> coursesTaken;    //Related courses taken
};

#endif
