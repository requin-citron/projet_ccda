#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include<string>
#include<iostream>

class Interaction {
private:
  std::string contenu;
  struct tm *date = new tm;
  void initDate();
  friend std::ostream& operator<<(std::ostream &os, Interaction &inte);

public:
  Interaction (std::string contenu);
  Interaction ();
  std::string getContenu();
  void setDate(struct tm &dt);
  struct tm getDate();

};

#endif
