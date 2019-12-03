#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <set>
#include <iterator>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE> {
	using container = std::set<T, COMPARE>;
	using container::container;
	using const_reference = typename container::const_reference;

	const_reference move(int index) const {
		auto it{this->begin()};
		auto pointer = std::next(it, index);
		return *pointer;
	}

	void emptyCheck() const {
		if (this->empty()) {
			throw std::out_of_range{"empty set!!"};
		}
	}

public:
	const_reference at(int index) const {
		int signedSize = this->size();
		if (index < signedSize && index >= -signedSize) {
			if (index < 0) index += signedSize;
			return move(index);
		}
		else {
			throw std::out_of_range{"index not in set range!!!"};
		}
	}

	const_reference operator[](int index) const {
		return this->at(index);
	}

	const_reference back() const {
		emptyCheck();
		return this->at(this->size() - 1);
	}

	const_reference front() const {
		emptyCheck();
		return this->at(0);
	}
};




#endif /* SRC_INDEXABLESET_H_ */
