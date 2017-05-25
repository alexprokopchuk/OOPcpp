#include "realMathUtils.h"
#include "Shapes.h"

#include <algorithm>

size_t Shape::sm_count = 0;

Shape::Shape()
{
  ++sm_count;
}

Shape::~Shape()
{
  --sm_count;
}

size_t Shape::GetCount()
{
  return sm_count;
}

BadShape::BadShape(const std::string & name) : Named(name)
{
}

void BadShape::print(std::ostream & os) const
{
  Named::print(os);
}

Point::Point() : Named("Point")
{
}

Point::Point(double x, double y) 
  : Named("Point"),
  m_x(x),
  m_y(y)
{
}

Point::Point(const Point & point) 
  : Named("Point"),
  m_x(point.m_x),
  m_y(point.m_y)
{
}

const double Point::getX() const
{
  return m_x;
}

const double Point::getY() const
{
  return m_y;
}

bool Point::operator==(const Point & point) const
{
  return (m_x == point.m_x && m_y == point.m_y);
}

void Point::print(std::ostream & os) const
{
  Named::print(os);
  os << std::string(".\r\nPoint coordinates: X : ") << m_x <<
         std::string(", Y : ") <<  m_y << std::string(".\r\n");
}

Circle::Circle() 
  : Named("Circle")
{
}

Circle::Circle(const Point & center, double radius) 
  : Named("Circle"),
  m_center(center),
  m_radius(radius),
  m_area(M_PI * m_radius * m_radius)
{
  if (Mur::isNegative(m_radius))
  {
    throw std::invalid_argument("Negative radius.\r\n");
  }
  if (Mur::isZero(m_radius))
  {
    throw std::invalid_argument("Zero radius.\r\n");
  }
}

Circle::Circle(const Circle & circle) 
  : Named("Circle"),
  m_center(circle.m_center),
  m_radius(circle.m_radius),
  m_area(circle.m_area)
{
}

void Circle::print(std::ostream & os) const
{
  Named::print(os);
  os << ".\r\nCenter is " << m_center <<
         "Radius: " << m_radius << std::string(".\r\n") <<
         "Area: " << m_area << std::string(".\r\n");
}

Rectangle::Rectangle() : Named("Rectangle")
{
}

Rectangle::Rectangle(const Point & first, const Point & second) 
  : Named("Rectangle"),
  m_first(first),
  m_second(first.getX(), second.getY()),
  m_third(second),
  m_fourth(second.getX(), first.getY()),
  m_length(first.getX() - second.getX()),
  m_width(first.getY() - second.getY()),
  m_area(m_length * m_width)
{
  if (Mur::isNegative(m_length))
  {
    throw std::invalid_argument("Negative length.\r\n");
  }
  if (Mur::isZero(m_length))
  {
    throw std::invalid_argument("Zero length.\r\n");
  }
  if (Mur::isNegative(m_width))
  {
    throw std::invalid_argument("Negative width.\r\n");
  }
  if (Mur::isZero(m_width))
  {
    throw std::invalid_argument("Zero width.\r\n");
  }

}

Rectangle::Rectangle(const Rectangle & rectangle) 
  : Named("Rectangle"),
  m_first(rectangle.m_first),
  m_second(rectangle.m_second),
  m_third(rectangle.m_third),
  m_fourth(rectangle.m_fourth),
  m_length(rectangle.m_length),
  m_width(rectangle.m_width),
  m_area(rectangle.m_area)
{
}

void Rectangle::print(std::ostream & os) const
{
  Named::print(os);
  os << ".\r\nFirst corner is " << m_first <<
    "Second corner is " << m_second <<
    "Third corner is " << m_third <<
    "Fourth corner is " << m_fourth <<
    "Length: " << m_length << std::string(".\r\n") <<
    "Width: " << m_width << std::string(".\r\n") <<
    "Area: " << m_area << std::string(".\r\n");
}

Square::Square() : Named("Square")
{
}

Square::Square(const Point & first, const Point & second) 
  : Named("Square"),
  m_first(first),
  m_second(first.getX(), second.getY()),
  m_third(second),
  m_fourth(second.getX(), first.getY()),
  m_sideLength(first.getX() - second.getX()),
  m_area(m_sideLength * m_sideLength)
{
  if (Mur::isNegative(m_sideLength))
  {
    throw std::invalid_argument("Negative length.\r\n");
  }
  if (Mur::isZero(m_sideLength))
  {
    throw std::invalid_argument("Zero length.\r\n");
  }
}

