#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<iterator>
#include<time.h>
#include<conio.h>
#include<intrin.h>
#include<fstream>

using namespace std;

class mySet {
public:
	set<int> values;
	vector<set<int>::iterator> pointers;
	char name;

	mySet(char n) :name(n) {}
	void gen(int n, int mod) {
		for (int i = 0; i < n; ++i)
			pointers.push_back(values.insert(rand() % (1+mod)).first);
	}
};

int setAnd(mySet A, mySet B, mySet& C) {
	C.values.clear();
	C.pointers.clear();
	set_intersection<set<int>::const_iterator, set<int>::const_iterator, insert_iterator<set<int>>>
		(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	for (auto it = C.values.cbegin(); it != C.values.cend(); ++it)
		C.pointers.push_back(it);
	return C.pointers.size();
}

int setDif(mySet A, mySet B, mySet& C) {
	C.values.clear();
	C.pointers.clear();
	set_difference<set<int>::const_iterator, set<int>::const_iterator, insert_iterator<set<int>>>
		(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	for (auto it = C.values.cbegin(); it != C.values.cend(); ++it)
		C.pointers.push_back(it);
	return C.pointers.size();
}

int erase(mySet& A, int p, int q) {
	if (p > q || A.pointers.empty())
		return 0;
	if (q > A.pointers.size())
		q = A.pointers.size();
	mySet T('A');
	int i = 0;
	for (auto it = A.pointers.cbegin(); it != A.pointers.cend(); ++it, ++i)
		if (i < p || i > q)
			T.pointers.push_back(T.values.insert((*(*it))).first);
	swap(A, T);
	return A.pointers.size();
}

int subst(mySet& A, mySet B, int p) {
	mySet T('A');
	int i = 0;
	auto itA = A.pointers.cbegin();
	for (; itA != A.pointers.cend() && i < p; ++itA, ++i)
		T.pointers.push_back(T.values.insert((*(*itA))).first);
	for (auto it = B.pointers.cbegin(); it != B.pointers.cend(); ++it)
		T.pointers.push_back(T.values.insert((*(*it))).first);
	for (; itA != A.pointers.cend(); ++itA)
		T.pointers.push_back(T.values.insert((*(*itA))).first);
	swap(A, T);
	return A.pointers.size();
}

int change(mySet& A, mySet B, int p) {
	if (p >= A.pointers.size()) {
		for (auto it = B.pointers.begin(); it != B.pointers.end(); ++it)
			A.pointers.push_back(A.values.insert((*(*it))).first);
	}
	else {
		auto itA = A.pointers.begin();
		auto itB = B.pointers.begin();
		int i = 0;
		while (i < p && itA != A.pointers.end()) { ++itA; ++i; }
		for (; itA != A.pointers.end() && itB != B.pointers.end(); ++itA, ++itB)
			*itA = A.values.insert(*(*itB)).first;
		for (; itB != B.pointers.end(); ++itB)
			A.pointers.push_back(A.values.insert((*(*itB))).first);
	}
	return A.pointers.size();
}


int main() {
	ofstream out("in.txt");
	if (!out) return 1;
	srand(time(nullptr));
	int countOfExperiment = 90 + rand() % 150;
	out << countOfExperiment << '\n';
	unsigned __int64 start, finish;
	int size, sets;
	for (int i = 0; i < countOfExperiment; ++i) {
		mySet A('A'), B('B'), C('C'), D('D'), E('E');
		try {
			sets = 4;
			int t = rand() % 250;
			size = t;
			A.gen(t, rand() % 1000);
			t = rand() % 250;
			size += t;
			B.gen(t, rand() % 1000);
			t = rand() % 250;
			size += t;
			C.gen(t, rand() % 1000);
			t = rand() % 250;
			size += t;
			D.gen(t, rand() % 1000);
			
			start = __rdtsc();
			size += setAnd(A, B, E); ++sets;
			size += setDif(E, A, B); ++sets;
			size += erase(D, rand()%5, rand()%500); ++sets;
			size += subst(E, B, rand() % 5); ++sets;
			size += setAnd(C, D, E); ++sets;
			size += erase(A, rand() % 300, rand() % 500); ++sets;
			size += setDif(A, C, B); ++sets;
			size += subst(A, A, rand() % 500); ++sets;
			size += change(D, A, rand() % 500); ++sets;
			size += setAnd(D, B, C); ++sets;
			size += erase(B, rand() % 300, rand() % 500); ++sets;
			size += subst(D, B, rand() % 500); ++sets;
			size += setDif(A, E, A); ++sets;
			size += change(D, A, rand() % 500); ++sets;
			size += subst(C, A, rand() % 500); ++sets;
			size += setAnd(B, A, B); ++sets;
			size += subst(D, B, rand() % 500); ++sets;
			size += (A, C, rand() % 500); ++sets;
			finish = __rdtsc();
			size /= sets;
			out << size << ' ' << static_cast<double>(finish - start) << '\n';
		}
		catch (...) {
			cout << "Что-то произошло, ошибка!";
		}
	}
	return 0;
}