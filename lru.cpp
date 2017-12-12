#include <vector>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
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
        int i = 0;
        while(iter != cacheList.end()) {
            cout<< setw(2) << ++i << ": cacheNode(" << setw(2) << iter->key << ") = " << iter->value << endl;;
            iter++;
        }
        cout <<endl;
    }
};


int main() {
    LRUCache *lru = new LRUCache(5);
    lru->set(1, "1");
    lru->set(2, "2");
    lru->set(5, "3");
    lru->set(6, "4");
    lru->set(7, "5");
    lru->set(10, "6");
    lru->set(14, "7");
    lru->set(12, "8");
    lru->show();


    lru->get(7);
    lru->show();
    return 1;
}

