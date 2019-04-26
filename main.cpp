/*********************************************************************************************
 * Authors: Christian Havranek, Isaac Florez                                                 *
 * Class: CS 415                                                                             *
 * Project: Project 3 (Making an index using 2-3 Tree)                                       *
 * Description: Use a 2-3 tree to create an index from a given given document with the words *
 * in the document as the keys in the 2-3 tree, and the line numbers where the key appears   *
 * as the information attached to the key.                                                   *
 * *********************************************************************** * * * * * * * * * */ 

#include <iostream>
#include <fstream>
#include "bst/bst.cpp"
#include "two3/two3.cpp"
#include <string>
using namespace std;

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
            if(choice == 1){
                myTree.printTree(cout);
                return 0;
            }

                //Search index for a word
            else if(choice == 2){
                myTree.contains();
                return 0;
            }

                //Save index
            else if(choice == 3){
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                myTree.printTree(output);
                output.close();
                cout << "Saved\n";
                return 0;
            }

            else
                break;
        }
        return 0;
    }
    else{
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
}

void compareBoth(BST bst, two3 two_3){

    string word;

    vector<string> wordsVec = bst.words;

    // BST
    double BST_start, BST_end, BST_total = clock();
    for (int i = 0; i < wordsVec.size(); i++){             // search every dist word in bst
        word = bst.words.at(i);
        if (bst.search(word)){   
            // do nothing
        }  
        else{ 
            cout << "Error searching BST for word: " << bst.words.at(i) << endl;
        }
    }
    // do calculations for time
    BST_end = clock();                                     
    BST_total = (double) (BST_end - BST_start)/CLOCKS_PER_SEC;


    // 2-3 Tree
    double T3_start, T3_end, T3_total = clock();
    for (int i = 0; i < wordsVec.size(); i++){             // search every dist word in two_3
        word = wordsVec[i];
        if (two_3.search(word)){
            // do nothing
        }
        else {
          cout << "Error searching 2-3 for word: " << wordsVec[i] << endl;
        }        
    }
    // do calculations for time
    T3_end = clock();                                     
    T3_total = (double) (T3_end - T3_start)/CLOCKS_PER_SEC;



    // output 
    cout << endl;
    cout << "Comparing build / search times for words in a BST and 2-3 tree " << endl << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Total time taken by BST: \t\t\t" << BST_total <<  " seconds" << endl;             
    cout << "Total time taken by 2-3 Tree: \t\t\t" << T3_total << " seconds" << endl;
    cout << endl;
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
            if(choice == 1){
                two3Tree.printTree(cout);
            }

                //Search index for a word
            else if(choice == 2){
                two3Tree.contains();
            }

                //Save index
            else if(choice == 3){
                string outputFile;
                cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                cin >> outputFile;
                ofstream output(outputFile.c_str());
                two3Tree.printTree(output);
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
        ifstream input2(argv[1]);

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
            BST bst;
            bst.buildTree(input);
            two3 two_3;
            two_3.buildTree(input2);

            compareBoth(bst, two_3);
        }
        else
        {
            cout << "Didn't choose a, b, or c.\nExiting program.";
            break;
        }

    }
	return 0;
}
