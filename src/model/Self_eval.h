#pragma once

#include "Abstract_evaluation.h"
#include "Grader_eval.h"

#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Json/Object.h>
#include <Wt/WDateTime.h>

namespace dbo = Wt::Dbo;

class Eval_item;
class Grader_eval;
class Submission;
class User;

class Self_eval : public Abstract_evaluation
{
public:
    Self_eval() {}
    Self_eval(const dbo::ptr<Eval_item>&,
              const dbo::ptr<Submission>&);

    const dbo::ptr<Eval_item>& eval_item() const override { return eval_item_; }
    const dbo::ptr<Submission>& submission() const override { return submission_; }

    dbo::ptr<Grader_eval> grader_eval() const { return grader_eval_.lock(); }
    const std::string& permalink() const { return permalink_; }

    std::string eval_url() const;
    std::string grade_url() const;

    std::string score_string(Viewing_context const&) const override;
    std::string owner_string(Viewing_context const&) const override;

    static dbo::ptr<Self_eval> find_by_permalink(dbo::Session&,
                                                 const std::string&);
    static std::string find_ungraded_permalink(dbo::Session&,
                                               const dbo::ptr<User>&);

    static dbo::collection<dbo::ptr<Self_eval>>
    find_with_grade_status(Grader_eval::Status, dbo::Session&);

    std::string rest_uri() const;
    Wt::Json::Object to_json(Viewing_context const&) const;

private:
    dbo::ptr<Eval_item>        eval_item_;
    dbo::ptr<Submission>       submission_;
    dbo::weak_ptr<Grader_eval> grader_eval_;
    std::string                permalink_;

public:
    static const int permalink_size = 16;

    template<typename Action>
    void persist(Action& a)
    {
        dbo::belongsTo(a, eval_item_, "eval_item", dbo::OnDeleteCascade);
        dbo::belongsTo(a, submission_, "submission", dbo::OnDeleteCascade);
        dbo::hasOne(a, grader_eval_, "self_eval");
        dbo::field(a, permalink_, "permalink", permalink_size);
        Abstract_evaluation::persist_(a);
    }
};

DBO_EXTERN_TEMPLATES(Self_eval)
