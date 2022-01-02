/*
 * COEN 320 project threads
 * Jasen Ratnam 40094237
 * 09/11/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

#define BSIZE 80

void *readCSV();
void *universalthread(int parameter);


/*
 * Main thread.
 */

int main ()
{
	/*
	 * variable to save id of thread created
	 */
	pthread_t	thread_id;
	//pthread_t	thread_id2;

	/*
	 * Parameters: a place for the thread ID, thread attributes,
	 * address of the function for the thread to execute, and a
	 * place to possibly pass in a parameter to that function.
	 * Default values (Prio 10, Round Robin Scheduling) = NULL
	 */

	//char fname = "Driving Data(KIA SOUL).csv";
	//read_csv(row, col, fname, data);

	printf("We are now creating two more threads...\n");
	pthread_create(&thread_id,NULL, (void *) &readCSV, NULL);
	//pthread_create(&thread_id2,NULL, (void *) &universalthread, (void *) 59);
	printf("Threads created.\n");

	printf("The main thread is going on...\n");
	printf("... as long as it hasn't used up its timeslice.\n");

	/*
	 * Main thread waits for a thread to complete
	 * The function pthread_join() will not return until the corresponding thread completes.
	 */
	printf("Main thread now waiting for %d thread to finish\n",thread_id);
	pthread_join(thread_id, NULL);
	//pthread_join(thread_id2, NULL);
	printf("Thread %d completed its function!\n",thread_id);
	//printf("Thread %d completed its function!\n",thread_id2);

	//printf("Main thread now waiting for termination through user.\n");
 	//pause();

	return EXIT_SUCCESS;
}


void *readCSV()
{
	//DO something
	printf("CSV readin active\n");

	//open CSV file
	FILE *filePointer;
	char *field;


	char *filename= "dataset.txt";
	char *mode = "r";

	char buffer[BSIZE];

	filePointer = fopen(filename, mode);

	if (filePointer == NULL)
	{
		fprintf(stderr, "ERROR: Unable to open file: %s\n", filename);
		perror(filePointer);
		exit(-1);
	}

	//read file
	while(fgets(buffer,BSIZE,filePointer))
	{
		field=strtok(buffer,",");
		printf("%s\t",field);

		field=strtok(NULL,",");
		printf("%s\t",field);

		field=strtok(NULL,",");
		printf("%s\t",field);

		field=strtok(NULL,",");
		printf("%s\t",field);

		field=strtok(NULL,",");
		printf("%s\t\n",field);
	}

	//close the file
	fclose(filePointer);

	//Termination of thread
	printf ("CSV reading is finished.\n");

	return(NULL);
}

void *universalthread(int parameter)
{
	//Intialize local temporary variable
	int localvariable = 3;
	//Intialize the counter of loop
	int counter = 0;

	//start running code
	printf("universalthread is now running...\n");

	//loop thread with period of 2
	while ( counter < 5)
	{
		//Do operations
		printf ("universalthread: localvariable %d * parameter %d = %d\n", localvariable, parameter, (localvariable * parameter));
		localvariable = localvariable + parameter;
		counter++;

		//wait until next period before next execution
		sleep(2);
	}

	//End of thread
	printf("universalthread with parameter %d finished.\n",parameter);
	return(NULL);
}
