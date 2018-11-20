#include <set>
#include <cstdio>
#include <functional>
#include "sla.hxx"

int main(){
	std::set<int, std::less<int>, SlabAllocator<int>> l;
	l.insert(1);
	l.insert(5);
	l.insert(3);
	l.insert(6);
	l.insert(2);
	l.insert(7);
	l.insert(4);
	l.insert(8);
	l.insert(9);
	for(int i : l){
		std::printf("%i,", i);
	}
	l.clear();
}

