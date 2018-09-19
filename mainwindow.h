#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "project_map.h"
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <vector>
#include <QDialog>
#include <QListWidgetItem>
#include <QKeyEvent>


using std::cout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionOverview_triggered();

    void on_actionCollect_Resources_triggered();

    void on_todo_button_clicked();

    void on_notes_button_clicked();

    void on_questions_button_clicked();

    void on_resources_button_clicked();

    void load_listwidget(string section);

    void on_add_clicked();

    void on_delete_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    project_map map;
    void main_buttons_enabled(bool);
    string current_section;
    void keyPressEvent(QKeyEvent *e);


};

#endif // MAINWINDOW_H
