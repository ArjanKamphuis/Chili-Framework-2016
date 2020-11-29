#pragma once

#include <vector>

// remove an element from a vector
// messes up the order of elements
// (faster than erase and doesn't need iter)
template<typename T>
inline void remove_element(std::vector<T>& vec, size_t index)
{
	std::swap(vec[index], vec.back());
	vec.pop_back();
}
