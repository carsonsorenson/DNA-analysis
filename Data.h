#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
class Data //class initialization of the data class
{
public:
	Data(std::vector<int> seq1, std::vector<int> seq2);
	int index(int x, int y) const;
	int findAlignment();
	void traceBack();
	void printToTextFile(std::string path);
	char charVal(int n);
	~Data();

private:
	int height;
	int width;
	int* matrix;
	std::vector<std::vector<int> > scoreMatrix;
	std::vector<int> seq1;
	std::vector<int> seq2;
	int finalScore;
	std::vector<char> alignA;
	std::vector<char> alignB;
};
#endif
