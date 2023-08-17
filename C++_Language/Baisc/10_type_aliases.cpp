#include<iostream>
#include<vector>

int main()
{
	typedef double distance_t1;

	using distance_t2 = double;

	std::vector<std::pair<std::string, std::string>> a;

	using namespace std;

	vector<pair<string, string>> a;

	//typef
	typedef std::vector<std::pair<std::string, std::string>> pair_list_t1;
	pair_list_t1 p1;

	// using   
	using pair_list_t2 = std::vector<std::pair<std::string, std::string>>;
	pair_list_t2 p2;


	return 0;
}