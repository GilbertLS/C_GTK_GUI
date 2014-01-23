#ifndef SUMLIST_H
#define SUMLIST_H

#include <gtkmm.h>
#include "modelcolumns.h"
#include "selectlist.h"
#include "io.h"
#include <dirent.h>
#include <sstream>
#include <string>

class SumList : public SelectList
{

  public:
    SumList(const std::string&);
    void getFormatFromFile(IO*);
    void getApplications(IO*, const std::string&);
    void printToFile(IO*, std::string&);

  private:
    int gradSort(const Gtk::TreeModel::iterator& a, const Gtk::TreeModel::iterator& b);
    int sortString(const std::string&, const std::string&);

};

#endif
