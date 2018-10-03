#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    //disable all actions until project file is loaded
    main_buttons_enabled(false);
    current_section = "";

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

    //prompt the user for a file
    QString filename =  QFileDialog::getOpenFileName(this,"Select a file","","Text files (*.txt)");

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
    QString filename = QFileDialog::getSaveFileName(this,"Save your file","","Text files (*.txt)");
    map.write_to_file(filename);


}

void MainWindow::on_actionOverview_triggered()
{

}

void MainWindow::on_actionCollect_Resources_triggered()
{

}

void MainWindow::main_buttons_enabled(bool enabled){

    ui->questions_button->setEnabled(enabled);
    ui->notes_button->setEnabled(enabled);
    ui->resources_button->setEnabled(enabled);
    ui->todo_button->setEnabled(enabled);

}


void MainWindow::on_todo_button_clicked()
{
    //make sure Listview is clear
    ui->listWidget->clear();
    load_listwidget("TODO");

}

void MainWindow::on_notes_button_clicked()
{
    //make sure Listview is clear
    ui->listWidget->clear();
    load_listwidget("NOTES");

}

void MainWindow::on_questions_button_clicked()
{
    ui->listWidget->clear();
    load_listwidget("QUESTIONS");
}

void MainWindow::on_resources_button_clicked()
{
    ui->listWidget->clear();
    load_listwidget("RESOURCES");
}

void MainWindow::load_listwidget(string section){

    current_section = section;
    vector<info_node>& node_list = map.sections[current_section];
    ui->listWidget->clear();

    for(unsigned int i =0; i< node_list.size(); i++){
        ui->listWidget->addItem(QString::fromStdString(node_list[i].title));
    }

    //go to the next screen
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_add_clicked()
{
    //call make_node with "this" parameter
    info_node node_new = make_node(this);
    map.sections[current_section].push_back(node_new);
    load_listwidget(current_section);

}

void MainWindow::on_delete_2_clicked()
{

    //get the current item and delete it from the list
    vector<info_node>& node_list = map.sections[current_section];
    int selected_indx = ui->listWidget->currentRow();
    node_list.erase(node_list.begin() + selected_indx);
    load_listwidget(current_section);


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
    if(e->key() == Qt::Key_Backspace){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

