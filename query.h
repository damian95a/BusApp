#pragma once
#ifndef __QUERY__
#define __QUERY__

#include "GUI.h"
#include <pqxx/pqxx>

#include <string>
#include <sstream>
#include <codecvt>
#include <locale>

#include <algorithm>
#include <vector>

void route_q(int id1, int id2, pqxx::connection *C, printout* f);

void bus_q(int id, pqxx::connection *C, printout* f);

void timetable_q(int linia, pqxx::connection *C, printout* f);


void show_table_q(const int idx, pqxx::connection *C, printout* f);

void insert_table(int id, pqxx::connection *C, Insertion* f);

#endif