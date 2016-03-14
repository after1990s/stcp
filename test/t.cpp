#include <vector>
#include <iostream>
void f0(int *p)
{
	p[0] = 3;
	p[1] = 4;
}
void output(std::vector<int> &d)
{
	for (auto i: d)
	{
		std::cout << i;
	}
	std::cout << std::endl;
}
int main()
{
	std::vector<int> d;
	d.resize(1);
	f0(d.data());
	output(d);
	d.resize(d.size() + 2);
	output(d);
	d.erase(d.begin(), d.end());
	std::cout << d.size();
	
	return 0;
}
