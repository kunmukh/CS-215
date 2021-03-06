//File: document.cpp
// Implementation of the Document class
//
//-----------------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment:    Editor             Date assigned:  2/23/2017
// Programmer:    Kunal Mukherjee    Date completed: 2/28/2017

//header file
#include "document.h"

//The default constructor
Document::Document()
{
  //The current line is initialized to zero
  currentPos = 0;
}

//It reads lines from an input stream,
//replacing any lines that already exists.
void Document::Load (std::istream &in)
{
  std::string line;
  //sets the current postition to 0
  currentPos = 0;

  //read in line as long as it doesnot hit EOF
  while (std::getline(in, line))
    {
      //Put the line into the vector 
      lines.push_back(line);     
    }
}

//Function clears the document of any lines
void Document::MakeEmpty()
{
       lines.clear();
       currentPos = 0;    
}

//Returns true if the document has no lines, false otherwise
bool Document::IsEmpty() const
{
  // A boolean variable
  bool result = false;

  //If the list is empty then set result to true, by
  //default it is false
  if (lines.empty())
    result = true;

  // Return the result
  return result;
}

 //Inserts a line in front of the current line
void Document::Insert (std::string newLine)
 {
   lines.insert(lines.begin() + currentPos, newLine);
 }
  
//Inserts a line at the end of he document
void Document::Append (std::string newLine)
{
 //Put the line at the end of the document
  lines.push_back(newLine);

  if (lines.size() != 1)
    {
      //increment the postion to match the current position
      currentPos = lines.size() - 1;
    }
}

//Replace the content of the current line
void Document::Replace (std::string new_line)
{
  //if the document is empty throw an error
  if (lines.empty())
    {
      throw std::string(" The document is empty ");
    }
  //if the document is not empty then replace the 
  //content of the current line
  lines[currentPos] = new_line;
}

//Erase the current line from the document
void Document::Erase()
 {
   // if the document is emepty throw an exception
   if (lines.empty())
     {
       throw std::string(" The document is empty ");
     }

   //the current line is removed and the next line
   //becomes the current line
   else
     {
       lines.erase(lines.begin() + currentPos);
       if (currentPos == lines.size())
	 {
	   currentPos--;
	 }
     }  
 }

//find the first line in the document containing
//the target string and make it the current line
bool Document::Find (std::string target)
{
  //Default the result is false
  bool result = false;

  //Go through the whole vector
  for (int i = 0; i < lines.size(); i++)
    {
      // if a first line matches the target string
      if (lines[i].find(target) != std::string::npos)  
	{
	  //making that the current lin0
	  currentPos = i;
	  //making the result true
	  return true;
	}
    }
  return result;
}

//sets the current line (index) to n
void Document::SetCurrent( int n)
{
  // if the document is emepty throw an exception
  if (lines.empty())
    {
      throw std::string(" The document is empty ");
    }
  
  //if n < o or the docment has less than n+1 lines
  else if ( n < 0 || lines.size() < n + 1)
    {
      //exception
      throw std::string("Not enough lines are there");
    }
  else
    //set the current line to n
    currentPos = n;
}

//moves the current line |n| places. If n> 0, it moves
//in the forward direction, if n < 0, it moves in the
//backward direction
void Document::MoveCurrent( int n)
{
 // if the document is emepty throw an exception
  if (lines.empty())
    {
      throw std::string(" The document is empty ");       
    }
  
  //if  the docment has less than n+1 lines
  else if ( lines.size ( )-1  < currentPos + n || currentPos + n < 0)
    {
      //exception
      throw std::string("Not enough lines are there");
    }
  else
    {
      //move the position n places
      currentPos = currentPos + n;	
    }  
}

//writes the current line, including a newline, to an
//output stream
void Document::WriteLine (std::ostream &out) const
 {
   // if the dpcument is empty the function is ignored
   if (lines.empty())
     return;
   
   else     
     out << lines[currentPos] << std::endl;
   
 }

 //Writes the document to an output stream
void Document::WriteAll (std::ostream &out) const
{
  //write the document and the current line index stays
  // the same
  for (int i = 0; i < lines.size(); i++)
    {
      out << lines[i] << std::endl;
    }
}



