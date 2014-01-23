/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Utility class used for input/output
 *
 * Last Modified: Mar 8, 2013
 *
 */

#include "io.h"
using namespace std;

IO::IO()
{

}

int IO::appendToFile(const std::string& f, std::string* s, int size) 
{
  char text[MAX_BUF];

  ofstream outFile(f.c_str(), ios::app);

  if (!outFile) 
  {
    return 0;
  }

  for (int i = 0; i < size; i++)
    outFile << s[i] << endl;

  return 1;
}

int IO::sendToFile(const std::string& f, std::string* s, int size) 
{
  char text[MAX_BUF];

  ofstream outFile(f.c_str(), ios::out);

  if (!outFile) 
  {
    return 0;
  }

  for (int i = 0; i < size; i++)
    outFile << s[i] << endl;

  return 1;
}

int IO::getFromFile(const string& f, string* s, int size) 
{
  int count = 0;
  char text[MAX_BUF];
  ifstream inf(f.c_str(), ios::in);

  if (!inf)
    return 1;
  

  while (!inf.eof() && count < size) 
  {
    inf.getline(text, MAX_BUF);
    s[count] = text;
    count++;
  }

  if(count < size)
    s[count-1] = "/0";

  return 0;
}

int IO::getFileLength(const string& f)
{
  int counter = 0;
  std::string line;
  std::ifstream myfile(f.c_str(), ios::in);

  while (std::getline(myfile, line))
    ++counter;

  return counter;
}

int IO::findWord(std::string& filename, std::string& keyword)
{
  std::string line;
  ifstream in(filename.c_str());

  if(in.is_open())
  {
    while(getline(in,line))
    {
      if(line.find(keyword) != std::string::npos)
        return 1;
    }
  }

  return 0;
}
