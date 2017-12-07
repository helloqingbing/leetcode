#include <iostream>
#include "Finder.h"
#include "Container.h"
int main()
{
    std::string str("Hello, string and list!");
    std::cout<<str<<endl;

    Container *pContainer = new Container("MovieFinder");
    pContainer->setConfigure("test.txt");
    pContainer->showAll();
    delete pContainer;

    return 0;
}
