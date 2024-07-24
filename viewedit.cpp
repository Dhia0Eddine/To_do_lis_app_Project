#include "viewedit.h"
#include "ui_viewedit.h"
#include<QEvent>
#include <QMetaType>
#include <QApplication>
#include<QWidget>
#include<QKeyEvent>
using namespace std;
ViewEdit::ViewEdit(QWidget *parent,Task *T)
    : QDialog(parent)
    , ui(new Ui::ViewEdit),T(T)
{
    ui->setupUi(this);
    ui->textEdit->setText(QString::fromStdString(T->getdescription()));
    ui->dateEdit->setDate(QDate(T->getDate().getYear(), T->getDate().getMonth(), T->getDate().getDay()));
    ui->textEdit->installEventFilter(this);
    ui->timeEdit->setTime(QTime(T->getTime().getHour(), T->getTime().getMinute(), T->getTime().getSecond()));
    ui->saveTime->setStyleSheet(
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
    ui->saveDate->setStyleSheet(
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
    ui->saveDesc->setStyleSheet(
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
    ui->saveAll->setStyleSheet(
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
    ui->Quit->setStyleSheet(
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
}


ViewEdit::~ViewEdit()
{

    delete ui;
}


void ViewEdit::on_saveDate_clicked()
{
    int year = ui->dateEdit->date().year();
    int month = ui->dateEdit->date().month();
    int day = ui->dateEdit->date().day();
    Date d(day,month,year);
    T->setDate(d);
}


void ViewEdit::on_saveTime_clicked()
{
    int houre=ui->timeEdit->time().hour();
    int minute=ui->timeEdit->time().minute();
    Time t(houre,minute);
    T->setTime(t);
}

void ViewEdit::on_saveDesc_clicked()
{
    std::string description=ui->textEdit->toPlainText().toStdString();
    T->setdescription(description);
    emit taskUpdated(T);
}


void ViewEdit::on_saveAll_clicked()
{
    on_saveDate_clicked();
    on_saveTime_clicked();
    on_saveDesc_clicked();

}

void ViewEdit::on_Quit_clicked()
{
    close();

}
void ViewEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_saveAll_clicked();
    } else {
        QDialog::keyPressEvent(event); // Call the base class implementation
    }
}
bool ViewEdit::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->textEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            on_saveDesc_clicked();
            return true; // Event is handled
        }
    }
    return QDialog::eventFilter(obj, event); // Pass the event to the base class
}
