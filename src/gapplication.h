#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#define GAPP_NUM_ATTRIBUTES 4

#include "student.h"
#include "course.h"
#include "work.h"
#include "application.h"
#include "Queue.h"
#include <string>
#include <sstream>

class GradApplication : public Application
{
  public:
    GradApplication(const std::string&, Student*);
    ~GradApplication();
    GradApplication(std::string c[], int size, Student* s);

    virtual void    createFromStrings(std::string s[], int n);
};

#endif
