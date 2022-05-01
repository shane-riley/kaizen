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
	pthread_cond_t visitors_waiting_cond;

	// Admitting guides
	int guides_admitting;
	pthread_mutex_t guides_admitting_mutex;
	pthread_cond_t guides_admitting_cond;

	// Guides inside
	int guides_inside;
	pthread_mutex_t guides_inside_mutex;
	pthread_cond_t guides_inside_cond;

	// Visitors inside
	int visitors_inside;
	pthread_mutex_t visitors_inside_mutex;
	pthread_cond_t visitors_inside_cond;

	// Guides leaving
	int guides_leaving;
	pthread_mutex_t guides_leaving_mutex;
	pthread_cond_t guides_leaving_cond;

};

static struct shared_data s;


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
	pthread_cond_init(&s.visitors_waiting_cond, NULL);

	s.guides_admitting = 0;
	pthread_mutex_init(&s.guides_admitting_mutex, NULL);
	pthread_cond_init(&s.guides_admitting_cond, NULL);

	s.guides_inside = 0;
	pthread_mutex_init(&s.guides_inside_mutex, NULL);
	pthread_cond_init(&s.guides_inside_cond, NULL);

	s.visitors_inside = 0;
	pthread_mutex_init(&s.visitors_inside_mutex, NULL);
	pthread_cond_init(&s.visitors_inside_cond, NULL);

	s.guides_leaving = 0;
	pthread_mutex_init(&s.guides_leaving_mutex, NULL);
	pthread_cond_init(&s.guides_leaving_cond, NULL);
	// s.guides_leaving_flag = 0;
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
	pthread_cond_destroy(&s.visitors_waiting_cond);

	pthread_mutex_destroy(&s.guides_admitting_mutex);
	pthread_cond_destroy(&s.guides_admitting_cond);

	pthread_mutex_destroy(&s.guides_inside_mutex);
	pthread_cond_destroy(&s.guides_inside_cond);

	pthread_mutex_destroy(&s.visitors_inside_mutex);
	pthread_cond_destroy(&s.visitors_inside_cond);

	pthread_mutex_destroy(&s.guides_leaving_mutex);
	pthread_cond_destroy(&s.guides_leaving_cond);
}


/**
 * Implements the visitor arrival, touring, and leaving sequence.
 */
void visitor(int id)
{
	// Visitor arrives
	visitor_arrives(id);

	// Check for a ticket
	int ticket_availible = 0;
	pthread_mutex_lock(&s.ticket_mutex);
	{
		if (s.tickets > 0) { 
			ticket_availible = 1;
			s.tickets--;
		}
	}
	pthread_mutex_unlock(&s.ticket_mutex);

	// If no ticket, leave
	if (!ticket_availible) {
		visitor_leaves(id);
		return;
	}

	// Ticket acquired!

	// Add to list of waiting visitors
	pthread_mutex_lock(&s.visitors_waiting_mutex);
	{
		printf("Visitor %d: WAITING\n", id);
		print_state();
		s.visitors_waiting++;
	}
	pthread_mutex_unlock(&s.visitors_waiting_mutex);

	// Wait for a guide
	pthread_mutex_lock(&s.guides_admitting_mutex);
	{
		while (s.guides_admitting == 0) {
			pthread_cond_wait(&s.visitors_waiting_cond, &s.guides_admitting_mutex);
		}

		// There is a spot availible
		// Take the spot
		s.guides_admitting--;

		// Signal a guide to admit and remove visitor from count
		pthread_cond_signal(&s.guides_admitting_cond);

		// Tour the place
		visitor_tours(id);
		print_state();

	}
	pthread_mutex_unlock(&s.guides_admitting_mutex);

	// Decrement count of visitors inside
	pthread_mutex_lock(&s.visitors_inside_mutex);
	{
		s.visitors_inside--;
		pthread_cond_signal(&s.visitors_inside_cond);
		// Leave museum
		visitor_leaves(id);
		print_state();
	}
	pthread_mutex_unlock(&s.visitors_inside_mutex);

}

