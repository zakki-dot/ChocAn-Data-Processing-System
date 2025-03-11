template <class TYPE>
Table<TYPE>::Table(): table(nullptr), table_size(TABLE_SIZE)
{
    table = new Node<TYPE>*[table_size];
    for (int i = 0; i < table_size; ++i)
    {
        table[i] = nullptr;
    }
}

template <class TYPE>
Table<TYPE>::~Table<TYPE>()
{
    for (int i = 0; i < table_size; ++i)
    {
        if (table[i])
            dealloc(table[i]);
    }

    delete [] table;
}

template <class TYPE>
Table<TYPE>::Table(const Table<TYPE> & src)
{}

template <class TYPE>
Table<TYPE> & Table<TYPE>::operator=(const Table<TYPE> & src)
{}

template <class TYPE>
int Table<TYPE>::display() const
{
    for(int i = 0; i < TABLE_SIZE; ++i){
      display(table[i]);
    }

    return 1;
}

template <class TYPE>
int Table<TYPE>::display(Node<TYPE> * head) const
{
    Node<TYPE> * current = head;

    while(current != nullptr)
    {
        current->display();
        current = current->get_next();
    }

    return 1;
}

template <class TYPE>
bool Table<TYPE>::add(TYPE & src)
{
    int ID = src.get_key();
    if (ID == -1)
        return false;

    int key = hash(ID);

    // base case if the list was already empty at this index
    if (table[key] == nullptr){ 
      table[key] = new Node<TYPE>(src);
      table[key]->set_next(nullptr);
      return true;
    }

    // case where it's already holding something.
    else{
      Node<TYPE>* temp = table[key];
      table[key] = new Node<TYPE>(src);
      table[key]->set_next(temp);
      return true;
    }

    // otherwise, something weird has happened.
    return false;
}

template <class TYPE>
int Table<TYPE>::hash(int src) const
{
    int number = src;

    return number % TABLE_SIZE;
}

template <class TYPE>
bool Table<TYPE>::remove(const string& id, const string& name)
{
  int key = 0;
  try{
    key = stoi(id);
  }
  catch(...){
    return false;
  }

  key = hash(key);
  
  return remove(table[key], name);
}

template <class TYPE>
bool Table<TYPE>::remove(Node<TYPE> *& head, const string& name)
{
  if (!head) // at the end
    return false;

  if (head->compare_name(name)) // found the person to delete
  {
    Node<TYPE> * temp = head->get_next();
    delete head;
    head = temp;
    return true;
  }

  return remove(head->get_next(), name);
}

template <class TYPE>
int Table<TYPE>::dealloc(Node<TYPE> *& head)
{
    int i = 0;

    if (!head) // if we are at the end of the list
        return i;
    
    i = 1 + dealloc(head->get_next()); // traverse to the end of the list

    // as we unwind the stack, deallocate.
    if (head)
        delete head;
    return i;
}

template <class TYPE>
bool Table<TYPE>::lookup(const string& id, const string& name)
{
  int key = 0;
  try{
    key = stoi(id);
  }
  catch(...){
    return false;
  }

  key = hash(key);

  return lookup(table[key], name);
}

template <class TYPE>
bool Table<TYPE>::lookup(Node<TYPE>* head, const string& name)
{
  if (!head) // at the end
    return false; // person not found.

  if (head->compare_name(name)) // found the person
  {
    head->display(); // display their info
    return true;
  }

  return lookup(head->get_next(), name);
}

template <class TYPE>
bool Table<TYPE>::save(const string& filename)
{
  ofstream file_out;
  if (!table) // empty hash table
    return false;

  // truncate the file
  file_out.open(filename, ios::trunc);
  file_out.close();
  // iterate each index.
  for (int i = 0; i < TABLE_SIZE; ++i){
    // save each member/provider in the lll
    save(table[i], filename);
  }
  return true;
}

template <class TYPE>
bool Table<TYPE>::save(Node<TYPE> * head, const string& filename)
{
  //ofstream file_out;
  if (!head) // at the end
    return false;

  save(head->get_next(), filename);
  // unwinding the stack
  // call the class's save function
  return head->save(filename);
}

template <class TYPE>
bool Table<TYPE>::find(TYPE &src, const string &ID, const string &name)
{
  int key = 0;
  try{
    key = stoi(ID);
  }
  catch(...){
    return false;
  }

  key = hash(key);

  return find(table[key], src, name);
}

template <class TYPE>
bool Table<TYPE>::find(Node<TYPE>* head, TYPE &src, const string& name)
{
  if (!head) // at the end
    return false;

  if (head->compare_name(name))
    return head->copy_person(src);

  return find(head->get_next(), src, name);
}

template <class TYPE>
bool Table<TYPE>::load_member(const string& filename)
{
  ifstream file_in;
  string name;
  string number;
  string address;
  string state;
  string city;
  string zipcode;
  string ID;
  bool status;
  string comments;

  file_in.open(filename);
  if (!file_in)
    return false;

  getline(file_in, name, ':');
  while(!file_in.eof())
  {
    getline(file_in, number, ':');
    getline(file_in, address, ':');
    getline(file_in, state, ':');
    getline(file_in, city, ':');
    getline(file_in, zipcode, ':');
    getline(file_in, ID, ':');
    file_in >> status;
    file_in.ignore(100, ':');
    getline(file_in, comments, '\n');

    Member member(name, number, address, state, city, zipcode, ID, status, comments);
    add(member);

    getline(file_in, name, ':');
  }

  return true;
}

template <class TYPE>
bool Table<TYPE>::load_provider(const string& filename)
{
  ifstream file_in;
  string name;
  string number;
  string address;
  string state;
  string city;
  string zipcode;
  string ID;
  string service_code;
  float fee;

  file_in.open(filename);
  if (!file_in)
    return false;

  getline(file_in, name, ':');
  while(!file_in.eof())
  {
    getline(file_in, number, ':');
    getline(file_in, address, ':');
    getline(file_in, state, ':');
    getline(file_in, city, ':');
    getline(file_in, zipcode, ':');
    getline(file_in, ID, ':');
    getline(file_in, service_code, ':');
    file_in >> fee;
    file_in.ignore(100, '\n');

    Provider provider(name, number, address, state, city, zipcode, ID, fee, service_code);
    add(provider);

    getline(file_in, name, ':');
  }

  return true;
}