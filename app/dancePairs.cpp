// dancePairs.cpp

#include "dancePairs.hpp"
#include "LLQueue.hpp"

#include <string>
#include <sstream>
#include <vector>


std::map<int, int> assignDancePairs(std::istream & in)
{
	std::vector<std::vector<int>> man_pref; //each index represents man i+1, and the vector at that index represents their preferences.
	std::vector<std::vector<int>> woman_pref; //each index represents woman i+1, and the vector at that index represents their preferences.
	std::string line; //Used to store information about each person's match.
	int p; //used to store the value of preferences from each pair.
	std::stringstream ss;

	int numPairs;  // could be unsigned.
	getline(in, line); //Gets the first line which represents the number of pairs, whitespace (\n) is removed.
	numPairs = atoi(line.c_str());  //Turns the string integer to an integer.

	LLQueue<int> manQ; //Initialized linked list Queue of nodes which store data of type int.

	for (int w = 1; w <= numPairs; w++) //Adding preferences of men to the vector as well as enqueueing them.
	{
		getline(in, line); //Get line which contains man w's preferences
		ss << line; //store line into ss
		manQ.enqueue(w); //Enqueue man w into the queue.
		std::vector<int> prefm; //Used for storing preferences of man w.
		while (ss >> p)
		{
			prefm.push_back(p); //push value into vector.
		}
		man_pref.push_back(prefm);//Push vector into man_pref vector. Each index in the vector is a vector storing man w's preferences.
		ss.str(std::string());//resets ss to empty string
		ss.clear();//clears any fail and eof flags.
	}
	
	for (int a = numPairs + 1; a <= numPairs * 2; a++) //Add the preferences of the women to the separate woman_pref vector.
	{
		getline(in, line);
		ss << line;
		std::vector<int> prefw;
		while (ss >> p)
		{
			prefw.push_back(p);
		}
		woman_pref.push_back(prefw);
		ss.str(std::string());
		ss.clear();
	}
	std::map<int, int> pair_mapping; //Mapping used to hold each pairing of man and woman.
	//map.at(i) tells which woman the ith man is sharing paired with.
	

	while(not manQ.isEmpty())
	{
		bool has_match = false;
		int man_num = manQ.front(); //Gets the first man in queue. -1 for the index in vector.
		int man_prefers = man_pref[man_num - 1][0]; //Index 0 of the man's preference is his most preferred partner that has not been interacted with.
		manQ.dequeue(); //Remove man from queue.
	
	 	man_pref[man_num-1].erase(man_pref[man_num-1].begin()); //Removes first woman from man_num's preference list

		for(std::map<int,int>::iterator it = pair_mapping.begin(); it != pair_mapping.end(); it++)
		{
			if (it->second == man_prefers) //If woman is the person man prefers.
			{
				for(size_t ind = 0; ind < woman_pref.size(); ind++) //Loop through woman's preferences
				{
					if (woman_pref[it->second - 1][ind] == man_num || woman_pref[it->second - 1][ind] == it->first) //Look for whether man or woman's current match.
					{
						if (woman_pref[it->second - 1][ind] == man_num) //Found the man, which means he is higher on woman's preference list.
						{
							manQ.enqueue(it->first); //Put woman's current match back into the queue.
							pair_mapping.erase(it->first); //Remove the woman and her match from the current map.
							pair_mapping[man_num] = man_prefers; //Add a key value pair of man and woman into the mapping
						}
						else //Found woman's current match first, which means the current match is higher on woman's prefences list.
						{
							manQ.enqueue(man_num); //Put window person back into queue.
						}
						has_match = true; //Found the woman.
						break;//Break out of loop to check for person matches.
					}
				}
			}
			if(has_match) //If a match was found
				break; //Break out of the for-loop and deal with the next person in the queue.
		}
		if (not has_match) //If man's reference of woman does not yet have a match.
		{
			pair_mapping[man_num] = man_prefers; //Add a key value pair of man and woman into the mapping.
		}
	}
	
	return pair_mapping;  // return the mapping for the pairs.
}
