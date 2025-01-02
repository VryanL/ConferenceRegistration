#include "registrationwindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Conference Registration");
    resize(1000,500);
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayOut = new QVBoxLayout();

    tableOfRegisters = new QTableWidget();
    tableOfRegisters->setColumnCount(8);
    QStringList headers;
    headers << "Name" << "Affiliation" << "Email"  << "Fee"
            << "Booking Date" << "Type"  << "Category" << "Qualification";
    tableOfRegisters->setHorizontalHeaderLabels(headers);
    tableOfRegisters->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableOfRegisters->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *topRLayOut = new QHBoxLayout();
    registerB = new QPushButton("&Register");
    QLabel *topSaceO = new QLabel();
    QLabel *topSaceT = new QLabel();
    topRLayOut->addWidget(registerB);
    topRLayOut->addWidget(topSaceO);
    topRLayOut->addWidget(topSaceT);

    QHBoxLayout *midTopSearch = new QHBoxLayout();
    findB = new QPushButton("&Find Person");
    searchEdit = new QLineEdit();
    QLabel *midTopSace = new QLabel();
    midTopSearch->addWidget(findB,1);
    midTopSearch->addWidget(searchEdit,1);
    midTopSearch->addWidget(midTopSace,1);
    findB->setEnabled(false);

    QHBoxLayout *midTopBandCombo = new QHBoxLayout();
    QPushButton *numAttB = new QPushButton("&Number of Attendees");
    combAtt = new QComboBox();
    combAtt->addItem("Total");
    combAtt->addItem("By Affiliation");
    combAtt->addItem("Registration");
    combAtt->addItem("StudentRegistration");
    combAtt->addItem("GuestRegistration");
    QLabel *spaceMid = new QLabel();
    midTopBandCombo->addWidget(numAttB);
    midTopBandCombo->addWidget(combAtt);
    midTopBandCombo->addWidget(spaceMid);

    QHBoxLayout *comboxButtonL = new QHBoxLayout();
    feeBox = new QComboBox();
    feeBox->addItem("All");
    feeBox->addItem("Registration");
    feeBox->addItem("StudentRegistration");
    feeBox->addItem("GuestRegistration");

    QPushButton *totalFeeB = new QPushButton("&Calculate Total Fees");
    comboxButtonL->addWidget(totalFeeB);
    comboxButtonL->addWidget(feeBox);
    QLabel *space = new QLabel();
    comboxButtonL->addWidget(space);

    QSpacerItem *spacerBot = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *bottomBut = new QHBoxLayout();
    QPushButton *quitB = new QPushButton("&Quit");
    bottomBut->addSpacerItem(spacerBot);
    bottomBut->addWidget(quitB);

    mainLayOut->addWidget(tableOfRegisters,1);
    mainLayOut->addLayout(topRLayOut);
    mainLayOut->addLayout(midTopSearch);
    mainLayOut->addLayout(midTopBandCombo);
    mainLayOut->addLayout(comboxButtonL);
    mainLayOut->addLayout(bottomBut);

    mainWidget->setLayout(mainLayOut);
    setCentralWidget(mainWidget);

    connect(registerB, SIGNAL(clicked(bool)), this, SLOT(addRegistration()));
    connect(findB, SIGNAL(clicked(bool)), this, SLOT(findPerson()));
    connect(searchEdit, SIGNAL(textChanged(QString)), this, SLOT(textChage()));
    connect(searchEdit, SIGNAL(returnPressed()), findB, SLOT(click()));
    connect(numAttB, SIGNAL(clicked(bool)), this, SLOT(numberAttendees()));
    connect(totalFeeB, SIGNAL(clicked(bool)), this, SLOT(calculateFee()));
    connect(quitB, SIGNAL(clicked(bool)), this, SLOT(close()));
}

RegistrationWindow::~RegistrationWindow() {}

