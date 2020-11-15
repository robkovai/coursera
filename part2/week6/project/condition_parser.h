#pragma once

#include <memory>
#include <iostream>

#include "node.h"

std::shared_ptr<Node> ParseCondition(std::istream& is);
