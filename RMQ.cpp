#include "RMQ.h"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <ranges>
#include <algorithm>
#include <limits.h>
#include <chrono>


bool RMQ::queryInputIsValid(const int& i, const int& j)
{
	return (i > 0 || i < j || j < inputArray.size());
}

RMQ::RMQ(const int& length) : inputArray(length), preprocessed(false)
{
	// Create a random number generator
	std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr))); // Seed with current time
	// Create a distribution for the desired range
	std::uniform_int_distribution<int> distribution(0, 1000000);
	// Fill the vector with random integers
	for (int& num : inputArray) {
		num = distribution(generator);
	}
}

void RMQ::preProcess()
{
	// preprocess for queryV2
	auto startPreprocessing = std::chrono::high_resolution_clock::now();
	rangesDataBaseV1 = std::vector<std::vector<int>>(inputArray.size(), std::vector<int>(inputArray.size()));
	for (int i = 0; i < inputArray.size(); ++i) {
		for (int j = i; j < inputArray.size(); ++j) {
			if (i == j) {
				rangesDataBaseV1[i][j] = inputArray[i];
			}
			else {
				rangesDataBaseV1[i][j] = std::min(rangesDataBaseV1[i][j-1], inputArray[j]);
			}
		}
	}
	auto stopPreprocessing = std::chrono::high_resolution_clock::now();
	std::cout << "Time took to preprocess for queryV2: " << std::chrono::duration_cast<std::chrono::microseconds>(stopPreprocessing - startPreprocessing) << " microseconds" << std::endl;
	// preprocess for queryV3
	startPreprocessing = std::chrono::high_resolution_clock::now();
	int inputArraySizeSqrt = std::floor(std::sqrt(inputArray.size()));
	rangesDataBaseV2 = std::vector<int>(inputArraySizeSqrt);
	for (int i = 0; i < inputArraySizeSqrt; ++i) {
		auto subrange = std::ranges::subrange(inputArray.begin() + i * inputArraySizeSqrt, inputArray.begin() + (i + 1) * inputArraySizeSqrt);
		auto min_it = std::ranges::min_element(subrange);
		rangesDataBaseV2[i] = *min_it;
	}
	stopPreprocessing = std::chrono::high_resolution_clock::now();
	std::cout << "Time took to preprocess for queryV3: " << std::chrono::duration_cast<std::chrono::microseconds>(stopPreprocessing - startPreprocessing) << " microseconds" << std::endl;
	// preprocess for queryV4
	startPreprocessing = std::chrono::high_resolution_clock::now();
	int inputArraySizeLog = std::floor(std::log2(inputArray.size()));
	rangesDataBaseV3 = std::vector<std::vector<int>>(inputArray.size(), std::vector<int>(inputArraySizeLog + 1));
	logValues = std::unordered_map<int, int>();
	for (int k = 0; k <= inputArraySizeLog; ++k) {
		for (int i = 0; i + std::pow(2, k) <= inputArray.size(); ++i) {
			if (k == 0) rangesDataBaseV3[i][k] = inputArray[i];
			else
			{
				rangesDataBaseV3[i][k] = std::min(rangesDataBaseV3[i][k - 1], rangesDataBaseV3[i + std::pow(2, k - 1)][k - 1]);
			}
		}
	}
	for (int i = 0; i < inputArray.size(); ++i) {
		logValues[i] = std::floor(std::log2(i));
	}
	stopPreprocessing = std::chrono::high_resolution_clock::now();
	std::cout << "Time took to preprocess for queryV4: " << std::chrono::duration_cast<std::chrono::microseconds>(stopPreprocessing - startPreprocessing) << " microseconds" << std::endl;
	preprocessed = true;
}



int RMQ::queryV1(const int& i, const int& j) {
	if (!queryInputIsValid(i,j)) return -1;
	return std::ranges::min(std::ranges::subrange(inputArray.begin() + i, inputArray.begin() + j + 1));
}


int RMQ::queryV2(const int& i, const int& j)
{
	if (!queryInputIsValid(i, j)) return -1;
	if (!preprocessed) {
		std::cerr << preprocessErrorMessage << std::endl;
		return -1;
	}
	return rangesDataBaseV1[i][j];
}

int RMQ::queryV3(const int& i, const int& j)
{
	if (!queryInputIsValid(i, j)) return -1;
	if (!preprocessed) {
		std::cerr << preprocessErrorMessage << std::endl;
		return -1;
	}
	int ASizeSqrt = std::floor(std::sqrt(inputArray.size())), min = INT_MAX, minAtBlock;
	int iBlockNum = i / ASizeSqrt, jBlockNum = j / ASizeSqrt;
	bool iAtBlockStart = i % ASizeSqrt == 0, jAtBlockEnd = (j+1) % ASizeSqrt == 0;
	int bStart = iAtBlockStart ? iBlockNum : iBlockNum + 1;
	int bEnd = jAtBlockEnd ? jBlockNum : jBlockNum - 1;
	if (bStart < bEnd || bStart == bEnd) {
		min = std::ranges::min(std::ranges::subrange(rangesDataBaseV2.begin() + bStart, rangesDataBaseV2.begin() + bEnd + 1));
	}
	if (!iAtBlockStart || !jAtBlockEnd) {
		if (iBlockNum == jBlockNum) {
			return queryV1(i, j);
		}
		// iBlockNum != jBlockNum
		if (!iAtBlockStart) {
			minAtBlock = std::ranges::min(std::ranges::subrange(inputArray.begin() + i, inputArray.begin() + (iBlockNum + 1) * ASizeSqrt));
			min = std::min(min, minAtBlock);
		}
		if (!jAtBlockEnd) {
			minAtBlock = std::ranges::min(std::ranges::subrange(inputArray.begin() + jBlockNum * ASizeSqrt, inputArray.begin() + j + 1));
			min = std::min(min, minAtBlock);
		}
	}
	return min;
}


int RMQ::queryV4(const int& i, const int& j) {
	if (!queryInputIsValid(i, j)) return -1;
	if (!preprocessed) {
		std::cerr << preprocessErrorMessage << std::endl;
		return -1;
	}
	int t = j - i + 1, k = logValues[t];
	return std::min(rangesDataBaseV3[i][k], rangesDataBaseV3[j - std::pow(2, k) + 1][k]);
}
	

void RMQ::printA() {
	std::ranges::for_each(inputArray, [](const auto& i) {std::cout << i << " ";});
	std::cout << std::endl;
}
