#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>




class UserDatabase;
class MovieDatabase;


struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};


//Custom struct created to allow the necessary comparisons upon Set STL insertion
struct MovieRankComparison
{
    MovieRankComparison(const std::string& id, int score, const MovieDatabase* mDatabase){
        movie_id = id;
        compatibility_score = score;
        mdb = mDatabase;
    }
    const MovieDatabase* mdb;
    std::string movie_id;
    int compatibility_score;
   
};




class Recommender
{
  public:
    Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database);
    std::vector<MovieAndRank>  recommend_movies(const std::string& user_email, int movie_count) const;

  private:
    const UserDatabase* m_udb;
    const MovieDatabase* m_mdb;
    
    
};

#endif // RECOMMENDER_INCLUDED
