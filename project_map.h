#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "info_node.h"
#include "vector"
#include <memory>
#include <QFile>
#include <iostream>
#include <unordered_map>
#include <string>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;
using std::string;
using std::pair;
using std::endl;
using std::ostream;


class project_map
{
public:
    project_map();

    unordered_map<string,vector<info_node>> sections;

    void clear();
    void load_file(QString);
    bool is_loaded();
    void print_map(ostream&);

private:
    bool loaded;

};

#endif // PROJECT_MAP_H
