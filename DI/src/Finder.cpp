#include <fstream>
#include "Movie.h"
#include "Finder.h"
#include "Object.h"
using namespace std;

Finder::Finder() {
}

Finder::~Finder() {
}
IMPLEMENT_DYNCRT_BASE(Finder)
IMPLEMENT_DYNCRT_CLASS(Finder)

IMPLEMENT_DYNCRT_CLASS(MovieFinder)
ListMovie* MovieFinder::loadAll() {
    ListMovie* movieList = new ListMovie;
    string item;
    if(this->m_strPath.empty()) return NULL;
    ifstream inf(this->m_strPath.c_str(), ios::in);
    Movie m;
    while(getline(inf, item, '\n')) {
        std::string strTemp(item);
        m.setStrDictor(strTemp.substr(0, strTemp.find(':')));
        m.setStrName(strTemp.substr(strTemp.find(':') + 1, strTemp.length() - 1));
        movieList->push_back(m);
    }
    inf.close();
    return movieList;
}

void MovieFinder::showAll() {
    ListMovie *movies = loadAll();
    if(movies->size() == 0) return ;
    ListMovie::iterator ite;
    int i = 1;
    for(ite = movies->begin(); ite != movies->end(); ++ite) {
        Movie mv = *ite; //Get the current item in list
        std::cout<<"Movie "<<i++<<" :"<<mv.getStrDirector()<<" - "<<mv.getStrName()<<std::endl;
    }
}

