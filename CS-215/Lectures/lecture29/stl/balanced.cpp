// File: balanced.cpp
// Program that determines if an expression consisting of (, ), [, ], {, and }
// delimiters is well-formed (i.e. they are balanced and nested properly)
// Based on Dale, et al., C++ Plus Data Structures 6/e, Chapter 5
// Modified to use STL stack

#include <iostream>
#include <stack>


// Function: IsOpen
// Returns true if symbol is a left symbol
bool IsOpen (char symbol);  // REC'D: symbol to test

// Function: IsClosed
// Returns true if symbol is a right symbol
bool IsClosed (char symbol);  // REC'D: symbol to test

// Function: Matcheds
// Returns true if symbol is the corresponding right symbol for openSymbol
bool Matches (char openSymbol,  // REC'D: a left symbol
	      char symbol);     // REC'D: a right symbol

int main()
{
   using namespace std;
   char symbol;

   stack<char> stk; //stack of characters

   bool balanced = true;
   char openSymbol;
  
   cout << "Enter an expression and press return." << endl;

   // read the first char
   cin.get(symbol); // want to be able to detect the newline

   // process until the sybmol is a newline or the expression is not balanced
   while (symbol != '\n' && balanced)
   {
      // process symbol
     if (IsOpen(symbol))
       stk.push(symbol);
      // read the next symbol
     else if (IsClosed(symbol))
       {
	 if(!stk.empty())
	   {
	     openSymbol = stk.top();
	     stk.pop();
	     balanced = Matches (openSymbol, symbol);
	   }
	 else
	   balanced = false;
       }

     // read the next symbol     
     cin.get(symbol);
   }

   //if stack is not empty, there were too many left
   if (!stk.empty())
     balanced = false;


   if (balanced)
      cout << "Expression is well formed." << endl;
   else
      cout << "Expression is not well formed."  << endl;
   return 0;
}
    
bool IsOpen(char symbol)
{
   return (symbol == '(') || (symbol == '{') || (symbol == '[');
}      

bool IsClosed(char symbol)
{
   return (symbol == ')') || (symbol == '}') || (symbol == ']');
}      

bool Matches (char openSymbol, char symbol)
{
   return  (((openSymbol == '(') && symbol == ')')
	    || ((openSymbol == '{') && symbol == '}')
	    || ((openSymbol == '[') && symbol == ']'));
}
