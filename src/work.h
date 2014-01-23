#ifndef WORK_H
#define WORK_H

#include <string>
#include <stdlib.h>

#define WORK_NUM_ATTRIBUTES 4

class Work
{

  public:
    Work();
    Work(std::string*, int);
    int createFromStrings(std::string*, int);
    int setTitle(const std::string&);
    int setResponsibilities(const std::string&);
    int setStart(const std::string&);
    int setEnd(const std::string&);
    int toStrings(std::string s[], int);

  private:
    std::string title;
    std::string responsibilities;
    std::string startDate;
    std::string endDate;
};

#endif
