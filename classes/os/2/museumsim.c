#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "museumsim.h"

//
// In all of the definitions below, some code has been provided as an example
// to get you started, but you do not have to use it. You may change anything
// in this file except the function signatures.
//


struct shared_data {
	
	// Tickets
	int tickets;
	pthread_mutex_t ticket_mutex;

	// Waiting visitors
	int visitors_waiting;
	pthread_mutex_t visitors_waiting_mutex;
	pthread_cond_t visitors_waiting_to_enter;

	// Admitting guides
	int open_spots;
	pthread_mutex_t open_spots_mutex;
	pthread_cond_t guides_waiting_to_admit;

	// Guides inside
	int guides_inside;
	pthread_mutex_t guides_inside_mutex;
	pthread_cond_t guides_waiting_to_enter;

	int guides_done;
	pthread_mutex_t guides_done_mutex;
	pthread_cond_t guides_waiting_for_guides;

	// Visitors inside
	int visitors_inside;
	pthread_mutex_t visitors_inside_mutex;

	pthread_cond_t guides_waiting_for_visitors;

	int all_guides_done;

};
static struct shared_data s;

void print_state() {
	//printf("%d\t%d\t%d\t%d\t%d\n", s.tickets, s.visitors_waiting, s.open_spots, s.visitors_inside, s.guides_inside);
}

/**
 * Set up the shared variables for your implementation.
 * 
 * `museum_init` will be called before any threads of the simulation
 * are spawned.
 */
void museum_init(int num_guides, int num_visitors)
{
	s.tickets = MIN(VISITORS_PER_GUIDE * num_guides, num_visitors);
	pthread_mutex_init(&s.ticket_mutex, NULL);

	s.visitors_waiting = 0;
	pthread_mutex_init(&s.visitors_waiting_mutex, NULL);
	pthread_cond_init(&s.visitors_waiting_to_enter, NULL);

	s.open_spots = 0;
	pthread_mutex_init(&s.open_spots_mutex, NULL);
	pthread_cond_init(&s.guides_waiting_to_admit, NULL);

	s.guides_inside = 0;
	pthread_mutex_init(&s.guides_inside_mutex, NULL);
	pthread_cond_init(&s.guides_waiting_to_enter, NULL);

	s.visitors_inside = 0;
	pthread_mutex_init(&s.visitors_inside_mutex, NULL);

	s.guides_done = 0;
	pthread_mutex_init(&s.guides_done_mutex, NULL);
	pthread_cond_init(&s.guides_waiting_for_guides, NULL);

	pthread_cond_init(&s.guides_waiting_for_visitors, NULL);

	s.all_guides_done = 0;
}


/**
 * Tear down the shared variables for your implementation.
 * 
 * `museum_destroy` will be called after all threads of the simulation
 * are done executing.
 */
void museum_destroy()
{
	pthread_mutex_destroy(&s.ticket_mutex);
	
	pthread_mutex_destroy(&s.visitors_waiting_mutex);
	pthread_cond_destroy(&s.visitors_waiting_to_enter);

	pthread_mutex_destroy(&s.open_spots_mutex);
	pthread_cond_destroy(&s.guides_waiting_to_admit);

	pthread_mutex_destroy(&s.guides_inside_mutex);
	pthread_cond_destroy(&s.guides_waiting_to_enter);

	pthread_mutex_destroy(&s.visitors_inside_mutex);

	pthread_mutex_destroy(&s.guides_done_mutex);

	pthread_cond_destroy(&s.guides_waiting_for_guides);
	pthread_cond_destroy(&s.guides_waiting_for_visitors);
}


/**
 * Implements the visitor arrival, touring, and leaving sequence.
 */
void visitor(int id)
{
	// visitor_arrives(id);
	// visitor_tours(id);
	// visitor_leaves(id);

	// Visitor arrives
    visitor_arrives(id);

	// Visitor attempts to get ticket
	// If fail, leave
	pthread_mutex_lock(&s.ticket_mutex);
	{
		pthread_mutex_lock(&s.visitors_waiting_mutex);
		{
			if (s.tickets > 0) { 
				s.tickets--;
			} else {
				visitor_leaves(id);
				//print_state();
				pthread_mutex_unlock(&s.ticket_mutex);
				pthread_mutex_unlock(&s.visitors_waiting_mutex);
				return;
			}
			s.visitors_waiting++;
		}
		pthread_mutex_unlock(&s.visitors_waiting_mutex);
		//print_state();
	}
	pthread_mutex_unlock(&s.ticket_mutex);

	// If no ticket, leave
	

	
   

	// Signal to waiting guides
	pthread_cond_signal(&s.guides_waiting_to_admit);

	// Wait for a spot
	pthread_mutex_lock(&s.open_spots_mutex);
	{
		while (s.open_spots == 0) {
			//printf("Visitor %d waiting for guide\n", id);
			pthread_cond_wait(&s.visitors_waiting_to_enter, &s.open_spots_mutex);
		}

		// There is a guide availible

		// Take the spot
		s.open_spots--;

		// Actually admit the visitor
		pthread_mutex_lock(&s.visitors_inside_mutex);
		{
			s.visitors_inside++;
			//print_state();
		}
		pthread_mutex_unlock(&s.visitors_inside_mutex);
		
	}
	pthread_mutex_unlock(&s.open_spots_mutex);

	// Not in lock because of delay
	visitor_tours(id);
	

	// Leave the museum
	pthread_mutex_lock(&s.visitors_inside_mutex);
	{
		s.visitors_inside--;
		visitor_leaves(id);
		//print_state();
		pthread_cond_broadcast(&s.guides_waiting_for_visitors);
	}
	pthread_mutex_unlock(&s.visitors_inside_mutex);
}

