#include "bdd_utils.hpp"

using namespace std;
static int sqlite_select_handler_get_list(void *void_ptr, int argc, char **argv, char **colName){
  if(argc <7){
    cerr << "select error" << endl;
    exit(2);
  }
  list<fiche> *lst_ptr = (list<fiche> *)void_ptr;
  fiche curr;
  curr.mail = string(argv[0]);
  curr.prenom = string(argv[1]);
  curr.nom = string(argv[2]);
  curr.entreprise = string(argv[3]);
  curr.telephone =  string(argv[4]);
  curr.photo = string(argv[5]);
  curr.date_creation = string(argv[6]);
  lst_ptr->push_back(curr);
  return 0;
}


list<fiche> get_fiche_list(){
  list<fiche> ret;
  sqlite3 *db;
  if(sqlite3_open(DB_NAME, &db) != 0){
    cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
    exit(1);
  }
  string sql_request = "SELECT * FROM clients;";
  if(sqlite3_exec(db, sql_request.c_str(), sqlite_select_handler_get_list, &ret, NULL) != SQLITE_OK){
    cerr << sqlite3_errmsg(db) << endl;
    exit(1);
  }
  sqlite3_close(db);
  return ret;
}
//a voir pour la gestion d'erreur
void insert_fiche(fiche *f){
  if(f->email == NULL){
    cerr << "email not define" << endl;
    exit(3);
  }
  
}
