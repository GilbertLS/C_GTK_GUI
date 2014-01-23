#ifndef SELECTIONLIST_H
#define SELECTIONLIST_H

#define MAX_ROWS 20

#include <gtkmm.h>
#include "modelcolumns.h"
#include "io.h"
#include <dirent.h>

class SelectList : public Gtk::ScrolledWindow
{

  public:
    SelectList();
    SelectList(const std::string&);
    void getFromFile(IO*);
    int  getSelection(Glib::ustring& s);
    void getApplications(IO* i, const std::string&);
    void getFormatFromFile(IO* i);
    void clear();
    ModelColumns columns;
    Gtk::TreeView                treeView;

  protected:
    Glib::RefPtr<Gtk::TreeStore> model;
    std::string			 listFile;
};

#endif
