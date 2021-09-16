#include "soci/connection-parameters.h"
#include "soci/session.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

constexpr auto kdbname = "test.sqlite3";

int main(int argc, char** argv) {
  // create with a connection_parameters object
  {
    soci::connection_parameters params(soci::sqlite3, kdbname);
    soci::session sqlite3(params);  // create if not exists
  }

  // create with a string
  { soci::session sqlite3(soci::sqlite3, kdbname); }
  return 0;
}