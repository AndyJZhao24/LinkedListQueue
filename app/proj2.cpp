// proj2.cpp

#include "proj2.hpp"
#include "LLQueue.hpp"

#include <map>
#include <string>
#include <sstream>
#include <vector>

// This is a demo of the code to show you how to read from istream
// Please see the assignment description to see the exact format
// you can expect the input to be.
std::map<int, int> assignBusSeats(std::istream & in)
{
	std::vector<std::vector<int>> window_pref; //each index represents window person i+1, and the vector at that index represents their preferences.
	std::vector<std::vector<int>> aisle_pref; //each index represents aisle person i+1, and the vector at that index represents their preferences.
	std::string line; //Used to store information about each person's seating.
	int p; //used to store the value of preferences from each row.
	std::stringstream ss;

	int numSeats;  // could be unsigned.
	getline(in, line); //Gets the first line which represents the number of seats, whitespace (\n) is removed.
	numSeats = atoi(line.c_str());  //Turns the string integer to an integer.

	LLQueue<int> windowQ; //Initialized linked list Queue of nodes which store data of type int.

	for (int w = 1; w <= numSeats; w++) //Adding preferences of window people to the vector as well as enqueueing them.
	{
		getline(in, line); //Get line which contains window person w's preferences
		ss << line; //store line into ss/
		windowQ.enqueue(w); //Enqueue window person w into the queue.
		std::vector<int> prefw; //Used for storing preferences of window person w.
		while (ss >> p)
		{
			prefw.push_back(p); //push value into vector.
		}
		window_pref.push_back(prefw);//Push vector into window_pref vector. Each index in the vector is a vector storing window person w's preferences.
		ss.str(std::string());//resets ss to empty string
		ss.clear();//clears any fail and eof flags.
	}
	
	for (int a = numSeats + 1; a <= numSeats * 2; a++) //Add the preferences of the aisle people to the separate aisle_pref vector.
	{
		getline(in, line);
		ss << line;
		std::vector<int> prefa;
		while (ss >> p)
		{
			prefa.push_back(p);
		}
		aisle_pref.push_back(prefa);
		ss.str(std::string());
		ss.clear();
	}
	std::map<int, int> seat_mapping; //Mapping used to hold each the seat mappings between window people and aisle people.
	//map.at(i) tells which numbered aisle person the ith window person is sharing a bench with
	

	while(not windowQ.isEmpty())
	{
		bool has_match = false;
		int window_person_num = windowQ.front(); //Gets the first window person in queue. -1 for the index in vector.
		int window_person_prefers = window_pref[window_person_num - 1][0]; //Index 0 of the window person's preference is his/her most preferred seating partner that has not been interacted with.
		windowQ.dequeue(); //Remove window person from queue.
	
	 	window_pref[window_person_num-1].erase(window_pref[window_person_num-1].begin()); //Removes first aisle person from window_person_num's preference list

		for(std::map<int,int>::iterator it = seat_mapping.begin(); it != seat_mapping.end(); it++)
		{
			if (it->second == window_person_prefers) //If aisle person is the person window person prefers.
			{
				for(size_t ind = 0; ind < aisle_pref.size(); ind++) //Loop through aisle person's preferences
				{
					if (aisle_pref[it->second - 1][ind] == window_person_num || aisle_pref[it->second - 1][ind] == it->first) //Look for whether window person or aisle person's current match.
					{
						if (aisle_pref[it->second - 1][ind] == window_person_num) //Found the window person first, which means he is higher on aisle's pref list.
						{
							windowQ.enqueue(it->first); //Put aisle person's current match back into the queue.
							seat_mapping.erase(it->first); //Remove the aisle person and his match from the current map.
							seat_mapping[window_person_num] = window_person_prefers; //Add a key value pair of window person and aisle person into the mapping
						}
						else //Found aisle person's current match first, which means the current match is higher on aisle person's prefences list.
						{
							windowQ.enqueue(window_person_num); //Put window person back into queue.
						}
						has_match = true; //Found the aisle person.
						break;//Break out of loop to check for person matches.
					}
				}
			}
			if(has_match) //If a match was found
				break; //Break out of the for-loop and deal with the next person in the queue.
		}
		if (not has_match) //If window person's preference of aisle person does not yet have a match.
		{
			seat_mapping[window_person_num] = window_person_prefers; //Add a key value pair fo window person and aisle person into the mapping.
		}
	}
	
	return seat_mapping;  // return the mapping for the bus.
}
