#pragma once
#include "class.h"

#define MEMBER_FILE "list_of_members.txt"
#define PROVIDER_FILE "list_of_providers.txt"

// This header file contains the hash table data structure

template <class TYPE> // the node class.
class Node {
public:
  Node<TYPE>();
  ~Node<TYPE>();
  Node<TYPE>(const TYPE &src);
  // Node<TYPE> &operator=(const Node<TYPE> &src);

  // functions for LLL collision operations
  Node<TYPE> *&get_next();
  void set_next(Node<TYPE> *src);

  bool display() const;
  bool compare_name(const string &name);
  bool save(const string &filename);
  // bool load(const string &filename);
  bool copy_person(TYPE &src);

private:
  TYPE person;
  Node<TYPE> *next;
};

template <class TYPE> // hash table ADT class
class Table {
public:
  Table<TYPE>();
  ~Table<TYPE>();
  Table<TYPE>(const Table<TYPE> &src);
  Table<TYPE> &operator=(const Table<TYPE> &src);

  int display() const;     // function to display all people in the table
  bool add(TYPE &src);     // Function to add people to the table
  int hash(int src) const; // takes in a string to hash (aka, the ID number).
  bool remove(const string &id,
              const string &name); // removing a member or provider
  bool lookup(const string &id,
              const string &name); // function to lookup a specific member.

  bool save(const string &filename); // function to save list of
                                     // members/providers into a text file

  bool find(TYPE &src, const string &ID, const string &name);
  bool load_member(const string &filename);
  bool load_provider(const string &filename);

private:
  // wrapper functions for recursions
  bool remove(Node<TYPE> *&head, const string &id);
  int display(Node<TYPE> *head) const;
  int dealloc(Node<TYPE> *&head); // for deallocating hash table
  bool lookup(Node<TYPE> *head, const string &id);
  bool save(Node<TYPE> *head, const string &filename);
  bool find(Node<TYPE> *head, TYPE &src, const string &name);
  // bool load(Node<TYPE> *head, const string &filename);

  Node<TYPE> **table;
  int table_size;
};

#include "node.tpp"
#include "table.tpp"