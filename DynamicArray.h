#pragma once
#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 1) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}
	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }


	// start -------  iterator
	class iterator
	{
	private:
		DynamicArray* _da;
		int			  _i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;

		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}
		iterator() = default;

		friend class const_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}

		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}


		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}

		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			++_i;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--() {
			--_i;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--_i;
			return temp;
		}

		iterator operator+(int num) const {
			return iterator(*_da, _i + num);
		}
		iterator operator-(int num) const {
			return iterator(*_da, _i - num);
		}
	};
	// end -----------  iterator

	// start ----------- const_iterator
	class const_iterator
	{
	private:
		const DynamicArray* _da;
		int			  _i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}
		const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}
		friend class const_iterator;

		const const_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}
		const const_iterator& operator=(const const_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const const_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const const_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		const_iterator& operator++() {
			++_i;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator temp(*this);
			++_i;
			return temp;
		}
		const_iterator& operator--() {
			--_i;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator temp(*this);
			--_i;
			return temp;
		}

		const_iterator operator+(int n)
		{
			_i += n;
			return*this;
		}




	};
	// end ------------ const_iterator


		// start -------  reverse_iterator
	class reverse_iterator
	{
	private:
		DynamicArray* _da;
		int			  _i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		reverse_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		reverse_iterator(const reverse_iterator& other) : _da(other._da), _i(other._i) {}

		// in const_iterator:	const_iterator(const iterator& other)
		//     					operator=(const iterator& other)

		const reverse_iterator& operator=(const reverse_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const reverse_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const reverse_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		reverse_iterator& operator++() {
			--_i;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			--_i;
			return temp;
		}
		reverse_iterator& operator--() {
			++_i;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			++_i;
			return temp;
		}

		reverse_iterator operator+(int num) const {
			return reverse_iterator(*_da, _i + num);
		}
		reverse_iterator operator-(int num) const {
			return reverse_iterator(*_da, _i - num);
		}


	};
	// end -----------  reverse_iterator










	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	const iterator& erase(const iterator& iterToErase)
	{

		T* temp = new T[_physicalSize];
		int wi = 0;  //write index
		iterator iterIndex = this->begin();
		iterator iterEnd = this->end();
		int returnedIterindex = _physicalSize;

		for (int i = 0; i <= _physicalSize; i++)
		{

			if (iterIndex != iterToErase)
			{
				temp[wi] = *iterIndex;
				iterIndex++; wi++;
			}
			else
			{
				_logicalSize--;
				returnedIterindex = wi - 1; // keep the index previous the deleted one and return it
				iterIndex++;
			}
		}

		delete[] _arr;
		_arr = temp;

		return iterator(*this, returnedIterindex);
	}

	// TODO 
	const iterator& erase(const iterator& first, const iterator& last)
	{
		T* temp = new T[_physicalSize];
		int writeIdx = 0;
		int returnedIterindex = 0;
		int count = 0;
		iterator iterIndex = this->begin();
		iterator end = this->end();

		for (int i = 0; i < _logicalSize; i++)
		{
			if (iterIndex == first)
			{
				returnedIterindex = count - 1;

				while (iterIndex != (last + 1) && iterIndex != end)
				{
					iterIndex++;
					++i;
				}
				i--;
			}
			else
			{
				temp[writeIdx] = *iterIndex;
				iterIndex++;
				writeIdx++;
				count++;
			}

		}

		if (first == this->begin() && last == this->end())
			returnedIterindex = 0;

		delete[] _arr;
		_arr = temp;
		_logicalSize = writeIdx;
		return iterator(*this, returnedIterindex);
	}

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}
	const_iterator cend() const {
		return const_iterator(*this, _logicalSize);
	}

	reverse_iterator rbegin() const {
		return reverse_iterator(*this, 0);
	}
	reverse_iterator rend() const {
		return reverse_iterator(*this, _logicalSize);
	}

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	T* _arr;
	int _logicalSize;
	int _physicalSize;
};