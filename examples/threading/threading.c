#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    
    struct thread_data* thread_args = (struct thread_data *)thread_param;
    
    //wait
    usleep(1000 * thread_args->wait_to_obtain_ms);
    
    //obtain mutex
    int rc = pthread_mutex_lock(thread_args->mutex);
    if (rc != 0)
    {
    	ERROR_LOG("Failed to obtain mutex");
    }
    else
    {
    	//wait
    	usleep(1000 * thread_args->wait_to_release_ms);
    	
    	//release mutex
    	rc = pthread_mutex_unlock(thread_args->mutex);
    	if (rc != 0)
    	{
    		ERROR_LOG("Failed to release mutex");
    	}
    	else
    	{
    		thread_args->thread_complete_success = true;
    	}
    }
    
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     
     //allocate memory for thread_data
     struct thread_data *params = (struct thread_data *)malloc(sizeof(struct thread_data));
     if (params == NULL)
     {
     	ERROR_LOG("Failed to allocate thread_data"); // return if no available memory
     }
     else
     {
     	memset(params,0,sizeof(struct thread_data));
     	params->thread = thread;
     	params->mutex = mutex;
     	params->wait_to_obtain_ms = wait_to_obtain_ms;
     	params->wait_to_release_ms = wait_to_release_ms;
     	params->thread_complete_success = false;
     	
     	int rc = pthread_create(thread,NULL,threadfunc,params);
     	if (rc != 0)
     	{
     		ERROR_LOG("Failed to create pthread");
     		free(params);
     	}
     	else
     	{
     		// pthread started successfully
     		return true;
     	}
     	
     	//free()
     }
     
     
    return false;
}

