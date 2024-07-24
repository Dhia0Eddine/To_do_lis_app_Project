#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
#include "taskmanager.h"
#include "viewedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_Add_clicked();
    void on_remove_clicked();
    void itemDoubleClicked(QListWidgetItem* item);
    void on_clearAll_clicked();

private:
    Ui::MainWindow *ui;
    TaskManager *Tasks;
    ViewEdit *view_edit_dialog;

    void updateTask(QListWidgetItem* item, std::shared_ptr<Task> T);

    std::vector<std::shared_ptr<Task>> TS;

};

#endif // MAINWINDOW_H
