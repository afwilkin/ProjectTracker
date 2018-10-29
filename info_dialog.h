#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <QDialog>

class info_node;

namespace Ui {
class info_dialog;
}

class info_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit info_dialog(QWidget *parent, info_node* in_node=nullptr);
    ~info_dialog();

private slots:
    void on_buttonBox_accepted();
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    Ui::info_dialog *ui;
    info_node* node_ptr;
    bool ctrl_pressed;
};

#endif // INFO_DIALOG_H
