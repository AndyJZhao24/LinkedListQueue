#include "dancePairs.hpp"

int main()
{
	std::map<int, int> dance_pairs;
	std::string pairs, men_pref, women_pref;

	std::cout << "How many pairs are going to be dancing? ";
	std::cin >> pairs;
	std::cin.ignore(1);
	std::string full_string = pairs + "\n";

	std::cout << "What are the preferences of the men?\n";

	for(int i = 0; i < stoi(pairs); i++)
	{
		std::getline(std::cin, men_pref);
		full_string += men_pref + "\n";
	}

	std::cout << "\nWhat are the preferences of the women?\n";
	for(int i = 0; i < stoi(pairs); i++)
	{
		std::getline(std::cin, women_pref);
		full_string += women_pref + "\n";
	}

	std::istringstream stream(full_string);
	dance_pairs = assignDancePairs(stream);
	for(auto it = dance_pairs.begin(); it != dance_pairs.end(); it++)
	{
		std::cout << "Man #" << it->first << " is with Woman #" << it->second << std::endl;
	}

    return 0;
}

