#pragma once

#include <Wt/Dbo/Dbo>
#include <Wt/WDateTime>

namespace dbo = Wt::Dbo;

class Auth_token;
class User;

namespace Wt {
namespace Dbo {
template<>
struct dbo_traits<Auth_token> : public dbo_default_traits {
    using IdType = std::string;
    static IdType invalidId() { return std::string(); }
    static const char* surrogateIdField() { return nullptr; }
};
}
}

struct Auth_token {
    Auth_token() {};
    Auth_token(const std::string& value, const Wt::WDateTime& expires)
            : value(value), expires(expires) {}

    std::string value;
    Wt::WDateTime expires;
    dbo::ptr<User> user;

    template<typename Action>
    void persist(Action& a)
    {
        dbo::id(a, value, "value");
        dbo::field(a, expires, "expires");
        dbo::belongsTo(a, user, "user", dbo::OnDeleteCascade);
    }
};

DBO_EXTERN_TEMPLATES(Auth_token);
