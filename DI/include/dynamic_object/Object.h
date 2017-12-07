#ifndef __C_OBJECT_H_
#define __C_OBJECT_H_

#include "ObjectFactory.h"

class CObject
{
public:
    CObject(): className("CObject") {}
    virtual ~CObject(){}
    virtual const std::string GetClassName()
    {
        return className;
    }
private:
    std::string className;
};

#endif //__C_OBJECT_H_
