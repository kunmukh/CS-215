// File: tree.cpp
// Definitions of TreeType class, a binary search tree, operations
// Based on Dale, et al., C++ Plus Data Structures 6/e, Chapter 8
// Contains iterative versions of PutItem and DeleteItem

#include "tree.h"
struct TreeNode
{
   ItemType info;
   TreeNode* left;
   TreeNode* right;
};

// Prototypes for the helper functions.  Note these are not member functions
// and they receive a pointer to a treenode that is to be acted upon.
void Destroy(TreeNode*& tree);
void CopyTree(TreeNode*& copy, const TreeNode* originalTree);
int CountNodes(TreeNode* tree);
void FindNode(TreeNode* tree, ItemType item,
	      TreeNode*& nodePtr, TreeNode*& parentPtr);
void DeleteNode(TreeNode*& tree);
void GetPredecessor(TreeNode* tree, TreeNode*& parentPtr, ItemType &data);
void PrintTree(TreeNode* tree, std::ostream& out);
void PreOrder(TreeNode* tree, std::queue<ItemType>& que);
void InOrder(TreeNode* tree, std::queue<ItemType>& que);
void PostOrder(TreeNode* tree, std::queue<ItemType>& que);

TreeType::TreeType()
{
   root = NULL;
}

TreeType::TreeType(const TreeType& originalTree)
{
   // Calls recursive function CopyTree to copy originalTree
   // into root.
   CopyTree(root, originalTree.root);
}

void CopyTree(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL) // original is empty tree
    copy = NULL;           // copy is empty tree
  else
    {
      // Make copy of the root node
      copy = new TreeNode;
      copy->info  = originalTree->info;
      //Make copy of left subtree
      CopyTree (copy->left, originalTree->left);
      //Make copy of right subtree
      CopyTree (copy->right, originalTree->right);
    }
}

TreeType::~TreeType()
{
   // Calls recursive function Destroy to destroy the tree.
   Destroy(root);
}

void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL) //not empty
    {
      // Destroy the left child
      Destroy (tree->left);
      //Destroy the right child
      Destroy (tree->right);
      // Delete the root node
      delete tree;
    }
}

void TreeType::MakeEmpty()
{
   Destroy(root);
   root = NULL;
}

TreeType & TreeType::operator= (const TreeType& originalTree)
{
   // Use the swap technique
   TreeType theCopy (originalTree);
   // Swap contents
   std::swap (root, theCopy.root);
   std::swap (preQue, theCopy.preQue);
   std::swap (inQue, theCopy.inQue);
   std::swap (postQue, theCopy.postQue);
   // Return self object, destructor automatically called on theCopy
   //    to delete the old data nodes
   return *this;   // 'this' is a pointer, so need to dereference
}

bool TreeType::IsFull() const
{
   // Returns true if there is no room for another item 
   //  on the free store; false otherwise.
   TreeNode* location;
   try
   {
      location = new TreeNode;
      delete location;
      return false;
   }
   catch(std::bad_alloc exception)
   {
      return true;
   }
}

bool TreeType::IsEmpty() const
{
   return root == NULL;
}

int TreeType::GetLength() const
{
   // Calls recursive function CountNodes to count the 
   // nodes in the tree.
   return CountNodes(root);
}

int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
   if (tree == NULL)  // Base case: empty tree
      return 0;
   else
      // Smaller-caller is children subtrees
      // General case is count in this tree is sum of count
      //    in each children subtrees plus one for this node
      return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

ItemType TreeType::GetItem(ItemType item, bool& found)
{
   // Calls function FindNode to search the tree for item.
   TreeNode *itemPtr, *parentPtr;
   FindNode (root, item, itemPtr, parentPtr);
   return itemPtr->info;
}

void FindNode(TreeNode* tree, ItemType item,
     TreeNode*& nodePtr, TreeNode*& parentPtr)
// Post: If a node is found with the same key as itemπs, then 
//       nodePtr points to that node and parentPtr points to its 
//       parent node. If the root node has the same key as itemπs,
//       parentPtr is NULL. If no node has the same key, then 
//       nodePtr is NULL and parentPtr points to the node in the 
//       tree that is the logical parent of item.

{
  nodePtr = tree;
  parentPtr = NULL;
  bool found = false;
  while (nodePtr != NULL && !found)
  {
    if (item < nodePtr->info)
    {
      parentPtr = nodePtr;
      nodePtr = nodePtr->left;
    }
    else if (item > nodePtr->info)
    {
      parentPtr = nodePtr;
      nodePtr = nodePtr->right;
    }
    else
      found = true;
  }
}

