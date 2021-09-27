#include "bdd_utils.hpp"
#include "fiche_client.hpp"


using namespace std;
int main(int argc, char const *argv[]) {
  list<fiche> curr = get_fiche_list();
  for(auto it: curr){
    print_fiche(&it);
  }
  return 0;
}
