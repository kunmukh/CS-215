//File: setcard.cpp
// Implementation of the SetCard class
//
//-----------------------------------------------------------------
// Class: CS 215                     Instructor: Dr. Deborah Hwang
// Assignment:    setcard.cpp        Date assigned:  2/2/2017
// Programmer:    Kunal Mukherjee    Date completed: 9/2/2017

#include "setcard.h" //header file

//a static library so that ToString can return the
//correct Number, Color, Shade and Shape
static std::string NumberConversion[] = {"ERROR","ONE", "TWO", "THREE"};
static std::string ColorConversion[] = {"RED","GREEN","PURPLE"};
static std::string ShadeConversion[] = { "SOLID", "STRIPED", "OPEN"};
static std::string ShapeConversion[] = { "DIAMOND", "SQUIGGLE", "OVAL"};

SetCard::SetCard()
{
  //The way setcard is first initialized
  number = 1;  
  color = RED;
  shade = SOLID;
  shape = DIAMOND;
}

//this is a transformer fuction, when transfored the data
//stored in private part of the class
void SetCard::Initialize(int newNumber,
			 ColorType newColor,
			 ShadeType newShade,
			 ShapeType newShape)
{
  if (newNumber < 1 || newNumber > 3) //error checking to see
                                      //the number is in between
                                      //1-3; exception is trown
    {
      throw std::string("Date::Intialize() - error in newMonth value");
    }
  
  // the data is read from its varibale is stored
  // in the respective data class
  number = newNumber; 

  color = newColor;

  shade = newShade;

  shape = newShape;
}

//GetNumber is a accessor function returns the number
int SetCard::GetNumber() const
 {
   return number;
 }

//GetColor is a accessor function returns the color
ColorType SetCard::GetColor() const
{
  return color;
}

//GetShade is a accessor function returns the shade
ShadeType SetCard::GetShade() const
{
  return shade;
}

//GetShape is a accessor function returns the shape
ShapeType SetCard::GetShape() const
{
  return shape;
}

//IsSet returns a boolean value after
//going throught the steps and to see if
//the three are a set or not
bool SetCard:: IsSet(SetCard card2, SetCard card3) const
{
  // If all the four data attributes are same for all the
  //three cards defined.
  // The A set is three cards where each characteristic is 
  //the same in all three cards or different in all three cards.   

  
  if ( (((number == card2.number) && (number == card3.number)) ||
	(( number != card2.number) && (number != card3.number) &&
	 (card2.number != card3.number))) &&
       (((color == card2.color) && (color == card3.color)) ||
	(( color != card2.color) && (color != card3.color) &&
	 (card2.color != card3.color))) &&
       (((shade == card2.shade) && (shade == card3.shade)) ||
	(( shade != card2.shade) && (shade != card3.shade) &&
	 (card2.shade != card3.shade))) &&
       (((shape == card2.shape) && (shape == card3.shape)) ||
	((shape != card2.shape) && (shape != card3.shape) &&
	 (card2.shape != card3.shape))))
    {
      return true;
    }

    else
      return false;
}

//ToString returns the expanded form of the data read in from the
//file
std::string SetCard::ToString() const 
{
  return NumberConversion[number] + " " + ColorConversion[color]+
   " " + ShadeConversion[shade] + " " + ShapeConversion[shape] ;
}

//verloaded operator function that reads SET card values from
//an input stream, without prompting
std::istream &operator >> (std::istream &in, SetCard &aCard)
{
  //Each character is to be converted to its attribute type value,
  //where needed, and stored in the attributes
  
  int intNum;
  char intColor;
  char intShape;
  char intShade;
  
  in >> intNum;

  //Appropiate error is checked for each input stream
   if (in.fail())
    return in;
   
   //error checking: only that 1,2,3 is entered
   if (intNum < 1 || intNum > 3)  
     {
       in.setstate (std::ios_base::failbit);
       return in;
     }
     
  in >> intColor;

   if (in.fail())
    return in;

    //error checking: only that G,R,P is entered
   if (intColor != 'G' && intColor != 'R' && intColor != 'P' )
     {
       in.setstate (std::ios_base::failbit);
       return in;
     }
   
   in >> intShade;

   if (in.fail())
    return in;

   //error checking: only that L,S,O is entered
    if (intShade != 'L' && intShade != 'S' && intShade != 'O' )
     {
       in.setstate (std::ios_base::failbit);
       return in;
     }
   
  in >> intShape;

  if (in.fail())
    return in;

  //error checking: only that D,S,O is entered
  if (intShape != 'D' && intShape != 'S' && intShape != 'O' )
     {
       in.setstate (std::ios_base::failbit);
       return in;
     }

  //the appropiate variable is being converted to its
  //appropiate attribute type
  if (intNum == 1)
    aCard.number = 1;
  if (intNum == 2)
    aCard.number = 2;
  if (intNum == 3)
    aCard.number = 3;

  if (intColor == 'G')
    aCard.color = GREEN;
  if (intColor == 'R')
    aCard.color = RED;
  if (intColor == 'P')
    aCard.color = PURPLE;

  if (intShade == 'L')
    aCard.shade = SOLID;
  if (intShade == 'S')
    aCard.shade = STRIPED;
  if (intShade == 'O')
    aCard.shade = OPEN;

  if (intShape == 'D')
    aCard.shape = DIAMOND;
  if (intShape == 'S')
    aCard.shape = SQUIGGLE;
  if (intShape == 'O')
    aCard.shape = OVAL;  
  
  
  return in;  //returns the out stream
}

// overloaded operator function that prints SET card attributes
//to an output stream in the format readable
std::ostream &operator << (std::ostream &out, SetCard aCard)
{
   int intNum;
  char intColor;
  char intShape;
  char intShade;

  //the attributes are converted back to its
  //original character and integer 
  if (aCard.number == 1)
    intNum  = 1;
  if (aCard.number == 2)
    intNum  = 2;
  if (aCard.number == 3)
    intNum = 3;

  if (aCard.color == GREEN)
    intColor = 'G';
  if (aCard.color == RED)
    intColor = 'R';
  if (aCard.color == PURPLE)
    intColor = 'P'; 

  if (aCard.shade == SOLID)
    intShade = 'L';
  if (aCard.shade == STRIPED)
    intShade = 'S';
  if (aCard.shade == OPEN)
    intShade = 'O';


  if (aCard.shape == DIAMOND)
    intShape = 'D';
   if (aCard.shape == SQUIGGLE)
    intShape = 'S';
    if (aCard.shape == OVAL)
    intShape = 'O'; 
  
  
  out << intNum <<  intColor
      << intShade << intShape; //the encoded card information
                               //is printed out in the output stream

  return out; //returns the out stream
}
