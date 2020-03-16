//
// Created by shdwp on 3/13/2020.
//

#ifndef GLPL_PCH_H
#define GLPL_PCH_H

#include <memory>

using std::unique_ptr;
using std::make_unique;

using std::shared_ptr;
using std::make_shared;

using std::weak_ptr;

using std::move;
using std::forward;

using std::begin;
using std::end;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include "glmisc/util/util.h"

#include <fmt/core.h>
using fmt::format;
using fmt::print;

#endif //GLPL_PCH_H
