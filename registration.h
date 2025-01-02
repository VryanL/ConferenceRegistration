#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "person.h"
#include <QDate>
#include <QString>

#include <QObject>

class Registration : public QObject
{
    Q_OBJECT

public:
    static const double STANDARD_FEE;

    Registration(Person* a);
    Person *getAttendee() const;
    QDate getBookingDate() const;
    virtual double calculateFee() const;
    virtual QString toString() const;

private:
    Person* m_Attendee;
    QDate m_BookingDate;
};

#endif // REGISTRATION_H
