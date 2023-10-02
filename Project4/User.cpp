#include "User.h"

#include <string>
#include <vector>
using namespace std;
//CHECK IF CAN USE NAMESPEACE STD

User::User(const string& full_name, const string& email, const vector<string>& watch_history)
{
    m_fullName = full_name;
    m_email = email;
    m_watchedMovies = watch_history;
}

string User::get_full_name() const
{
    return m_fullName;  // Replace this line with correct code.
}

string User::get_email() const
{
    return m_email;  // Replace this line with correct code.
}

vector<string> User::get_watch_history() const
{
    return m_watchedMovies;  // Replace this line with correct code.
}
