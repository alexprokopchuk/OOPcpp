#include <iostream>
#include <string>

class Printable
{
public:
  virtual ~Printable() = default;

protected:
  virtual void print(std::ostream & os) const = 0;

private:
  friend std::ostream & operator<<(std::ostream & os, const Printable & obj)
  {
    obj.print(os);
    return os;
  }
};

class Named : public virtual Printable
{
public:
  Named() = delete;
  Named(const std::string & name) : m_name(name)
  {
  }
  Named(const Named & name) = delete;
  virtual ~Named() = default;

protected:
  virtual void print(std::ostream & os) const override
  {
    os << m_name;
  }

private:
  std::string m_name;
};
