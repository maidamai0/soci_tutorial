#include <exception>
#include <iostream>
#include <utility>
#include <vector>

#include "soci/into.h"
#include "soci/session.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"
#include "soci/statement.h"
#include "soci/transaction.h"
#include "soci/use.h"

void print_table() {
  std::cout << "Table: " << ktable << std::endl;
  soci::session sql(soci::sqlite3, kdbname);

  std::vector<int> ids(5);
  std::vector<std::string> names(5);

  sql << "SELECT * FROM test", soci::into(ids), soci::into(names);

  for (size_t i = 0; i < ids.size(); i++) {
    std::cout << ids[i] << ":" << names[i] << std::endl;
  }
}

int main(int argc, char** argv) {
  try {
    soci::session sql(soci::sqlite3, kdbname);
    sql << "CREATE TABLE " << ktable << " (id INTEGER, name VARCHAR(255))";

    {
      soci::transaction transaction(sql);

      int id = 0;
      std::string name;
      soci::statement stmt = (sql.prepare << "INSERT INTO " << ktable
                                          << " (id, name) VALUES (:id,:name)",
                              soci::use(id, "id"), soci::use(name, "name"));

      for (const auto& [_id, _name] : {std::make_pair(1, "Alice"),
                                       {2, "Bob"},
                                       {3, "Carol"},
                                       {4, "David"},
                                       {5, "Eve"}}) {
        id = _id;
        name = _name;
        stmt.execute(true);
      }

      std::cout << "before commit" << std::endl;
      print_table();
      transaction.commit();
    }

    std::cout << "after commit" << std::endl;
    print_table();

    sql << "DROP TABLE test";
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}