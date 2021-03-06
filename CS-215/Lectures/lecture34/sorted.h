// File: sorted.h
// Defines SortedType<ItemType>, a template for a sorted list of items
// Circular Doubly-Linked list implementation
// Based on Dale, et al., C++ Plus Data Structures 6/e, Chapter 6

//  An ItemType must define the following:
//  RelationType:  {LESS, GREATER, EQUAL}
//  Member function ComparedTo(ItemType item) which returns 
//       LESS, if self "comes before" item 
//       GREATER, if self "comes after" item 
//       EQUAL, if self and item are the same 
//
// Its header file must be included _before_ this header file

template<class ItemType>
struct NodeType
{
   ItemType info;
   NodeType<ItemType>* next;
   NodeType<ItemType>* back;
};

#include <algorithm> //STL swap function template
template<class ItemType>
class SortedType
{
  public:
   // Constructor - creates an empty list
   SortedType();

   //Copy Constructor - creates a list that is a copy of the original
   //Parameter must be const refrence, since a value paramter creation
   //calls the copy constructor
   SortedType(const SortedType<ItemType> & original);

   
   //Assignemnt operator = - make this this be a copy of the original
   SortedType<ItemType> & operator=(const SortedType<ItemType> & original);

   // Destructor - deletes nodes when object is destroyed
   ~SortedType();

   // Function: Returns the list to the empty state.
   // Post:  List is empty.
   void MakeEmpty();

   // Function:  Determines whether list is full.
   // Returns: true if list is full; false otherwise
   bool IsFull() const;

   // Function: Determines the number of elements in list.
   // Returns: number of elements in list
   int GetLength() const;

   // Function: Retrieves list element whose key matches item's key (if
   //           present).
   // Returns: an element someItem whose key matches item's key, and
   //       passes back found = true
   // 	 otherwise returns item and passes back found = false
   ItemType GetItem(ItemType item,       // REC'D: item to find
		    bool& found) const;  // P'BACK: true if item found
                                         //         false otherwise

   // Function: Adds item to list.
   // Assumes: List is not full, item is not in list.
   void PutItem(ItemType item);  // REC'D: item to insert

   // Function: Deletes the element whose key matches item's key.
   // Assumes: Exactly one element in list has a key matching item's key.
   void DeleteItem(ItemType item);  // REC'D: item with key to match

   // Function: Initializes current position for an iteration through the list.
   void ResetList();

   // Function: Gets the next element in list.
   // Assumes: List has not been changed since last call.
   //          Element at current position is not last in list.
   // Post: Current position is updated to next position.
   // Returns: a copy of element at the new current position.
   ItemType GetNextItem();

private:
  int length;
  NodeType<ItemType>* listData;
  NodeType<ItemType>* currentPos;
};

template<class ItemType>
SortedType<ItemType>::SortedType()  // Class constructor
{
   length = 0;
   listData = new NodeType<ItemType>; // create header node
   listData->next = listData;
   listData->back = listData;
   
   /* listData->back = NULL; */
   /* listData->next = new NodeType<ItemType>; */
   /* listData->next->back = listData; // create trailer node */
   /* listData->next->next = NULL */
}

template<class ItemType>
SortedType<ItemType>::SortedType(const SortedType<ItemType> & original)
{
  //CReate the header node
   listData = new NodeType<ItemType>; // create header node
   listData->next = listData;
   listData->back = listData;

   //scanning pointer to the original data nodes
   NodeType<ItemType> *scanPtr = (original.listData)->next;
   while(scanPtr != original.listData) // stop at original's header node
     {
       //Create the node copy
       NodeType<ItemType> *newNode = new NodeType<ItemType>;
       newNode->info = scanPtr->info;

       // Insert at the end of the list
       //listData is the successor node;
       //listDta->back is the predecessor node
       //Set newNode's links
       newNode->next = listData;
       newNode->back = listData->back;
       //set predecessor's next link to newNode
       listData->back->next = newNode;
       //Set the sucessor's back ink to newNode
       listData->back = newNode;

       //go to the next node in original
       scanPtr = scanPtr->next;
     }
   length = original.length;
}

