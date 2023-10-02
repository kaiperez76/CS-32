//
//  History.cpp
//  Project 1(CS 32)
//
//  Created by Kai Perez on 1/11/23.
//

#include <iostream>
#include "History.h"
#include "Arena.h"
#include "globals.h"

History::History(int nRows, int nCols){
    
    m_Row = nRows;
    m_Col = nCols;
    
    for(int r = 0; r < nRows; r++){
        for(int c = 0; c < nCols; c++){
            numGrid[r][c] = 0;
            letterGrid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c){
    
    if(r < 1 || r > m_Row)
        return false;
    if(c < 1 || c > m_Col)
        return false;
    
    numGrid[r - 1][c -1] += 1;
    
    //need to assign letters by updated number grid. can do it by using ASCII or hardcoding each one
    
    if (numGrid[r-1][c-1] == 1){
        letterGrid[r-1][c-1] = 'A';
        return true;}
    if (numGrid[r-1][c-1] > 25){
        letterGrid[r-1][c-1] = 'Z';
        return true;}
    if(numGrid[r-1][c-1] < 25 && numGrid[r-1][c-1] > 0){
        letterGrid[r-1][c-1] += 1;
    }
        
    

                
 
    
    return true;
}

void History::display() const{
    clearScreen();
    for (int r = 0; r < m_Row; r++){
        for (int c = 0; c < m_Col; c++){
            cout << letterGrid[r][c];}
        cout << endl;
    }
    cout << endl;
}


