
#include "Base.h"
#include "Container.h"

class Shape : public virtual Printable
{
public:
  Shape();
  Shape(const Shape & shape) = delete;
  virtual ~Shape();
  static size_t GetCount();

protected:
  virtual void print(std::ostream & os) const = 0;

private:
  static size_t sm_count;
};

class BadShape : public Shape, public Named
{
public:
  BadShape() = delete;
  BadShape(const std::string & name);
  BadShape(const BadShape & badShape) = delete;
  virtual ~BadShape() = default;

private:
  virtual void print(std::ostream & os) const override;
};

class Point : public Shape, public Named
{
public:
  Point();
  virtual ~Point() = default;
  Point(double x, double y);
  Point(const Point & point);

  const double getX() const;
  const double getY() const;

  bool operator==(const Point & point) const;

protected:
  virtual void print(std::ostream & os) const override;

private:
  double m_x = 0.0;
  double m_y = 0.0;
};

class Circle : public Shape, public Named
{
public:
  Circle();
  virtual ~Circle() = default;
  Circle(const Point & center, double radius);
  Circle(const Circle & circle);

protected:
  virtual void print(std::ostream & os) const override;

private:
  Point m_center;
  double m_radius = 0.0;
  double m_area = 0.0;
};

class Rectangle : public Shape, public Named
{
public:
  Rectangle();
  virtual ~Rectangle() = default;
  Rectangle(const Point & first, const Point & second);
  Rectangle(const Rectangle & rectangle);

protected:
  virtual void print(std::ostream & os) const override;

private:
  Point m_first;
  Point m_second;
  Point m_third;
  Point m_fourth;
  double m_length = 0.0;
  double m_width = 0.0;
  double m_area = 0.0;
};

class Square : public Shape, public Named
{
public:
  Square();
  virtual ~Square() = default;
  Square(const Point & first, const Point & second);
  Square(const Square  & square);

protected:
  virtual void print(std::ostream & os) const override;

private:
  Point m_first;
  Point m_second;
  Point m_third;
  Point m_fourth;
  double m_sideLength = 0.0;
  double m_area = 0.0;
};

class Polyline : public Shape, public Named
{
public:
  Polyline();
  virtual ~Polyline() = default;
  Polyline(const Polyline  & polyline);
  void addPoint(const Point & point);

protected:
  virtual void print(std::ostream & os) const override;

private:
  void addPointImpl(const Point & point);

  Container<Point> m_aNodes;
  int m_nbSegments = 0;
  double m_length = 0.0;
};

class Polygon : public Shape, public Named
{
public:
  Polygon();
  virtual ~Polygon() = default;
  Polygon(const Polygon  & polygon);
  void addPoint(const Point & point);
  void finishCreating();

protected:
  virtual void print(std::ostream & os) const override;

private:
  void addPointImpl(const Point & point);

  Container<Point> m_aNodes;
  int m_nbSegments = 0;
  double m_perimeter = 0.0;
};