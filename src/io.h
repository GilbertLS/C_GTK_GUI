#ifndef IO_H
#define IO_H

#define MAX_BUF 80

#include <string>
#include <fstream>
#include <iostream>

class IO
{

  public:
    IO();
    int getFromFile(const std::string&, std::string*, int);
    int sendToFile(const std::string&, std::string*, int);
    int appendToFile(const std::string&, std::string*, int);
    int getFileLength(const std::string&);
    int findWord(std::string&, std::string&);
};

#endif
