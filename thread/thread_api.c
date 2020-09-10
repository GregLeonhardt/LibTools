/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains the source code for publicly accessible functions
 *  of the 'thread' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_THREAD            ( "ALLOCATE STORAGE FOR THREAD" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <ctype.h>              //  Determine the type contained
#include <pthread.h>            //  pthread_*
#include <unistd.h>             //  Access to the POSIX operating system API
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "thread_lib.h"         //  API for ALL THREAD__*           PRIVATE
                                //*******************************************

/****************************************************************************
 * API Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Initialize a thread start & wait structure
 *
 *  @param  thread_wait_p   Pointer to the thread stop & wait structure.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/


void
thread_flow_init(
    struct  thread_flow_t   *   thread_flow_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Initialize the signal and lock structures.
    pthread_cond_init(  &thread_flow_p->signal, 0 );
    pthread_mutex_init( &thread_flow_p->lock, 0 );

    // Set the access lock.
    pthread_mutex_lock( &thread_flow_p->lock );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

     // DONE!
}

/****************************************************************************/
/**
 *  Signal a thread to resume processing.
 *
 *  @param  thread_wait_p   Pointer to the thread stop & wait structure.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
thread_resume(
    struct  thread_flow_t   *   thread_flow_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    // Set the access lock.
    pthread_mutex_lock( &thread_flow_p->lock );

    // Signal the thread that it can start again.
    pthread_cond_signal( &thread_flow_p->signal );

    // Release the access lock.
    pthread_mutex_unlock( &thread_flow_p->lock );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

     // DONE!
}

/****************************************************************************/
/**
 *  Cause a thread to wait for a resume signal.
 *
 *  @param  thread_wait_p   Pointer to the thread stop & wait structure.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
thread_wait(
    struct  thread_flow_t   *   thread_flow_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    // Signal the thread that it can start again.
    pthread_cond_wait( &thread_flow_p->signal, &thread_flow_p->lock );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

     // DONE!
}


/****************************************************************************/
/**
 *  Spawn off a new thread.
 *
 *  @param  function_p      Pointer to the thread function.
 *  @param  parm_p          Pointer to data that is passed to the new function.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
thread_new(
    void                            (*function_p)( void * ),
    void                        *   parm_p
    )
{
    pthread_t                       pthread;
    pthread_attr_t                  attr;
    int                             rc;

    //  Loop until the new thread is created or rock turns to dust.
    while ( 1 )
    {
        //  Initialize a new Pthread attribute structure for the new thread.
        rc = pthread_attr_init( &attr );

        //  Was the attribute initialization successful ?
        if ( rc == 0 )
        {
            //  YES:    Set the thread type to DETACHED
            rc = pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );

            //  Were we able to successfully set the type ?
            if ( rc != 0 )
            {
                //  NO:     Display a message and terminate the test.
                log_write( MID_WARNING, "thread_new",
                              "WARNING: pthread_attr_setdetachstate() failed.\n" );
            }

            //  Create the new thread
            rc = pthread_create( &pthread,
                                 &attr,
                                 (void *(*)(void *))function_p,
                                 (void*)parm_p );

            //  We don't need the attribute structure any more.
            pthread_attr_destroy( &attr );
        }

        //  Was the new thread successfully created ?
        if ( rc == 0 )
        {
            //  YES:    We are done here
            return;
        }
        else
        {
            //  NO:     Wait and try it again.
            sleep( 1 );
        }
    }
}

/****************************************************************************/
