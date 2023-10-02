//
//  main.cpp
//  Project 2 (CS32)
//
//  Created by Kai Perez on 1/24/23.
//

#include <iostream>
#include <cassert>
#include "Set.h"
using namespace std;


int main(){
    
    string letter = "a";
        Set alpha;
        Set alpha2(alpha);
        Set* alphaP = &alpha;
        assert(alpha2.empty());
        
        assert(alpha.empty()); //tests empty set
        assert(!alpha.contains("a"));
        assert(!alpha.erase("a"));
        assert(alpha.size() == 0);
        assert(!alpha.get(0,letter) && letter == "a");
        alpha.swap(*alphaP);
        
        assert(alpha.insert("a"));
        assert(alpha.insert("b"));
        assert(alpha.insert("c"));
        assert(!alpha.insert("c"));
        assert(alpha.insert("d"));
        
        alpha.swap(alpha2);
        alpha2.swap(alpha);
        
        assert(alpha2.insert("a"));
        assert(alpha2.insert("b"));
        Set result;
        unite(alpha,alpha2,result);
        
        cout << "abcd: " << endl;
        result.dump();
        
        butNot(alpha,alpha2,result);
        cout << "cd: " << endl;
        result.dump();
        unite(result,alpha2, result);
        unite(alpha,alpha,alpha);
        cout << "abcd: " << endl;
        alpha.dump();
        
        
        cout << "abcd: " << endl;
        result.dump();

        cout << "ab: " << endl;
        alpha2.dump();
        
        butNot(result,result,result);
        cout << "Nothing: " << endl;
        result.dump();

 

    Set X;
    assert(X.size() == 0);              //check that size 0
    assert(X.empty());                  //check that it returns as empty;
    assert(!X.erase("Laser"));          //nothing to erase
    assert(X.insert("ades"));           //inserts in to a empty Set
    assert(!X.insert("ades"));          //doesn't insert duplicates
    assert(X.insert("spade"));          //inserts without issue alphabetically
    assert(X.insert("zade"));           //inserts without issue alphabetically
    assert(X.insert("jade"));           //inserts without issue alphabetically
    assert(X.size() == 4);              //check that size is 4
    X.dump();      //print out list forward/backwards to ensure pointers intact after insert
    assert(!X.empty());                 //check that the list is not empty
    assert(X.contains("ades") && X.contains("spade"));  //check that contains is working
    assert(X.erase("jade"));            //check that erase works with pointers intact
    X.dump();      //print out list forward/backwards to ensure pointers intact after erase
    assert(X.erase("spade"));           //check that erase works with pointers intact
    assert(!X.erase("spade"));          //erase doesn't work after item been removed
    assert(X.erase("zade"));            //check that erase works with pointers intact
    assert(X.erase("ades"));            //check that erase works with pointers intact
    assert(X.size() == 0);              //check that size 0
    assert(X.empty());                  //check that it returns as empty;




    ItemType Test = "Test";

    Set Y;
    assert(Y.insert("Avi"));           //inserts without issue alphabetically
    assert(Y.insert("Larsen"));        //inserts without issue alphabetically
    assert(Y.insert("Joey"));          //inserts without issue alphabetically
    assert(Y.insert("Rohit"));          //inserts without issue alphabetically
    assert(Y.get(2, Test));            //get works when indexing within linked list
    assert(Test == "Larsen");          //Saves correct value in to value passed in
    assert(!Y.get(4, Test));           //doesn't work when indexing out of list
    assert(Test == "Larsen");          //value passed in remains unchanged

    Set Z;
    assert(Z.insert("Brady"));          //inserts without issue alphabetically
    assert(Z.insert("Rohit"));          //inserts without issue alphabetically
    assert(Z.insert("Arian"));          //inserts without issue alphabetically
    assert(Z.insert("Jon"));            //inserts without issue alphabetically
    assert(Z.get(2, Test));            //get works when indexing within linked list
    assert(Test == "Jon");              //Saves correct value in to value passed in
    assert(!Z.get(100, Test));           //doesn't work when indexing out of list
    assert(Test == "Jon");              //value passed in remains unchanged


    Y.swap(Z);                    //swapping works and values switch including size
    assert(Y.contains("Arian") && Y.contains("Brady") && Y.size() == 4);
    assert(Z.contains("Avi") && Z.contains("Joey") && Z.size() == 4);




    Set XX;
    Set YY;

    unite(Y, Z, XX);        //unite works
    Set ZZ(XX);             //can initialize a set w a copy constructor
    ZZ.dump();              // ensure pointers intact after unite
    butNot(XX, Y, YY);      //save an identical list to Z in YY
    YY.dump();              //ensure pointers are intact
    ZZ = YY;                //check assignment operator
    ZZ.dump();              //contains corrrect values (YY)
    butNot(XX, Y, XX);      //works while refering to the same set
    XX.dump();              //check contains values in XX and not in Y
    unite(XX, Y, XX);       //works in same set
    XX.dump();              //prints out the Z and Y together
    butNot(XX, XX, XX);     //emptys out the Set
    assert(XX.empty());     //check that set is now empty
    unite(ZZ, ZZ, ZZ);      //checks that string remains the same
    ZZ.dump();              //check that ZZ remains the same

    
    
    
    
    
//      Set ss1;
//      ss1.insert("laobing");
//      Set ss2;
//      ss2.insert("matzo");
//      ss2.insert("pita");
//      ss1.swap(ss2);
//      //ss1.dump();
//      assert(ss1.size() == 2  &&  ss1.contains("matzo")  &&  ss1.contains("pita")  &&
//             ss2.size() == 1  &&  ss2.contains("laobing"));
//
//
//      Set ss;
//          ss.insert("dosa");
//          assert(!ss.contains(""));
//          ss.insert("tortilla");
//          ss.insert("");
//          ss.insert("focaccia");
//          assert(ss.contains(""));
//          ss.erase("dosa");
//          assert(ss.size() == 3  &&  ss.contains("focaccia")  &&  ss.contains("tortilla")  &&
//                      ss.contains(""));
//    std::string v;
//          assert(ss.get(1, v)  &&  v == "focaccia");
//          assert(ss.get(0, v)  &&  v == "");
//
//
//      Set s;
//             assert(s.empty());
//             ItemType x = "arepa";
//             assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
//             s.insert("chapati");
//             assert(s.size() == 1);
//             assert(s.get(0, x)  &&  x == "chapati");
//        std::cout << "Passed all tests" << std::endl;
//    X.insert("Avi");
//    X.insert("Joey");
//    X.insert("sarepas");
//
//    X.dump();
////    Set sss(X);
//  //  sss.dump();
//
//  //  X = Y;
//   // Y.dump();
//   // X.dump();
//
//
//
//    unite(X, Y, s);
//    s.dump();
//
//
//
//    butNot(X, Y, s);
//    s.dump();
//
    
    
   
}
