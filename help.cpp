#include <iostream>
#include <vector>


int main(){
	std::vector<int> v;
	v.resize(5, 0);
	auto iter1 = v.cbegin(); // константный итератор указывает на первый элемент
	v.insert(iter1, 0, 8);
	std::cout << v[0] << std::endl;
	return 0;
}