#pragma once

#include <cstdlib>
#include <functional>
#include <iterator>
#include <vector>


// TODO: SFINAE with operator> and operator< checking
// Use C++20 concepts?
/**
 * @brief Create a vector of reference_wrappers in an incremental order from the iterator range 
 * 
 * @tparam Container container type to order
 * @tparam ConstIt container from and to iterators 
 * @param from iterator start
 * @param to iterator end
 * @return auto vector of reference_wrappers to the object
 */
template<typename Container, typename ConstIt = typename Container::const_iterator>
auto sortedView(ConstIt from, ConstIt to) {
	std::vector<std::reference_wrapper<const typename Container::value_type> > viewContainer;

	// Allocate space for each element
	const auto itemCount = static_cast<std::size_t>(std::abs(std::distance(from, to)));
	viewContainer.reserve(itemCount);

	// Insert a const ref to each element
	std::transform(from, to, std::back_inserter(viewContainer), 
		[](const auto& el){ return std::cref(el); }
	);

	// Sort the vector of references in order
	std::sort(std::begin(viewContainer), std::end(viewContainer), 
		[](const auto& lhs, const auto& rhs){ return lhs.get() < rhs.get(); }
	);

	return viewContainer;
}
