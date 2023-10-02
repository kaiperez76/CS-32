//
//  Set.cpp
//  Project 2 (CS32)
//
//  Created by Kai Perez on 1/24/23.
//


#include "Set.h"
#include <iostream>



Set::Set(){
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
}



Set::Set(const Set &other){
    m_size = other.m_size;
    
    if (m_size == 0){
        m_head = nullptr;
        m_tail = nullptr;
        return;
    }
    
    
    Node* headItem = new Node;
    m_head = headItem;
    headItem->m_prev = nullptr;
    headItem->m_next = nullptr;
    headItem->m_data = other.m_head->m_data;
    
    Node* currItem = other.m_head;
    Node* prevItemNew = headItem;
    
    while (currItem->m_next != nullptr) {
        currItem = currItem->m_next;
        Node* newItem = new Node;
        newItem->m_prev = prevItemNew;
        newItem->m_next = nullptr;
        newItem->m_data = currItem->m_data;
        prevItemNew->m_next = newItem;
        prevItemNew = newItem;
    }
    m_tail = prevItemNew;
}


Set& Set::operator=(const Set& other){
    if(this != &other){
        Set temp(other);
        swap(temp);
    }
    return *this;
    
}



Set::~Set(){
    if (m_size == 0){
        delete m_head;
        delete m_tail;
        return;
    }
    Node* currItem = m_head;
    if(m_size > 0){
        while (currItem != nullptr){
            Node* nextItem = currItem->m_next;
            delete currItem;
            currItem = nextItem;
        }
    }
}



void Set::dump() const{
    Node* tempFront = m_head;
    Node* tempBack = m_tail;
    std::cerr << m_size << std::endl;
    while (tempFront != nullptr){
        std::cerr << tempFront->m_data << std::endl;
        tempFront = tempFront->m_next;
    }
    std::cerr << std::endl;
    while (tempBack != nullptr){
        std::cerr << tempBack->m_data << std::endl;
        tempBack = tempBack->m_prev;
    }
}


bool Set::empty() const{
    if (m_size == 0)
        return true;
    else
        return false;
}


int Set::size() const{
    return m_size;
}


bool Set::insert(const ItemType &value){
    if(contains(value))
        return false;
    
    
    if (m_size == 0){                   //inserting node for size == 0
        Node* temp = new Node;
        m_head = temp;
        m_tail = temp;
        temp->m_next = nullptr;
        temp->m_prev = nullptr;
        m_head->m_data = value;
        m_size++;
        return true;
    }
   
            
    Node* currItem = m_head;
    Node* prevItem = nullptr;

        
    while (currItem != nullptr) {           //traversing through List
        if(currItem->m_data > value){
                break;}
        prevItem = currItem;
        currItem = currItem->m_next;
    }
        
    
    if (currItem != nullptr && currItem->m_prev == nullptr){  //inserting at beggining
        Node* insert = new Node;
        insert->m_data = value;
        insert->m_prev = nullptr;
        insert->m_next = currItem;
        currItem->m_prev = insert;
        m_head = insert;
        m_size++;
        return true;
    }

         
         
    Node* insert = new Node;
    insert->m_data = value;
         
    insert->m_prev = prevItem;     //inserting anywhere else
    insert->m_next = currItem;
    if (currItem != nullptr){
        currItem->m_prev = insert;}
    if (currItem == nullptr){
        m_tail = insert;}
    prevItem->m_next = insert;
        
       
    m_size++;
    return true;
}



bool Set::erase(const ItemType &value){
    Node* nextItem;
    Node* currItem = m_head;
    Node* prevItem = nullptr;
    
    if(!contains(value))
        return false;
    
    if(m_size == 1){
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        m_size--;
        return true;
    }
   
    while(currItem->m_next != nullptr){     //traverse to target value
        if(currItem->m_data == value)
            break;
        prevItem = currItem;
        currItem = currItem->m_next;
    }
    
    
    if(currItem->m_next == nullptr){        //last item erasing
        delete currItem;
        prevItem->m_next = nullptr;
        m_tail = prevItem;
        m_size--;
        return true;
    }
        
        
    if(currItem->m_prev == nullptr){        //first item erasing
        nextItem = currItem->m_next;
        delete currItem;
        nextItem->m_prev = nullptr;
        m_head = nextItem;
        m_size--;
        return true;
    }
        
        
    nextItem = currItem->m_next;        //middle item erasing
    prevItem->m_next = nextItem;
    nextItem->m_prev = prevItem;
    delete currItem;
    m_size--;
    return true;
}



bool Set::contains(const ItemType &value) const {
    
    Node* temp = m_head;
    if(m_size > 0){         //check for matches
        while (temp != nullptr){
            if (temp->m_data == value)
                return true;
            temp = temp->m_next;
        }
    }
    return false;
}

bool Set::get(int i, ItemType &value) const{
    if (i < 0 || i >= m_size){
        return false;
    }
    
    int count = 0;
    for (Node* k = m_head; k != nullptr; k = k->m_next){
        if (count == i){
            value = k->m_data;
            return true;
        }
        count++;
    }
    return false;
}


void Set::swap(Set &other){
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    Node* temp2 = m_head;
    m_head = other.m_head;
    other.m_head = temp2;
    
    temp2 = m_tail;
    m_tail = other.m_tail;
    other.m_tail = temp2;
 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NON_MEMBER FUNCTION IMPLEMENTATIONS///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void unite(const Set& s1, const Set& s2, Set& result){
    Set Empty;
    
    ItemType storage;
    
    for(int k = 0; k < s1.size(); k++){
        s1.get(k, storage);
        Empty.insert(storage);
    }
    for(int k = 0; k < s2.size(); k++){
        s2.get(k, storage);
        Empty.insert(storage);
    }
    result.swap(Empty);
}


void butNot(const Set& s1, const Set& s2, Set& result){
    Set Empty;
    
    ItemType storage;
    
    for(int k = 0; k < s1.size(); k++){
        s1.get(k, storage);
        if(!s2.contains(storage)){
            Empty.insert(storage);
        }
    }
    result.swap(Empty);
}

