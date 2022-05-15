#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <tuple>

#include "sortedView.hpp"


/**
 * @brief Represents a large object
 */
struct LargeObject {
	LargeObject() = default;

	LargeObject(uint64_t num)
		: order{num}
		{}

	// Copy operation is expensive, disable it
	LargeObject(const LargeObject&) = delete;
	LargeObject& operator=(const LargeObject&) = delete;

	// Move could be fine, but example should not use it!
	LargeObject(LargeObject&&) = delete;
	LargeObject& operator=(LargeObject&&) = delete;

	uint64_t getOrder() const {
		return order;
	}

	// TODO: Use three-way comparison when using C++20
	bool operator<(const LargeObject& rhs) const {
		return this->getOrder() < rhs.getOrder();
	}

private:
	uint64_t order = 0;
};


static void sortedViewExample() {
	// Allocating large objects in the stack is always a bad idea,
	// but I would like to try the array deduction
	std::array collection{
		LargeObject{47},
		LargeObject{91},
		LargeObject{20},
		LargeObject{40},
		LargeObject{8}
	};

	std::cout << "Default order of elements" << std::endl;

	{	// Capture this block so it is not interfering with others
		std::ostringstream listElements;

		for (const auto& el : collection) {
			listElements << el.getOrder() << ", ";
		}

		std::cout << "[" << listElements.str() << "]" << std::endl;
	}

	{
		using collectionType = decltype(collection);
		const auto sortedCollection = sortedView<collectionType>(std::cbegin(collection), std::cend(collection),
			std::less<collectionType::value_type>()
		);

		/* TODO: Use boost to avoid trailing comma (if I remember correctly, it is something like)
		boost::algorithm::join(collection | boost::adaptors::transformed(
			[](const auto& largeObject) { return largeObject.get().getOrder(); }
		), ", ");
		*/

		std::ostringstream listElements;
		for (const auto& el : sortedCollection) {
			listElements << el.get().getOrder() << ", ";
		}

		std::cout << "[" << listElements.str() << "]" << std::endl;
	}
}


/**
 * @brief Example program entry point
 * 
 * @return int 0 (success)
 */
int main() {
	std::cout << "Hello" << std::endl;

	sortedViewExample();

	return 0;
}
