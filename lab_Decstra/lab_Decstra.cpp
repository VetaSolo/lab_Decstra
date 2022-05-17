#include <iostream>
#include "decstra.h"
int main()
{
	

	DoubleList<string> CitiesCounter;
	CustomMap<string, int> CitiesMap;

	// go through input file to create Maps based on future graph vertexes and calculate count of them 
	ifstream file_input;
	file_input.open("air.txt");
	string oneString;
	string FirstCityName = "";
	string SecondCityName = "";
	string toInt = "";
	int costTravel = 0;
	while (!file_input.eof()) {
		getline(file_input, oneString);
		cout << oneString << '\n';
		FirstCityName = oneString.substr(0, oneString.find(';'));
		if (!CitiesCounter.contains(FirstCityName)) {
			CitiesMap.insert(FirstCityName, CitiesCounter.getSize());
			CitiesCounter.push_back(FirstCityName);
		}
		oneString.erase(0, oneString.find(';') + 1);
		SecondCityName = oneString.substr(0, oneString.find(';'));
		if (!CitiesCounter.contains(SecondCityName)) {
			CitiesMap.insert(SecondCityName, CitiesCounter.getSize());
			CitiesCounter.push_back(SecondCityName);
		}
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
	}
	file_input.close();

	int Vertexes = CitiesCounter.getSize();

	// create empty graph to dijkstra algorith
	DijkstraGraphs MyDijkstraGraphs(Vertexes);

	// go through input file to add vertexes to the graph
	file_input.open("air.txt");
	while (!file_input.eof()) {
		getline(file_input, oneString);
		FirstCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		SecondCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		if (toInt != "N/A") {
			costTravel = stoi(toInt);
			MyDijkstraGraphs.add_edge(CustomPair<string, int>(CitiesMap.find(FirstCityName)->key, CitiesMap.find(FirstCityName)->value), CustomPair<string, int>(CitiesMap.find(SecondCityName)->key, CitiesMap.find(SecondCityName)->value), costTravel);
		}
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		if (toInt != "N/A") {
			costTravel = stoi(toInt);
			MyDijkstraGraphs.add_edge(CustomPair<string, int>(CitiesMap.find(SecondCityName)->key, CitiesMap.find(SecondCityName)->value), CustomPair<string, int>(CitiesMap.find(FirstCityName)->key, CitiesMap.find(FirstCityName)->value), costTravel);
		}
	}

	// cities to dijkstra algorithm
	string city_from = "NYC";
	string city_to = "Rim";

	cout << "\nFind the lowest cost path from " << city_from << " to " << city_to << ":\n";

	cout << MyDijkstraGraphs.dijkstra_lowest_cost_path(CustomPair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), CustomPair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));

	cout << "\nTravelling cost is: ";

	try {
		cout << MyDijkstraGraphs.dijkstra_lowest_cost(CustomPair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), CustomPair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));
	}
	catch (const invalid_argument error) {
		cout << error.what();
	}


	city_from = "Batumi";
	city_to = "SPb";

	cout << "\n\nFind the lowest cost path from " << city_from << " to " << city_to << ":\n";

	cout << MyDijkstraGraphs.dijkstra_lowest_cost_path(CustomPair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), CustomPair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));

	cout << "\nTravelling cost is: ";

	try {
		cout << MyDijkstraGraphs.dijkstra_lowest_cost(CustomPair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), CustomPair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));
	}
	catch (const invalid_argument error) {
		cout << error.what();
	}

};
