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
#include <semaphore.h>
#include <string>

//period of the CSV reader
#define SleepTime 1
//period of the thread that displays the variables in microsecond
#define DispTime 500000 //1000000
//buffer to save variables
#define BUFFER_SIZE 9

std::string buffer[BUFFER_SIZE];
std::string Fuel_consumptioni;
std::string Engine_speedi;
std::string Engine_coolant_temperaturei;
std::string Current_Geari;
std::string Transmission_Oil_Temperaturei;
std::string Vehicle_speedi;
std::string Acceleration_speed_Longitudinali;
std::string Indication_of_brake_switchi;
std::string Timei;
int index1=0;

sem_t full,empty;
pthread_mutex_t mutex;

void* read_csv_thread(void *id);
void* Fuel_consumption(void *id);
void* Engine_speed(void *id);
void* Engine_coolant_temperature(void *id);
void* Current_Gear(void *id);
void* Transmission_Oil_Temperature(void *id);
void* Vehicle_speed(void *id);
void* Acceleration_speed_Longitudinal(void *id);
void* Indication_of_brake_switch(void *id);
void* display_variables(void *id);

/*
 * Thread Function to display the variables wanted from the vehicle
 * Outputs the Fuel_consumption, Engine_speed, Engine_coolant_temperature, Current_Gear,
 * Transmission_Oil_Temperature, Vehicle_speed, Acceleration_speed_Longitudinal and Indication_of_brake_switch
 * Outputs variable values every DispTime
 */
void* display_variables(void *id)
{
	while(1){

		std::cout<< "\n" <<std::endl;
		std::cout<< "Fuel_consumption: " << Fuel_consumptioni <<std::endl;
		std::cout<< "Engine_speed: " << Engine_speedi <<std::endl;
		std::cout<< "Engine_coolant_temperature: " << Engine_coolant_temperaturei <<std::endl;
		std::cout<< "Current_Gear: " << Current_Geari <<std::endl;
		std::cout<< "Transmission_Oil_Temperature: " << Transmission_Oil_Temperaturei <<std::endl;
		std::cout<< "Vehicle_speed: " << Vehicle_speedi <<std::endl;
		std::cout<< "Acceleration_speed_Longitudinal: " << Acceleration_speed_Longitudinali <<std::endl;
		std::cout<< "Indication_of_brake_switch: " << Indication_of_brake_switchi <<std::endl;

		usleep(DispTime);
	}
	return NULL;
}

/*
 * Thread function to fetch the fuel consumption value from the vehicle dataset
 * Gets the first variable from the current line from the dataset given from the reading thread
 * Waits until a line is read in the reading thread using semaphore
 * Repeated every period of 0.01s, Gets new value from data set every 0.01s
 */
void* Fuel_consumption(void *id)
{
	while(1){

		//Wait on a semaphore, until the reading thread has read a line from the dataset
		sem_wait(&full);
		//lock access to read value without interuption
		pthread_mutex_lock(&mutex);

		if(Fuel_consumptioni != buffer[0])Fuel_consumptioni = buffer[0];

		//std::cout<<"Fuel_consumption: "<<Fuel_consumptioni<<std::endl;

		//release mutex and semaphore
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		usleep(10000);
	}
	return NULL;
}

/*
 * Thread function to fetch the Engine Speed (RPM) value from the vehicle dataset
 * Gets the second variable from the current line from the dataset given from the reading thread
 * Repeated every period of 0.5s, Gets new value from data set every 0.5s
 */
void* Engine_speed(void *id)
{
	while(1){

		if(Engine_speedi != buffer[1])Engine_speedi = buffer[1];

		//std::cout<<"Engine_speed: "<<Engine_speedi<<std::endl;

		usleep(500000);
	}
	return NULL;
}

/*
 * Thread function to fetch the engine coolant temperature value from the vehicle dataset
 * Gets the third variable from the current line from the dataset given from the reading thread
 * Repeated every period of 2s, Gets new value from data set every 2s
 */
void* Engine_coolant_temperature(void *id)
{
	while(1){

		if(Engine_coolant_temperaturei != buffer[2])Engine_coolant_temperaturei = buffer[2];

		//std::cout<<"Engine_coolant_temperature: "<<Engine_coolant_temperaturei<<std::endl;

		sleep(2);
	}
	return NULL;
}

/*
 * Thread function to fetch the current gear value from the vehicle dataset
 * Gets the fourth variable from the current line from the dataset given from the reading thread
 * Repeated every period of 0.1s, Gets new value from data set every 0.1s
 */
