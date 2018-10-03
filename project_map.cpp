#include "project_map.h"
#include "info_node.h"
#include <QTextStream>

string LINE_DELIMETER = "--------------------";

project_map::project_map()
{

    //insantiate empty map
    sections["TODO"];
    sections["DONE"];
    sections["QUESTIONS"];
    sections["ANSWERED"];
    sections["NOTES"];
    sections["RESOURCES"];


    loaded = false;
}

void project_map::clear(){

    //shared pointers should handle the freeing of memory
    sections["TODO"].clear();
    sections["DONE"].clear();
    sections["QUESTIONS"].clear();
    sections["ANSWERED"].clear();
    sections["NOTES"].clear();
    sections["RESOURCES"].clear();

    loaded=false;
}

bool project_map::is_loaded(){
    return loaded;
}

void project_map::load_file(QString filename){

    string current_section = "";

    //load the file
    QFile file(filename);

    //while we can get a new line
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    while (!file.atEnd()) {
        string line(file.readLine());

        //grab the section
        if(line == LINE_DELIMETER){
            current_section = file.readLine();
        }
        else{
            //create the node
            info_node node = make_node(file);

            sections[current_section].push_back(node);
        }
    }

    loaded = true;
}

void project_map::print_map(ostream& cout){

    //iterate through the map
    for(auto itr = sections.begin(); itr!= sections.end(); itr++){
        //print out the section
        cout<<LINE_DELIMETER<<'\n' << itr->first<< '\n' <<LINE_DELIMETER << endl;
        //iterate through the vector
        for(int i =0; i < itr->second.size(); i++){
            auto node = itr->second[i];

            //print out the title
            cout<<node.title<<endl;

            //print out a \t and then main_info
            cout<<'\t'<<node.main_info<<endl;

        }
    }

}

void project_map::print_map(QTextStream& cout){

    //iterate through the map
    for(auto itr = sections.begin(); itr!= sections.end(); itr++){
        //print out the section
        cout<<QString::fromStdString(LINE_DELIMETER)<<'\n' << QString::fromStdString(itr->first)<< '\n' <<QString::fromStdString(LINE_DELIMETER)<< '\n';
        //iterate through the vector
        for(int i =0; i < itr->second.size(); i++){
            auto node = itr->second[i];

            //print out the title
            cout<<'-'<<QString::fromStdString(node.title)<<'\n';

            //print out a \t and then main_info
            cout<<'\t'<<'-'<<QString::fromStdString(node.main_info)<<'\n';

        }
    }

}


void project_map::write_to_file(QString filename){

    //load the file
    QFile file(filename);

    //while we can get a new line
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);
    print_map(out);

}
