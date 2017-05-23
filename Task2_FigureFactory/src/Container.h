#include <stdexcept>

template<typename T>
class Container
{
public:
  Container();
  ~Container();
  Container(size_t count);
  Container(size_t count, const T & value);
  Container(const Container & constainer) = delete;
  void pop_front();
  void pop_back();
  void push_front(const T & value);
  void push_back(const T & value);
  const T & front() const;
  const T & back() const;
  T & front();
  T & back();
  size_t size() const;
  bool empty() const;
  void clear();
  class Iterator;
  Iterator begin() const;
  Iterator end() const;

private:
  class node;
  size_t m_count = 0;
  node * m_pHead = nullptr;
  node * m_pBack = nullptr;
};

//===============node implementation=======================

template<typename T>
class Container<T>::node
{
public:
  node();
  node *& next();
  node *& prev();
  const node *& next() const;
  const node *& prev() const;
  T & data();
  const T & data() const;

private:
  T m_data = T();
  node * m_pNext = nullptr;
  node * m_pPrev = nullptr;
};

template<typename T>
Container<T>::node::node()
{
}

template<typename T>
typename Container<T>::node *& Container<T>::node::next()
{
  return m_pNext;
}

template<typename T>
typename Container<T>::node *& Container<T>::node::prev()
{
  return m_pPrev;
}

template<typename T>
const typename Container<T>::node *& Container<T>::node::next() const
{
  return m_pNext;
}

template<typename T>
const typename Container<T>::node *& Container<T>::node::prev() const
{
  return m_pPrev;
}

template<typename T>
typename T & Container<T>::node::data()
{
  return m_data;
}

template<typename T>
const typename T & Container<T>::node::data() const
{
  return m_data;
}

//===============Container implementation========================

template<typename T>
Container<T>::Container()
{
}

template<typename T>
Container<T>::~Container()
{
  clear();
}

template<typename T>
Container<T>::Container(size_t count)
{
  for (; 0 < count; --count)
  {
    push_back(T());
  }
}

template<typename T>
Container<T>::Container(size_t count, const T & value)
{
  for (; 0 < count; --count)
  {
    push_back(value);
  }
}

template<typename T>
void Container<T>::pop_front()
{
  if (!empty())
  {
    if (1 != size())
    {
      auto pDummy = m_pHead->next();
      delete m_pHead;
      m_pHead = nullptr;
      --m_count;
      m_pHead = pDummy;
      m_pHead->prev() = nullptr;
    }
    else
    {
      delete m_pHead;
      m_pBack = nullptr;
      m_pHead = nullptr;
      --m_count;
    }
  }
}

template<typename T>
void Container<T>::pop_back()
{
  if (!empty())
  {
    if (1 != size())
    {
      auto pDummy = m_pBack->prev();
      delete m_pBack;
      m_pBack = nullptr;
      --m_count;
      m_pBack = pDummy;
      m_pBack->next() = nullptr;
    }
    else
    {
      delete m_pBack;
      m_pBack = nullptr;
      m_pHead = nullptr;
      --m_count;
    }
  }
}

template<typename T>
void Container<T>::push_front(const T & value)
{
  auto pDummy = new node;
  pDummy->data() = value;
  if (!empty())
  {
    pDummy->next() = m_pHead;
    m_pHead->prev() = pDummy;
  }
  else
  {
    m_pBack = pDummy;
  }
  m_pHead = pDummy;
  ++m_count;
}


template<typename T>
void Container<T>::push_back(const T & value)
{
  auto pDummy = new node;
  pDummy->data() = value;
  if (!empty())
  {
    pDummy->prev() = m_pBack;
    m_pBack->next() = pDummy;
  }
  else
  {
    m_pHead = pDummy;
  }
  m_pBack = pDummy;
  ++m_count;
}

template<typename T>
const T & Container<T>::front() const
{
  if (empty())
  {
    throw std::out_of_range("Container is empty!\r\n");
  }
  return m_pHead->data();
}

template<typename T>
const T & Container<T>::back() const
{
  if (empty())
  {
    throw std::out_of_range("Container is empty!\r\n");
  }
  return m_pBack->data();
}

template<typename T>
T & Container<T>::front()
{
  if (empty())
  {
    throw std::out_of_range("Container is empty!\r\n");
  }
  return m_pHead->data();
}

template<typename T>
T & Container<T>::back()
{
  if (empty())
  {
    throw std::out_of_range("Container is empty!\r\n");
  }
  return m_pBack->data();
}

template<typename T>
size_t Container<T>::size() const
{
  return m_count;
}

template<typename T>
bool Container<T>::empty() const
{
  return 0 == m_count;
}

template<typename T>
void Container<T>::clear()
{
  while (!empty())
  {
    pop_front();
  }
}

//===============Iterator implementation====================
template<typename T>
class Container<T>::Iterator
{
public:
  Iterator(node * pnode);
  Iterator() = delete;
  ~Iterator();
  void operator++();
  bool operator!=(const Iterator & iter) const;
  bool operator==(const Iterator & iter) const;
  T & operator*();
  const T & operator*() const;
  T * operator->();
  const T * operator->() const;

private:
  node * m_pnode = nullptr;
};

template<typename T>
typename Container<T>::Iterator Container<T>::begin() const
{
  return Iterator(m_pHead);
}

template<typename T>
typename Container<T>::Iterator Container<T>::end() const
{
  return Iterator(nullptr);
}

template<typename T>
Container<T>::Iterator::Iterator(node * pnode)
{
  m_pnode = pnode;
}


template<typename T>
Container<T>::Iterator::~Iterator()
{
}

template<typename T>
void Container<T>::Iterator::operator++()
{
  if (m_pnode)
  {
    m_pnode = m_pnode->next();
  }
}

template<typename T>
bool Container<T>::Iterator::operator!=(const typename Container<T>::Iterator & right) const
{
  return !(m_pnode == right.m_pnode);
}

template<typename T>
bool Container<T>::Iterator::operator==(const typename Container<T>::Iterator & right) const
{
  return (m_pnode == right.m_pnode);
}

template<typename T>
T & Container<T>::Iterator::operator*()
{
  if (!m_pnode)
  {
    throw std::out_of_range("Element doesn't exist!\r\n");
  }
  return m_pnode->data();
}

template<typename T>
const T & Container<T>::Iterator::operator*() const
{
  if (!m_pnode)
  {
    throw std::out_of_range("Element doesn't exist!\r\n");
  }
  return m_pnode->data();
}

template<typename T>
T * Container<T>::Iterator::operator->()
{
  if (!m_pnode)
  {
    throw std::out_of_range("Element doesn't exist!\r\n");
  }
  return &m_pnode->data();
}

template<typename T>
const T * Container<T>::Iterator::operator->() const
{
  if (!m_pnode)
  {
    throw std::out_of_range("Element doesn't exist!\r\n");
  }
  return &m_pnode->data();
}