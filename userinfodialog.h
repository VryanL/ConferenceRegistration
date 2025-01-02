#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class UserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    UserInfoDialog(QWidget *parent = nullptr);
    QString getName();
    QString getEmail();
    QString getAffiliation();
    QString getType();
    QString getExtraInfo();

private:
    QFormLayout *layout;
    QLineEdit *nameEdit;
    QLineEdit *emailEdit;
    QLineEdit *affiliationEdit;
    QComboBox *typeBox;
    QLineEdit *extraInfo;
    QLabel *info;
    bool needInfo=false;
    QDialogButtonBox *buttonBox;

private slots:
    void textCheck();
    void typeChange();
};

#endif // USERINFODIALOG_H
