#ifndef HISTLOCAL_HPP
#define HISTLOCAL_HPP
#include <list>
#include <string>
#include <time.h>
#include "tag.hpp"
#include "contact.hpp"
#include "interaction.hpp"

#define CHANGE_LAST_NAME 1
#define CHANGE_FIRST_NAME 2
#define CHANGE_ENTREPRISE_NAME 3
#define CHANGE_MAIL 4
#define CHANGE_PHONE 5
#define CHANGE_PATH_PICTURE 6
#define CHANGE_DATE 7
#define ADD_INTERACTION 8
#define DELETE_INTERACTION 9

#define CHANGE_CONTENUE 10
#define ADD_TAG 11
#define DELETE_TAG 12


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
