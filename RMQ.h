#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include <unordered_map>

constexpr int N = 1500;


class RMQ
{
public:
	RMQ(const std::vector<int> input) : inputArray(input), preprocessed(false) {};
	RMQ(std::initializer_list<int> input) : inputArray(input), preprocessed(false) {};
	RMQ(const int& length);
	RMQ() : RMQ(N) {};

	void preProcess();
	int queryV1(const int& i, const int& j);
	int queryV2(const int& i, const int& j); // O(1)
	int queryV3(const int& i, const int& j); // O(sqrt(n))
	int queryV4(const int& i, const int& j); // O(log(n))
	void printA();

	inline static const std::string preprocessErrorMessage = "Preprocess haven't been called - can't return an valid answer.";
private:
	std::vector<int> inputArray;
	std::vector<std::vector<int>> rangesDataBaseV1;
	std::vector<int> rangesDataBaseV2;
	std::vector<std::vector<int>> rangesDataBaseV3;
	std::unordered_map<int, int> logValues;
	bool preprocessed;
	bool queryInputIsValid(const int& i, const int& j);

};
