/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: List containing strings, created from file for the summary window. Also is scrollable.
 *
 * Last Modified: March2, 2013
 *
 */

#include "sumlist.h"

SumList::SumList(const std::string& file)
 : SelectList(file)
{

  model->set_default_sort_func (sigc::mem_fun (*this, &SumList::gradSort));
  model->set_sort_column(-1, Gtk::SORT_ASCENDING);
}

void SumList::getApplications(IO* i, const std::string& path)
{
  DIR           *d;
  std::string    s[4];
  std::string    z[9];
  std::string    q;
  struct dirent *dir;
  d = opendir(path.c_str());
  Gtk::TreeModel::Row row;

  Gtk::TreeModel::Row parent = *(model->append());
  q.assign(path.end()-9, path.end());
  parent[columns.colA] = q;

  Gtk::TreeModel::Row grad;
  Gtk::TreeModel::Row undergrad;
  bool created = false;

  //iterate over every file and directory in path
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      q = dir->d_name;
      if(q.compare("assigned") != 0 && q.find(".") == -1) {
        i->getFromFile(path + "/" + q, s, 4);
        q = "students/" + s[1];
        i->getFromFile(q, z, 9);

        // Add undergrad and grad categories for every class thats has applications
        if(!created) 
        {
          grad = *(model->append(parent.children()));
          grad[columns.colC] = "GRAD";
          undergrad = *(model->append(parent.children()));
          undergrad[columns.colC] = "UNDERGRAD";
          created = true;
        }

        // Sort applications by grad or ungrad
        if(z[0].compare("grad") == 0)
        {
          row = *(model->append(grad.children()));
          row[columns.colK] = z[5];
          row[columns.colL] = z[6];
          row[columns.colM] = z[7];
        }
        else
        {
          row = *(model->append(undergrad.children()));
          row[columns.colI] = z[7];
          row[columns.colJ] = z[8];

        }

        // Print information to correct columns
        row[columns.colA] = s[2];
        row[columns.colB] = s[0];
        row[columns.colC] = z[0];
        row[columns.colD] = s[3];
        row[columns.colE] = z[1];
        row[columns.colF] = z[2];
        row[columns.colG] = z[3];
        row[columns.colH] = z[4];

      }
      
    }

    closedir(d);
  }
    model->set_sort_column(-1, Gtk::SORT_ASCENDING);
}

// Sort the applications
int SumList::gradSort(const Gtk::TreeModel::iterator& a, 
		 const Gtk::TreeModel::iterator& b)
{
  const Gtk::TreeModel::Row row_a = *a;
  const Gtk::TreeModel::Row row_b = *b;
  std::stringstream s;
  std::stringstream z;

  if(row_a.get_value(columns.colC).compare("undergrad") == 0)
  {
    // Sort undergrad rows by CGPA
    Glib::ustring s1 = row_a.get_value(columns.colI);
    Glib::ustring s2 = row_b.get_value(columns.colI);
    int i1;
    int i2; 
    
    s << s1.raw();
    s >> i1;
    z << s2.raw();
    z >> i2;

    if(i1 > i2)
      return -1;
    else if(i1 < i2)
      return 1;
    else
    {
      // If CGPA are the same sort by last name
      s1 = row_a.get_value(columns.colG);
      s2 = row_b.get_value(columns.colG);

      return sortString(s1.raw(), s2.raw());
    }
  }
  else if (row_a.get_value(columns.colC) == "grad")
  {
      // Sort grad rows by research
      Glib::ustring s1 = row_a.get_value(columns.colK);
      Glib::ustring s2 = row_b.get_value(columns.colK);

      if(s1.compare(s2)==0)
      {
        s1 = row_a.get_value(columns.colG);
        s2 = row_b.get_value(columns.colG);

        return sortString(s1.raw(), s2.raw());
      }
      else
        return s1.compare(s2);
  }	
}

// Sort strings alphabetically
int SumList::sortString(const std::string& s1, const std::string& s2)
{
  return s1.compare(s2);
}

// Get the formatting from a file
void SumList::getFormatFromFile(IO* i)
{
  std::string s[13];
  i->getFromFile(listFile, s, 13);

  treeView.append_column(s[0], columns.colA);
  treeView.append_column(s[1], columns.colB);
  treeView.append_column(s[2], columns.colC);
  treeView.append_column(s[3], columns.colD);
  treeView.append_column(s[4], columns.colE);
  treeView.append_column(s[5], columns.colF);
  treeView.append_column(s[6], columns.colG);
  treeView.append_column(s[7], columns.colH);
  treeView.append_column(s[8], columns.colI);
  treeView.append_column(s[9], columns.colJ);
  treeView.append_column(s[10], columns.colK);
  treeView.append_column(s[11], columns.colL);
  treeView.append_column(s[12], columns.colM);
}

void SumList::printToFile(IO* i, std::string &file)
{
  Gtk::TreeModel::Children classes = model->children();
  std::string s1 = "";
  i->sendToFile(file, &s1, 1);

  // Print every class name
  for(Gtk::TreeModel::iterator iter = classes.begin(); iter != classes.end(); ++iter)
  {
    Gtk::TreeModel::Row row = *iter;
    std::string s1 = row.get_value(columns.colA) + " ";
    i->appendToFile(file, &s1, 1);

    // Print the GRAD and UNDERGRAD groups
    Gtk::TreeModel::Children groups = row.children();
    for(Gtk::TreeModel::iterator iter2 = groups.begin(); iter2 != groups.end(); ++iter2)
    {
      Gtk::TreeModel::Row row2 = *iter2;
      std::string s1 = "\t" + row2.get_value(columns.colA) + " ";
      s1.append(row2.get_value(columns.colB) + " ");
      s1.append(row2.get_value(columns.colC) + " ");
      i->appendToFile(file, &s1, 1);

      // Print every students information
      Gtk::TreeModel::Children students = row2.children();
      for(Gtk::TreeModel::iterator iter3 = students.begin(); iter3 != students.end(); ++iter3)
      {
        Gtk::TreeModel::Row row3 = *iter3;
        std::string s1 = "\t\t\t" + row3.get_value(columns.colA) + " ";
        s1.append(row3.get_value(columns.colB) + " ");
        s1.append(row3.get_value(columns.colC) + " ");
        s1.append(row3.get_value(columns.colD) + " ");
        s1.append(row3.get_value(columns.colE) + " ");
        s1.append(row3.get_value(columns.colF) + " ");
        s1.append(row3.get_value(columns.colG) + " ");
        s1.append(row3.get_value(columns.colH) + " ");
        s1.append(row3.get_value(columns.colI) + " ");
        s1.append(row3.get_value(columns.colJ) + " ");
        s1.append(row3.get_value(columns.colK) + " ");
        s1.append(row3.get_value(columns.colL) + " ");
        s1.append(row3.get_value(columns.colM) + " ");
        i->appendToFile(file, &s1, 1);
      }
    }
  }
}
