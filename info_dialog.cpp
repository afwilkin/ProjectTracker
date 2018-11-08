#include "info_dialog.h"
#include "ui_info_dialog.h"
#include "info_node.h"
#include <QKeyEvent>
#include <QDebug>

info_dialog::info_dialog(QWidget *parent, info_node* in_node) :
    QDialog(parent),
    ui(new Ui::info_dialog),
    node_ptr(in_node)
{
    ctrl_pressed = false;
    ui->setupUi(this);
    ui->title->setText(QString::fromStdString(node_ptr->title));
    ui->info->append(QString::fromStdString(node_ptr->main_info));
    ui->title->setFocus();
}

info_dialog::~info_dialog()
{
    delete ui;
}


void info_dialog::on_buttonBox_accepted()
{
    node_ptr->main_info = ui->info->toPlainText().toUtf8().constData();
    node_ptr->title = ui->title->text().toUtf8().constData();
}

void info_dialog::keyPressEvent(QKeyEvent *e){

    //if there is a ctrl+ enter we want to save
    if(e->key() == Qt::Key_Control){
        ctrl_pressed = true;
    }
    else if(e->key() == Qt::Key_Alt && ctrl_pressed){
        on_buttonBox_accepted();
        accept();
    }
    else if(e->key() == Qt::Key_Escape ){
        done(QDialog::Rejected);
    }
}

void info_dialog::keyReleaseEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Control){
        ctrl_pressed = false;
    }

}


