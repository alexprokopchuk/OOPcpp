#include "Shapes.h"

#include<algorithm>
#include<random>

class RandParamsShapeFactory
{
public:
  RandParamsShapeFactory();
  RandParamsShapeFactory(double leftLimint, double rightLimint);
  RandParamsShapeFactory(const RandParamsShapeFactory & factory) = delete;
  ~RandParamsShapeFactory();

  Shape * createPoint();
  Shape * createCircle(); 
  Shape * createRectangle();
  Shape * createSquare();
  Shape * createPolyline();
  Shape * createPolygone();

private:

  Shape *& registerShape(Shape *& pShape);
  Point * createRandomPoint();

  Container<Shape *> m_createdShapes;
  std::mt19937 m_generator;
  std::uniform_real_distribution<double> m_uniRealDistr;
};