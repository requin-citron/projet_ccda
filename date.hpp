#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>

//! Class qui s'occupe de la gestion des dates
/*!
    Elle encapsule une structure tm et fournie toutes les méthodes necessaires pour traité avec cette objet en toutes transparance et simplicité.
*/
class Date {
    private:
        //! Le structure tm appartenant au C
        tm *d;
    public:
        //! Constructeur
        Date();
        //! Constructeur dédié à la création des todos
        Date(std::string s);
        //! Destructeur
        ~Date();
        //! Accesseurs de l'attribut interne à tm
        int day() const;
        //! Accesseurs de l'attribut interne à tm
        int mon() const;
        //! Accesseurs de l'attribut interne à tm
        int year() const;
        //! Accesseurs de l'attribut interne à tm
        int hour() const;
        //! Accesseurs de l'attribut interne à tm
        int min() const;
        //! Accesseurs de l'attribut interne à tm
        int sec() const;
        //! Affichage simplifié avec juste la date
        std::string print() const;
        //! Affichage complet avec les heures
        std::string printAll() const;
        friend std::ostream& operator<<(std::ostream &flux, Date const& d);
        friend bool operator==(Date const& a, Date const& b);
        friend bool operator!=(Date const& a, Date const& b);
        friend bool operator<(Date const& a, Date const& b);
        friend bool operator>(Date const& a, Date const& b);
        friend bool operator<=(Date const& a, Date const& b);
        friend bool operator>=(Date const& a, Date const& b);
};

#endif
