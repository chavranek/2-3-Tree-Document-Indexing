#include "two3.h"
#include "time.h"
#include <iomanip>
#include <sstream>

two3::two3()
{
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool two3::isEmpty()
{
    return root == NULL;
}

void two3::contains() const
{
    string input;
    node * foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    // isInTree will have either false, right, or left to distinguish whether or not
    // the word is in the tree, and if it is what key location is it at?
    string isInTree = containsHelper(input, root, foundNode);
    if(isInTree == "left"){
        cout << "Line Numbers: " << foundNode->leftLines[0];
        for(int i = 1; i < foundNode->leftLines.size(); i++)
            cout << ", " << foundNode->leftLines[i];
        cout << '\n';
    }
    else if (isInTree == "right"){
        cout << "Line Numbers: " << foundNode->rightLines[0];
        for(int i = 1; i < foundNode->rightLines.size(); i++)
            cout << ", " << foundNode->rightLines[i];
        cout << '\n';
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

string two3::containsHelper(const string & word, node * t, node * &result) const{
    if (t == NULL)
        return "false";
    else if (t->leftKey.compare(word) == 0){
        result = t;
        return "left";
    }
    else if (t->rightKey.compare(word) == 0){
        result = t;
        return "right";
    }
    // this condition is to check the
    else if (t->rightKey == NULL){
        if (word > t->leftKey){
            return containsHelper(word, t->center, result);
        }
        else
            return containsHelper(word, t->left, result);
    }
    else
        if (word < t->leftKey){
            return containHelper(word, t->left, result);
        }
        else if (word > t->leftKey && word < t->rightkey){
            return containHelper(word, t->center, result);
        }
        return containsHelper(word, t->right, result);
}

void two3::buildTree(ifstream & input){
    int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
    stringstream tempWord;
    double totalTime, finishTime, startTime = clock();
    while (!input.eof()) {
        string tempLine, tempWord;

        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter( newline or space) is found
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }

            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);

            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                insertHelper(tempWord, line, root, distWords);
                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
            }

        }
        line++;
    }
    //Do time and height calculation
    finishTime = clock();
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);

    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
         << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
         <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
         <<"Height of BST is : " << treeHeight << endl;

}

void two3::insertHelp(const string & word, int line, node *& rt, int &distWords){
    // going to try to follow code from open dsa
    if (rt == NULL){
        rt = new node(word, NULL, NULL, NULL, NULL, NULL);
        rt->leftLines.pushback(line);
        distWords++;
    }
    else if (rt.isLeaf()){ // insert at leaf node
        rt.add();
    }
    else{
        if (word.compare(rt->leftKey) < 0){ // insert left
            insertHelp(word, line, rt->left, distWords);
        }
        else if (word.compare(rt->leftKey) == 0){ // found our word in the tree. Insert the line number into the vector.
            rt->leftLines.pushback(line);
        }
        else if(rt->rightKey == NULL){ // single node
            if(word.compare(rt->leftKey) > 0){
                insertHelp(word, line, rt->center);
            }
            else if()
        }

    }
}

void two3::node::add(){
    if (this.rightKey == NULL){ // if only one key in the node add the value to this leaf
        if(this.leftKey)
    }
}


int two3::height(node * root){
    if (root = NULL) return 0;

    int depth = 0;

    int L = height(root->left);
    int R = height(root->right);
    
    if (L > R) return L + 1;
    else
        return R + 1;
}

//Prints the index to the supplied receiver, either
//cout or the output file
void two3::printTree(ostream & out) const {
    out << "2-3 Search Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Called by printTree(), does the actual formatted printing
void two3::printTreeHelper(node *t, ostream & out) const{
    if(t == NULL)
        return;
    else {
        printTreeHelper(t->left, out);
        out << setw(30) << std::left;
        out << t->leftKey << " " << t->leftLines[0]; 
        for (int i = 1; i < t->leftLines.size(); i++)
            out << ", " << t->leftLines[i];
        out << endl;

        if (t->rightKey == "") { //since right key is empty, there is no middle child
            printTreeHelper(t->center, out); //but this implementation, if right empty, center = right child, and right is null
        }
        else if (t->rightKey != "") {
            printTreeHelper(t->center, out);
            out << setw(30) << std::left;
            out << t->rightKey << " " << t->rightLines[0];
            for (int i = 1; i < t->rightLines.size(); i++)
                out << ", " << t->rightLines[i];
            out << endl;
            printTreeHelper(t->right, out);
        }
    }
}