void TreeType::PutItem(ItemType item)
// Post: item is in tree.
{
  TreeNode* newNode;
  TreeNode* nodePtr;
  TreeNode* parentPtr;

  // prepare new node; will be a leaf
  newNode = new TreeNode;
  newNode->info = item;
  newNode->left = NULL;
  newNode->right = NULL;

   // Calls function FindNode to find item's place in the tree
  FindNode(root, item, nodePtr, parentPtr);
  
  if (parentPtr == NULL)		// Insert as root.
    root = newNode;
  else if (item < parentPtr->info)      // Attach new node on correct side
    parentPtr->left = newNode;
  else
     parentPtr->right = newNode;
}

void TreeType::DeleteItem(ItemType item)
// Post: There is no node in the tree whose info member 
//       matches item. 
{
  TreeNode* nodePtr;
  TreeNode* parentPtr;
 
  // Find the item to delete
  FindNode(root, item, nodePtr, parentPtr);

  if (nodePtr == root)                  // Delete the root
     DeleteNode(root);
  else if (parentPtr->left == nodePtr)  // Delete the node on the correct side
     DeleteNode(parentPtr->left);
  else
     DeleteNode(parentPtr->right);
}


void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
   ItemType data;
   TreeNode* tempPtr;

   tempPtr = tree;
   if (tree->left == NULL)  // has a right child or is a leaf
   {
      tree = tree->right;
      delete tempPtr;
   }
   else if (tree->right == NULL)  // has a left child
   {
      tree = tree->left;
      delete tempPtr;
   }
   else  // has two children
   {
      // find precedessor node in left subtree
      TreeNode* parentPtr = tree;
      GetPredecessor(tree->left, parentPtr, data);
      // move the predecessor node data into this node
      tree->info = data;

/*****************
 Corrected code 
 *****************/
      if (parentPtr == tree) // Predecessor node is first node of left subtree
	 DeleteNode(tree->left);
      else                   // Otherwise, it is right child of parent
	 DeleteNode(parentPtr->right);  
   }
}

void GetPredecessor(TreeNode* tree, TreeNode*& parentPtr, ItemType &data)
// Modified from version in textbook to set parentPtr to point to the 
// parent of the right-most node in tree, so that precedessor node can be
// delete without called the recursive Delete function
// Sets data to the info member of the right-most node in tree.
{
   // traverse down right branch until get to the last one
   while (tree->right != NULL)
   {
      parentPtr = tree;
      tree = tree->right;
   }      
   data = tree->info;
}

void TreeType::Print(std::ostream& out) const
// Calls recursive function PrintTree to print items in the tree.
{
   PrintTree(root, out);
}

void PrintTree(TreeNode* tree, std::ostream& out) 
// Overloaded helper function
{
   if (tree != NULL)
   {
      PrintTree(tree->left, out);   // Print left subtree.
      out << " " << tree->info;
      PrintTree(tree->right, out);  // Print right subtree.
   }
}

void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
   switch (order)
   {
      case PRE_ORDER : PreOrder(root, preQue);
	 break;
      case IN_ORDER  : InOrder(root, inQue);
	 break;
      case POST_ORDER: PostOrder(root, postQue);
	 break;
   }
}


void PreOrder(TreeNode* tree, 
	      std::queue<ItemType>& preQue)
// Post: preQue contains the tree items in preorder.
{
   if (tree != NULL)
   {
      preQue.push(tree->info);
      PreOrder(tree->left, preQue);
      PreOrder(tree->right, preQue);
   }
}


void InOrder(TreeNode* tree, 
	     std::queue<ItemType>& inQue)
// Post: inQue contains the tree items in inorder.
{
   if (tree != NULL)
   {
      InOrder(tree->left, inQue);
      inQue.push(tree->info);
      InOrder(tree->right, inQue);
   }
}


void PostOrder(TreeNode* tree, 
	       std::queue<ItemType>& postQue)
// Post: postQue contains the tree items in postorder.
{
   if (tree != NULL)
   {
      PostOrder(tree->left, postQue);
      PostOrder(tree->right, postQue);
      postQue.push(tree->info);
   }
}


ItemType TreeType::GetNextItem(OrderType order, bool& finished)
{
   finished = false;
   ItemType item;
   switch (order)
   {
      case PRE_ORDER  :
	 item = preQue.front();
	 preQue.pop();
	 if (preQue.empty())
	    finished = true;
	 break;
      case IN_ORDER   :
	 item = inQue.front();
	 inQue.pop();
	 if (inQue.empty())
	    finished = true;
	 break;
      case  POST_ORDER:
	 item = postQue.front();
	 postQue.pop();
	 if (postQue.empty())
	    finished = true;
	 break;
   }
   return item;
}
