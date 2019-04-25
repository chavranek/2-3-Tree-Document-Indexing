/*
 * Authors: Christian Havranek, Isaac Florez
 * Class: CS 415
 * Project: Project 3 (Making an index using 2-3 Tree)
 * Description: Use a 2-3 tree to create an index from a given given document with the words
 * in the document as the keys in the 2-3 tree, and the line numbers where the key appears
 * as the information attached to the key.
 * */

#include <iostream>
#include <fstream>
#include "bst/bst.cpp"
#include "two3/two3.cpp"
#include <string>
using namespace std;

/*void justBuildTree(tree, input){
    if(input.is_open()){
        tree.buildTree(input);
        input.close;
    }
}*/

int bstFunction(BST & myTree, ifstream & input){
    int choice = 0;

    if(input.is_open()){
        myTree.buildTree(input);
        input.close();
        while(1){
            choice = 0;
            cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
            cin >> choice;

            choice = int(choice);

            //Print index
            if(choice == 1)
                myTree.printTree(cout);

                //Search index for a word
            else if(choice == 2)
                myTree.contains();

                //Save index
            else if(choice == 3){
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                myTree.printTree(output);
                output.close();
                cout << "Saved\n";
            }

            else
                break;
        }
    }
    else{
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
}

int two3Function(two3 & two3Tree, ifstream & input){
    int choice = 0;

    if(input.is_open()){
        two3Tree.buildTree(input);
        input.close();
        while(1){
            cout << endl;
            choice = 0;
            cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
            cin >> choice;

            choice = int(choice);

            //Print index
            if(choice == 1)
                cout << "hey";
                //myTree.printTree(cout);


                //Search index for a word
            else if(choice == 2){
                two3Tree.contains();
                cout << two3Tree.root->leftKey;
            }

                //Save index
            else if(choice == 3){
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                //myTree.printTree(output);
                output.close();
                cout << "Saved\n";
            }

            else
                break;
        }
    }
    else{
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
}

/*void compareBoth(BST tree,  two3 otherTree){
    setTimer;
    start searching bst;
    end timer;

    set timer2;
    start searching two3;
    end timer2;
}*/

int main(int argc, char* argv[]) {
	string choice;
	if (argc != 2) {
	    cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
	    return 1;
	}

	while(1)
    {
        cout << "Choose one of the options below by entering the corresponding letter.";
        cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree\n";
        cin >> choice;

        ifstream input(argv[1]);

        if (choice == "a")
        {
            cout << "Creating an index using a BST.\n";
            BST myTree;
            bstFunction(myTree, input);
            cout << "";
        }

        else if (choice == "b")
        {
            cout << "Creating an index using a 2-3 Tree.";
            two3 two3Tree;
            two3Function(two3Tree, input);
        }

        else if (choice == "c")
        {
            cout << "Comparing time to build and search all the words in a BST and 2-3 tree ";
            /*BST tree;
            bstFunction();

            two3 otherTree;
            two3Function();

            compareBoth(tree, otherTree)
            */

        }

        else
        {
            cout << "Didn't choose a, b, or c.\nExiting program.";
            break;
        }

    }
	return 0;
}