Square::Square(const Square & square) 
  : Named("Square"),
  m_first(square.m_first),
  m_second(square.m_second),
  m_third(square.m_third),
  m_fourth(square.m_fourth),
  m_sideLength(square.m_sideLength),
  m_area(square.m_area)
{
}

void Square::print(std::ostream & os) const
{
  Named::print(os);
  os << ".\r\nFirst corner is " << m_first <<
    "Second corner is " << m_second <<
    "Third corner is " << m_third <<
    "Fourth corner is " << m_fourth <<
    "Side Length: " << m_sideLength << std::string(".\r\n") <<
    "Area: " << m_area << std::string(".\r\n");
}


Polyline::Polyline() : Named("Polyline")
{
}

Polyline::Polyline(const Polyline & polyline) 
  : Named("Polyline"),
  m_nbSegments(polyline.m_nbSegments),
  m_length(polyline.m_length)
{
  if (polyline.m_aNodes.empty())
  {
    throw std::invalid_argument("Polyline does not have nodes.\r\n");
  }
  for (const auto & it : polyline.m_aNodes)
  {
    m_aNodes.push_back(it);
  }
}

void Polyline::addPoint(const Point & point)
{
  try
  {
    addPointImpl(point);
  }
  catch (const std::invalid_argument & e)
  {
    std::cout << e.what();
  }
}

void Polyline::addPointImpl(const Point & point)
{
  for (const auto & it : m_aNodes)
  {
    if (it == point)
    {
      throw std::invalid_argument("Point already exist.\r\n");
    }
  }
  if (!m_aNodes.empty())
  {
    ++m_nbSegments;
    m_length += sqrt(fabs((point.getX() - m_aNodes.back().getX()) + (point.getY() - m_aNodes.back().getY())));
  }
  m_aNodes.push_back(point);
}

void Polyline::print(std::ostream & os) const
{
  Named::print(os);
  os << ".\r\nNumber of points " << m_aNodes.size() << std::string(".\r\n")
     << "Number of segments " << m_nbSegments << std::string(".\r\n")
     << "Length " << m_length << std::string(".\r\n");
}

Polygon::Polygon() : Named("Polygon")
{
}

Polygon::Polygon(const Polygon & polygon) 
  : Named("Polygon"),
  m_nbSegments(polygon.m_nbSegments),
  m_perimeter(polygon.m_perimeter)
{
  if (polygon.m_aNodes.empty())
  {
    throw std::invalid_argument("Polygon does not have nodes.\r\n");
  }
  if (3 > polygon.m_aNodes.size())
  {
    throw std::invalid_argument("Polygon does not have enough nodes.\r\n");
  }
  for (const auto & it : polygon.m_aNodes)
  {
    m_aNodes.push_back(it);
  }
}

void Polygon::addPoint(const Point & point)
{
  try
  {
    addPointImpl(point);
  }
  catch (const std::invalid_argument & e)
  {
    std::cout << e.what();
  }
}

void Polygon::finishCreating()
{
  if (3 > m_aNodes.size())
  {
    throw std::invalid_argument("Polygon does not have enough nodes.\r\n");
  }
  ++m_nbSegments;
  m_perimeter += sqrt(fabs((m_aNodes.back().getX() - m_aNodes.front().getX()) + (m_aNodes.back().getY() - m_aNodes.front().getY())));
}

void Polygon::print(std::ostream & os) const
{
  Named::print(os);
  os << ".\r\nNumber of points " << m_aNodes.size() << std::string(".\r\n")
     << "Number of segments " << m_nbSegments << std::string(".\r\n")
     << "Perimeter " << m_perimeter << std::string(".\r\n");
}

void Polygon::addPointImpl(const Point & point)
{
  for (const auto & it : m_aNodes)
  {
    if (it == point)
    {
      throw std::invalid_argument("Point already exist.\r\n");
    }
  }
  if (!m_aNodes.empty())
  {
    ++m_nbSegments;
    m_perimeter += sqrt(fabs((point.getX() - m_aNodes.back().getX()) + (point.getY() - m_aNodes.back().getY())));
  }
  m_aNodes.push_back(point);
}
