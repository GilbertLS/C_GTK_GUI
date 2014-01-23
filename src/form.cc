/*
 * Code by: Gilbert Lavergne-Shank
 *	    Jordan Laforest
 *
 * Class: Form containing text entries, created from file. Also is scrollable.
 *
 * Last Modified: Mar 22, 2013
 *
 */

#include "form.h"

Form::Form(const std::string& file)
: gridLayout()
{
  listFile = file;
  
  // Window properties
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  gridLayout.set_row_homogeneous(true);
  //gridLayout.set_column_homogeneous(true);
  add(gridLayout);
  gridLayout.show_all_children();

  show_all_children();
}

void Form::getFormatFile(IO* i)
{
  entriesNum = 0;
  std::string s[MAX_ENTRIES];
  std::string d = listFile;
  i->getFromFile(d, s, MAX_ENTRIES);

  for(int j = 0; j < MAX_ENTRIES; j++) {
    if(s[j] == "/0") {
      entriesNum = j;
      break;
    }
    entriesNum = j;
  }
  for(int j = 0; j < entriesNum; j++) {
    labels[j].set_text(s[j]);
    labels[j].set_alignment(0.0, 0.5);

    gridLayout.attach(labels[j], 1, j+1 , 1, 1);
    gridLayout.attach(entries[j], 2, j+1, 1, 1);
  }
}

void Form::getEntries(std::string s[], int* n)
{
  int count = 0;
  while(count < *n && count < entriesNum) {
    s[count] = entries[count].get_text().c_str();
    count++;
  }

  *n  = count;
}

void Form::clear()
{
  for(int i = 0; i < MAX_ENTRIES; ++i)
  {
    entries[i].set_text("");
  }
}

void Form::createFromStrings(std::string* s, int size)
{
  int count = 0;
  while (count < size && count < entriesNum)
  {
    entries[count].set_text(s[count]);
    count++;
  }
}

void Form::hideEntry(int i)
{
  if (i < entriesNum)
    entries[i].hide();
}
