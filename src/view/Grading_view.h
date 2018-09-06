#pragma once

#include "Abstract_file_view.h"

#include <Wt/Dbo/ptr.h>

class Self_eval;
class Session;

class Grading_view : public Abstract_file_view
{
public:
    Grading_view(const Wt::Dbo::ptr<Self_eval>, Session&);

private:
    Wt::Dbo::ptr<Self_eval> model_;
};
