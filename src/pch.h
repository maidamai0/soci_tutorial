#pragma once

#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

constexpr auto kdbname = "test.sqlite3";
constexpr auto ktable = "test";

#define LOGI std::cout << __FILE__ << ":" << __LINE__ << ": "
#define LOGE std::cerr << __FILE__ << ":" << __LINE__ << ": "