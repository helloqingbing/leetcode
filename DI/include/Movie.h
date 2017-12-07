#ifndef __MOVIE__
#define __MOVIE__
#include <string>
#include <list>

class Movie {
    std::string m_strDictor;
    std::string m_strName;
public:
    Movie() {
        m_strDictor =  "";
        m_strName.assign("");
    }
    virtual ~Movie() {}

    std::string getStrDirector() {
        return this->m_strDictor;
    }

    std::string getStrName() {
        return this->m_strName;
    }

    void setStrDictor(std::string strDictor) {
        this->m_strDictor = strDictor;
    }

    void setStrName(std::string strName) {
        this->m_strName = strName;
    }
};
#endif
