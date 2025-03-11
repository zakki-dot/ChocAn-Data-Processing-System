#pragma once
#include "table.h"

#define DIRECTORY "provider_directory.txt"
#define RECORDS "service_records.txt"
#define MEMBERS "list_of_members.txt"
#define PROVIDERS "list_of_providers.txt"

struct Service {
  string code;
  string description;
  double fee;
};

void provider_terminal(Table<Member> &members, Table<Provider> &providers);
void manager_terminal(Table<Member> &members, Table<Provider> &providers);
void check_in(Table<Member> &members, Table<Provider> &providers,
              Provider provider);
vector<string> split(const string &s, char delimiter);
Service find_service(const string &target);
bool remove_provider(Table<Provider> &providers);
bool add_provider(Table<Provider> &providers);
void run_report();
bool add_member(Table<Member> &members);
bool remove_member(Table<Member> &members);
void display_services();
void display_file(string filename);
bool validate_admin_creds(const string &user, const string &pass);