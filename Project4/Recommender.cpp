#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"


#include <string>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

//comparison operator for set insertion
bool operator<(const MovieRankComparison& a, const MovieRankComparison& b)
{
    if(a.compatibility_score > b.compatibility_score)
        return true;
    else if(b.compatibility_score > a.compatibility_score)
        return false;
    else{
        Movie* MovieA = a.mdb->get_movie_from_id(a.movie_id);
        Movie* MovieB = b.mdb->get_movie_from_id(b.movie_id);
        if(MovieA->get_rating() > MovieB->get_rating()){
            return true;
        }
        else if(MovieB->get_rating() > MovieA->get_rating()){
            return false;
        }
        else{
            if(MovieA->get_title() > MovieB->get_title()){
                return true;
            }
            else{
                return false;
            }
        }

    }
}





Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_udb = &user_database;
    m_mdb = &movie_database;
    
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)  const
{
    //first add all the items the player has watched to an unordered map from movie id to score
    //then move calculated scores and movies to a set that will order these movies properly
    //then move the amount of recommendations the user requested from the set to the final vector and return
    std::unordered_map<std::string, int> movieToCompatability;
    set<MovieRankComparison> orderedMovies;
    vector<MovieAndRank> finalVector;
    
    User* currUser = m_udb->get_user_from_email(user_email);
    
    if(currUser == nullptr || movie_count <= 0){
        return finalVector;
    }
    
    currUser->get_watch_history();
    
    //for all the movies the player has watched
    for(int k = 0; k <  currUser->get_watch_history().size(); k++){
        Movie* currMovie = m_mdb->get_movie_from_id(currUser->get_watch_history()[k]);
        
        //get the movies with the same directors and add it in to the map with proper score(accounting for previous inclusion)
        for(int n = 0; n < currMovie->get_directors().size(); n++){
            vector<Movie*> movieWithDirector = m_mdb->get_movies_with_director(currMovie->get_directors()[n]);
            for(int x = 0; x < movieWithDirector.size(); x++){
                pair<unordered_map<string, int>::iterator, bool> result = movieToCompatability.insert(make_pair(movieWithDirector[x]->get_id(), 20));
                if(!result.second){
                    result.first->second += 20;
                }
            }
        }
        //get the movies with the same actors and add it in to the map with proper score(accounting for previous inclusion)
        for(int n = 0; n < currMovie->get_actors().size(); n++){
            vector<Movie*> movieWithActor = m_mdb->get_movies_with_actor(currMovie->get_actors()[n]);
            for(int x = 0; x < movieWithActor.size(); x++){
                pair<unordered_map<string, int>::iterator, bool> result = movieToCompatability.insert(make_pair(movieWithActor[x]->get_id(), 30));
                if(!result.second){
                    result.first->second += 30;
                }
            }
        }
        //get the movies with the same genres and add it in to the map with proper score(accounting for previous inclusion)
        for(int n = 0; n < currMovie->get_genres().size(); n++){
            vector<Movie*> movieWithGenre = m_mdb->get_movies_with_genre(currMovie->get_genres()[n]);
            for(int x = 0; x < movieWithGenre.size(); x++){
                pair<unordered_map<string, int>::iterator, bool> result = movieToCompatability.insert(make_pair(movieWithGenre[x]->get_id(), 1));
                if(!result.second){
                    result.first->second += 1;
                }
            }
        }
        
    }
    //if its been watched by the person then dont add it to the map
    for(int k = 0; k <  currUser->get_watch_history().size(); k++){
        movieToCompatability.erase(currUser->get_watch_history()[k]);}
    
    //moving from unordered map to a (ordered) set
    for (const pair<string, int> movie : movieToCompatability) {
        MovieRankComparison mrc(movie.first, movie.second, m_mdb);
        orderedMovies.insert(mrc);
    }
    
    //adding everything to final vector
    set<MovieRankComparison>::iterator it = orderedMovies.begin();
    int count = 0;
    while(it != orderedMovies.end() && count < movie_count){
        string movieID = it->movie_id;
        int compatability = it->compatibility_score;
        finalVector.push_back(MovieAndRank(movieID, compatability));
        count++;
        it++;
    }
    
    return finalVector; 
}
