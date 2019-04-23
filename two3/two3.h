#ifndef two3_H
#define two3_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class two3{
    private:
    struct node
    {

        node(){
            string leftKey = "";
            string rightKey = "";
            node *center = NULL;
            node *left = NULL;
            node *right = NULL;
            node *parent = NULL;
        }
        node(const string &lk,
             const string &rk,
             node *l, node *r, node *c, node *p)
                : leftKey(lk), rightKey(rk),
                  left(l), right(r), center(c), parent(p)
        {
            leftLines.resize(0), rightLines.resize(0);
        }

        string leftKey;
        string rightKey;
        node *center;
        node *left;
        node *right;
        node *parent;
        vector<int> leftLines;
        vector<int> rightLines;

        bool isLeaf(){
            return left == NULL;
        }

        /*void setLeft(string key, vector<int> lines){
            leftKey = key;
            leftLines = lines;
        }
        void setRight(string key, vector<int> lines){
            rightKey = key;
            rightLines = lines;
        }*/
        void setLeftChild(node *it)
        {
            left = it;
        }
        void setCenterChild(node *it)
        {
            center = it;
        }
        void setRightChild(node *it)
        {
            right = it;
        }
        void add(const string & word, int line);
    };
    string containsHelper(const string & x, node * t, node* &result) const;
public:
    two3();
    void contains() const;
    bool isEmpty();
    void printTree(ostream & out = cout) const;
    void buildTree(ifstream & input);
    vector<string> distinctInputWords;
    void insertHelp(const string & word, int line, node *& rt, int &distWords);
    node *root;
};

#endif