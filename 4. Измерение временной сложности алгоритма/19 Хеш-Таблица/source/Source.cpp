#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <fstream>
#include <intrin.h>

using namespace std;

typedef unordered_multimap<int, int> HT;

auto keySel = [](auto pair) {return pair.first;};  //Лямбда функции (селекторы пары)
auto valSel = [](auto pair) {return pair.second;};

void getInf(const HT& T, char name)
{
	if (!T.empty()) {
		unsigned n = T.bucket_count();
		for (unsigned i = 0; i<n; ++i) {
			cout << "A[" << i << "]: ";
			for (auto it = T.cbegin(i); it != T.cend(i); ++it)
				cout << "{" << it->first << ":" << it->second << "} ";
			cout << "\n";
		}
	}
	else
		cout << "Хеш-таблица " << name << " пустая";
	cout << endl;
}
//***********************************************************************
void getInfSeq(const HT& T, char name)
{
	if (!T.empty()) {
		cout << name << " = <";
		int s = T.size();
		for (int i = 0; i < s; ++i) {
			for (HT::const_iterator it = T.cbegin(); it != T.cend(); ++it)
				if (it->second == i) {
					cout << it->first << ' ';
					break;
				}
		}
		cout << "\b>" << endl;
	}
	else
		cout << name << " - Пустая последовательность!"<<endl;
}
//***********************************************************************
void genSet(HT& T, int arrPower, int hPower)
{
	T.clear();
	for (int i = 0; i < arrPower; ++i) {
		T.insert(HT::value_type((rand() % hPower + 1), i));
	}
}
//***********************************************************************
int concat(HT& leftExp, const HT &rightExp)
{
	if (!rightExp.empty()) {
		int newPos = leftExp.size();
		int s = rightExp.size();
		for (int i = 0; i < s; ++i) {
			for (HT::const_iterator it = rightExp.cbegin(); it != rightExp.cend(); ++it)
				if (it->second == i) {
					leftExp.insert(HT::value_type((*it).first, newPos++));
					break;
				}
		}
	}
	return leftExp.size();
}
//***********************************************************************
int erase(HT& T, int start, int finish)
{
	if (!T.empty()) {
		int s = T.size();
		for (int i = start; i < s && i <= finish; ++i) {
			for (HT::iterator it = T.begin(); it != T.end(); ++it)
				if (it->second == i) {
					T.erase(it);
					break;
				}
		}
		for (auto &temp : T)
			if (temp.second >= finish)
				temp.second = temp.second - (finish - start) - 1;
	}
	return T.size();
}
//***********************************************************************
int excl(HT& leftExp, const HT& rightExp)
{
	int stPos = -1, curPos = -1, step = 0;
	
	if (!rightExp.empty() && !leftExp.empty()) {
		if (leftExp.size() < rightExp.size())
			return 1;
		int sizeL = leftExp.size();
		int sizeR = rightExp.size();
		for (int i = 0; i < sizeL && (curPos - stPos + 1) != sizeR; ++i) {
			for (HT::const_iterator itL = leftExp.cbegin(); itL != leftExp.cend(); ++itL)
				if (itL->second == i) {
					if (stPos == -1) {
						HT::const_iterator itR = rightExp.cbegin();
						for (; itR != rightExp.cend() && itR->second != 0; ++itR);
						if (itR->first == itL->first)
							curPos = stPos = itL->second;
					}
					else
						for (HT::const_iterator itR = rightExp.cbegin(); itR != rightExp.cend(); ++itR)
							if (itR->first == itL->first) {
								if (itL->second > curPos && itL->second - curPos == 1) {
									curPos = itL->second;
								}
							}
					if ((curPos - stPos +1) == sizeR)
						break;
					if (curPos != itL->second)
						stPos = -1;
				}
		}

		if(stPos!=-1)
			erase(leftExp, stPos, stPos + rightExp.size()-1);
		else return -1;
	}
	return leftExp.size();
}
//***********************************************************************
int mapAnd(const HT& leftExp, const HT& rightExp, HT& result)
{
	result.clear();
	vector<int> vl(leftExp.size()), vr(rightExp.size()), vm;
	transform(leftExp.begin(), leftExp.end(), vl.begin(), keySel);  
	transform(rightExp.begin(), rightExp.end(), vr.begin(), keySel);
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	set_intersection(vl.cbegin(), vl.cend(), vr.cbegin(), vr.cend(), inserter(vm, vm.begin()));
	int i = 0;
	for (auto it = vm.cbegin(); it != vm.cend(); ++it, ++i)
		result.insert(HT::value_type((*it), i));
	return result.size();
}
//***********************************************************************

int mapOr(const HT& leftExp, const HT& rightExp, HT& result)
{
	result.clear();
	vector<int> vl(leftExp.size()), vr(rightExp.size()), vm;
	transform(leftExp.begin(), leftExp.end(), vl.begin(), keySel);   
	transform(rightExp.begin(), rightExp.end(), vr.begin(), keySel); 
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	set_union(vl.cbegin(), vl.cend(), vr.cbegin(), vr.cend(), inserter(vm, vm.begin()));
	int i=0;
	for (auto it = vm.cbegin(); it != vm.cend(); ++it, ++i)
		result.insert(HT::value_type((*it), i));
	return result.size();
}
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	setlocale(0, ".1251");
	srand(time(nullptr));
	ofstream fout("in.txt");
	if (!fout) return 1;
	int countOfExperiments = (rand() % 101)+150; //от 150 до 250
	fout << countOfExperiments << "\n";
	unsigned _int64 t1, t2;
	for (int tempCount = 0; tempCount < countOfExperiments; ++tempCount)
	{
		try{
			HT Els[5];
			int size = 0, temp, sets = 4;
			for (int i = 0; i < 4; ++i) {
				temp = (rand() % 101) + 40; //мощность множества от 40 до 140
				size += temp;
				genSet(Els[i], temp, 1000);
			}
			t1 = __rdtsc();
			size += concat(Els[1], Els[3]); ++sets;
			size += concat(Els[2], Els[3]); ++sets;
			size += mapAnd(Els[1], Els[2], Els[4]); ++sets;
			size += mapOr(Els[4], Els[2], Els[3]); ++sets;
			size += excl(Els[2], Els[4]); ++sets;
			size += excl(Els[1], Els[4]); ++sets;
			size += erase(Els[4], rand()%20, rand()%100 + 20); ++sets;
			size += erase(Els[0], rand() % 20, rand() % 100 + 20); ++sets;
			size += concat(Els[2], Els[0]); ++sets;
			size += concat(Els[2], Els[2]); ++sets;
			size += mapOr(Els[2], Els[3], Els[0]); ++sets;
			t2 = __rdtsc();
			size /= sets;
			fout << size << ' ' << static_cast<double>(t2 - t1) << '\n';
		}
		catch (...) {
			cout << "Произошёл сбой!" << endl;
		}
	}
	return 0;
}