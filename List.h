#pragma once
#include <vector>
#include <map>

class ListNode
{
public:
	ListNode* prev;
	ListNode* next;
	ListNode* rand;
	std::string data;

	ListNode(std::string data) : prev(nullptr), next(nullptr), rand(nullptr), data(data) {}
};

class ListRand
{
public:
	ListNode* head;
	ListNode* tail;
	int32_t count;

	ListRand() : head(nullptr), tail(nullptr), count(0) {}

	~ListRand();
	// Serializes list to the given file in format (data rand_pointer_index)
	void serialize(std::ofstream& file);

	// Deserializes list from the given file
	void deserialize(std::ifstream& file);

	// Fills list with N elements with random data
	void addNElementsWithRandData(const int32_t n, const int32_t length);

	// Restore random pointers in every element according to how it was before
	void restoreRandomPointers(const std::vector<int>& randomElements, const std::map<int, ListNode*>& listElements);
	// Add element ot the end of the list
	void add(ListNode* listNode);

	// Fills (or not - it is random) the rand properties of each element in the list by random properties
	void fillRands();

	// Deletes all elements in the list and leaves nullptr in both tail and head
	void clear();


	// Prints all the list to the console, format for every element is (index, prev, next, rand)
	void print();
};

// Generates random string with length length
std::string genRandomString(const int32_t length);