void* Current_Gear(void *id)
{
	while(1){

		if(Current_Geari != buffer[3])Current_Geari = buffer[3];

		//std::cout<<"Current_Gear: "<<Current_Geari<<std::endl;

		usleep(100000);
	}
	return NULL;
}

/*
 * Thread function to fetch the transmission oil temperature value from the vehicle dataset
 * Gets the fifth variable from the current line from the dataset given from the reading thread
 * Repeated every period of 5s, Gets new value from data set every 5s
 */
void* Transmission_Oil_Temperature(void *id)
{
	while(1){

		if(Transmission_Oil_Temperaturei != buffer[4])Transmission_Oil_Temperaturei = buffer[4];

		//std::cout<<"Transmission_Oil_Temperature: "<<Transmission_Oil_Temperaturei<<std::endl;

		sleep(5);
	}
	return NULL;
}

/*
 * Thread function to fetch the vehicle speed value from the vehicle dataset
 * Gets the sixth variable from the current line from the dataset given from the reading thread
 * Repeated every period of 0.1s, Gets new value from data set every 0.1s
 */
void* Vehicle_speed(void *id)
{
	while(1){


		// Extract speed
		if(Vehicle_speedi != buffer[5])Vehicle_speedi = buffer[5];

		//std::cout<<"Vehicle_speed: "<<Vehicle_speedi<<std::endl;

		usleep(100000);
	}
	return NULL;
}

/*
 * Thread function to fetch the acceleration speed longitudinal value from the vehicle dataset
 * Gets the seventh variable from the current line from the dataset given from the reading thread
 * Repeated every period of 0.15s, Gets new value from data set every 0.15s
 */
void* Acceleration_speed_Longitudinal(void *id)
{
	while(1){

		if(Acceleration_speed_Longitudinali != buffer[6])Acceleration_speed_Longitudinali = buffer[6];

		//std::cout<<"Acceleration_speed_Longitudinal: "<<Acceleration_speed_Longitudinali<<std::endl;

		usleep(150000);
	}
	return NULL;
}

/*
 * Thread function to fetch the indication of brake switch value from the vehicle dataset
 * Gets the eight variable from the current line from the dataset given from the reading thread
 * Repeated every period of 0.1s, Gets new value from data set every 0.1s
 */
void* Indication_of_brake_switch(void *id)
{
	while(1){

		if(Indication_of_brake_switchi != buffer[6])Indication_of_brake_switchi = buffer[7];

		//std::cout<<"Indication_of_brake_switch: "<<Indication_of_brake_switchi<<std::endl;

		usleep(100000);
	}
	return NULL;
}


/*
 * Data producer
 * Reads a line of the file every period of sleepTime
 * Place all variables of interest into a buffer every period
 * Update the buffer with new variables from dataset every period
 */
void* read_csv_thread(void *id){

	//Initalize variables
	std::string val;
	std::string line;
	std::ifstream myFile;
	char filename[] = "dataset.txt";

	//open csv file with dataset and verify for errors
	myFile.open(filename);

	if(!myFile.is_open())
	{
		std::cout << "Could not open file" << std::endl;
	}


	// Read dataset if no error opening it
	if(myFile.good()){
		// Extract the first line in the dataset
		// The names of every variable of interest is the first line
		std::getline(myFile, line);

		// Create a stringstream from line
		std::stringstream ss(line);
		//std::cout<<line<<std::endl;

		// Read the rest of the dataset, line by line
		// Read every period of 0.01s
		// While there is still lines
		while(std::getline(myFile, line)){

			// Create a stringstream of the current line
			std::stringstream ss(line);

			// Wait until semaphore is empty and enter it
			// Lock mutex to not let other threads to get access
			sem_wait(&empty);
			pthread_mutex_lock(&mutex);

			// Keep track of the current column index
			// The variable index
			// 0: Full Consumption, 1: Engine Speed (RPM), 2: Engine Coolant Temperature, 3: Current Gear
			// 4: Transmission Oil Temperature, 5: Vehicle Speed, 6: Acceleration Speed Longitudinal, 7: Indication of break switch
			int x = 0;

			// Extract each value of the current line
			while(std::getline(ss, val, ',')){
				// Add the current variable to the 'x' column's values vector
				buffer[x] = val;

				// Increment the column index
				x++;
			}
			// All variables of the current line are stored in the buffer
			// std::cout<<"\nProduced "<<line<<std::endl;

			// Release semaphore and mutex
			pthread_mutex_unlock(&mutex);
			sem_post(&full);

			//wait until next period
			sleep(SleepTime);
		}

	}

	// Close file
	myFile.close();
	return NULL;
}

