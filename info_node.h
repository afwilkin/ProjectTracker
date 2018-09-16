#ifndef INFO_NODE_H
#define INFO_NODE_H

#include <QString>
#include <QFile>
#include <string>

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

#endif // INFO_NODE_H
