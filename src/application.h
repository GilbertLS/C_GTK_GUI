#ifndef APPLICATION_H
#define APPLICATION_H

#define APP_NUM_ATTRIBUTES 4

#include "student.h"
#include "course.h"
#include "work.h"
#include "Queue.h"
#include <string>
#include <sstream>

enum AppStatus {PENDING, REJECTED, ACCEPTED, CLOSED};

class Application
{
  public:
    Application(const std::string&, Student*);
    Application(Student*);
    Application(std::string c[], int size, Student* s);
    virtual ~Application(){};

    void    pushCourseTA(Course*);
    Course* popCourseTA();
    Course* frontCourseTA();
    bool    isCourseTAEmpty();

    void    pushWork(Work*);
    Work*   popWork();
    Work*   frontWork();
    bool    isWorkEmpty();

    int      toStrings(std::string*, int);
    virtual  void    createFromStrings(std::string s[], int n);
    void     createFromStringss(std::string s[], int n);
    int      getIDStr(std::string&);
    void     setCourse(const std::string&);
    Student* getApplicant();

    //Overloaded operators
    Application& operator-();
    Application& operator+();

    Course* getCourseTA(int);
    Work* getWork(int);

  protected:
    void   getStatusString(string*);

    Queue<Course> coursesTA;    //Related courses TAed
    Queue<Work>   work;         //Relevant work experience
    std::string   appNum;
    std::string   course;
    AppStatus     status;
    Student*      applicant;

    void setUniqueID();
};

#endif
