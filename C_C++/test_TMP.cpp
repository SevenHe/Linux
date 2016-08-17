#include <iostream>
using namespace std;

template <class T>
void swap(T t) {
	cout << "Class T" << endl;
}

template <typename T1>
void swap(T1* t) {
	cout << "Pointer T" << endl;
}

template <typename T2, typename U>
void swap(const T2 t, U dv = 0) {
//	typedef 	U		default_value;
	typedef 	T2 		value_type;
	cout << "Const T" << t << endl;
}

int main()
{
	return 0;
}
