#ifndef __FINDER__
#define __FINDER__
#include "Movie.h"
#include <iostream>
#include <string>
#include <list>
#include "Object.h"
using namespace std;

typedef list<Movie> ListMovie;

class Finder {
DECLEAR_DYNCRT_BASE(Finder)
DECLEAR_DYNCRT_CLASS(Finder, Finder)
public:
    Finder();
    virtual ~Finder();
    virtual void setFilePath(std::string filePath) {}
    virtual ListMovie* loadAll() { return NULL; }
    virtual void showAll() {}

};

class MovieFinder : public Finder {
DECLEAR_DYNCRT_CLASS(MovieFinder, Finder)
private:
    std::string m_strPath;
public:
    MovieFinder() {
        std::cout<<"Constructure MovieFinder...."<<std::endl;
    }

    MovieFinder(std::string strPath) {
        this->m_strPath = strPath;
    }

    void setFilePath(std::string filePath) {
        this->m_strPath = filePath;
    }

    virtual ~MovieFinder() {};

    ListMovie* loadAll();
    void showAll();
};
#endif
