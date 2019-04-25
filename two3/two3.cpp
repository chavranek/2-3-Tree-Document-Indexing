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
    else if (t->rightKey == ""){
        if (word > t->leftKey){
            return containsHelper(word, t->center, result);
        }
        else
            return containsHelper(word, t->left, result);
    }
    else
        if (word < t->leftKey){
            return containsHelper(word, t->left, result);
        }
        else if (word > t->leftKey && word < t->rightKey){
            return containsHelper(word, t->center, result);
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
                // fake is only there to satisfy the conditions for insertHelp
                node * fake = new node("", "", NULL, NULL, NULL, NULL);
                insertHelp(tempWord, line, root, distWords, fake);
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
    treeHeight = height(root);

    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
         << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
         <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
         <<"Height of 2-3 tree is : " << treeHeight << endl;

}

void two3::insertHelp(const string & word, int line, node *& rt, int &distWords, node *& parent){
    // going to try to follow code from open dsa
    if (rt == NULL){
        rt = new node(word, "", NULL, NULL, NULL, parent);
        rt->leftLines.push_back(line);
        distWords++;
        if (root == NULL){ // root is NULL so we need to assign it a value
            root = rt;
        }
    }
    else if (rt->isLeaf()){ // potentially insert at this leaf node
        if (word.compare(rt->leftKey) == 0){ // word is the same as the left key in the root node
            rt->leftLines.push_back(line);
        }
        else if (rt->rightKey != "" && word.compare(rt->rightKey) == 0) { // word = right key value
            rt->rightLines.push_back(line);
        }
        else{ // the word isn't equal to either values in the node. Going to insert. (promotion may be needed)
            add(word, line, rt, parent);
            distWords++;
        }
    }
    else{ // looking at 2 node conditions first and then check 3 node conditions
        if (word.compare(rt->leftKey) < 0){ // insert left
            insertHelp(word, line, rt->left, distWords, rt);
        }
        else if (word.compare(rt->leftKey) == 0){ // found our word in the tree. Insert the line number into the vector.
            rt->leftLines.push_back(line);
        }
        else if (rt->rightKey == "" && word.compare(rt->leftKey) > 0){ // single node and greater than left node
            insertHelp(word, line, rt->center, distWords, rt);
        }
        else if (rt->rightKey != ""){ // this is a 3 node
            if (word.compare(rt->rightKey) > 0){ // greater than the right key, go down the left side of the tree
                insertHelp(word, line, rt->right, distWords, rt);
            }
            else if(word.compare(rt->rightKey) == 0){ // the word is equivalent to the right key, insert in lines vector
                rt->rightLines.push_back(line);
            }
            else if (word.compare(rt->leftKey) > 0 && word.compare(rt->rightKey) < 0){ // word is greater than the left
                // key position but is less than the right key word so it goes in the middle
                insertHelp(word, line, rt->center, distWords, rt);
            }
        }
    }

}

void two3::promote(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent){
    if (parent->leftKey == ""){ // we are at the top of the tree and will need to create a new root
        node * leftNode = new node(smallWord, "", NULL, NULL, NULL, NULL);
        leftNode->leftLines = smallLines;
        node * centerNode = new node(largeWord, "", NULL, NULL, NULL, NULL);
        centerNode->leftLines = largeLines;
        node * newRoot = new node(middleWord, "", leftNode, NULL, centerNode, NULL);
        newRoot->leftLines = middleLines;
        leftNode->parent = newRoot;
        centerNode->parent = newRoot;
        root = newRoot;
    }

}

void two3::promoteLeftIntoTwoNode(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent){
    /*this function handles the promotion of a left child node into a parent node that only has one key in it*/

    // move the center child node into the right child node first
    // handle the left key parameters first
    // establish a right node to store the information in first
    node * rightNode = new node("", "", NULL, NULL, NULL, parent);
    rightNode->leftKey = parent->center->leftKey;
    rightNode->leftLines = parent->center->leftLines;

    if (parent->center->rightKey != ""){ // only want to move the right key elements if it actually has a key and lines vector
        rightNode->rightKey = parent->center->rightKey;
        rightNode->rightLines = parent->center->rightLines;
    }

    // set the center child with with the largest key from the split.
    // Don't need to create a new node since it already exists. Simply need to change the values it has.
    parent->center->leftKey = largeWord;
    parent->center->leftLines = largeLines;
    parent->center->rightKey = "";
    parent->center->rightLines.clear();

    // set the left child node with the smallest key from the split.
    parent->left->leftKey = smallWord;
    parent->left->leftLines = smallLines;
    parent->left->rightKey = "";
    parent->left->rightLines.clear();

    // promote the middle value into the parent node.
    // Note: a promotion from the left child is always going to require shifting the current left key into the right key
    // shift the left key into the right key (including the vector) first
    parent->rightKey = parent->leftKey;
    parent->rightLines = parent->leftLines;

    // now insert into the left key and left lines the promoted value
    parent->leftKey = middleWord;
    parent->leftLines = middleLines;
}

