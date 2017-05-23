#include "RandParamsShapeFactory.h"

int main()
{  
  Container<Shape *> lShapes;

  RandParamsShapeFactory * fact = new RandParamsShapeFactory;

  for (int i = 0; i < 10; ++i)
  {
    lShapes.push_back(fact->createPoint());
    lShapes.push_back(fact->createCircle());
    lShapes.push_back(fact->createRectangle());
    lShapes.push_back(fact->createSquare());
    lShapes.push_back(fact->createPolyline());
    lShapes.push_back(fact->createPolygone());
  }

  std::cout << "Number of figures: " << lShapes.size() << std::endl << std::endl;
  short counter = 0;
  for (auto & it : lShapes)
  {
    ++counter;

    std::cout << "Figure " << counter << " is the " << *it << std::endl;
  }
  std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;

  std::cout << "Delete shapes." << std::endl;

  delete fact;

  std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;

  return 0;
}