#include "bdd_utils.hpp"

using namespace std;
int main(int argc, char const *argv[]) {
  sqlite3 *db;
  if(sqlite3_open("./db.sqlite3", &db) != 0){
    cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
    exit(1);
  }
  string sql_request = "select * from clients;";
  if(sqlite3_exec(db, sql_request.c_str(), callback) != SQLITE_OK){
    cerr << strerror(errno) << endl;
    exit(1);
  }

  return 0;
}
