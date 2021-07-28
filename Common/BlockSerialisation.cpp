#include "BlockSerialisation.h"
#include <iostream>

template<typename T>
struct bits {
	const T& t;
	bits(const T& t) : t(t) {}
	bits(bits&&) = default;
	bits(const bits&) = default;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const bits<T>& b) {
	for (size_t i = 0; i < sizeof(T); i++)
	{
		os << ((char*)&b.t)[i];
	}
	return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, const bits<T>& b) {
	for (size_t i = 0; i < sizeof(T); i++)
	{
		is >> ((char*)&b.t)[i];
	}
	return is;
}



std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Block>& block)
{
	//std::cout << bits(block->blockId());

	os << bits(block->blockId());
	//for (auto c : block.dynamicContent())
	//	os << c;
	return os;
}

std::istream& operator>>(std::istream& is, std::shared_ptr<Block>& block)
{
	size_t blockId;
	is >> bits(blockId);
	//std::cout << blockId;
	if (blockId == 0) {
		block = std::make_shared<Air>();
	}
	else {
		block = std::make_shared<Dirt>();
	}

	return is;
}