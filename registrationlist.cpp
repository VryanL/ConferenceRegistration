#include "registrationlist.h"

bool RegistrationList::addRegistration(Registration *r)
{
    if (!r)
        return false;

    if (m_AttendeeList.isEmpty())
    {
        m_AttendeeList.append(r);
        return true;
    }

    for (Registration* p : m_AttendeeList)
    {
        if (p->getAttendee()->getName() == r->getAttendee()->getName())
        {
            if (p->getAttendee()->getEmail() == r->getAttendee()->getEmail())
            {
                QMessageBox::warning(nullptr, "Registration Error",
                                     QString("The name: \'%1\' is already registered with the email: \'%2\'."
                                             "\nPlease use a different name or email.").
                                     arg(p->getAttendee()->getName(), p->getAttendee()->getEmail()));
                return false;
            }
        }
    }

    m_AttendeeList.append(r);
    return true;
}

RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
    m_AttendeeList.clear();
}

bool RegistrationList::isRegistered(QString n) const
{
    if (n.isEmpty())
        return false;

    for (Registration *r: m_AttendeeList)
    {
        if (r->getAttendee()->getName() == n)
            return true;
    }

    return false;
}

double RegistrationList::totalFee(QString t) const
{
    double x = 0.00;
    if (t == "All")
    {
        for (Registration *r: m_AttendeeList)
            x += r->calculateFee();
    }
    else if (t == "Registration" || t == "StudentRegistration" || t == "GuestRegistration")
    {
        for (Registration *r: m_AttendeeList)
            if (r->metaObject()->className() == t )
                x += r->calculateFee();
    }
    return x;
}

int RegistrationList::totalRegistrations(QString a) const
{
    int t = 0;
    if (a.isEmpty())
        return t;

    if (a == "Total")
    {
        t = m_AttendeeList.length();
        return t;
    }
    else if (a == "Registration" || a == "StudentRegistration" || a == "GuestRegistration")
    {
        for (Registration *r: m_AttendeeList)
        {
            if (r->metaObject()->className() == a)
                t++;
        }
        return t;
    }

    for (Registration *r: m_AttendeeList)
    {
        if (r->getAttendee()->getAffiliation() == a)
            t++;
    }

    return t;
}

QList<Registration *> RegistrationList::getAttendeeList() const
{
    return m_AttendeeList;
}


