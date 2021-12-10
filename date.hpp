#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

//! Class qui s'occupe de la gestion des dates
/*!
    elle encapsule une structure tm et fournie toutes les méthodes nécessaires pour traité avec cet objet en toute transparance et simplicité
*/
class Date {
    private:
        //! la structure tm appartenant au C
        tm *d;
        bool grand_flag=false;
    public:
        //! constructeur
        Date();
        //! constructeur dédié à la création des todos
        Date(std::string s);
        //! destructeur
        ~Date();
        //! accesseurs de l'attribut interne à tm
        int day() const;
        //! accesseurs de l'attribut interne à tm
        int mon() const;
        //! accesseurs de l'attribut interne à tm
        int year() const;
        //! accesseurs de l'attribut interne à tm
        int hour() const;
        //! accesseurs de l'attribut interne à tm
        int min() const;
        //! accesseurs de l'attribut interne à tm
        int sec() const;
        //! accesseurs de l'attribut grand
        bool grand() const;
        //! affichage simplifié avec juste la date
        std::string print() const;
        //! affichage complet avec les heures
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