//returns thisobject so that = can be chained, e.g l1 = l2 = l3
//member function; parameret is the same type as result
template<class ItemType>
SortedType<ItemType> & SortedType<ItemType>::operator=
  (const SortedType<ItemType> & original)
  {
    // Make a copy of the original
    SortedType<ItemType> theCopy (original);

    // Swap the contents of this objects and theCopy
    std::swap(this->listData, theCopy.listData);
    std::swap(this->length, theCopy.length);

    // Returns this object
    return *this; // "this" is a pointer to the self object
                   // so needs to de derefrenced
                  // the destruction of theCopy, will deallocate the old nodes
  }

template<class ItemType>
SortedType<ItemType>::~SortedType()
{
   NodeType<ItemType>* tempPtr;
   NodeType<ItemType>* lastNode = listData->back; //pointer to last node
   
   // Delete the nodes
   while (listData != lastNode )  // stop when get to end of list
   {
      tempPtr = listData;
      listData = listData->next;
      delete tempPtr;
   }

   //Delete the last node
   delete lastNode;

}

template<class ItemType>
void SortedType<ItemType>::MakeEmpty()
{
   NodeType<ItemType>* tempPtr;
   NodeType<ItemType>* deletePtr = listData->next; // start at first data node
   
   // Delete the nodes
   while (deletePtr->next != listData)  // stop when get to the header node
   {
      tempPtr = deletePtr;
      deletePtr = deletePtr->next;
      delete tempPtr;
   }
   //Hook the header node up to the empty 
   /* deletePtr->back = listData; */
   /* listData->next = deletePtr; */
   /* length = 0; */

   listData->next = listData;
   listData->back = listData;
   length = 0;
}

// Helper function that finds item in the list
template<class ItemType>
void FindItem(NodeType<ItemType>* listData, ItemType item, 
	      NodeType<ItemType>*& location, bool& found)
// Pre:  List is not empty.
// Post: If there is an element someItem whose key matches item's 
//		key, then found = true; otherwise, found = false. 
//       If found, location contains the address of someItem; 
//       otherwise, location contains the address of the logical 
//		successor of item.
{
  bool moreToSearch = true;

  location = listData->next; //start with the first data node
  found = false;
  while (moreToSearch && !found)
  {
    if (item.ComparedTo(location->info) == LESS)
      moreToSearch = false;
    else if (item.ComparedTo(location->info) == EQUAL)
      found = true;
    else
    {
      location = location->next;
      moreToSearch = (location->next != listData); //true have not come back the
                                                   //to  header node
    }
  }
}

template<class ItemType>
ItemType SortedType<ItemType>::GetItem (ItemType item, bool& found) const
{
   NodeType<ItemType> *location;

   FindItem(listData, item, location, found);
   if (found)  // return Info(location)
      item = location->info;

   return item;
}

template<class ItemType>
void SortedType<ItemType>::PutItem(ItemType item)
{
  NodeType<ItemType>* newNode;
  NodeType<ItemType>* location;
  bool found;
  
  newNode = new NodeType<ItemType>;
  newNode->info = item;
  FindItem(listData, item, location, found);

  // Set new node links to predecessor and successor
  // NodeType<ItemType>* predecessor = location->back;
  newNode->back = location->back; // newNode->back = predecessor;
  newNode->next = location;

  // Set predecessor next link to newNode
  location->back->next = newNode; //predecessor->next = newNode
    
  // Set successor back link
    location->back = newNode;

  length++;
}

template<class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
{
  NodeType<ItemType>* location;
  bool found;
  
  FindItem(listData, item, location, found);

  // Set predecessor next link to the sucessor
  location->back->next = location->back;

  // Set successor back link to the predecessor
  location->next = location->back;


  delete location;
  length--;
}

template<class ItemType>
bool SortedType<ItemType>::IsFull() const
{
   NodeType<ItemType>* location;
   try
   {
      location = new NodeType<ItemType>;
      delete location;
      return false;
   }
   catch(std::bad_alloc exception)
   {
      return true;
   }
}

template<class ItemType>
int SortedType<ItemType>::GetLength() const
{
   return length;
}

template<class ItemType>
void SortedType<ItemType>::ResetList()
{
   currentPos = NULL;
} 

template<class ItemType>
ItemType SortedType<ItemType>::GetNextItem()
{
   ItemType item;
   if (currentPos == NULL)
      currentPos = listData->next;  // start with first data node
   item = currentPos->info; 
   currentPos = currentPos->next;
   return item;
} 
