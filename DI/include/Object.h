#ifndef __OBJECT__
#define __OBJECT__

#include <map>
#include <string>

// if we call Object::Create before _auto_register, then m_class_set is empty, it will return NULL, cause issue.

#define DECLEAR_DYNCRT_BASE(Object)  \
public: \
    typedef Object *(*ClassGen)();  \
    static Object* Create(const std::string &class_name) {  \
        std::map<std::string, ClassGen>::iterator iter = m_class_set.find(class_name); \
        if(m_class_set.end() != iter) { \
            return (iter->second)(); \
        } \
        return NULL; \
    } \
    struct _auto_register { \
        _auto_register(const std::string& class_name, ClassGen creator) { \
            m_class_set.insert(map<std::string, ClassGen>::value_type(class_name, creator)); \
            /* or m_class_set[class_name] = createor; */ \
            /* or m_class_set.insert(pair<std::string, ClassGen>(class_name, creator)) ; */ \
        } \
    }; \
    static std::map<std::string, ClassGen> m_class_set;

#define IMPLEMENT_DYNCRT_BASE(Object)  \
    std::map<string, Object::ClassGen> Object::m_class_set;

#define DECLEAR_DYNCRT_CLASS(Derived, Object) \
public: \
    static Object *Create() { \
        return (Object*)(new Derived); \
    }

#define IMPLEMENT_DYNCRT_CLASS(Derived) \
    static Derived::_auto_register _register_##Derived(#Derived,Derived::Create);

#endif
