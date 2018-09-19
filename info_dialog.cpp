#include "info_dialog.h"
#include "ui_info_dialog.h"
#include "info_node.h"

info_dialog::info_dialog(QWidget *parent, info_node* in_node) :
    QDialog(parent),
    ui(new Ui::info_dialog),
    node_ptr(in_node)
{
    ui->setupUi(this);
    ui->title->setText(QString::fromStdString(node_ptr->title));
    ui->info->append(QString::fromStdString(node_ptr->main_info));
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
