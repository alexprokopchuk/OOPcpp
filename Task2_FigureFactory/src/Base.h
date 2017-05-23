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
  Named(std::string name) : m_info(name)
  {
  }
  Named(const Named & name) = delete;
  virtual ~Named() = default;

protected:
  virtual void print(std::ostream & os) const override
  {
    os << m_info;
  }

private:
  std::string m_info;
};
