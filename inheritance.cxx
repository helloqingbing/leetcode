#include <iostream>
using namespace std;

class B1   
{
public:
    B1(int i) {
        cout<<"B1(): "<<i<<endl;
    }

    ~B1() {
        cout<<"~B1()"<<endl;
    }  
};


class B2    
{
public:  
    B2(int j) {
        cout<<"B2(): "<<j<<endl;
    }
    ~B2() {
        cout<<"~B2()"<<endl; 
    } 
};


class B3   
{  
public:  
    B3() { 
        cout<<"B3(): *" <<endl;
    }  
    ~B3() {
        cout<<"~B3()"<<endl;
    }
};


class C: public B2, public B1, public B3   
{
public:   
    C(int a,int b,int c,int d):B1(a),B2(b),memberB2(b),memberB1(c) {
        this->m = d;
        cout<<"C(): " << this->m <<endl;
    }

    ~C() {
        cout<<"~C()"<<endl;
    }  
private:  
    B1 memberB1;  
    B2 memberB2;  
    B3 memberB3;  
    int m;  
};

int main(){
    C obj(1,2,3,4); 
    return 1;  
}

/*
B2(): 2
B1(): 1
B3(): *
B1(): 3
B2(): 2
B3(): *
C()
~C()
~B3()
~B2()
~B1()
~B3()
~B1()
~B2()

*/  
