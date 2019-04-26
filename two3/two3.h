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
        node(const string &lk,const string &rk,
            node *l, node *r, node *c, node *p): 
            leftKey(lk), rightKey(rk), left(l), right(r), center(c), parent(p)
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
    };
    string containsHelper(const string & x, node * t, node* &result) const;
public:
    two3();
    void contains() const;
    bool isEmpty();
    void printTree(ostream & out = cout) const;
    void printTreeHelper(node *t, ostream & out) const;
    void buildTree(ifstream & input);
    void compareBoth();
    int height(node * root);
    vector<string> words;
    void insertHelp(const string & word, int line, node *& rt, int &distWords, node *& parent);
    node *root;
    bool search(string x);
    void add(const string & word, int line, node *& currentNode, node*& parent);
    void promote(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent);
    void promoteHelper(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent);
    void promoteLeftIntoTwoNode(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent);
    void promoteCenterIntoTwoNode(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent);
};
#endif










