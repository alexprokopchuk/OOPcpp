#include "Container.h"
#include <iostream>
#include <string>

int main()
{
  Container<std::string> myCont(1, "world");

  myCont.push_front("Here we go!");

  std::cout << myCont.front() << std::endl;

  myCont.pop_front();

  myCont.push_back("Let's go!");

  std::cout << myCont.back() << std::endl;

  myCont.pop_back();

  std::cout << "Container size is equal " << myCont.size() << std::endl;

  std::cout << "Container is " << (myCont.empty() ? "empty." : "full.") << std::endl;

  std::cout << "Container is cleared" << std::endl;
  myCont.clear();

  std::cout << "Container size is equal " << myCont.size() << std::endl;

  std::cout << "Container is " << (myCont.empty() ? "empty." : "full.") << std::endl;

  myCont.push_back("world");
  myCont.push_front("Hello");
  myCont.push_back("!");

  std::cout << "Container size is equal " << myCont.size() << std::endl;

  std::cout << "Container is " << (myCont.empty() ? "empty." : "full.") << std::endl;

  for (const auto & it : myCont)
  {
    std::cout << it << " ";
  }
 

  return 0;
}