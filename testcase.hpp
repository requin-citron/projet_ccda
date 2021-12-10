#ifndef TESTCASE_HPP
#define TESTCASE_HPP

#include <unistd.h>
#include "date.hpp"
#include "tagList.hpp"
#include "contact.hpp"
#include "contactCatalog.hpp"
#include "window.hpp"

void showHist(ContactCatalog *cata);
void showHist(Contact *conta);
void showHist(Interaction *inte);
void showTodo(std::pair<std::string,Date*>* magie);
void showAll(std::list<Contact*>* magie);
void contactShowInteraction(Contact *conta);
void contactInteractionTestCase(TagList *tags_lst);
void InteractionEraseTag();
void tagListTestCase();
void tagListEraseAllTagsTestCase();
void testHistLocal();
void testCatalog();
void testDate();
void testTodo();
void testDBSave();
void testDBImport();
void testJsonSave();
void runTestsCase();

#endif // TESTCASE_HPP
