#ifndef MODEL_COLUMNS_H
#define MODEL_COLUMNS_H

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
  public:
    ModelColumns()
    { add(colA); add(colB); add(colC); add(colD); add(colE); add(colF); add(colG); add(colH); add(colI); add(colJ); add(colK); add(colL); add(colM); add(colN);}
  
    Gtk::TreeModelColumn<Glib::ustring> colA;
    Gtk::TreeModelColumn<Glib::ustring> colB;
    Gtk::TreeModelColumn<Glib::ustring> colC;
    Gtk::TreeModelColumn<Glib::ustring> colD;
    Gtk::TreeModelColumn<Glib::ustring> colE;
    Gtk::TreeModelColumn<Glib::ustring> colF;
    Gtk::TreeModelColumn<Glib::ustring> colG;
    Gtk::TreeModelColumn<Glib::ustring> colH;
    Gtk::TreeModelColumn<Glib::ustring> colI;
    Gtk::TreeModelColumn<Glib::ustring> colJ;
    Gtk::TreeModelColumn<Glib::ustring> colK;
    Gtk::TreeModelColumn<Glib::ustring> colL;
    Gtk::TreeModelColumn<Glib::ustring> colM;
    Gtk::TreeModelColumn<Glib::ustring> colN;
};

#endif
