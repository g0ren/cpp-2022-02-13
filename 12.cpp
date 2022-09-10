#include <iostream>
#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
#define MIN_N 0
#define MAX_N 100
#define MAX(X, Y) (((X)>(Y))?(X):(Y))
#define MIN(X, Y) (((X)<(Y))?(X):(Y))

void swap(int &a, int &b);
int* fillArrayFromKeyboard();
void printArray(int *ar);
void sort(int *ar);
int* resizeArray(int *ar, int newsize);
int* deleteElement(int *ar, int index);
int* set(int *ar);
bool in(int *ar, int el);

/*
 * Задание 1. Даны два массива: А[M] и B[N] (M и N вводятся
 с клавиатуры). Необходимо создать третий массив мини-
 мально возможного размера, в котором нужно собрать
 элементы массива A, которые не включаются в массив B,
 без повторений.
 *
 */
int* setminus(int *a, int *b) {
	a = set(a);
	b = set(b);
	int *r = new int[a[0]];
	int *ptr = r;
	*ptr = a[0];
	ptr++;
	for (int i = 1; i <= a[0]; i++) {
		if (!in(b, a[i])) {
			*ptr = a[i];
			ptr++;
		}
	}
	return resizeArray(r, ptr - r - 1);
}

/*
 * Задание 2. Даны два массива: А[M] и B[N] (M и N вводятся
 с клавиатуры). Необходимо создать третий массив мини-
 мально возможного размера, в котором нужно собрать
 элементы массивов A и B, которые не являются общими
 для них, без повторений.
 *
 */
int* setxor(int *a, int *b) {
	a = set(a);
	b = set(b);
	int *r = new int[a[0] + b[0]];
	int *ptr = r;
	*ptr = a[0] + b[0];
	ptr++;
	for (int i = 1; i <= a[0]; i++) {
		if (!in(b, a[i])) {
			*ptr = a[i];
			ptr++;
		}
	}
	for (int i = 1; i <= b[0]; i++) {
		if (!in(a, b[i])) {
			*ptr = b[i];
			ptr++;
		}
	}
	return resizeArray(r, ptr - r - 1);
}

int main() {
	int *A { }, *B { }, *R1 { }, *R2 { };
	cout << "Creating array A" << endl;
	A = fillArrayFromKeyboard();
	cout << endl;

	cout << "Creating array B" << endl;
	B = fillArrayFromKeyboard();
	cout << endl;

	A = set(A);
	cout << "Set of A is { ";
	printArray(A);
	cout << "}" << endl;

	B = set(B);
	cout << "Set of B is { ";
	printArray(B);
	cout << "}" << endl;

	R1 = setminus(A, B);
	cout << "A \\ B is { ";
	printArray(R1);
	cout << "}" << endl;

	R2 = setxor(A, B);
	cout << "A xor B is { ";
	printArray(R2);
	cout << "}" << endl;

	delete[] A;
	delete[] B;
	delete[] R1;
	delete[] R2;

	return 0;
}

void printArray(int *ar) {
	for (int i = 1; i <= ar[0]; i++) {
		cout << *(ar + i) << " ";
	}
	//cout << endl;
}

void swap(int &a, int &b) {
	int t { };
	t = a;
	a = b;
	b = t;
}

void sort(int *ar) {
	bool sorted { };
	while (!sorted) {
		sorted = 1;
		for (int i = 1; i < ar[0]; i++) {
			if (ar[i] > ar[i + 1]) {
				sorted = 0;
				swap(ar[i], ar[i + 1]);
			}
		}
	}
}

int* fillArrayFromKeyboard() {
	int size { };
	cout << "Enter array size: ";
	cin >> size;
	int *r = new int[size + 1] { };
	r[0] = size;
	for (int i = 1; i <= size; i++) {
		cout << "Enter element #" << i << ": ";
		cin >> r[i];
	}
	return r;
}

int* resizeArray(int *ar, int newsize) {
	int oldsize { ar[0] };
	int *r = new int[newsize] { };
	r[0] = newsize;
	for (int i = 1; i <= MIN(oldsize, newsize); i++)
		r[i] = ar[i];
	delete[] ar;
	return r;
}

int* deleteElement(int *ar, int index) {
	for (int i = index; i < ar[0]; i++)
		ar[i] = ar[i + 1];
	return resizeArray(ar, ar[0] - 1);
}

int* set(int *ar) {
	sort(ar);
	for (int i = 1; i < ar[0]; i++) {
		if (ar[i] == ar[i + 1])
			return set(deleteElement(ar, i));
	}
	return ar;
}

bool in(int *ar, int el) {
	for (int i = 1; i <= ar[0]; i++)
		if (ar[i] == el)
			return true;
	return false;
}
