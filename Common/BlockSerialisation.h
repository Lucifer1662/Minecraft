#pragma once
#include <ostream>
#include <istream>
#include "Block.h"
#include "StandardBlock.h"

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Block>& block);
std::istream& operator>>(std::istream& is, std::shared_ptr<Block>& block);
