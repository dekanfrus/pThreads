//**********************************************************************************
//
// John Alves
// Operating Systems
// Project #2: Computing PI
// November 2nd, 2015
// Instructor: Dr. Katangur
//
//**********************************************************************************


//**********************************************************************************
//
// Includes and Defines
//
//**********************************************************************************
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define MAX_THREADS 512

// Function prototype for compute_pi function
void *compute_pi( void * );

// Global variable declaration
int sample_points;
int total_hits;
int total_misses;
int hits[ MAX_THREADS ];
int sample_points_per_thread;
int num_threads;
double total;

// Variables to store the start and end time of the program execution
clock_t start, end;


int main( int argc, char *argv[] )
{
  /* local variables */
  int ii;
  int retval;
  pthread_t p_threads[MAX_THREADS];
  pthread_attr_t attr;
  double computed_pi;

  /* initialize local variables */
  retval = 0;

  pthread_attr_init( &attr );
  pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );

  /* parse command line arguments into sample points and number of threads */
  /* there is no error checking here!!!!! */
  sample_points = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  /* uncomment this block if you want interactive input!!!! */
  /* if so...comment out the two statements above */
    
  /*printf( "Enter number of sample points: " );
  scanf( "%d", &sample_points );
  printf( "Enter number of threads: " );
  scanf( "%d%", &num_threads );*/
  
  // Store the current time in the "start" variable
  start = clock();
  
  total_hits = 0;
  sample_points_per_thread = sample_points / num_threads;

  // Create the number of threads as requested by the user from the command line
  // Each thread will execute the compute_pi function
  for( ii=0; ii<num_threads; ii++ )
    {
	  
      hits[ii] = ii;
      pthread_create( &p_threads[ ii ], &attr, compute_pi, (void *) &hits[ii] );
	  
    }

  // Join all threads
  for( ii=0; ii<num_threads; ii++ )
    {
       pthread_join( p_threads[ ii ], NULL );
       total_hits += hits[ ii ];
	   
    }
  
   computed_pi = 4.0 * (double) total_hits / ((double) (sample_points));

   // Store the final clock time
   end = clock();

   printf( "Computed PI = %lf\n", computed_pi );

   // Calculate the total execution time and then print that to the screen
   total = (double)(end - start) / CLOCKS_PER_SEC;

   printf("Execution Time = %lf\n", total);

  /* return to calling environment */
  return( retval );
}

//********************************************************************
//
// Compute PI  Function
//
//
// Global Parameters
// --------------------
//
//
// Local Variables
// ------------------
// seed			unsigned int	Used to seed the random number generator
// ii			int				Counter for the for loop
// hit_pointer	int pointer		Pointer for the thread number
// local_hits	int				Holds the number of sample points each thread is responsible for
// rand_no_x	double			Holds a randomly generated number
// rand_no_y	double			Holds a randomly generated number
//
//*******************************************************************
void *compute_pi( void *s )
{
  unsigned int seed;
  int ii;
  int *hit_pointer;
  int local_hits;
  double rand_no_x;
  double rand_no_y;

  hit_pointer = (int *) s;
  seed = *hit_pointer;
  local_hits = 0;


  for( ii=0; ii < sample_points_per_thread; ii++ )
    {
	  
      rand_no_x = (double) (rand_r( &seed ))/(double)RAND_MAX;
      rand_no_y = (double) (rand_r( &seed ))/(double)RAND_MAX;
      if(((rand_no_x - 0.5) * (rand_no_x - 0.5) +
	  (rand_no_y - 0.5) * (rand_no_y - 0.5)) < 0.25)
	local_hits++;
      seed *= ii;
	  
    }

  *hit_pointer = local_hits;
  pthread_exit(0);
}
