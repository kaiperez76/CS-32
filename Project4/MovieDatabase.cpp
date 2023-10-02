#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;




MovieDatabase::MovieDatabase()
{

}

MovieDatabase::~MovieDatabase()
{
    vector<Movie*>::iterator it = m_allocatedMovies.begin();
     while (it != m_allocatedMovies.end()) {
         delete *it;
         it = m_allocatedMovies.erase(it);
     }
}


bool MovieDatabase::load(const string& filename)
{
    ifstream file(filename);
    string line;
    string ID;
    string Title;
    string releaseYear;
    string Director;
    string Actor;
    string Genre;
    string ratingStr;
    
    
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
        getline(currline, ID, '\n');
        
        getline(file, line);
        stringstream currline2(line);
        getline(currline2, Title, '\n');
        
        getline(file, line);
        stringstream currline3(line);
        getline(currline3, releaseYear, '\n');
        
        //read every line till comma
        getline(file, line);
        vector<string> allDirectors;
        stringstream currline4(line);
        while(getline(currline4, Director, ',')){
            allDirectors.push_back(Director);
        }
        
        getline(file, line);
        vector<string> allActors;
        stringstream currline5(line);
        while(getline(currline5, Actor, ',')){
            allActors.push_back(Actor);
        }
        
        
        getline(file, line);
        vector<string> allGenres;
        stringstream currline6(line);
        while(getline(currline6, Genre, ',')){
            allGenres.push_back(Genre);
    
        }
        
       
        getline(file, line);
        stringstream currline7(line);
        getline(currline7, ratingStr, '\n');
        float Rating = stof(ratingStr);
        
        Movie* newMovie = new Movie(ID, Title, releaseYear, allDirectors, allActors, allGenres, Rating);
        
        m_allocatedMovies.push_back(newMovie);
        
        //add movie to different type of maps
        m_idToMovie.insert(ID, newMovie);

        for(int k = 0; k < allDirectors.size(); k++){
            m_directorToMovie.insert(allDirectors[k], newMovie);}
        
        for(int k = 0; k < allActors.size(); k++){
            m_actorToMovie.insert(allActors[k], newMovie);}
        
        for(int k = 0; k < allGenres.size(); k++){
            m_genreToMovie.insert(allGenres[k], newMovie);}
        
        getline(file, line);
        
        
    }
    

    file.close();
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string, Movie*>::Iterator it(m_idToMovie.find(id));

    if(it.is_valid()){
        return it.get_value();}
    return nullptr;

}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    //follows treemm to director and returns all items in its member vector
    vector<Movie*> allMovies;
    TreeMultimap<string, Movie*>::Iterator it(m_directorToMovie.find(director));
    
    while(it.is_valid()){
        allMovies.push_back(it.get_value());
        it.advance();
    }
    return allMovies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    //follows treemm to actor and returns all items in its member vector
    vector<Movie*> allMovies;
    TreeMultimap<string, Movie*>::Iterator it(m_actorToMovie.find(actor));
    
    while(it.is_valid()){
        allMovies.push_back(it.get_value());
        it.advance();
    }
    return allMovies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    //follows treemm to genre and returns all items in its member vector
    vector<Movie*> allMovies;
    TreeMultimap<string, Movie*>::Iterator it(m_genreToMovie.find(genre));
    
    while(it.is_valid()){
        allMovies.push_back(it.get_value());
        it.advance();
    }
    return allMovies; 
}
