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
        return false;
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
}
