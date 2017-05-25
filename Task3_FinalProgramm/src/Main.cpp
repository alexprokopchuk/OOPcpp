#include "RandParamsShapeFactory.h"

int main()
{  
  Container<Shape *> lShapes;

  RandParamsShapeFactory factory;

  for (int i = 0; i < 10; ++i)
  {
    lShapes.push_back(factory.createPoint());
    lShapes.push_back(factory.createCircle());
    lShapes.push_back(factory.createRectangle());
    lShapes.push_back(factory.createSquare());
    lShapes.push_back(factory.createPolyline());
    lShapes.push_back(factory.createPolygone());
  }

  std::cout << "Number of figures: " << lShapes.size() << std::endl << std::endl;
  short counter = 0;
  for (auto & it : lShapes)
  {
    ++counter;

    std::cout << "Figure " << counter << " is the " << *it << std::endl;
  }
  std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;

  factory.deleteCreatedShapes();

  std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;

  return 0;
}