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

    void on_todo_button_clicked();

    void on_notes_button_clicked();

    void on_questions_button_clicked();

    void on_resources_button_clicked();

    void load_listwidget(string section);

    void on_add_clicked();

    void on_delete_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_resolve_clicked();

    void on_home_button_clicked();





private:
    Ui::MainWindow *ui;
    project_map map;
    void main_buttons_enabled(bool);
    bool main_buttons_access;
    string current_section;
    void keyPressEvent(QKeyEvent *e);
    void MainWindow::keyReleaseEvent(QKeyEvent *e);
    bool ctrl_pressed;
    QString global_dir;
    void set_current_section(string section);


};

#endif // MAINWINDOW_H
