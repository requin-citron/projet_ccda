#include "date.hpp"

Date::Date() {
    time_t tn = time(NULL);
    d = new tm(*localtime(&tn));
}

Date::Date(std::string s) : Date() {
    if (!(s[2]=='/'&&s[5]=='/')) return;
    int day = std::stoi(s.substr(0,2));
    int mon = std::stoi(s.substr(3,2))-1;
    int year = std::stoi(s.substr(6));
    std::string hour;
    std::string min;
    std::string sec;
    if (day<1||day>31||mon<0||mon>11||year<1900||year>3000) return;
    d->tm_mday = day;
    d->tm_mon = mon;
    d->tm_year = year-1900;
    if(s.length()==19){
        hour = s.substr(11);
        min = s.substr(14);
        sec = s.substr(17);
        if(hour[0]>='0' && hour[0]<='9' && min[0]>='0' && min[0]<='9' && sec[0]>='0' && sec[0]<='9'){
            d->tm_hour = std::stoi(hour);
            d->tm_min = std::stoi(min);
            d->tm_sec = std::stoi(sec);
        }
    }
}

Date::~Date(){delete this->d;}

int Date::day() const {return d->tm_mday;}
int Date::mon() const {return d->tm_mon+1;}
int Date::year() const {return d->tm_year+1900;}
int Date::hour() const {return d->tm_hour;}
int Date::min() const {return d->tm_min;}
int Date::sec() const {return d->tm_sec;}

std::string Date::print() const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day() << "/"
       << std::setfill('0') << std::setw(2) << mon() << "/" << year();
    return ss.str();
}
std::string Date::printAll() const {
    std::stringstream ss;
    ss << print() << "-" << std::setfill('0') << std::setw(2) << hour() << ":"
       << std::setfill('0') << std::setw(2) << min() << ":"
       << std::setfill('0') << std::setw(2) << sec();
    return ss.str();
}

std::ostream& operator<<(std::ostream &flux, Date const& d) {
    flux << d.printAll();
    return flux;
}
bool operator==(Date const& a, Date const& b) {return difftime(mktime(a.d),mktime(b.d))==0;}
bool operator!=(Date const& a, Date const& b) {return !(a==b);}
bool operator<(Date const& a, Date const& b) {return difftime(mktime(a.d),mktime(b.d))<0;}
bool operator>(Date const& a, Date const& b) {return !(a<b)&&a!=b;}
bool operator<=(Date const& a, Date const& b) {return a<b||a==b;}
bool operator>=(Date const& a, Date const& b) {return a>b||a==b;}
