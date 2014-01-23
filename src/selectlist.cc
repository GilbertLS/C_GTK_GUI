/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: List containing strings, created from file. Also is scrollable.
 *
 * Last Modified: Feb 1, 2013
 *
 */

#include "selectlist.h"

SelectList::SelectList(const std::string& file)
{
  listFile = file;

  // Window properties
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  
  // Add the treeView
  add(treeView);

  // Create and set model
  model = Gtk::TreeStore::create(columns);
  treeView.set_model(model);
}

void SelectList::getFromFile(IO* i) {
  treeView.append_column("Courses", columns.colA);
  Gtk::TreeModel::Row row;

  std::string s[MAX_ROWS];
  i->getFromFile(listFile, s, MAX_ROWS);

  for(int j = 0; j < MAX_ROWS; j++) {
    if(s[j] == "/0")
      break;

    row = *(model->append());
    row[columns.colA] = s[j];
  }
}

void SelectList::getApplications(IO* i, const std::string& path)
{
  DIR           *d;
  std::string    s[4];
  std::string    z[8];
  std::string    q;
  struct dirent *dir;
  d = opendir(path.c_str());
  Gtk::TreeModel::Row row;
  model->clear();

  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      q = dir->d_name;
      if(q.compare("assigned") != 0 && q.find(".") == -1) {
        i->getFromFile(path + "/" + q, s, 4);
        q = "students/" + s[1];
        i->getFromFile(q, z, 8);

        row = *(model->append());
        row[columns.colA] = s[0];
        row[columns.colB] = s[3];
        row[columns.colC] = z[0];
        row[columns.colD] = z[1];
        row[columns.colE] = z[2];
        row[columns.colF] = z[6];
        row[columns.colG] = z[7];
      }
      
    }

    closedir(d);
  }
  Gtk::TreeView::Column* pColumn = treeView.get_column(5);
  if(pColumn) {
    pColumn->set_sort_column(columns.colF);
    pColumn->set_sort_indicator(true);
    //pColumn->set_sort_order(Gtk::SORT_DESCENDING);
  }
}

void SelectList::getFormatFromFile(IO* i)
{
  std::string s[7];
  i->getFromFile(listFile, s, 7);

    treeView.append_column(s[0], columns.colA);
    treeView.append_column(s[1], columns.colB);
    treeView.append_column(s[2], columns.colC);
    treeView.append_column(s[3], columns.colD);
    treeView.append_column(s[4], columns.colE);
    treeView.append_column(s[5], columns.colF);
    treeView.append_column(s[6], columns.colG);
}

//get selected row column a text
int SelectList::getSelection(Glib::ustring& s) {
  Gtk::TreeModel::Row row = *treeView.get_selection()->get_selected();
  if(row) //If anything is selected
  {
    s = row.get_value(columns.colA);
    return 0;
  }
  return 1;
}

void SelectList::clear()
{
  model->clear();
}