void two3::promoteCenterIntoTwoNode(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent){
    // set up the new node that will now be the right child
    // no matter what the right node wil always have the largest value from the split
    node * rightNode = new node(largeWord, "", NULL, NULL, NULL, parent);
    rightNode->leftLines = largeLines;
    parent->right = rightNode;
    //cout << "large lines at promotion" << largeLines[0] << endl;
    //cout << "right lines are promotion" << parent->right->leftLines

    // set the center node values to the smallest values from the split
    parent->center->leftKey = smallWord;
    parent->center->leftLines = smallLines;

    // empty out the right key elements of the center node
    parent->center->rightKey = "";
    parent->center->rightLines.clear();

    // promote the middle value up into the parent node. The value being promoted up will always have a higher value than the left key.
    parent->rightKey = middleWord;
    parent->rightLines = middleLines;

}

void two3::promoteHelper(const string smallWord, const string middleWord, const string largeWord, vector<int> smallLines, vector<int> middleLines, vector<int> largeLines, node *& currentNode, node *& parent){
    if (parent->leftKey == ""){ // the parent is a NULL node which means we are going to promote the parent.
        cout << "root node promotion" << endl;
        promote(smallWord, middleWord, largeWord, smallLines, middleLines, largeLines, currentNode, parent);
    }
    else if (parent->rightKey == ""){ // we are just going to insert the promoted element into the parent node since it has a free slot
        if (parent->left->leftKey == currentNode->leftKey){ // we are promoting from the left child into the parent
            promoteLeftIntoTwoNode(smallWord, middleWord, largeWord, smallLines, middleLines, largeLines, currentNode, parent);
        }
        else{ // only other option is that we are promoting from the center
            promoteCenterIntoTwoNode(smallWord, middleWord, largeWord, smallLines, middleLines, largeLines, currentNode, parent);
        }
    }
    else{
        cout << "three node parent promotion" << endl;
    }
}

    void two3::add(const string & word, int line, node*& currentNode, node*& parent){
    if (currentNode->rightKey == ""){ // working with a 2 node at the leaf level
        if(word.compare(currentNode->leftKey) > 0){ // word is greater than the left key so the word can be placed in the right
            currentNode->rightKey = word;
            currentNode->rightLines.push_back(line);

        }
        else{ // the word is smaller than the left key so we need to swap the values
            currentNode->rightKey = currentNode->leftKey;
            currentNode->rightLines = currentNode->leftLines;
            currentNode->leftKey = word;
            currentNode->leftLines.clear();
            currentNode->leftLines.push_back(line);
        };
    }
    else{ // the node we are at has two keys in it, and a promotion will be required.
        // first step is to figure out which words are smaller.
        string smallestWord;
        string middleWord;
        string largestWord;

        vector<int> smallestLines;
        vector<int> middleLines;
        vector<int> largestLines;

        if (word.compare(currentNode->leftKey) < 0){ // the current word is the smallest word
            smallestWord = word;
            smallestLines.push_back(line);
            middleWord = currentNode->leftKey;
            middleLines = currentNode->leftLines;
            largestWord = currentNode->rightKey;
            largestLines = currentNode->rightLines;
        }
        else if (word.compare(currentNode->rightKey) > 0){ // the current word is the largestWord
            smallestWord = currentNode->leftKey;
            smallestLines = currentNode->leftLines;
            middleWord = currentNode->rightKey;
            middleLines = currentNode->rightLines;
            largestWord = word;
            largestLines.push_back(line);
        }
        else{ // the word is greater than the left key, but smaller than the right key, so it is the middle value
            smallestWord = currentNode->leftKey;
            smallestLines = currentNode->leftLines;
            middleWord = word;
            middleLines.push_back(line);
            largestWord = currentNode->rightKey;
            largestLines = currentNode->rightLines;
        }

        //node * firstNode = new node();

        promoteHelper(smallestWord, middleWord, largestWord, smallestLines, middleLines, largestLines, currentNode, parent);
    }
}


int two3::height(node * root){
    if (root == NULL) return 0;

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







