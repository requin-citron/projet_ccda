#ifndef HISTLOCAL_HPP
#define HISTLOCAL_HPP
#include <list>
#include <string>
#include <time.h>
#include "contact.hpp"
#include "interaction.hpp"

#define CHANGE_LAST_NAME 1


class Contact;
class Interaction;


class HistLocal {
private:
  std::list<std::pair<std::string, struct tm>> hist_lst;

public:
  HistLocal ();
  void insertHist(Contact *conta, char flag);
  void insertHist(Contact *conta, Interaction *inte, char flag);
  std::list<std::pair<std::string, struct tm>>* getLst();
};


#endif
