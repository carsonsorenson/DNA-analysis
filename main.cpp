#include "Data.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

std::vector<int> parseFile(std::string file) { //This function opens up a file and matches 'a' 'g' 'c' 't' to its associated position in the score matrix
	std::vector<int> v; //function will return a vector of correct indexes into the score matrix
	std::ifstream instream;
	instream.open(file);
	std::string sequence;
	while (instream >> sequence) {
		for (unsigned int i = 0; i < sequence.size(); i++) {
			sequence[i] = tolower(sequence[i]);
			switch (sequence[i]) { //switch statement to determine the correct position in the score matrix depending on each letter in the sequence
			case 'a':
				v.push_back(0);
				break;
			case 'c':
				v.push_back(1);
				break;
			case 'g':
				v.push_back(2);
				break;
			case 't':
				v.push_back(3);
				break;
			case 'n': // 'n' changes to 'a'
				v.push_back(0);
				break;
			default: // case if we find a letter that does not match 'a' 'g' 'c' 't' 'n'
				std::cout << "The letter " << sequence[i] << " was found in sequence" << std::endl;
				break;
			}
		}
	}
	return v;
}

void humanNeandertalStudy() {
	//This computes the sequence score between neandertal and human and outputs the traceback to a text file
	std::cout << "Comparing Prototypical Human with Neandertal" << std::endl;
	std::vector<int> seq1 = parseFile("sequences/prototypical_human.txt");
	std::vector<int> seq2 = parseFile("sequences/neandertal.txt");
	Data data(seq1, seq2);
	std::cout << "Alignment Score: " << data.findAlignment() << std::endl;
	data.traceBack();
	data.printToTextFile("neandertal_study/Prototypical Human vs neandertal.txt");
	std::cout << "The data has been written to the output file \"neadertal_study/Prototypical Human vs neandertal.txt\"" << std::endl << std::endl;
	return;
}

void greatApeStudy() {
	//First section loads the paths to the ape sequences and puts the names of the different apes in a list
	//It then will loop through and compute each unique pairs sequence
	std::string humanPath = "sequences/prototypical_human.txt";
	std::string filePath = "sequences/";
	std::string extension = ".txt";
	std::vector<std::string> apes = { "Baboon", "Bonobo", "Chimpanzee", "Gorilla (Western Lowland)", "Gorilla", "West African Common Chimpanzee" };
	std::vector<int> seq1 = parseFile(humanPath);
	for (unsigned int i = 0; i < apes.size(); i++) {
		std::cout << "Comparing Prototypical Human with " << apes[i] << std::endl;
		std::vector<int> seq2 = parseFile(filePath + apes[i] + extension);
		Data data(seq1, seq2);
		std::cout << "Alignment Score: " << data.findAlignment() << std::endl;
		data.traceBack();
		std::string outputFile = "great_ape_study/Prototypical Human vs " + apes[i] + extension;
		data.printToTextFile(outputFile);
		std::cout << "The data has been written to the output file \"" << outputFile << "\"" << std::endl << std::endl;
	}

	//Second section loops throught the ape sequences and compares it to the human sequence, it will then output the text file
	//with the correct traceback
	std::ofstream oFile;
	oFile.open("great_ape_study/great_ape_data.txt");
	std::cout << "Data between the apes" << std::endl;
	int inc = 0;
	for (unsigned int i = 0; i < apes.size() - 1; i++) {
		for (unsigned int j = i + 1; j < apes.size(); j++) {
			inc++;
			std::vector<int> seq1 = parseFile(filePath + apes[i] + extension);
			std::vector<int> seq2 = parseFile(filePath + apes[j] + extension);
			Data data(seq1, seq2);
			oFile << "Score between: " << apes[i] << " and " << apes[j] << " " << data.findAlignment() << std::endl;
			std::cout << inc << " finished " << apes[i] << " vs " << apes[j] << std::endl;
		}
	}
	oFile.close();
	std::cout << std::endl;
	return;
}

void humanStudy() { //This loads the 10 different humans into a list, next it loops through each of the combinations to compute the sequence distance between the files
	int inc = 0;
	std::vector<std::string> paths = { "Aborigine", "American", "Armenia", "Chinese", "Ethiopia", "France", "German", "Native American", "Nicobarese", "Samoan" };
	std::string path = "sequences/";
	std::string extension = ".txt";
	std::ofstream oFile;
	oFile.open("human_study/human_data.txt");
	for (unsigned int i = 0; i < paths.size() - 1; i++) {
		for (unsigned int j = i + 1; j < paths.size(); j++) {
			inc++;
			std::vector<int> seq1 = parseFile(path + paths[i] + extension);
			std::vector<int> seq2 = parseFile(path + paths[j] + extension);
			Data data(seq1, seq2);
			oFile << "Score between: " << paths[i] << " and " << paths[j] << " " << data.findAlignment() << std::endl;
			std::cout << inc << " finished " << paths[i] << " vs " << paths[j] << std::endl;
		}
	}
	oFile.close();
	return;
}

int main()
{
	humanNeandertalStudy(); //This will run the human neandertal test
	greatApeStudy(); //This will run the great ape study
	humanStudy(); //This will compare the 10 different humans to each other
	return 0;
}
