// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <memory>

namespace server
{
class BoardProducer;
using BoardProducerPtr = std::shared_ptr<BoardProducer>;
}