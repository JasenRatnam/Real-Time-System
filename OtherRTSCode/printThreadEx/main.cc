#include <iostream>
#include "pthread.h"
#include <string>

#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <utility> // std::pair
#include <fstream> // std::ifstream,getline
#include <sstream> // std::stringstream

#define SleepTime 0.01

static pthread_mutex_t mutex;

//std::vector<std::pair<std::string, std::vector<std::string> > > read_csv(char filename[]);
//void print_vec(std::vector<std::pair<std::string, std::vector<std::string> > > &dataset);
void* read_csv_thread(void *id);

void* read_csv_thread(void *id){
	// Reads a CSV file into a vector of <string, vector<int>> pairs where
	// each pair represents <column name, column values>

	// Create a vector of <string, int vector> pairs to store the result
	std::vector<std::pair<std::string, std::vector<std::string> > > result;

	std::string val;
	std::string line, colname;
	std::ifstream myFile;
	char filename[] = "dataset.txt";
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
		std::cout<<line<<std::endl;
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
			sleep(SleepTime);
			std::cout<<line<<std::endl;
		}//end while

	}
	// Close file
	myFile.close();

	return NULL;

}

int main()
{
	//char filename[] = "dataset.txt";

	//call read function
	//std::vector<std::pair<std::string, std::vector<std::string> > > dataset = read_csv("dataset.txt");

    pthread_t thread;

    //file reader thread read a line every 10ms
	int t = pthread_create(&thread, NULL, read_csv_thread, (void*)thread);

	if (t != 0)
	{
		std::cout << "Error in thread creation: " << t << std::endl;
	}

	//Need thread to get Full Consumption every 10 ms
	//Need thread to get Engine Speed (RPM) every 500 ms
	//Need thread to get Engine Coolant Temperature every 2 s
	//Need thread to get Current Gear every 100 ms
	//Need thread to get Transmission Oil Temperature every 5 s
	//Need thread to get Vehicle Speed every 100 ms
	//Need thread to get Acceleration Speed Longitudinal every 150 ms
	//Need thread to get Indication of break switch every 100 ms

	//Need thread to display vehicle information

	void* status;
	 t = pthread_join(thread, &status);
	if (t != 0)
	{
		std::cout << "Error in thread join: " << t << std::endl;
	}

    return 0;
}
