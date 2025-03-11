#pragma once
#include <cctype>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// This class header file contains the inheritance hiearchy.

const int MAX = 100;       // for temporary array of chars.
const int TABLE_SIZE = 61; // prime number for hash table

// PROVIDER AND MEMBER CLASS FOR HASH TABLE

class Person // base class
{
public:
  Person();
  Person( // for the initialization list
      const string &name, const string &number, const string &address,
      const string &state, const string &city, const string &zipcode,
      const string &ID);
  ~Person();
  // Person(const Person &src); // copy constructor
  // Person &
  // operator=(const Person &src); // assignment operator (likely not needed if
  // the
  //  class has no dynamic memory)

  void display() const;
  int get_key() const;
  bool compare_name(const string &name);
  bool save(const string &filename);
  string get_name() const;
  string get_number() const;
  string get_address() const;
  string get_state() const;
  string get_city() const;
  string get_zip() const;
  string get_id() const;

protected:
  string name;
  string number;
  string address;
  string state;
  string city;
  string zipcode;
  string ID;
};

// Member subclass
class Member : public Person {
public:
  Member();
  Member(const string &name, const string &number, const string &address,
         const string &state, const string &city, const string &zipcode,
         const string &ID, bool status, const string &comments);
  ~Member();

  void display() const;
  bool save(const string &filename);
  bool get_status() const;

  /* Not needed
    string get_address();
    string get_state();
    string get_zip();
  */

private:
  bool status;     // true = active, false = suspended
  string comments; // doctor notes basically
};

// Provider subclass
class Provider : public Person {
public:
  Provider();
  Provider(const string &name, const string &number, const string &address,
           const string &state, const string &city, const string &zipcode,
           const string &ID, const float fee, const string &service_code);
  ~Provider();

  void display() const;
  bool save(const string &filename);
  float get_fee() const;
  string get_service_code() const;

private:
  string service_code;
  float fee;
};