/**
 * Implements the guide arrival, entering, admitting, and leaving sequence.
 */
void guide(int id)
{

	int num_visitors_to_admit = VISITORS_PER_GUIDE;
	// guide_admits(id);
	// guide_leaves(id);

	// Guide arrives
	guide_arrives(id);
	//print_state();

	// Wait for space in museum
	pthread_mutex_lock(&s.guides_inside_mutex);
	{

		while (s.guides_inside == GUIDES_ALLOWED_INSIDE || s.all_guides_done) {
			pthread_cond_wait(&s.guides_waiting_to_enter, &s.guides_inside_mutex);
		}

		// This thread has space
		// Enter museum
		s.guides_inside++;
		guide_enters(id);
		//print_state();
	}
	pthread_mutex_unlock(&s.guides_inside_mutex);


	// While more visitors in personal count
	while (num_visitors_to_admit > 0) {
		// TODO: check more visitors availible

		int done_early = 0;
		pthread_mutex_lock(&s.open_spots_mutex);
		{
			pthread_mutex_lock(&s.ticket_mutex);
			{
				pthread_mutex_lock(&s.visitors_waiting_mutex);
				{
					if (s.open_spots >= (s.tickets + s.visitors_waiting)) {
						done_early = 1;
					} else {
						s.open_spots++;
					}
				}
				pthread_mutex_unlock(&s.visitors_waiting_mutex);
			}
			pthread_mutex_unlock(&s.ticket_mutex);

			// Signal to visitors
			pthread_cond_signal(&s.visitors_waiting_to_enter);

		}
		pthread_mutex_unlock(&s.open_spots_mutex);

		if (done_early) {
			break;
		}

		// Add a spot
		// pthread_mutex_lock(&s.open_spots_mutex);
		// {
			

			
		// }
		// pthread_mutex_unlock(&s.open_spots_mutex);
		//printf("Guide %d opens spot\n", id);
		//print_state();


		// Wait for a visitor
		pthread_mutex_lock(&s.visitors_waiting_mutex);
		{
			while (s.visitors_waiting == 0) {
				//printf("Guide %d waiting for visitor\n", id);
				pthread_cond_wait(&s.guides_waiting_to_admit, &s.visitors_waiting_mutex);
			}

			// Remove the visitor from waiting
			s.visitors_waiting--;

			// Actually admit, dummy
			guide_admits(id);
		}
		pthread_mutex_unlock(&s.visitors_waiting_mutex);
		//print_state();

		num_visitors_to_admit--;
	}

	// Declare done
	pthread_mutex_lock(&s.guides_done_mutex);
	{
		s.guides_done++;
	}
	pthread_mutex_unlock(&s.guides_done_mutex);

	// Check all guides done
	pthread_mutex_lock(&s.guides_done_mutex);
	{
		pthread_mutex_lock(&s.guides_inside_mutex);
		{
			while (s.guides_done < s.guides_inside && !s.all_guides_done) {
				pthread_mutex_unlock(&s.guides_done_mutex);
				pthread_cond_wait(&s.guides_waiting_for_guides, &s.guides_inside_mutex);
				pthread_mutex_lock(&s.guides_done_mutex);
			}

			// All guides are done
			s.all_guides_done = 1;

			// Flag allows all threads out
			pthread_cond_broadcast(&s.guides_waiting_for_guides);
		}
		pthread_mutex_unlock(&s.guides_inside_mutex);
		
	}
	pthread_mutex_unlock(&s.guides_done_mutex);

	// Wait for other guides to be ready to leave

	// Wait for visitors to leave
	pthread_mutex_lock(&s.visitors_inside_mutex);
	{
		while (s.visitors_inside > 0) {
			pthread_cond_wait(&s.guides_waiting_for_visitors, &s.visitors_inside_mutex);
		}
	}
	pthread_mutex_unlock(&s.visitors_inside_mutex);


	// Remove the guide
	pthread_mutex_lock(&s.guides_inside_mutex);
	{
		s.guides_inside--;
		guide_leaves(id);
		if (s.guides_inside == 0) {
			// Last thread, reset flag and signal
			s.all_guides_done = 0;
			pthread_cond_signal(&s.guides_waiting_to_enter);
		}
	}
	pthread_mutex_unlock(&s.guides_inside_mutex);
	

		// Check more visitors availible (tickets and visitors waiting)
		// If not, leave

		// Add a spot

		// Wait for a visitor

		// Admit the visitor
		// Remove one from the line
		// Add one to inside
		// Signal waiting visitors
}


