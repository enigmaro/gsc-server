#pragma once

#include <Wt/WCompositeWidget.h>
#include <Wt/Dbo/ptr.h>

namespace Wt {
class WContainerWidget;
}

class User;
class Session;

class Profile_view : public Wt::WCompositeWidget
{
public:
    Profile_view(Wt::Dbo::ptr<User> const&, Session&);

private:
    Wt::Dbo::ptr<User> user_;
    Session& session_;
    Wt::WContainerWidget* impl_;
};
