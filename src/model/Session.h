#pragma once

#include "auth/User_database.h"
#include "auth/User.h"

#include <Wt/Auth/Login.h>
#include <Wt/Auth/AbstractUserDatabase.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/SqlConnectionPool.h>

#include <vector>

class User;
class User_stats;

class Session : public Wt::Dbo::Session
{
public:
    Session(Wt::Dbo::SqlConnectionPool&);

    Wt::Auth::AbstractUserDatabase& users();

    Wt::Auth::Login& login() { return login_; }

    Wt::Dbo::Session& dbo() { return *this; };

    Wt::Dbo::ptr<User> user() const;

    std::string user_name() const;

    Wt::Dbo::ptr<User> create_user(const std::string& username,
                                   const std::string& password,
                                   User::Role role = User::Role::Student);

    void become_user(const Wt::Dbo::ptr<User>&);

    std::vector<dbo::ptr<User_stats>> top_users(int limit);
    int find_ranking();
    void add_to_score(int s);

    static void map_classes(Wt::Dbo::Session&);

    static void configureAuth();

    static std::unique_ptr<Wt::Dbo::SqlConnectionPool>
    createConnectionPool(const std::string&);

    static const Wt::Auth::AuthService& auth();

    static const Wt::Auth::AbstractPasswordService& passwordAuth();

private:
    User_database users_;
    Wt::Auth::Login login_;

    mutable Wt::Dbo::ptr<User> user_;

    void create_index(const char* table, const char* field, bool unique = true);
};

