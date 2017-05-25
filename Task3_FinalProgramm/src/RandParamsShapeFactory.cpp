#include "RandParamsShapeFactory.h"


RandParamsShapeFactory::RandParamsShapeFactory() 
  : m_generator(std::random_device()()),
  m_uniRealDistr(-100.0, 100.0)
{
}

RandParamsShapeFactory::RandParamsShapeFactory(double leftLimint, double rightLimint) 
  : m_generator(std::random_device()()),
  m_uniRealDistr(std::min(leftLimint, rightLimint),
  std::max(leftLimint, rightLimint))
{

}

RandParamsShapeFactory::~RandParamsShapeFactory()
{
  deleteCreatedShapes();
}

Shape * RandParamsShapeFactory::createPoint()
{
  auto xCoord = m_uniRealDistr(m_generator);
  auto yCoord = m_uniRealDistr(m_generator);
  Shape * pPoint = new Point(xCoord, yCoord);
  return registerShape(pPoint);
}

Shape * RandParamsShapeFactory::createCircle()
{
  Point * centerPoint = nullptr;
  Shape * pCircle = nullptr;
  try
  {
    centerPoint = createRandomPoint();
  }
  catch (const std::bad_cast & e)
  {
    pCircle = new BadShape("Bad Circle. " + std::string(e.what()) + "\r\n");
    return registerShape(pCircle);
  }
  auto radius = m_uniRealDistr(m_generator);
 
  try
  {
    pCircle = new Circle(*centerPoint, radius);
  }
  catch (const std::invalid_argument & e)
  {
    delete pCircle;
    pCircle = new BadShape("Bad Circle. " + std::string(e.what()) + "\r\n");
  }
  return registerShape(pCircle);
}

Shape * RandParamsShapeFactory::createRectangle()
{
  Point * firstPoint = nullptr;
  Point * secondPoint = nullptr;
  Shape * pRectangle = nullptr;
  try
  {
    firstPoint = createRandomPoint();
    secondPoint = createRandomPoint();
  }
  catch (const std::bad_cast & e)
  {
    pRectangle = new BadShape("Bad Rectangle. " + std::string(e.what()) + "\r\n");
    return pRectangle;
  }
  
  try
  {
    pRectangle = new Rectangle(*firstPoint, *secondPoint);
  }
  catch (const std::invalid_argument & e)
  {
    delete pRectangle;
    pRectangle = new BadShape("Bad Rectangle. " + std::string(e.what()) + "\r\n");
  }
  return registerShape(pRectangle);
}

Shape * RandParamsShapeFactory::createSquare()
{
  Point * firstPoint = nullptr;
  Point * secondPoint = nullptr;
  Shape * pSquare = nullptr;
  try
  {
    firstPoint = createRandomPoint();
    secondPoint = createRandomPoint();
  }
  catch (const std::bad_cast & e)
  {
    pSquare = new BadShape("Bad Square. " + std::string(e.what()) + "\r\n");
    return registerShape(pSquare);
  }

  try
  {
    pSquare = new Rectangle(*firstPoint, *secondPoint);
  }
  catch (const std::invalid_argument & e)
  {
    delete pSquare;
    pSquare = new BadShape("Bad Square. " + std::string(e.what()) + "\r\n");
  }
  return registerShape(pSquare);
}

Shape * RandParamsShapeFactory::createPolyline()
{
  Polyline polyLine;
  Shape * pPolyline = nullptr;

  std::uniform_int_distribution<int> uId(1, 100);
  auto nbOfPoints = uId(m_generator);
  for (int i = 0; i < nbOfPoints; ++i)
  {

    Point * newPoint = nullptr;
    try
    {
      newPoint = createRandomPoint();
    }
    catch (const std::bad_cast & e)
    {
      pPolyline = new BadShape("Bad Polyline. " + std::string(e.what()) + "\r\n");
      return  registerShape(pPolyline);
    }
    polyLine.addPoint(*newPoint);
  }

  try
  {
    pPolyline = new Polyline(polyLine);
  }
  catch (const std::invalid_argument & e)
  {
    delete pPolyline;
    pPolyline = new BadShape("Bad Polyline. " + std::string(e.what()) + "\r\n");
  }
  return registerShape(pPolyline);
}

Shape * RandParamsShapeFactory::createPolygone()
{
  Polygon polygon;
  Shape * pPolygon = nullptr;

  std::uniform_int_distribution<int> uId(1, 1000);
  auto nbOfPoints = uId(m_generator);
  for (int i = 0; i < nbOfPoints; ++i)
  {

    Point * newPoint = nullptr;
    try
    {
      newPoint = createRandomPoint();
    }
    catch (const std::bad_cast & e)
    {
      pPolygon = new BadShape("Bad Polygon. " + std::string(e.what()) + "\r\n");
      return registerShape(pPolygon);
    }
    polygon.addPoint(*newPoint);
  }
  try
  {
    polygon.finishCreating();
  }
  catch (const std::bad_cast & e)
  {
    new BadShape("Bad Polygon. " + std::string(e.what()) + "\r\n");
  }

  try
  {
    pPolygon = new Polygon(polygon);
  }
  catch (const std::invalid_argument & e)
  {
    delete pPolygon;
    pPolygon = new BadShape("Bad Polygon. " + std::string(e.what()) + "\r\n");
  }
  return registerShape(pPolygon);
}

void RandParamsShapeFactory::deleteCreatedShapes()
{
  if (m_createdShapes.empty())
  {
    return;
  }
  size_t containerSize = m_createdShapes.size();
  for (; 0 < containerSize; --containerSize)
  {
    delete m_createdShapes.front();
    m_createdShapes.pop_front();
  }
  std::cout << "Shapes deleted." << std::endl;
}

Shape *& RandParamsShapeFactory::registerShape(Shape *& pShape)
{
  m_createdShapes.push_back(pShape);
  return pShape;
}

Point * RandParamsShapeFactory::createRandomPoint()
{
  auto randomPont = dynamic_cast<Point *>(createPoint());

  if (nullptr == randomPont)
  {
    delete randomPont;
    throw std::bad_cast("Bad cast from Shape to Point.\r\n");
  }
  return randomPont;
}
