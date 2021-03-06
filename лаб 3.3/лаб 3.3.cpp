// лаб 3.3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void* part_seq(void* arr, size_t num, size_t size, int(*pfun)(const void*)) {
	size_t j, t;
	char  c, *q;
	char* p = (char*)arr;
	char* i = (char*)arr;
	char* e = (char*)arr + (num * size);

	while (i < e) {
		if ((*pfun)(i)) {
			if (sizeof(size_t) == size) {
				for (q = i; q > p; q -= size) {
					t = *(size_t*)q;
					*(size_t*)q = *(size_t*)(q - size);
					*(size_t*)(q - size) = t;
				}
			}
			else {
				for (q = i; q > p; q -= size) {
					for (j = 0; j < size; ++j) {
						c = *(q + j);
						*(q + j) = *(q - size + j);
						*(q - size + j) = c;
					}
				}
			}
			p += size;
		}
		i += size;
	}
	return (void*)p;
}

static int compare(const void* a) {
	return *(int*)a == 0;
}

int main(void) {
	int*   p, *e;
	int    a[] = { 0, 1, 0, 0, 2, 3, 0, 4, 0, 5 };
	size_t   n = sizeof(a) / sizeof(a[0]);

	e = (int*)part_seq(a, n, sizeof(a[0]), &compare);

	for (p = &a[0]; p != &a[n]; ++p)
		printf("%d ", *p);
	putchar('\n');
	return 0;
}