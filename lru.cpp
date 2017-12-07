#include <vector>
#include <list>
#include <string>
#include <map>
#include <iostream>
using namespace std;


struct cacheNode {
    int key;
    string value;
    cacheNode(int k, string v):key(k), value(v) {}
};

class LRUCache {
public:
    int capacity;
    list<cacheNode> cacheList;
    map<int, list<cacheNode>::iterator> cacheMap;

    LRUCache(int size):capacity(size) {}
    
    string get(int key) {
        if(capacity <= 0) return "";
        if(cacheMap.find(key) == cacheMap.end()) return "";
        string value = cacheMap[key]->value;
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return value;
    }

    void set(int key, string value) {
        if(cacheMap.find(key) != cacheMap.end()) {
            cacheMap.find(key)->second->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        } else {
            if(capacity == cacheList.size()) {
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            cacheList.push_front(cacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
    }

    void show() {
        if(capacity <= 0) return;
        list<cacheNode>::iterator iter = cacheList.begin();

        while(iter != cacheList.end()) {
            cout<< "cacheNode(" << iter->key << ") = " << iter->value << endl;;
            iter++;
        }
        cout <<endl;
    }
};


int main() {
    LRUCache *lru = new LRUCache(20);
    lru->set(1, "abcd");
    lru->set(2, "aasdfasdfbcd");
    lru->set(5, "asdfasdfljlabcd");
    lru->set(6, "asdfasdfeabcd");
    lru->set(7, "dfdfdfdabcd");
    lru->set(10, "asdfljljwerabcd");
    lru->set(14, "basdfasdfabcd");
    lru->set(12, "34werwerabcd");
    lru->show();


    lru->get(7);
    lru->show();
    return 1;
}

