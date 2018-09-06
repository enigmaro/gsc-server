#pragma once

#include "../model/Session.h"
#include "File_manager_view.h"

#include <Wt/WContainerWidget.h>

class Named_tab_widget;

class Session;

class Main_view : public Wt::WContainerWidget
{
public:
    Main_view(Session&, Wt::WContainerWidget* parent = nullptr);

    void set_title(const Wt::WString&);
    void set_widget(std::unique_ptr<Wt::WWidget>);

private:
    Wt::WText* title_;
    Wt::WContainerWidget* root_;
    Session& session_;
};
