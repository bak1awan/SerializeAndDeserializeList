// Serialization and deserialization
#include <iostream>
#include <fstream>
#include <ctime>
#include "List.h"

constexpr int32_t AMOUNT_OF_ELEMENETS = 10; // amount of elements to generate in list
const std::string FILENAME = "Serialized_list.txt"; // filename for serializing/deserializing
constexpr int32_t STRING_LENGTH = 1; // length of data string generated for each element in list

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	// ===== Create list and fill it with data =====
	ListRand* randomList = new ListRand();
	randomList->addNElementsWithRandData(AMOUNT_OF_ELEMENETS, STRING_LENGTH);
	randomList->fillRands();

	randomList->print();

	// ===== Serialize list to the file =====
	std::ofstream outf(FILENAME);

	if (!outf)
	{
		std::cerr << "Could not open file for writing!\n" << std::endl;
		exit(1);
	}

	randomList->serialize(outf);

	outf.close();

	// ===== Deserialize list from the file =====
	std::ifstream inf(FILENAME);
	if (!inf)
	{
		std::cerr << "Could not open file for reading!\n" << std::endl;
		exit(1);
	}

	randomList->deserialize(inf);

	inf.close();

	randomList->print();

	delete randomList;

	return 0;
}