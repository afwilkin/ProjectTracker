#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

void set_dir_path(QString path);
QString get_dir_path();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resolve->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
    //disable all actions until project file is loaded
    main_buttons_enabled(false);
    set_current_section("HOME");
    ctrl_pressed = false;
    main_buttons_access = false;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

    //make sure that our data structure is clean
    map.clear();

    main_buttons_enabled(true);

}

void MainWindow::on_actionOpen_triggered()
{

    //get the last file location
    QString last_dir = get_dir_path();

    //prompt the user for a file
    QString filename =  QFileDialog::getOpenFileName(this,"Select a file",last_dir,"Text files (*.txt)");

    set_dir_path(filename);

    //call function to load file into our data structure
    map.load_file(filename);

    //enable the buttons if everything is loaded alright
    if(map.is_loaded()){
        main_buttons_enabled(true);
    }

    map.print_map(cout);

}

void MainWindow::on_actionSave_triggered()
{
    QString last_dir = get_dir_path();
    QString filename = QFileDialog::getSaveFileName(this,"Save your file",last_dir,"Text files (*.txt)");
    set_dir_path(filename);
    map.write_to_file(filename);


}

void MainWindow::main_buttons_enabled(bool enabled){

    ui->questions_button->setEnabled(enabled);
    ui->notes_button->setEnabled(enabled);
    ui->resources_button->setEnabled(enabled);
    ui->todo_button->setEnabled(enabled);

    main_buttons_access = enabled;

}


void MainWindow::on_todo_button_clicked()
{
    if(main_buttons_access){
        //make sure Listview is clear
        ui->listWidget->clear();
        load_listwidget("TODO");
    }

}

void MainWindow::on_notes_button_clicked()
{
    if(main_buttons_access){
        //make sure Listview is clear
        ui->listWidget->clear();
        load_listwidget("NOTES");
    }

}

void MainWindow::on_home_button_clicked()
{
    //make sure Listview is clear
    set_current_section("HOME");
    ui->listWidget->clear();
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_questions_button_clicked()
{
    if(main_buttons_access){
        ui->listWidget->clear();
        load_listwidget("QUESTIONS");
    }
}

void MainWindow::on_resources_button_clicked()
{
    if(main_buttons_access){
        ui->listWidget->clear();
        load_listwidget("RESOURCES");
    }
}

void MainWindow::load_listwidget(string section){

    set_current_section(section);
    vector<info_node>& node_list = map.sections[current_section];
    ui->listWidget->clear();

    for(unsigned int i =0; i< node_list.size(); i++){
        ui->listWidget->addItem(QString::fromStdString(node_list[i].title));
    }

    //if need be show the "resolved" button
    if(section=="TODO" || section=="QUESTIONS"){
        ui->resolve->setVisible(true);
    }
    else{
        ui->resolve->setVisible(false);
    }

    //go to the next screen
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_add_clicked()
{
    //call make_node with "this" parameter
    info_node node_new = make_node(this);

    if(node_new.title != ""){
        map.sections[current_section].push_back(node_new);
        load_listwidget(current_section);
    }

}

void MainWindow::on_delete_2_clicked()
{

    //get the current item and delete it from the list
    vector<info_node>& node_list = map.sections[current_section];
    int selected_indx = ui->listWidget->currentRow();
    if (selected_indx != -1){
        node_list.erase(node_list.begin() + selected_indx);
        load_listwidget(current_section);
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int selected_indx = ui->listWidget->currentRow();
    vector<info_node>& node_list = map.sections[current_section];
    info_dialog edit_dialog(this,&node_list[selected_indx]);
    edit_dialog.exec();

    load_listwidget(current_section);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    //backspace
    if(e->key() == Qt::Key_Backspace){
        on_home_button_clicked();
    }

    //CTRL
    if(e->key() == Qt::Key_Control){
        ctrl_pressed = true;
    }

    //Ctrl + S
    if(e->key() == Qt::Key_S){
        if(ctrl_pressed){
            on_actionSave_triggered();
        }
    }

    //Ctrl + R
    if(e->key() == Qt::Key_R){
        if(ctrl_pressed && (current_section == "QUESTIONS" || current_section == "TODO" )){
            on_resolve_clicked();
        }
    }

    //Ctrl + N
    if(e->key() == Qt::Key_N){
        if(ctrl_pressed){
            if(current_section == "HOME"){
                on_actionNew_triggered();
            }
            else{
                on_add_clicked();
            }
        }
    }

    //delete
    if(e->key() == Qt::Key_Delete){
        on_delete_2_clicked();
    }

    //1
    if(e->key() == Qt::Key_1){
        on_todo_button_clicked();
    }

    //2
    if(e->key() == Qt::Key_2){
        on_notes_button_clicked();
    }

    //3
    if(e->key() == Qt::Key_3){
        on_questions_button_clicked();
    }

    //4
    if(e->key() == Qt::Key_4){
        on_resources_button_clicked();
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Control){
        ctrl_pressed = false;
    }

}

void MainWindow::on_resolve_clicked()
{
    string resolved_section;
    if( current_section == "TODO"){
        resolved_section = "DONE";
    }
    else{
        resolved_section = "ANSWERED";
    }

    //move the item to the other list
    vector<info_node>& current_node_list = map.sections[current_section];
    vector<info_node>& resolve_node_list = map.sections[resolved_section];
    int selected_indx = ui->listWidget->currentRow();
    resolve_node_list.push_back(*(current_node_list.begin() + selected_indx));
    current_node_list.erase(current_node_list.begin() + selected_indx);
    load_listwidget(current_section);
}

void set_dir_path(QString path){
    //create the settings object
    if(path == ""){
        return;
    }
    path = path.left(path.lastIndexOf("/"));
    QSettings settings("WilkinsAF", "Project Tracker");
    settings.setValue("global_path",path);
}

QString get_dir_path(){
    //create the settings object
    QSettings settings("WilkinsAF", "Project Tracker");
    QString retVal(settings.value("global_path","").toString());
    if(retVal == ""){
        retVal = QDir::homePath();
    }
    return retVal;
}

void MainWindow::set_current_section(string section){
    setWindowTitle(QString::fromStdString(section));
    current_section = section;
}
