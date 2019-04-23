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
                insertHelp(tempWord, line, root, distWords);
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
    //treeHeight = findHeight(root);

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

void two3::insertHelp(const string & word, int line, node *& rt, int &distWords){
    // going to try to follow code from open dsa
    if (rt == NULL){
        rt = new node(word, "", NULL, NULL, NULL, NULL);
        rt->leftLines.push_back(line);
        distWords++;
    }
    else if (rt->isLeaf()){ // potentially insert at this leaf node
        if (word.compare(rt->leftKey) == 0){ // word is the same as the left key in the root node
            rt->leftLines.push_back(line);
        }
        else if (rt->rightKey != "" && word.compare(rt->rightKey) == 0) { // word = right key value
            rt->rightLines.push_back(line);
        }
        else{ // the word isn't equal to either values in the node. Going to insert. (promotion may be needed)
            rt->add(word, line);
            distWords++;
        }
    }
    else{ // looking at 2 node conditions first and then check 3 node conditions
        if (word.compare(rt->leftKey) < 0){ // insert left
            insertHelp(word, line, rt->left, distWords);
        }
        else if (word.compare(rt->leftKey) == 0){ // found our word in the tree. Insert the line number into the vector.
            rt->leftLines.push_back(line);
        }
        else if (rt->rightKey == "" && word.compare(rt->leftKey) > 0){ // single node and greater than left node
            insertHelp(word, line, rt->center, distWords);
        }
        else if (rt->rightKey != ""){ // this is a 3 node
            if (word.compare(rt->rightKey) > 0){ // greater than the right key, go down the left side of the tree
                insertHelp(word, line, rt->right, distWords);
            }
            else if(word.compare(rt->rightKey) == 0){ // the word is equivalent to the right key, insert in lines vector
                rt->rightLines.push_back(line);
            }
            else if (word.compare(rt->leftKey) > 0 && word.compare(rt->rightKey) < 0){ // word is greater than the left
                // key position but is less than the right key word so it goes in the middle
                insertHelp(word, line, rt->center, distWords);
            }
        }
    }

}

void two3::node::add(const string & word, int line){
    if (this->rightKey == ""){ // working with a 2 node at the leaf level
        if(word.compare(this->leftKey) > 0){ // word is greater than the left key so the word can be placed in the right
            this->rightKey = word;
            this->rightLines.push_back(line);
        }
        else{ // the word is greater than the left key so we need to swap the values
            this->rightKey = this->leftKey;
            this->rightLines = this->leftLines;
            this->leftKey = word;
            this->leftLines.clear();
            this->leftLines.push_back(line);
        };
    }
}
