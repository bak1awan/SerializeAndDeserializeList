#include <sstream>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include "List.h"

ListRand::~ListRand()
{
	clear();
}

// Serializes list to the given file in format (data rand_pointer_index)
void ListRand::serialize(std::ofstream& file)
{
	std::map<ListNode*, int> listStructure;
	ListNode* current = head;

	// fill map with pointer and its index
	for (int32_t index = 0; current; current = current->next, ++index)
	{
		listStructure.insert({ current, index });
	}

	current = head;

	// store list size
	file << count << '\n';

	// foreach element in the list
	while (current)
	{
		// find random pointer if it is exists
		const auto it = listStructure.find(current->rand);

		// if it is exists, store its index as reference for later converting
		const int32_t randElemIndex = it == listStructure.end() ? -1 : it->second;
		// format output string for this template: index data randIndex
		file << std::string(current->data + ' ' + std::to_string(randElemIndex));
		// check for tail element
		if (current->next) file << '\n';
		// iterate
		current = current->next;
	}
}

// Deserializes list from the given file
void ListRand::deserialize(std::ifstream& file)
{
	// clear previous nodes
	clear();

	// read amount of elements
	int32_t counter{};
	file >> counter;

	// for random pointers indexes - index corresponds to the number of element, value - to the number of random element it is pointing
	std::vector<int> randomElements(counter, 0);

	// map for matching the element and its number
	std::map<int, ListNode*> listElements;

	for (int32_t i = 0; i < counter; ++i)
	{
		std::string data;
		int32_t randIndex{};

		// read data and index of the element in rand property
		file >> data >> randIndex;

		// connect n-th element to its further pointer in rand property
		randomElements[i] = randIndex;

		add(new ListNode(data));

		// store pair of the element and its index in the map
		listElements.insert({ i, tail });
	}

	restoreRandomPointers(randomElements, listElements);
}

// Fills list with N elements with random data
void ListRand::addNElementsWithRandData(const int32_t n, const int32_t length)
{
	if (n < 0)
	{
		std::cerr << "You could not add negative amount of elements!\n";
		exit(1);
	}
	for (int32_t i = 0; i < n; ++i)
	{
		add(new ListNode(genRandomString(length)));
	}
}

// Restore random pointers in every element according to how it was before
void ListRand::restoreRandomPointers(const std::vector<int>& randomElements, const std::map<int, ListNode*>& listElements)
{
	// start from the head of the list
	ListNode* current = head;
	for (int32_t i = 0; i < count; ++i)
	{
		// if the element have any pointer in rand property
		if (randomElements[i] != -1)
		{
			current->rand = listElements.at(randomElements[i]); // find it in the map and assign to rand property
		}
		current = current->next; // otherwise just go further
	}
}

// Add element ot the end of the list
void ListRand::add(ListNode* listNode)
{
	++count; // increment list element counter

	if (!head) // if it is the first element in the list
	{
		head = listNode;
		tail = listNode;
	}
	else // add new element to the end of the list
	{
		tail->next = listNode;
		listNode->prev = tail;
		tail = listNode;
	}


}

// Fills (or not - it is random) the rand properties of each element in the list by random properties
void ListRand::fillRands()
{
	for (ListNode* currentNode = head; currentNode; currentNode = currentNode->next)
	{
		// make random the event of even creating a pointer to the random list element
		bool needRand = rand() % 2;
		if (!needRand) continue;

		// make random pointer to the existing list element
		const auto index = rand() % count;

		// iterate to this element
		ListNode* current = head;
		for (int32_t i = 0; i < index; ++i)
		{
			current = current->next;
		}

		// assign it to the new element rand pointer
		currentNode->rand = current;
	}
}

// Deletes all elements in the list and leaves nullptr in both tail and head
void ListRand::clear()
{
	count = 0;
	if (!head) return;
	ListNode* current = head->next;
	while (current)
	{
		delete current->prev;
		current = current->next;
	}
	delete tail;
	tail = nullptr;
	head = nullptr;
}

// Prints all the list to the console, format for every element is (index, prev, next, rand)
void ListRand::print()
{
	std::cout << "\n===================== LIST CONTENT =====================\n";
	ListNode* current = head;
	int32_t counter = 0;
	while (current)
	{
		printf("Element #%d: data - %s, prev - %p, next - %p, rand - %p.\n\n", //
			counter, current->data.c_str(), current->prev, current->next, current->rand);
		current = current->next;
		++counter;
	}
}

// Generates random string with length length
std::string genRandomString(const int32_t length) {
	std::string alphas = "abcdefghijklmnopqrstuvwxyz";
	std::string result;
	result.reserve(length);

	for (int32_t i = 0; i < length; ++i) {
		result += alphas[rand() % (alphas.size() - 1)];
	}

	return result;
}