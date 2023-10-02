//
//  Set.h
//  Project 2 (CS32)
//
//  Created by Kai Perez on 1/24/23.
//

#ifndef Set_h
#define Set_h


#include <string>

const int DEFAULT_MAX_ITEMS = 160;

using ItemType = std::string;

class Set
{
    public:
    Set();         // Create an empty set (i.e., one whose size() is 0).
    
    Set(const Set &other);      //copy constructor
    
    Set& operator=(const Set& other);
    
    ~Set();                 //destructor
    
    void dump() const;
    
    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
        // Insert value into the set if it is not already present.  Return
        // true if the value is actually inserted.  Leave the set unchanged
        // and return false if value is not inserted (perhaps because it
        // was already in the set or because the set has a fixed capacity and
        // is full).

    bool erase(const ItemType& value);
        // Remove the value from the set if it is present.  Return true if the
        // value was removed; otherwise, leave the set unchanged and
        // return false.
     
    bool contains(const ItemType& value) const;
        // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
        // If 0 <= i < size(), copy into value the item in the set that is
        // strictly greater than exactly i items in the set and return true.
        // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
        // Exchange the contents of this set with the other one.
    
    
    
    private:
    int m_size;
    struct Node {
        ItemType m_data;
        Node* m_next;
        Node* m_prev;
    };
    Node* m_head;
    Node* m_tail;

    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NON_MEMBER FUNCTION DECLARATIONS//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void unite(const Set& s1, const Set& s2, Set& result);
//unite 2 different sets while accounting for duplicates

void butNot(const Set& s1, const Set& s2, Set& result);
//save values in set 1 that are not in set 2 in Set Result


#endif /* Set_h */
