#ifndef FORMM_H
#define FORMM_H

#define MAX_ENTRIES 10

#include <gtkmm.h>
#include <string>
#include "io.h"

class Form : public Gtk::ScrolledWindow
{

  public:
    Form(const std::string&);
    void getFormatFile(IO*);
    void getEntries(std::string*, int*);
    void clear();
    void createFromStrings(std::string* s, int size);
    void hideEntry(int);

  private:
    Gtk::Grid   gridLayout;
    Gtk::Label  labels[MAX_ENTRIES];
    Gtk::Entry  entries[MAX_ENTRIES];
    std::string	listFile;
    int entriesNum;
};

#endif
