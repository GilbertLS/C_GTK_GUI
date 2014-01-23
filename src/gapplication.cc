#include "gapplication.h"

GradApplication::GradApplication(const std::string& c, Student* s) : Application(c, s) { }

GradApplication::~GradApplication()
{
  while(!isCourseTAEmpty())
    delete(popCourseTA());
  while(!isWorkEmpty())
    delete(popWork());
}

void GradApplication::createFromStrings(std::string s[], int n)
{
  std::cout << n << std::endl;

  if(n >= 4)
  {
    appNum    = s[0];
    course    = s[2];
    status    = PENDING;
  }

  Application::createFromStringss(&s[5], n-5);

}

GradApplication::GradApplication(std::string c[], int size, Student* s) : Application(s)
{
  createFromStrings(c, size);
  applicant = s;
  setUniqueID();
}
