#ifndef INFO_NODE_H
#define INFO_NODE_H

#include <QString>
#include <QFile>
#include <string>
#include <QMainWindow>
#include <QFormLayout>
#include <QDialog>
#include <QLabel>
#include "info_dialog.h"

using std::string;

class info_node
{
public:
    info_node();
    info_node(string, string);
    string title;
    string main_info;

};

info_node make_node(QFile&);
info_node make_node(QMainWindow*);

#endif // INFO_NODE_H
