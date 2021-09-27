#ifndef BDD_UTILS_H
#define BDD_UTILS_H
#include <sqlite3.h>
#include <cerrno>
#include <iostream>
#include <cstring>
#include <list>
#include "fiche_client.hpp"
#define DB_NAME "./db.sqlite3"

std::list<fiche> get_fiche_list();

#endif
