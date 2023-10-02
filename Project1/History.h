//
//  History.h
//  Project 1(CS 32)
//
//  Created by Kai Perez on 1/11/23.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
      private:
        int m_Row;
        int m_Col;
        int numGrid[MAXROWS][MAXCOLS];
        char letterGrid[MAXROWS][MAXCOLS];
        
    };


#endif /* History_h */
