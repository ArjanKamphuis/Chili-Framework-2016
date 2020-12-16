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

// binary search finds matching element
// otherwise returns end
// Acc is a functor used to access the search keys in the elements
template <class Iter, typename T, typename Acc>
auto binary_find(Iter begin, Iter end, const T& val, Acc acc = [](const Iter::value_type& obj)->const Iter::value_type& { return obj; })
{
	const auto it = std::lower_bound(begin, end, val,
		[acc](const Iter::value_type& lhs, const T& rhs)
		{
			return acc(lhs) < rhs;
		});

	if (it != end && !(val < acc(*it)))
		return it;
	else
		return end;
}

// uses remove_if to remove elements matching predicate over entire container
// and then calls erase to remove the 'empty' husks at the end
template<class Container, class Pred>
void remove_erase_if(Container& container, Pred pred)
{
	// this destroys all elements matching the predicate
	// and fills the spaces with elements from the end
	const auto new_end = std::remove_if(container.begin(), container.end(), pred);
	// erase garbage husk element at end
	container.erase(new_end, container.end());
}
