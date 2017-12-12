#ifndef __INJECTFINDER__
#define __INJECTFINDER__
#include "Finder.h"
#include <string>

class Container {
    Finder *m_finder;
public:
    Container() {}
    Container(std::string finderName) {
        this->m_finder = Finder::Create(finderName);
    }

    void setConfigure(std::string fileName) {
        this->m_finder->setFilePath(fileName);
    }
    virtual ~Container() { delete m_finder;}
    void showAll() {
        this->m_finder->showAll();
    }
};

#endif
