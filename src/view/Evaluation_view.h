#pragma once

#include "../model/auth/User.h"
#include "../model/Submission.h"
#include "../model/Eval_item.h"

#include <Wt/WContainerWidget>
#include <Wt/Dbo/ptr>

#include <vector>

class Session;
class Submission;

class Eval_widget;
class File_viewer_widget;

class Evaluation_view : public Wt::WContainerWidget
{
public:
    Evaluation_view(const Wt::Dbo::ptr<Submission>&,
                    Session&,
                    Wt::WContainerWidget* parent = nullptr);

    void go_to(unsigned int);
    void go_default();

private:
    Wt::Dbo::ptr<Submission> submission_;
    Session& session_;
    User::Role role_;

    File_viewer_widget* viewer_;
    Wt::WContainerWidget* right_column_;

    std::vector<std::unique_ptr<Wt::WWidget>> rows_;

    // Is the current user allowed to change the self evaluation right now?
    bool can_eval_();

    void load_();

    void format_score_(const Eval_item::Type& type, double score,
                       std::ostringstream& fmt) const;

    void add_item_heading_(const Submission::Item& row,
                           WContainerWidget* item_widget) const;
    void add_scores_(const Submission::Item& row,
                     WContainerWidget* item_widget) const;

    friend class Eval_widget;
};