/**
 * Implements the guide arrival, entering, admitting, and leaving sequence.
 */
void guide(int id)
{

	// Number of visitors to admit
	int num_to_admit = VISITORS_PER_GUIDE;

	// Guide arrives
	guide_arrives(id);

	// Guide waits to enter
	pthread_mutex_lock(&s.guides_inside_mutex);
	{
		while (s.guides_inside >= GUIDES_ALLOWED_INSIDE) {
			pthread_cond_wait(&s.guides_inside_cond, &s.guides_inside_mutex);
		}

		// Guide enters
		s.guides_inside++;
		guide_enters(id);
		print_state();
	}
	pthread_mutex_unlock(&s.guides_inside_mutex);
	

	while (num_to_admit > 0) {
		// If here, there will always be space in the museum

		// Prepare to admit
		pthread_mutex_lock(&s.guides_admitting_mutex);
		{
			s.guides_admitting++;
		}
		pthread_mutex_unlock(&s.guides_admitting_mutex);

		pthread_mutex_lock(&s.visitors_waiting_mutex);
		{
			while (s.visitors_waiting == 0) {
				pthread_cond_wait(&s.guides_admitting_cond, &s.visitors_waiting_mutex);
			}

			// Admit the visitor
			s.visitors_waiting--;
			pthread_mutex_lock(&s.visitors_inside_mutex);
			{
				s.visitors_inside++;
			}
			pthread_mutex_unlock(&s.visitors_inside_mutex);
			guide_admits(id);
			// pthread_cond_signal(&s.visitors_waiting_cond);
		}
		pthread_mutex_unlock(&s.visitors_waiting_mutex);
		num_to_admit--;

		// Check tickets
		int ticket_availible = 0;
		pthread_mutex_lock(&s.ticket_mutex);
		{
			if (s.tickets > 0) { 
				ticket_availible = 1;
			}
		}
		pthread_mutex_unlock(&s.ticket_mutex);
		if (!ticket_availible) { break; };
	}

	// Guide is ready to leave
	while (1) {}
	// Increment guide leaving value
	// pthread_mutex_lock(&s.guides_leaving_mutex);
	// {
	// 	s.guides_leaving++;

	// 	pthread_mutex_lock(&s.guides_inside_mutex);
	// 	{
	// 		while (s.guides_leaving != s.guides_inside || !s.guides_leaving_flag) {
	// 			pthread_cond_wait(&s.guides_leaving_cond, &s.guides_leaving_mutex);
	// 		}
	// 	}
	// 	pthread_mutex_unlock(&s.guides_inside_mutex);

	// 	// These threads
		
	// }
	// pthread_mutex_unlock(&s.guides_leaving_mutex);


	// // Wait until visitors leave
	// pthread_mutex_lock(&s.visitors_inside_mutex);
	// {
	// 	while (s.visitors_inside > 0) {
	// 		pthread_cond_wait(&s.visitors_inside_cond, &s.visitors_inside_mutex);
	// 	}
	// }
	// pthread_mutex_lock(&s.visitors_inside_mutex);

	// // Set leaving flag to free others
	// s.guides_leaving_flag = 1;
	// pthread_cond_signal(&s.guides_leaving_cond);

	// // Decrement 
	// pthread_mutex_lock(&s.guides_inside_mutex);
	// {
	// 	s.guides_inside--;
	// 	s.guides_leaving--;

	// 	guide_leaves(id);

	// 	if (s.guides_inside == 0) {
	// 		// This is the last thread, signal to guides waiting to enter and lower flag
	// 		s.guides_leaving_flag = 0;
	// 		pthread_cond_broadcast(&s.guides_inside_cond);
	// 	}
		
	// }
	// pthread_mutex_unlock(&s.guides_inside_mutex);
}


void print_state() {
	printf("%d\t%d\t%d\t%d\n", s.visitors_waiting, s.guides_admitting, s.visitors_inside, s.guides_inside);
}