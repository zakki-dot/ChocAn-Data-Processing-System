#include "class.h"

Person::Person() {}

Person::Person(const string &name, const string &number, const string &address,
               const string &state, const string &city, const string &zipcode,
               const string &ID)
    : name(name), number(number), address(address), state(state), city(city),
      zipcode(zipcode), ID(ID) {}

Person::~Person() {}

void Person::display() const {
  cout << "Name: " << name << endl;
  cout << "Phone Number: " << number << endl;
  cout << "Address: " << address << endl;
  cout << "State: " << state << endl;
  cout << "City: " << city << endl;
  cout << "Zipcode: " << zipcode << endl;
  cout << "ID Number: " << ID << endl;
}

bool Person::compare_name(const string &name) { return this->name == name; }

int Person::get_key() const {
  try {
    if (ID.size() > 0)
      return stoi(ID);
    else
      return -1;
  } catch (...) {
    return -1;
  }
}

bool Person::save(const string &filename) {
  ofstream file_out;

  file_out.open(filename, ios::app);
  if (file_out) {
    file_out << name << ':' << number << ':' << address << ':' << state << ':'
             << city << ':' << zipcode << ':' << ID << ':';
    file_out.close();
    return true;
  }

  file_out.close();
  return false;
}

string Person::get_name() const { return name; }
string Person::get_number() const { return number; }
string Person::get_address() const { return address; }
string Person::get_state() const { return state; }
string Person::get_zi0p() const { return zipcode; }
string Person::get_id() const { return ID; }
string Person::get_city() const { return city; }

Member::Member() {
  status = false;
  comments = "";
}

Member::Member(const string &name, const string &number, const string &address,
               const string &state, const string &city, const string &zipcode,
               const string &ID, bool status, const string &comments)
    : Person(name, number, address, state, city, zipcode, ID), status(status),
      comments(comments) {}

Member::~Member() {}

void Member::display() const {
  Person::display();
  cout << "Status: ";

  if (status)
    cout << "Valid" << endl;
  else
    cout << "Suspended" << endl;

  cout << "Comments: " << comments << endl;
  cout << "\n";
}

bool Member::save(const string &filename) {
  ofstream file_out;

  if (Person::save("list_of_members.txt") == false)
    return false;

  file_out.open("list_of_members.txt", ios::app);
  if (file_out) {
    file_out << status << ':' << comments << endl;
    file_out.close();
  }
  return true;
}

bool Member::get_status() const { return status; }
/*
string Member::get_address() { return address; }

string Member::get_state() { return state; }

string Member::get_zip() { return zipcode; }
*/

Provider::Provider() : fee(0.0) {}
Provider::~Provider() {}
Provider::Provider(const string &name, const string &number,
                   const string &address, const string &state,
                   const string &city, const string &zipcode, const string &ID,
                   const float fee, const string &service_code)
    : Person(name, number, address, state, city, zipcode, ID),
      service_code(service_code), fee(fee) {}

void Provider::display() const {
  Person::display();
  cout << "Service Code: " << service_code << endl;
  cout << "Fee: $" << fixed << setprecision(2) << fee << endl;
  cout << "\n";
}

bool Provider::save(const string &filename) {
  ofstream file_out;

  if (Person::save("list_of_providers.txt") == false)
    return false;

  file_out.open("list_of_providers.txt", ios::app);
  if (file_out) {
    file_out << service_code << ':' << fee << endl;
    file_out.close();
  }
  return true;
}

float Provider::get_fee() const { return fee; }
string Provider::get_service_code() const { return service_code; }
