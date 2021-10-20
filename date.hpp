#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>

class Date {
    private:
        tm *d;
    public:
        Date();
        Date(std::string s);
        ~Date();
        int day() const;
        int mon() const;
        int year() const;
        int hour() const;
        int min() const;
        int sec() const;
        std::string print() const;
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
