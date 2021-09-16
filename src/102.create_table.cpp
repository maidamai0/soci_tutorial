#include <exception>
#include <iostream>
#include <vector>

#include "soci/into.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"
#include "soci/statement.h"

int main(int argc, char** argv) {
  // create with session simple interface
  try {
    soci::session sqlite3(soci::sqlite3, kdbname);
    sqlite3 << "create table " << ktable << "(id integer, name varchar(255))";
    sqlite3 << "drop table " << ktable;
  } catch (std::exception const& e) {
    LOGI << e.what() << std::endl;
  }

  // // create with statement
  // try {
  //   soci::session sqlite3(soci::sqlite3, kdbname);
  //   soci::statement create_stmt = sqlite3.prepare << "create table " << ktable << "(id integer, name varchar(255))";
  //   create_stmt.execute();
  //   soci::statement drop_stmt = sqlite3.prepare << "drop table " << ktable;
  //   drop_stmt.execute();
  // } catch (std::exception const& e) {
  //   LOGI << e.what() << std::endl;
  // }

  // // create with session member function
  // try {
  //   soci::session sqlite3(soci::sqlite3, kdbname);
  //   sqlite3.create_table(ktable);
  //   sqlite3.drop_table(ktable);
  // } catch (std::exception const& e) {
  //   LOGI << e.what() << std::endl;
  // }
  return EXIT_SUCCESS;
}