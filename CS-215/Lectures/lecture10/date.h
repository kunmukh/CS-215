// File: date.h
// Declare a class to represent the Date ADT
// Based on Dale, et al., C++ Plus Data Structures, Chapter 2 Case Study

#include <string>
#include <iostream>

#ifndef DATE_H // if this symbol is undefined , then proceed
               // if this symbol is defined, then skip to #endif
#define DATE_H


enum RelationType{LESS, EQUAL, GREATER};
//enum is short for enumerated value
//actual values are 0,1,2. not really relevant in case



class Date // class name becomes type name
{
   public:// visible to outside
          // ie prototypes of the operations

  //default costructor
  //is run when variable is declared
  //constructors have same name as class, but they don't return anything
  Date();

   // initializes this date (called self in textbook)
   void Initialize(int newMonth, int newDay, int newYear);

   // returns month
   int GetMonth() const; // const prevents functions from modifying
                         // private data members
                         // ensures that the function does not
                         // does not change the object

   // returns month name
   std::string GetMonthAsString() const; // note no namespace
                                         // declaration at beginning

   // returns year
   int GetYear() const;				

   // returns day
   int GetDay() const;

   // compare this date object with another date object
   // and return appropriate RelationType value
   RelationType CompareTo(Date rhs) const; //rhs for right-hand side
                                     //recieves right-hand operand

   //friend functino is a regular function that can access private data members
   //of the class objects
   friend std::istream& operator>> (std::istream& in, Date& aDate);
   friend std::ostream& operator<< (std::ostream& out, Date& aDate);


   private:// these things are hidden and only accessible by other
           // things in this class. eg data attributes
   int  month;  //  1-12
   int  day;	// 1-31			
   int  year;   // >1583
};// do not ever forget the semicolon!

#endif
