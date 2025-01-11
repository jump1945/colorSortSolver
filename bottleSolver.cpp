#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class BottleStack {
private:
	int bottleNumber;
	int maxSize;
	std::vector<short> stackVec;
	void constructor(int size) {
		if (size < 1) {
			std::cout << "invalidSize\n";
		}
		maxSize = size;
		stackVec.reserve(size);
	}
	void popBack(){
		if (isEmpty()) {
			std::cout << "trying to pop empty array in popBack()\n";
			return;
		}
		stackVec.pop_back();
		return;
	}
	void insert(short value) {
		stackVec.push_back(value);
		return;
	}
	void insertVector(std::vector<short>& baseVector) {
		//stackVec = std::move(baseVector);
		stackVec.swap(baseVector);
	}
	short getTop()const {
		if (isEmpty()) {
			std::cout << "getTop access empty array\n";
			return -1;
		}
		return stackVec.back();
	}
public:
	bool isFull()const {
		return stackVec.size() == maxSize;
	}
	bool isEmpty()const {
		return stackVec.size() == 0;
	}
	BottleStack(int num) {
		constructor(4);
		bottleNumber = num;
	}
	BottleStack(int num, int size) {
		constructor(size);
		bottleNumber = num;
	}
	BottleStack(int num, int size,std::vector<short> baseVector) {
		constructor(size);
		insertVector(baseVector);
		bottleNumber = num;
	}
	int getSize()const {
		return stackVec.size();
	}
	int getMaxSize()const {
		return maxSize;
	}
	int getBottleNumber()const {
		return bottleNumber;
	}
	short getValue(int index) const{
		if (index >= getSize()) {
			std::cout << "invalidIndex\n";
			return 0xFFFF;
		}
		return stackVec.at(index);
	}
	bool transfer(BottleStack& receiver) {
		if (isEmpty() || receiver.isFull()) {
			return false;
		}
		short topValue = getTop();
		if (receiver.isEmpty()) {
			popBack();
			receiver.insert(topValue);
			return true;
		}
		else if (getTop() != receiver.getTop()) {
			return false;
		}
		popBack();
		receiver.insert(topValue);
		return true;
	}
	void deTransfer(BottleStack& receiver) {
		if (isFull() || receiver.isEmpty()) {
			std::cout << "deTransfer error\n";
			return;
		}
		short topValue = receiver.getTop();
		receiver.popBack();
		insert(topValue);
		return;
	}
	bool isSingular() {
		if (isEmpty()) {
			return true;
		}
		int testValue = stackVec.at(0);
		int size = stackVec.size();
		for (int i = 1; i < size; i++) {
			if (testValue != stackVec.at(i)) {
				return false;
			}
		}
		return true;
	}
	bool operator<(const BottleStack& other) const {
		return stackVec < other.stackVec;
	}
	bool operator>(const BottleStack& other) const {
		return stackVec > other.stackVec;
	}
	bool operator==(const BottleStack& other) const {
		return stackVec == other.stackVec;
	}
	void printBottle() {
		for (auto& value : stackVec) {
			std::cout << value << ' ';
		}
		std::cout << "|\n";
	}
};


std::map<std::vector<BottleStack>, int> lookUpMap;
int saveNum = 0;

std::vector<std::pair<int, int>> findColorSortSolution(
	std::vector<BottleStack> bottleStackVec,
	std::vector<std::pair<int, int>> solutionTail){

	//sort to lessen the number of bottle combination thus lessen the amount of recursive call needed
	std::sort(bottleStackVec.begin(), bottleStackVec.end());
	if (lookUpMap.find(bottleStackVec) != lookUpMap.end()) {
		//if the transfer result to the solution that already exist
		//return empty vector to avoid infinite loop and optimize
		return {};
	}
	//if transfer doesn't exist save the transfers result
	lookUpMap[bottleStackVec] = saveNum++;

	bool correct = true;
	for (int i = 0; i < bottleStackVec.size();i++) {
		auto& bottle = bottleStackVec[i];
		if ((bottle.isSingular()&&bottle.isFull()) || bottle.isEmpty()) {
			continue;
		}
		//if atleast one bottle is wrong continue backtracking
		correct = false;
		for (int j = 0; j < bottleStackVec.size();j++) {
			if (i == j) continue; //skip transferring to itself
			if (bottle.transfer(bottleStackVec[j])) {
				int count=0;
				while (bottle.transfer(bottleStackVec[j]))count++;//multiple transfers
				//record the transfer
				std::vector<std::pair<int, int>> newVec = solutionTail;
				newVec.push_back({ bottle.getBottleNumber(), bottleStackVec[j].getBottleNumber() });
				//print out the current state of transferred bottle
				for (auto& bottleStackVec : bottleStackVec) {
					bottleStackVec.printBottle();
				}
				std::cout << "---------------------\n";
				// Recurse to find the solution of this transfer
				std::vector<std::pair<int, int>> result = findColorSortSolution(bottleStackVec, newVec);
				// found solution would be returned and it would not be empty
				if (!result.empty()) {
					//return found solution
					return result;
				}
				//reverse the transfer
				bottle.deTransfer(bottleStackVec[j]);
				//reverse multiple transfers
				while (count--)bottle.deTransfer(bottleStackVec[j]);
			}
		}
	}

	//return found solution
	if (correct) {
		return solutionTail;
	}

	//no solution found return empty
	return {};
}

int main(){
	int bottleCount, bottleSize;
	std::vector<BottleStack> bottleInput;
	std::cout << "enterBottleCount and bottleSize" << std::endl;
	std::cin >> bottleCount >> bottleSize;
	bottleInput.reserve(bottleCount);
	for (int i = 1; i <= bottleCount; i++) {
		std::cout << "bottle : " <<i<<" value" << std::endl;
		std::vector<short> tempVec;
		tempVec.reserve(bottleSize);
		for (int j = 0; j < bottleSize; j++) {
			short num;
			std::cin >> num;
			if (num == -1) {
				//terminate if num == -1
				break;
			}
			tempVec.push_back(num);
		}
		BottleStack newStack(i, bottleSize, tempVec);
		bottleInput.push_back(newStack);
	}
	std::vector<std::pair<int, int>> solution = findColorSortSolution(bottleInput, {});
	for (const auto& vecIndex : solution) {
		std::cout << vecIndex.first << ' ' << vecIndex.second << std::endl;
	}
	std::cout << "press C to close";
	while (getchar() != 'C');
}
//g++ C:\Users\Jump\Desktop\C++\bottleSolver.cpp -o C:\Users\Jump\Desktop\C++\com\bottleSolver.exe --static
/*
7 4
1 2 1 2
3 4 4 5
3 5 1 4
2 4 5 3
2 5 1 3
-1
-1
*/
/*
4 4
1 2 2 2
1 2 1 1
-1
-1
*/
/*
5 4
1 1 1 2
1 3 3 3
3 2 2 2
-1
-1
*/
/*
15 4
1 2 3 4
1 5 6 4
8 1 9 10
9 9 11 12
6 11 8 6
4 9 
*/