void RegistrationWindow::updateTable() const
{
    tableOfRegisters->clearContents();
    tableOfRegisters->setRowCount(0);
    for (const Registration* r: rList.getAttendeeList())
    {
        QStringList getR;
        getR << r->toString().split(' ', Qt::SkipEmptyParts);

        QString type = r->metaObject()->className();
        QString q = "";
        QString c = "";
        if (type == "StudentRegistration"){
            q = getR.last();
            getR.removeLast();
        }
        if (type == "GuestRegistration"){
            c = getR.last();
            getR.removeLast();
        }
        getR << type << c << q;

        int row = tableOfRegisters->rowCount();
        tableOfRegisters->insertRow(row);
        for (int i=0; i<getR.size(); i++)
        {
            QTableWidgetItem * item = new QTableWidgetItem(getR.at(i));
            item->setTextAlignment(Qt::AlignCenter);
            tableOfRegisters->setItem(row, i, item);
        }
    }
}

void RegistrationWindow::addRegistration()
{
    UserInfoDialog getUserinfo(this);
    if (getUserinfo.exec() == QDialog::Accepted)
    {
        person = new Person(getUserinfo.getName(),getUserinfo.getAffiliation(),getUserinfo.getEmail());

        if (getUserinfo.getType() == "Registration")
        {
            if (rList.addRegistration(new Registration(person))){
                QMessageBox::information(this, "Registered", QString("\'%1\' was added").arg(getUserinfo.getName()));
            }
        }
        else if (getUserinfo.getType() == "StudentRegistration")
        {
            if (rList.addRegistration(new StudentRegistration(person, getUserinfo.getExtraInfo()))){
                QMessageBox::information(this, "Registered", QString("\'%1\' was added").arg(getUserinfo.getName()));
            }
        }
        else if (getUserinfo.getType() == "GuestRegistration")
        {
            if (rList.addRegistration(new GuestRegistration(person, getUserinfo.getExtraInfo()))){
                QMessageBox::information(this, "Registered", QString("\'%1\' was added").arg(getUserinfo.getName()));
            }
        }
        updateTable();
    }
}

void RegistrationWindow::findPerson()
{
    QString gName = searchEdit->text();

    if(rList.isRegistered(gName))
        QMessageBox::information(this, "Seach result", QString("Yes, \'%1\' is registered.").arg(gName));
    else
        QMessageBox::information(this, "Seach result", QString("No, \'%1\' is not registered.").arg(gName));
    searchEdit->clear();
    registerB->setFocus();
}

void RegistrationWindow::textChage()
{
    if (searchEdit->text().isEmpty())
    {
        findB->setEnabled(false);
    }
    else
    {
        findB->setEnabled(true);
    }
}

void RegistrationWindow::numberAttendees()
{
    int total = 0;
    int i = combAtt->currentIndex();

    switch (i) {
    case 0:
    {
        total = rList.totalRegistrations("Total");
        QMessageBox::information(this, "Registered", QString("There is: %1 total registered.").arg(total));
        break;
    }
    case 1:
    {
        bool ok;
        QString gInst = QInputDialog::getText(this, "Number of attendees","Enter the Affiliation:",
                                              QLineEdit::Normal, "", &ok);
        if(ok)
        {
            total = rList.totalRegistrations(gInst);
            QMessageBox::information(this, "Registered",
                                     QString("There is: %1 registered in \'%2\'.").arg(total).arg(gInst));
        }
        break;
    }
    case 2:
    {
        total = rList.totalRegistrations("Registration");
        QMessageBox::information(this, "Registered",
                                 QString("There is: %1 registered for \'Registration\'.").arg(total));
        break;
    }
    case 3:
    {
        total = rList.totalRegistrations("StudentRegistration");
        QMessageBox::information(this, "Registered",
                                 QString("There is: %1 registered for \'StudentRegistration\'.").arg(total));
        break;
    }
    case 4:
    {
        total = rList.totalRegistrations("GuestRegistration");
        QMessageBox::information(this, "Registered",
                                 QString("There is: %1 registered for \'GuestRegistration\'.").arg(total));
        break;
    }
    default:
        break;
    }

    combAtt->setCurrentIndex(0);
    registerB->setFocus();
}

void RegistrationWindow::calculateFee()
{
    QString tFee = "R" + QString::number(rList.totalFee(feeBox->currentText()), 'f',2);
    QMessageBox::information(this, "Total fees", QString("Total fee for \'%1\' is: %2.").arg(feeBox->currentText(), tFee));
    feeBox->setCurrentIndex(0);
    registerB->setFocus();
}



