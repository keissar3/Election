#include "Exceptions.h"


int count_digits(int num)
{
	int count = 0;
	while (num != 0) {
		count++;
		num /= 10;
	}
	return count;
}