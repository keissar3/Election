#pragma once

template<class InputIterator, class T>
InputIterator Myfind(InputIterator begin, InputIterator end, const T& value)
{
	while (begin != end) {
		if (*begin == value)
			return begin;
		begin++;
	}
	return end;
}