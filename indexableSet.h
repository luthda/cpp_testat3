#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <iterator>
#include <stdexcept>
#include <functional>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE> {
	using container = std::set<T, COMPARE>;
	using container::container;
	using const_reference = typename container::const_reference;
	using difference_type = typename container::difference_type;

	const_reference elementAt(difference_type index) const {
		if (index < 0) index += this->size();
		auto it{this->begin()};
		return *std::next(it, index);
	}

public:
	const_reference at(difference_type index) const {
		difference_type signedSize = this->size();
		if (index >= signedSize || index < -signedSize) throw std::out_of_range{"index not in set range!!!"};
		return elementAt(index);
	}

	const_reference operator[](difference_type index) const {
		return at(index);
	}

	const_reference back() const {
		return at(-1);
	}

	const_reference front() const {
		return this->at(0);
	}
};
#endif /* SRC_INDEXABLESET_H_ */
