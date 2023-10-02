#include "UserDatabase.h"
#include "User.h"


#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



UserDatabase::UserDatabase()
{
    
}

UserDatabase::~UserDatabase(){
   vector<User*>::iterator it = m_allocatedUsers.begin();
    while (it != m_allocatedUsers.end()) {
        delete *it;
        it = m_allocatedUsers.erase(it);
    }
}



bool UserDatabase::load(const string& filename)
{
    
    ifstream file(filename);
    string line;
    string name;
    string email;
    string numMovies_str;
    string ID;
    
    if (!file.is_open()){
        return false;}
    
    //if the file is already loaded then return false
    for(int k = 0; k < m_loadedFiles.size();k++){
        if(filename == m_loadedFiles[k]){
            return false;
        }
    }
    m_loadedFiles.push_back(filename);
    
    while (getline(file, line))
    {
        stringstream currline(line);
        getline(currline, name, '\n');
        
        getline(file, line);
        stringstream currline2(line);
        getline(currline2, email, '\n');
        
        getline(file, line);
        stringstream currline3(line);
        getline(currline3, numMovies_str, '\n');
        
        int numMovies = stoi(numMovies_str);
        vector<string> watchedMovies;

        //loop through all of the moviie IDs the person has watched
        for(int k = 0; k < numMovies; k++){
            getline(file, line);
            stringstream currline4(line);
            getline(currline4, ID, '\n');
            watchedMovies.push_back(ID);
        }
        
        User* newUser = new User(name, email, watchedMovies);
        m_allocatedUsers.push_back(newUser);
        m_emailToUser.insert(email, newUser);
        getline(file, line);
        
    
    }
    

    file.close();
    return true;  
}



User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it(m_emailToUser.find(email));

    
    if(it.is_valid()){
        return it.get_value();}
    return nullptr;
}
