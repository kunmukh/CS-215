// Class: CS 215
// Assignment: In-class Exercise for 01/18/2017
// Programmer: <your name>

#include <iostream>
using namespace std;

// FUNCTION PROTOTYPE GOES HERE
// Objects            Type                Movement           Name
//------------------------------------------------------------------
//Price of item       double              received          price
//Sales tax rate      double              recived           rate
//sales tax amount    double              passed back       tax 
//total due           double              passedback        total
void compute_tax_and_total (double price, double rate, double &tax, double &total);

int main ()
{
   double item_price, tax_rate, sales_tax, total_due;

   // Ask the user to input data
   cout << "Enter the price of the item: ";
   cin >> item_price;
   cout << "Enter the sales tax rate (in decimal form): ";
   cin >> tax_rate;

   // Compute sales tax and total due - FUNCTION CALL GOES HERE
   compute_tax_and_total(item_price, tax_rate, sales_tax, total_due);
   // Note: no & in front of the arguments to refrence parameter


   // Display results
   cout.setf(ios::fixed|ios::showpoint); // show decimal
   // ios:: fixed - always display in fixed notation
   // ios::showpoint - always display the decimal point
   cout.precision(2); //number of places after the decimal point
   cout << "The amount sales tax is: " << sales_tax << endl;
   cout << "The total amount due is: " << total_due << endl;

   return 0;
}  // end main

// FUNCTION DEFINITION GOES HERE
void compute_tax_and_total (double price, double rate,    // value parameter
			    double &tax, double &total)     //refrence parameter

{
  tax = price * rate;  // note: no star for derefrence
  total = price + tax;

  
}


