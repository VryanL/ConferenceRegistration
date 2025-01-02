#include "guestregistration.h"

GuestRegistration::GuestRegistration(Person *a, QString q)
    : Registration(a), m_Category(q)
{/*intentionally empty*/}

double GuestRegistration::calculateFee() const
{
    return STANDARD_FEE * 0.1;
}

QString GuestRegistration::toString() const
{
    QString g = getAttendee()->toString() + " "
                + "R" + QString::number(calculateFee(),'f',2) + " "
                + getBookingDate().toString(Qt::ISODate) + " "
                + m_Category;
    return g;
}
