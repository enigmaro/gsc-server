#pragma once

#include "specializations.h"

#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/WDateTime>

namespace dbo = Wt::Dbo;

class File_data;
class Submission;

class File_meta
{
public:
    File_meta() {}

    const std::string& name() const { return name_; }
    const dbo::weak_ptr<File_data>& file_data() const { return file_data_; }
    int line_count() const { return line_count_; }
    const dbo::ptr<Submission>& submission() const { return submission_; }

    static dbo::ptr<File_meta>
    upload(const std::string& name,
           const std::string& contents,
           const dbo::ptr<Submission>&);

private:
    std::string              name_;
    Wt::WDateTime            time_stamp_;
    int                      line_count_;
    dbo::ptr<Submission>     submission_;
    dbo::weak_ptr<File_data> file_data_;

public:
    template<typename Action>
    void persist(Action& a)
    {
        dbo::field(a, name_, "name");
        dbo::field(a, time_stamp_, "time_stamp");
        dbo::field(a, line_count_, "line_count");
        dbo::belongsTo(a, submission_, "submission", dbo::OnDeleteCascade);
        dbo::hasOne(a, file_data_, "file_meta");
    }
};

DBO_EXTERN_TEMPLATES(File_meta);
