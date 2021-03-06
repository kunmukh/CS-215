// Function: search
// Searches array x for target.  
// Returns index of target or -1 if not found
int search(const int x[], int n, int target) {
   for (int i=0; i < n; i++) {          // Line 1
      if (x[i] == target)               // Line 2
	 return i;                      // Line 3
   }
   return -1;                           // Line 4
}  // end search



// Function: are_different
// Determines whether two arrays have no common elements
// Returns true if there are no common elements, false otherwise
bool are_different(const int x[], int n, int y[], int m_length) {
   for (int i=0; i < n; i++) {               // Line 1
      if (search(y, y_length, x[i]) != -1)   // Line 2
	  return false;                      // Line 3
   }
   return true;                              // Line 4
}  // end are_different



// Function: are_unique
// Determines whether the elements of x are all unique
// Returns true all elements of x are unique, false otherwise
bool are_unique (const int x[], int n) {
   for (int i = 0; i < n; i++)               // Line 1
      for (int j = 0; j < n; j++)            // Line 2
	 if (i != j && x[i] == x[j])         // Line 3
	    return false;                    // Line 4
   return true;                              // Line 5
}


/*
This chart gives some idea of how f(n) functions compare.
For f(256) instructions at 1us/instruction
(log_2 means log base 2)

   Function               Time
   -----------------------------------------
   log_2n                 8 us
   n                      .25 ms
   nlog_2n                2 ms
   n^2                    65 ms
   n^3                    17 s
   2^n                    3.7x10^61 centuries
*/
