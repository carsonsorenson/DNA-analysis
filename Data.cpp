#include "Data.h"

Data::Data(std::vector<int> seq1, std::vector<int> seq2) {
	height = int(seq1.size() + 1);
	width = int(seq2.size() + 1);
	matrix = new int[width * height]; //we will define the matrix as a single array size of width * height
	//this array can be indexed like a 2d array by doing the operation x + width * y. This will treat the cache as a
	//2d array, however it will be more efficient.
	matrix[0] = 0; //the 0'th position will be zero because we will never match a gap to a gap
	this->seq1 = seq1;
	this->seq2 = seq2;

	scoreMatrix.push_back({ 5, -1, -2, -1, -3 }); //append the score matrix to the 2d vector array
	scoreMatrix.push_back({ -1, 5, -3, -2, -4 });
	scoreMatrix.push_back({ -2, -3, 5, -2, -2 });
	scoreMatrix.push_back({ -1, -2, -2, 5, -1 });
	scoreMatrix.push_back({ -3, -4, -2, -1 });
}

int Data::index(int x, int y) const { //this is the function that takes our 1d array and treats it as a 2d array returning the correct index
	return x + width * y;
}

int Data::findAlignment() {
	//loops over the first row and adds the associated weights up
	for (int rows = 1; rows < width; rows++) {
		int score = scoreMatrix[4][seq2[rows - 1]];
		matrix[index(rows, 0)] = matrix[index(rows - 1, 0)] + score;
	}

	//loops over the first column and adds the associated weights up
	for (int columns = 1; columns < height; columns++) {
		int score = scoreMatrix[seq1[columns - 1]][4];
		matrix[index(0, columns)] = matrix[index(0, columns - 1)] + score;

	}

	//we now need to loop over the entire cache starting at (1, 1) and going to (width, height)
	for (int i = 1; i < width; i++) {
		for (int j = 1; j < height; j++) {
			int matchCase = matrix[index(i - 1, j - 1)] + scoreMatrix[seq2[i - 1]][seq1[j - 1]];
			int deleteCase = matrix[index(i - 1, j)] + scoreMatrix[seq2[i - 1]][4];
			int insertCase = matrix[index(i, j - 1)] + scoreMatrix[4][seq1[j - 1]];
			//solution construction is to take the max of 3 cases: matching, deleting, inserting
			matrix[index(i, j)] = std::max(insertCase, std::max(matchCase, deleteCase));
		}
	}
	finalScore = matrix[index(width - 1, height - 1)]; //the last element in the 2d array will be the solution
	return finalScore;
}

char Data::charVal(int n){
	//This function takes the number from the sequence and returns the associated character
	if (n == 0)
		return 'A';
	else if (n == 1)
		return 'C';
	else if (n == 2)
		return 'G';
	else
		return 'T';
}

void Data::traceBack(){
	int i = int(seq2.size());
	int j = int(seq1.size());
	while (i > 0 || j > 0) { //while rows and cols > 0 we will keep looping
		//this is the case where two things match, so we will add the letter to the allignment of A and B
		if (i > 0 && j > 0 && matrix[index(i, j)] == matrix[index(i - 1, j - 1)] + scoreMatrix[seq2[i - 1]][seq1[j - 1]]) {
			alignA.push_back(charVal(seq1[j - 1]));
			alignB.push_back(charVal(seq2[i - 1]));
			j--;
			i--;
		}
		//This case we will delete a, and add b to the sequence list
		else if (i > 0 && matrix[index(i, j)] == matrix[index(i - 1, j)] + scoreMatrix[seq2[i - 1]][4]) {
			alignA.push_back('-');
			alignB.push_back(charVal(seq2[i - 1]));
			i--;
		}
		//This case will add a to the sequence list and delete b
		else {
			alignA.push_back(charVal(seq1[j - 1]));
			alignB.push_back('-');
			j--;
		}
	}
	//uncomment to print the traceback out to the screen
	/*for (int i = int(alignA.size()) - 1; i>=0; i--){
		std::cout << alignA[i] << " " << alignB[i] << std::endl;
	}*/
}

void Data::printToTextFile(std::string file) {//This prints out the alignment score and the traceback to a text file
	std::ofstream oFile;
	oFile.open(file);
	oFile << "Alignment Score: " << finalScore << std::endl;
	for (int i = int(alignA.size()) - 1; i >= 0; i--) {
		oFile << alignA[i] << " " << alignB[i] << std::endl;
	}
	oFile.close();

}

Data::~Data() { //delete the memory we allocated for the cache
	delete[] matrix;
	matrix = NULL;
}

