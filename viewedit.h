#ifndef VIEWEDIT_H
#define VIEWEDIT_H

#include <QDialog>
#include"task.h"
namespace Ui {
class ViewEdit;
}

class ViewEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ViewEdit(QWidget *parent = nullptr,Task* T=nullptr);
    ~ViewEdit();

protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void taskUpdated(Task* t);
private slots:

    void on_saveDate_clicked();

    void on_saveTime_clicked();

    void on_saveDesc_clicked();

    void on_saveAll_clicked();

    void on_Quit_clicked();

private:
    Ui::ViewEdit *ui;
    Task* T;
};

#endif // VIEWEDIT_H