/*
 * Main method
 * Main thread
 * Initalizes and creates reader and display threads
 */
int main()
{
	//Initialize the Id's for the threads created
    pthread_t r_thread,fuel_thread,rpm_thread, coolant_thread,gear_thread,transmission_thread,speed_thread,acceleration_thread,brake_switch_thread,disp_thread;

    //Initialize the semaphore and mutex
    sem_init(&empty,0,BUFFER_SIZE);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);

	//initialize variables
	void* status;
	int t;

    //create file reader thread read a line every 10ms and check for errors
    t = pthread_create(&r_thread, NULL, read_csv_thread, (void*)r_thread);
	if (t != 0)
	{
		std::cout << "Error in file reading thread creation: " << t << std::endl;
	}

	//create Full Consumption thread to get variable value every 10ms and check for errors
	t = pthread_create(&fuel_thread, NULL, Fuel_consumption, (void*)fuel_thread);
	if (t != 0)
	{
		std::cout << "Error in fuel consumption thread creation: " << t << std::endl;
	}

	//create Engine Speed thread to get variable value every 500ms and check for errors
	t = pthread_create(&rpm_thread, NULL, Engine_speed, (void*)rpm_thread);
	if (t != 0)
	{
		std::cout << "Error in engine speed thread creation: " << t << std::endl;
	}

	//create engine coolant temperature thread to get variable value every 2s and check for errors
	t = pthread_create(&coolant_thread, NULL, Engine_coolant_temperature, (void*)coolant_thread);
	if (t != 0)
	{
		std::cout << "Error in coolant temperature thread creation: " << t << std::endl;
	}

	//create current gear thread to get variable value every 100ms and check for errors
	t = pthread_create(&gear_thread, NULL, Current_Gear, (void*)gear_thread);
	if (t != 0)
	{
		std::cout << "Error in current gear thread creation: " << t << std::endl;
	}

	//create transmission oil temperature thread to get variable value every 5s and check for errors
	t = pthread_create(&transmission_thread, NULL, Transmission_Oil_Temperature, (void*)transmission_thread);
	if (t != 0)
	{
		std::cout << "Error in transmission oil temp thread creation: " << t << std::endl;
	}

	//create vehicle speed thread to get variable value every 100ms and check for errors
	t = pthread_create(&speed_thread, NULL, Vehicle_speed, (void*)speed_thread);
	if (t != 0)
	{
		std::cout << "Error in engine speed thread creation: " << t << std::endl;
	}

	//create Acceleration Speed Longitudinal thread to get variable value every 100ms and check for errors
	t = pthread_create(&acceleration_thread, NULL, Acceleration_speed_Longitudinal, (void*)acceleration_thread);
	if (t != 0)
	{
		std::cout << "Error in Acceleration Speed Longitudinal thread creation: " << t << std::endl;
	}

	//create Indication of break switch thread to get variable value every 100ms and check for errors
	t = pthread_create(&brake_switch_thread, NULL, Indication_of_brake_switch, (void*)brake_switch_thread);
	if (t != 0)
	{
		std::cout << "Error in Indication of break switch thread creation: " << t << std::endl;
	}

	//create display thread to display the variables of interest every period dispTime and check for errors
	t = pthread_create(&disp_thread, NULL, display_variables, (void*)disp_thread);
	if (t != 0)
	{
		std::cout << "Error in display thread creation: " << t << std::endl;
	}


	//main thread waits until all other threads are finished executing

	//join all the threads created above to terminate program
	t = pthread_join(r_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in reader thread join: " << t << std::endl;
	}

	t = pthread_join(fuel_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in fuel consumption thread join: " << t << std::endl;
	}

	t = pthread_join(rpm_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in engine speed thread join: " << t << std::endl;
	}

	t = pthread_join(coolant_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in coolant thread join: " << t << std::endl;
	}

	t = pthread_join(gear_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in current gear thread join: " << t << std::endl;
	}

	t = pthread_join(transmission_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in transmission oil thread join: " << t << std::endl;
	}

	t = pthread_join(speed_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in vehicle speed thread join: " << t << std::endl;
	}

	t = pthread_join(acceleration_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in acceleration thread join: " << t << std::endl;
	}

	t = pthread_join(brake_switch_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in brake switch thread join: " << t << std::endl;
	}

	t = pthread_join(disp_thread, &status);
	if (t != 0)
	{
		std::cout << "Error in display thread join: " << t << std::endl;
	}

	pthread_exit(NULL);
    return 0;
}
