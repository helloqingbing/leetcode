#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct tree
{
    int data;
    tree *left,*right;
};

class Btree
{
    static int n;
    static int m;
    public:
    tree *root;
    Btree()
    {
        root=NULL;
    }
    void create_Btree(int);
    void Preorder(tree *);                  //Pre order 
    void inorder(tree *);                   //Inorder
    void Postorder(tree *);                 //Post order
    void display1() {Preorder(root); cout<<endl;}
    void display2() {inorder(root);cout<<endl;}
    void display3() {Postorder(root); cout<<endl;}  
    int count(tree *);                      //caculate tree node
    int findleaf(tree *);                   //find leaf node
    int findnode(tree *);                   //find leaf
    void PostOrderWithoutRecursion()
    {
        if(root == NULL) return;
        tree * p = root, *q = NULL;
        stack<tree*> s;
        do {
            while(p) {
                s.push(p);
                p = p->left;
            }
            q = NULL;
            while(!s.empty()) {
                p = s.top();
                s.pop();
                if(p->right == q) {
                    cout << p->data << " ";
                    q = p;
                }
                else 
                {
                    s.push(p);
                    p = p->right;
                    break;
                }
            }
        }while(!s.empty());
        cout<<endl;
    }
};                                          
int Btree::n=0;
int Btree::m=0;
void Btree::create_Btree(int x)
{
    tree *newnode=new tree;
    newnode->data=x;
    newnode->right=newnode->left=NULL;
    if(root==NULL)
        root=newnode;
    else
    {
        tree *back;
        tree *current=root;
        while(current!=NULL)
        {
            back=current;
            if(current->data>x)
                current=current->left;
            else
                current=current->right;
        }
        if(back->data>x)
            back->left=newnode;
        else
            back->right=newnode;
    }
}
int Btree::count(tree *p)
{
    if(p==NULL)
        return 0;
    else
        return count(p->left)+count(p->right)+1;      //................
}
void Btree::Preorder(tree *temp)    //...................
{
    if(temp!=NULL)
    {
        cout<<temp->data<<" ";
        Preorder(temp->left);
        Preorder(temp->right);
    }
}
void Btree::inorder(tree *temp)      //...................
{
    if(temp!=NULL)
    {
        inorder(temp->left);
        cout<<temp->data<<" ";
        inorder(temp->right);
    }
}
void Btree::Postorder(tree *temp)     //...................
{
    if(temp!=NULL)
    {
        Postorder(temp->left);
        Postorder(temp->right);
        cout<<temp->data<<" ";
    }
}
int Btree::findleaf(tree *temp)
{
    if(temp==NULL)return 0;
    else
    {
        if(temp->left==NULL&&temp->right==NULL)return n+=1;
        else
        {
            findleaf(temp->left);
            findleaf(temp->right);
        }
        return n;
    }
}
int Btree::findnode(tree *temp)
{
    if(temp==NULL)return 0;
    else
    {
        if(temp->left!=NULL&&temp->right!=NULL)
        {
            findnode(temp->left);
            findnode(temp->right);
        }
        if(temp->left!=NULL&&temp->right==NULL)
        {
            m+=1;
            findnode(temp->left);
        }
        if(temp->left==NULL&&temp->right!=NULL)
        {
            m+=1;
            findnode(temp->right);
        }
    }
    return m;
}


int main()
{
    Btree A;
    int array[]={7,4,2,3,15,35,6,45,55,20,1,14,56,57,58};
    int k;
    k=sizeof(array)/sizeof(array[0]);
    cout<<"Create Btree: "<<endl;
    for(int i=0;i<k;i++)
    {
        cout<<array[i]<<" ";
        A.create_Btree(array[i]);
    }
    cout<<endl;
    cout<<"Btree node number: "<<A.count(A.root)<<endl;
    cout<<"Btree leaf node number: "<<A.findleaf(A.root)<<endl;
    cout<<"Btree has only 1: "<<A.findnode(A.root)<<endl;
    cout<<endl<<"Pre: "<<endl;
    A.display1();
    cout<<endl<<"In : "<<endl;
    A.display2();
    cout<<endl<<"Post : "<<endl;
    A.display3();
    A.PostOrderWithoutRecursion();
    return 0;
}
