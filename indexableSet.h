#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <iterator>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : std::set<T, COMPARE> {
	using container = std::set<T, COMPARE>;
	using container::container;
	using size_type = typename container::size_type;
	using reference = typename container::reference;
	using const_reference = typename container::const_reference;

public:
	const_reference at(size_type index) const {
		if (index < this->size()) {
			auto it{this->begin()};
			advance(it, index);
			return *it;
		}
		else {
			throw std::out_of_range{"index not in set range!!!"};
		}

	}

	const_reference operator[](size_type index) const {
		return this->at(index);
	}

	reference front(size_type index) {
		return this[0];
	}

	reference back(size_type index) {
		return this[this->size() - 1];
	}





};



#endif /* SRC_INDEXABLESET_H_ */
