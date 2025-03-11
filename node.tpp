template <class TYPE>
Node<TYPE>::Node(): next(nullptr)
{}

template <class TYPE>
Node<TYPE>::~Node()
{
    next = nullptr;
}

template <class TYPE>
Node<TYPE>::Node(const TYPE & src)
{
    person = src;
}

/*
template <class TYPE>
Node<TYPE> & Node<TYPE>::operator=(const Node<TYPE> & src)
{
    person = src.person;
    return *this;
}*/

template <class TYPE>
Node<TYPE> *& Node<TYPE>::get_next()
{
    return next;
}

template <class TYPE>
void Node<TYPE>::set_next(Node<TYPE> * src)
{
    next = src;
}


template <class TYPE>
bool Node<TYPE>::display() const
{
  person.display();
  return true;
}

template <class TYPE>
bool Node<TYPE>::compare_name(const string& name)
{
  return person.compare_name(name);
}

template <class TYPE>
bool Node<TYPE>::save(const string& filename)
{
  return person.save(filename);
}

template <class TYPE>
bool Node<TYPE>::copy_person(TYPE& src)
{
  src = this->person;
  return true;
}