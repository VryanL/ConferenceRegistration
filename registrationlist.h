#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H

#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"

#include <QList>
#include <QMessageBox>

class RegistrationList
{
public:
    bool addRegistration(Registration* r);
    ~RegistrationList();
    bool isRegistered(QString n) const;
    double totalFee(QString t) const;
    int totalRegistrations(QString a) const;

    QList<Registration*> getAttendeeList() const;

private:
    QList<Registration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
