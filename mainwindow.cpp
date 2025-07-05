#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMetaType>
#include <QApplication>

using namespace std;

Q_DECLARE_METATYPE(std::shared_ptr<Task>)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Tasks = new TaskManager();
    Tasks->loadFromFile("save.txt");

    for (const auto& taskPtr : Tasks->getAllTasks()) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(taskPtr->getdescription()), ui->Items_List);
        item->setData(Qt::UserRole, QVariant::fromValue(taskPtr));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        ui->Items_List->addItem(item);
        TS.push_back(taskPtr); // Add to TS vector
    }

    connect(ui->Items_List, &QListWidget::itemDoubleClicked, this, &MainWindow::itemDoubleClicked);
    ui->itemText->installEventFilter(this);
    ui->Add->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(73, 147, 220);"
        "    color: #000000;"
        "    font-family: 'Times New Roman', serif;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 15px;"
        "    border: 1px solid #000000;"
        "    padding: 5px 10px;"
        "    box-shadow: 2px 2px 5px #888888;"
        "}"
        "QPushButton:hover {"
        "    background-color: #9370DB;"
        "    color: #ffffff;"
        "}"
        );
    ui->clearAll->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(73, 147, 220);"
        "    color: #000000;"
        "    font-family: 'Times New Roman', serif;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 15px;"
        "    border: 1px solid #000000;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #9370DB;"
        "    color: #ffffff;"
        "}"
        );
    ui->remove->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(73, 147, 220);"
        "    color: #000000;"
        "    font-family: 'Times New Roman', serif;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 15px;"
        "    border: 1px solid #000000;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #9370DB;"
        "    color: #ffffff;"
        "}"
        );
    ui->Items_List->setStyleSheet(
        "QListWidget {"
        "    background-color: #3F384A;"
        "    color: #ffffff;"
        "    font-family: 'Times New Roman', serif;"
             "font-style: italic;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "    border-radius: 15px;"
        "    border: 1px solid #000000;"
        "    padding: 5px 10px;"
        "}"
        "QListWidget:hover {"
        "    background-color: #9370DB;"
        "    color: #ffffff;"
        "}");
    ui->itemText->setStyleSheet(
        "QTextEdit {"
        "    background-color: rgb(85, 170, 255);"
        "    color: #ffffff;"
        "    font-family: 'Times New Roman', serif;"
        "font-style: italic;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "    border-radius: 15px;"
        "    border: 1px solid #000000;"
        "    padding: 5px 10px;"
        "caret-color: red;"
        "}"
        "QTextEdit:hover {"
        "    background-color: #9370DB;"
        "    color: #ffffff;"
        "caret-color: red;"
        "}");


}

MainWindow::~MainWindow()
{
    Tasks->clear(); // Ensure TaskManager is cleared before adding tasks
    for (const auto& taskPtr : TS) {
        Tasks->addTask(taskPtr);
    }
    Tasks->saveToFile("save.txt");
    delete ui;
    delete Tasks;
}

void MainWindow::on_Add_clicked()
{
    auto T = std::make_shared<Task>();
    T->setdescription(ui->itemText->toPlainText().toStdString());
    TS.push_back(T);
    QListWidgetItem *item = new QListWidgetItem(ui->itemText->toPlainText(), ui->Items_List);
    item->setData(Qt::UserRole, QVariant::fromValue(T));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);

    ui->Items_List->addItem(item);
    ui->itemText->clear();
    ui->itemText->setFocus();
}

void MainWindow::on_remove_clicked()
{
    QList<QListWidgetItem*> itemsToRemove;
    for (int i = 0; i < ui->Items_List->count(); ++i) {
        QListWidgetItem* item = ui->Items_List->item(i);
        if (item->checkState() == Qt::Checked) {
            itemsToRemove.append(item);
        }
    }

    for (QListWidgetItem* item : itemsToRemove) {
        auto T = item->data(Qt::UserRole).value<std::shared_ptr<Task>>();
        if (T) {
            Tasks->removeTask(*T); // Remove the task from TaskManager
            TS.erase(std::remove(TS.begin(), TS.end(), T), TS.end()); // Remove from TS vector
        }
        delete item; // Delete the item from QListWidget
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->itemText && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            on_Add_clicked();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::itemDoubleClicked(QListWidgetItem* item)
{
    auto T = item->data(Qt::UserRole).value<std::shared_ptr<Task>>();
    if (T) {
        view_edit_dialog = new ViewEdit(this, T.get());
        connect(view_edit_dialog, &ViewEdit::taskUpdated, [this, item, T](Task* updatedTask) {
            // Update TaskManager
            Tasks->removeTask(*T); // Remove the old task
            *T = *updatedTask; // Update the shared_ptr content
            Tasks->addTask(T); // Add the updated task

            // Update QListWidgetItem
            item->setText(QString::fromStdString(T->getdescription()));
            item->setData(Qt::UserRole, QVariant::fromValue(T));
        });
        view_edit_dialog->exec();
    }
}

void MainWindow::updateTask(QListWidgetItem* item, std::shared_ptr<Task> T)
{
    item->setText(QString::fromStdString(T->getdescription()));
}

void MainWindow::on_clearAll_clicked()
{
    ui->Items_List->clear();
    TS.clear();
    Tasks->clear();
}
