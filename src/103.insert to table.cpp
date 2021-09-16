#include <exception>
#include <iostream>
#include <vector>

#include "soci/into.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

int main(int argc, char** argv) {
  try {
    soci::session sql(soci::sqlite3, "hello.sqlite3");
    sql << "CREATE TABLE test (id INTEGER, name VARCHAR(255))";

    sql << "INSERT INTO test VALUES (1, 'Hello, World!')";
    sql << "INSERT INTO test VALUES (2, 'Hello, China!')";
    sql << "INSERT INTO test VALUES (3, 'Hello, America!')";
    sql << "INSERT INTO test VALUES (4, 'Hello, Australia!')";
    sql << "INSERT INTO test VALUES (5, 'Hello, UK!')";

    std::vector<int> ids(5);
    std::vector<std::string> names(5);

    sql << "SELECT * FROM test", soci::into(ids), soci::into(names);

    for (size_t i = 0; i < ids.size(); i++) {
      std::cout << ids[i] << ":" << names[i] << std::endl;
    }

    sql << "DROP TABLE test";

  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}