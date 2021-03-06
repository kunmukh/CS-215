///File: coder.cpp
// A driver program written to test the huffman  class and to create
// a binary tree of huffman code
//-----------------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment:    Project 7          Date assigned:  4/19/2017
// Programmer:    Kunal Mukherjee    Date completed: 4/26/2017

//directives are included
#include <string>
#include <iostream>
#include <fstream>

#include "huffman.h"

int main (int argc, char *argv[])
{
  using namespace std; //using the stadard namesspace
  
  if (argc != 2) // to see the proper usage in the commandline
    {
      cout << "Usage:" << argv[0] << "codefile" << endl;
    }
  
  ifstream in(argv[1]); //open file  

  if (!in) //check for sucess
    {
      cout << "Error opening code file: " << argv[1] << endl;
    }
  
  //creating the huffman  class
  HuffmanTree tree;
  //loading the class with the input stream
  tree.Load(in);
  //printing out the tree
  tree.Write(cout);
  //closing the input file
  in.close();

  //to get the command
  char command;
  //the name of the input and output file
  string line, line2;

  cout << "\n" << "Please choose one of:" << "\n"
       << "\n" << " " << "E - Encode a message"
       << "\n" << " " << "D - Decode a message"
       << "\n" << " " << "Q - Quit the program" << "\n" <<endl ;

  cout << "Enter your choice: ";
  cin >> command;
  //while it is not q
   while (toupper(command) != 'Q')
    {
      if (toupper(command) == 'E')
	{
	  //creating the input steam
	  cout << "Enter the name of a plaintext message file: ";
	  cin.ignore();
	  getline(cin, line);
	  //error checking of the input file
      	  ifstream in2(line.c_str());	 
      	  if (!in2)
      	    {
      	      cout << "Error plaintext message file " << line
      	  	   << ".  Try again" <<endl;
      	    }

	  //creating the output stream
	  cout << "Enter the name of output file: ";	 
	  getline(cin, line2);
	  ofstream in3(line2.c_str());
	  //error checking of the output file
	  if (!in3)
      	    {
      	      cout << "Error output " << line
      	  	   << ".  Try again" <<endl;
      	    }	  

	  //the messsage is encoded
	      tree.Encode(in2,in3);
	      //the files are closed
	      in2.close();
	      in3.close();
	    	    
	}

      if (toupper(command) == 'D')
	{
	  //creating the input stream
	  cout << "Enter the name of a compressed message file: ";
	  cin.ignore();
	  getline(cin, line);
	  ifstream in2(line.c_str());
	  //error checking of the input stream
	   if (!in2)
      	    {
      	      cout << "Error compressed message file " << line
      	  	   << ".  Try again" <<endl;
      	    }

	   //creating the output stream
	  cout << "Enter the name of output file: ";	  
	  getline(cin, line2);      	  
	  ofstream in3(line2.c_str());
	  //error checking the output stream
	  if (!in3)
      	    {
      	      cout << "Error output " << line
      	  	   << ".  Try again" <<endl;
      	    }
	  //the message is decoded     
	      tree.Decode(in2,in3);
	      //files are closed
	      in2.close();
	      in3.close();
	    	    
	}

      //if anyother command is inserted error is throwm
      if (toupper(command) != 'E' &&
	  toupper(command) != 'Q' &&
	  toupper(command) != 'D' )
	    
	  {
	    cout << "Incorrect Command" << endl;
	  }

      cout << "\n" << "Please choose one of:" << "\n"
	   << "\n" << " " << "E - Encode a message"
	   << "\n" << " " << "D - Decode a message"
	   << "\n" << " " << "Q - Quit the program" <<  " \n" << endl;

      //the next command is taken in to do the instructions
      cout << "Enter your choice: ";
      cin >> command;
    };
}

      

      

  
