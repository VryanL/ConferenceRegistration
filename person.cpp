#include "person.h"

Person::Person(QString n, QString a, QString e)
    : m_Name(n), m_Affiliation(a), m_Email(e)
{/*intentionally empty*/}

QString Person::getName() const
{
    return m_Name;
}

QString Person::getAffiliation() const
{
    return m_Affiliation;
}

QString Person::getEmail() const
{
    return m_Email;
}

QString Person::toString()
{
    QString p = m_Name + " " + m_Affiliation + " " + m_Email;
    return p;
}


