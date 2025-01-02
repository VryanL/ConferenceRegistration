#include "userinfodialog.h"

UserInfoDialog::UserInfoDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Registration");
    layout = new QFormLayout(this);

    nameEdit = new QLineEdit(this);
    layout->addRow("&Name:", nameEdit);

    emailEdit = new QLineEdit(this);
    layout->addRow("&Email:", emailEdit);

    affiliationEdit = new QLineEdit(this);
    layout->addRow("&Affiliation:", affiliationEdit);

    typeBox = new QComboBox(this);
    typeBox->addItem("Registration");
    typeBox->addItem("StudentRegistration");
    typeBox->addItem("GuestRegistration");
    layout->addRow("&Type:",typeBox);

    extraInfo = new QLineEdit(this);
    info = new QLabel("");
    layout->addRow(info, extraInfo);
    extraInfo->setEnabled(false);
    extraInfo->setVisible(false);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    layout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(textCheck()));
    connect(emailEdit, SIGNAL(textChanged(QString)), this, SLOT(textCheck()));
    connect(affiliationEdit, SIGNAL(textChanged(QString)), this, SLOT(textCheck()));
    connect(extraInfo, SIGNAL(textChanged(QString)), this, SLOT(textCheck()));
    connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChange()));
    connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(textCheck()));

    setLayout(layout);
}

QString UserInfoDialog::getName()
{
    return nameEdit->text();
}

QString UserInfoDialog::getEmail()
{
    return emailEdit->text();
}

QString UserInfoDialog::getAffiliation()
{
    return affiliationEdit->text();
}

QString UserInfoDialog::getType()
{
    return typeBox->currentText();
}

QString UserInfoDialog::getExtraInfo()
{
    return extraInfo->text();
}

void UserInfoDialog::textCheck()
{
    if (!nameEdit->text().isEmpty() && !emailEdit->text().isEmpty() && !affiliationEdit->text().isEmpty())
        if (needInfo && extraInfo->text().isEmpty())
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        else
            buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    else
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void UserInfoDialog::typeChange()
{
    switch (typeBox->currentIndex()) {
    case 0:
        info->setText("");
        extraInfo->setEnabled(false);
        extraInfo->setVisible(false);
        needInfo = false;
        break;
    case 1:
        info->setText("Qualification");
        extraInfo->setEnabled(true);
        extraInfo->setVisible(true);
        needInfo = true;
        break;
    case 2:
        info->setText("Category");
        extraInfo->setEnabled(true);
        extraInfo->setVisible(true);
        needInfo = true;
        break;
    default:
        break;
    }

}
