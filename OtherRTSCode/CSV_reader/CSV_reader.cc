
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <utility> // std::pair
#include <iostream> //cout,cin
#include <fstream> // std::ifstream,getline
#include <sstream> // std::stringstream

std::vector<std::pair<std::string, std::vector<std::string> > > read_csv(char filename[]){
	// Reads a CSV file into a vector of <string, vector<int>> pairs where
	// each pair represents <column name, column values>

	// Create a vector of <string, int vector> pairs to store the result
	std::vector<std::pair<std::string, std::vector<std::string> > > result;

	std::string val;
	std::string line, colname;
	std::ifstream myFile;

	myFile.open(filename);

	// Make sure the file is open
	if(!myFile.is_open()){
		std::cout << "Could not open file" << std::endl;
	}


	// Read the column names
	if(myFile.good()){
		// Extract the first line in the file
		std::getline(myFile, line);

		// Create a stringstream from line
		std::stringstream ss(line);

		// Extract each column name
		while(std::getline(ss, colname, ',')){

			// Initialize and add <colname, string vector> pairs to result
			std::pair<std::string, std::vector<std::string> > temp;
			std::vector<std::string> tempint;
			temp = std::make_pair(colname,tempint);
			result.push_back(temp);

		}

		int count = 0;
		// Read data, line by line
		while(std::getline(myFile, line)){

			// Create a stringstream of the current line
			std::stringstream ss(line);

			// Keep track of the current column index
			int x = 0;

			// Extract each word
			while(std::getline(ss, val, ',')){
			// Add the current integer to the 'x' column's values vector

			result.at(x).second.push_back(val);

			// Increment the column index
			x++;
			}
		}//end while

	}
	// Close file
	myFile.close();

	return result;

}
void print_vec(std::vector<std::pair<std::string, std::vector<std::string> > > &dataset){

	int numcol;
	int numval;
	numcol = dataset.size();
	numval = dataset.at(1).second.size();

	std::cout << "numcol: " << numcol << "\n" ;
	std::cout << "numval: " << numval << "\n" ;

	for (int i=0; i<numcol; i++){
		std::cout << dataset[i].first << ", "; //print out column names
	}

	for (int i=0; i<numval; i++) //for each row, theres aprox 94,000
	{
		for(int j=0; j < numcol;j++){//for each column, there's 8
			std::cout << "	 	," << dataset.at(j).second[i]; //print out the value
		}
		std::cout << "\n";
	}

}


int main (int argc, char *argv[]) {

	char filename[] = "dataset.txt";

	//call read function
	std::vector<std::pair<std::string, std::vector<std::string> > > dataset = read_csv("dataset.txt");
	print_vec(dataset);

	int wait;
	std::cout << "press enter to stop " << std::endl;
	std::cin >> wait;
	return 0;
}
