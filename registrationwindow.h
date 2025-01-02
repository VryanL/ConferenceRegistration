#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

#include "registrationlist.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "userinfodialog.h"

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();
    void updateTable() const;

private:
    Person *person;
    QTableWidget *tableOfRegisters;
    QPushButton *registerB;
    QPushButton *findB;
    QLineEdit *searchEdit;
    RegistrationList rList;
    QComboBox *combAtt;
    QComboBox *feeBox;

private slots:
    void addRegistration();
    void findPerson();
    void textChage();
    void numberAttendees();
    void calculateFee();

};
#endif // REGISTRATIONWINDOW_H
