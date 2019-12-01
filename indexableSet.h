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
	const_reference at(int index) const {
		int actualSize = this->size();
		if (index < 0) {
			index += actualSize;
		}
		if (index < actualSize) {
			auto it{this->begin()};
			std::advance(it, index);
			return *it;
		}
		else {
			throw std::out_of_range{"index not in set range!!!"};
		}

	}

	const_reference operator[](int index) const {
		return this->at(index);
	}

	reference front(int index) {
		return this[0];
	}

	reference back(int index) {
		return this[this->size() - 1];
	}





};



#endif /* SRC_INDEXABLESET_H_ */
