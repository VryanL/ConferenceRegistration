#include "registration.h"

const double Registration::STANDARD_FEE = 200.00;

Registration::Registration(Person* a)
    : m_Attendee(a), m_BookingDate(QDate::currentDate())
{/*intentionally empty*/}

Person* Registration::getAttendee() const
{
    return m_Attendee;
}

QDate Registration::getBookingDate() const
{
    return m_BookingDate;
}

double Registration::calculateFee() const
{
    return STANDARD_FEE;
}

QString Registration::toString() const
{
    QString r = m_Attendee->toString() + " "
                + "R" + QString::number(calculateFee(), 'f', 2) + " "
                + m_BookingDate.toString(Qt::ISODate);
    return r;
}
