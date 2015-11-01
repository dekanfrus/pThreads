#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define MAX_THREADS 512

void *compute_pi( void * );


int sample_points;
int total_hits;
int total_misses;
int hits[ MAX_THREADS ];
int sample_points_per_thread;
int num_threads;

clock_t start, end, total;


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

  start = clock();
  printf("Start time: %lf\n", start);

  pthread_attr_init( &attr );
  pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );

  /* parse command line arguments into sample points and number of threads */
  /* there is no error checking here!!!!! */
  /*sample_points = atoi(argv[1]);
  num_threads = atoi(argv[2]);*/

  /* uncomment this block if you want interactive input!!!! */
  /* if so...comment out the two statements above */
    
  printf( "Enter number of sample points: " );
  scanf( "%d", &sample_points );
  printf( "Enter number of threads: " );
  scanf( "%d%", &num_threads );
  

  total_hits = 0;
  sample_points_per_thread = sample_points / num_threads;

  for( ii=0; ii<num_threads; ii++ )
    {
	  
      hits[ii] = ii;
      pthread_create( &p_threads[ ii ], &attr, compute_pi, (void *) &hits[ii] );
	  
    }

  for( ii=0; ii<num_threads; ii++ )
    {
       pthread_join( p_threads[ ii ], NULL );
       total_hits += hits[ ii ];
	   
    }
  
   computed_pi = 4.0 * (double) total_hits / ((double) (sample_points));


   printf( "Computed PI = %lf\n", computed_pi );

   end = clock();
   printf("End time: %lf\n", end);

   total = (double)(end - start) / CLOCKS_PER_SEC;

   printf("Execution Time = %lf\n", total);

  /* return to calling environment */
  return( retval );
}


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
