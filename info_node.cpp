#include "info_node.h"
#include <string>
using std::string;

char peek_char(QFile& file);

info_node::info_node()
{
    title = "";
    main_info = "";
}

info_node::info_node(string in_title, string in_main_info){
    title = in_title;
    main_info = in_main_info;
}

info_node make_node(QFile& file){

    //Keep grabbing until we reach the next '-' or a /t that is the main section
    string main_info="";
    string title = string(file.readLine());

    //while the next character is a /t read the line and store in the main_info section
    char delimeter = peek_char(file);

    //read the main info
    while(delimeter == '\t'){
        main_info.append(file.readLine());
        delimeter = peek_char(file);
    }

    //return the node
    return info_node(title,main_info);

}

info_node make_node(QMainWindow* window){
    //open a dialog
    info_node retVal;
    info_dialog node_getter(window,&retVal);
    node_getter.exec();

    return retVal;

}

 char peek_char(QFile& file){
    char delimeter;
    file.peek(&delimeter,1);
    return delimeter;
}
