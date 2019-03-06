/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains private messaging queue management tools used internally
 *  by the 'queue' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/


/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <string.h>             //  Functions for managing strings
#include <stdlib.h>             //  ANSI standard library.
#include <unistd.h>             //  Access to the POSIX operating system API
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "queue_lib.h"          //  API for all QUEUE__*         PRIVATE
                                //*******************************************

/****************************************************************************
 * Enumerations local to this file
 ****************************************************************************/

//------------------------------------------------------------------
//------------------------------------------------------------------

/****************************************************************************
 * Definitions local to this file
 ****************************************************************************/

//------------------------------------------------------------------
#define DEBUG_MODULE_QUEUE      ( 1 )
//------------------------------------------------------------------

/****************************************************************************
 * Structures local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Storage Allocation local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * LIB Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Send a signal that there is a new message for 'queue_id'.
 *
 *  @param  queue_cb_p      Pointer to a message queue control block
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
QUEUE__send_signal(
    struct  queue_cb_t          *   queue_cb_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Wake-up a thread for the new message.
     ************************************************************************/

    // Signal the job queue thread that something new is on the queue.
    pthread_cond_signal(  &queue_cb_p->queue_signal );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Wait for a signal indicating there is a new message for 'queue_id'.
 *
 *  @param  queue_cb_p          Pointer to a message queue control block
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

#define QUEUE_ALT_METHOD          ( 1 )
void
QUEUE__wait_signal(
    struct  queue_cb_t          *   queue_cb_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Change the queue state to waiting.
    queue_cb_p->msg_queue_state = MSGQSTATE_RCV_WAITING;

    /************************************************************************
     *  Wait for a new message
     ************************************************************************/

    // Wait for a signal that there is a new message in the queue.
    pthread_cond_wait(    &queue_cb_p->queue_signal,
                          &queue_cb_p->queue_lock );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Change the queue state to waiting.
    queue_cb_p->msg_queue_state = MSGQSTATE_IDLE;
}

/****************************************************************************/
/**
 *  Verify that the queue name string meets all requirements for a valid
 *  queue name.
 *
 *  @param  queue_name_p    Pointer to an ASCII string containing the name.
 *
 *  @return queue_rc        See queue_rc_e for a list of return codes.
 *
 *  @note
 *
 ****************************************************************************/

enum queue_rc_e
QUEUE__verify_queue_name(
    char                        *   queue_name_p
    )
{
    /**
     *  @param  queue_rc        Return code                                 */
    enum    queue_rc_e              queue_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = QUEUE_RC_SUCCESS;

    /************************************************************************
     *  Validate the Message-Queue-Name
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Is the Queue-Name string too long ?
        if ( strlen( queue_name_p ) > QUEUE_NAME_L )
        {
            //  YES:    Set the error code.
            queue_rc = QUEUE_RC_QUEUE_NAME_TOO_LONG;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  All done.
    return( queue_rc );
}

/****************************************************************************/
/**
 *  Search the messaging queue list for a queue-name match.
 *
 *  @param  queue_name_p    Pointer to an ASCII string containing the name
 *                          of the queue to search for.
 *
 *  @return queue_rc        The message queue ID number when greater then
 *                          zero. When less then zero see queue_rc_e for a
 *                          list of failure codes.
 *
 *  @note
 *
 ****************************************************************************/

int
QUEUE__find_queue_name(
    char                        *   queue_name_p
    )
{
    /**
     *  @param  queue_id        The message queue ID number (handle)        */
    int                             queue_id;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;
    /**
     *  @param  access_key      Performance access key for a list           */
    int                             access_key;
    /**
     *  @param  queue_name      Expanded form of the queue_name             */
    char                            queue_name[ QUEUE_NAME_L + 1 ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_id = QUEUE_RC_SUCCESS;

    //  Prevent other threads from modifying the queue list.
    access_key = list_user_lock( queue_name_id_base_p );

    //  Build the space expanded queue_name
    //  @NOTE   This instruction should but can't use QUEUE_NAME_L
    snprintf( queue_name, sizeof( queue_name ),
              "%-8s", queue_name_p );

    /************************************************************************
     *  Locate the queue name in the list of message queues.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_id == QUEUE_RC_SUCCESS )
    {
        queue_cb_p = list_fget_first( queue_name_id_base_p, access_key );
        for ( queue_cb_p = list_fget_first( queue_name_id_base_p, access_key );
              queue_cb_p != NULL;
              queue_cb_p = list_fget_next( queue_name_id_base_p,
                                           queue_cb_p,
                                           access_key ) )
        {
            //  Is this the queue name we are looking for ?
            if ( strncmp( queue_cb_p->queue_name,
                          queue_name, QUEUE_NAME_L ) == 0 )
            {
                //  YES:    We are done looking
                break;
            }
        }
    }

    /************************************************************************
     *  Set the return code
     ************************************************************************/

    //  Did we find a name match ?
    if ( queue_cb_p == NULL )
    {
        //  NO:     It doesn't exist.
        queue_id = QUEUE_RC_QUEUE_NAME_NOT_PRESENT;
    }
    else
    {
        //  YES:    Return the Queue ID.
        queue_id = queue_cb_p->queue_id;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow other threads access to the queue list again.
    list_user_unlock( queue_name_id_base_p, access_key );

    //  All done.
    return( queue_id );
}

/****************************************************************************/
/**
 *  Create a new queue and add it to the queue name base list.
 *
 *  @param  queue_name_p    Pointer to an ASCII string containing the name
 *                          that will be assigned to the new message queue.
 *
 *  @return queue_rc        The message queue ID number when greater then
 *                          zero. When less then zero see queue_rc_e for a
 *                          list of failure codes.
 *
 *  @note
 *
 ****************************************************************************/

int
QUEUE__new(
    char                        *   queue_name_p
    )
{
    /**
     *  @param  queue_rc        Return_code                                 */
    int                             queue_rc;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;
    /**
     *  @param  access_key      Lock key for a list                         */
    int                             access_key;
    /**
     *  @param  queue_name      Expanded form of the queue_name             */
    char                            queue_name[ QUEUE_NAME_L + 1 ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = QUEUE_RC_SUCCESS;

    //  Prevent other threads from modifying the queue list.
    access_key = list_user_lock( queue_name_id_base_p );

    //  Build the space expanded queue_name
    //  @NOTE   This instruction should but can't use QUEUE_NAME_L
    snprintf( queue_name, sizeof( queue_name ),
              "%-8s", queue_name_p );

    /************************************************************************
     *  Allocate a new Queue Control Block.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Allocate storage space for a new
        queue_cb_p = (struct queue_cb_t*)malloc( sizeof( struct queue_cb_t ) );
        memset( queue_cb_p, 0x00, sizeof( struct queue_cb_t ) );
    }

    /************************************************************************
     *  Initialize the Queue Control Block.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Copy the Queue Name
        strncpy( queue_cb_p->queue_name, queue_name,
                 sizeof( queue_cb_p->queue_name ) );

        //  Initialize pthread stuff.
        pthread_mutex_init( &queue_cb_p->queue_lock,   0 );
        pthread_cond_init(  &queue_cb_p->queue_signal, 0 );

        //  There isn't anything on the queue yet.
        queue_cb_p->queue_state.queue_msg_count = 0;

        //  Set the Queue ID number.
        queue_cb_p->queue_id = ++last_used_queue_id;
    }

    /************************************************************************
     *  Append it to the list
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Create the new queue base
        queue_cb_p->queue_base_p = list_new( );

        log_write( MID_INFO, "QUEUE__new",
                      "Allocate a new list structure 'queue_cb_p->queue_base_p' [%p].\n",
                      queue_cb_p->queue_base_p );

        //  Append the new queue to the Name/ID list
        list_fput_last( queue_name_id_base_p, queue_cb_p, access_key );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Was the new queue successfully created ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  YES:    Set the Queue ID as the return code.
        queue_rc = queue_cb_p->queue_id;
    }

    //  Allow other threads access to the queue list again.
    list_user_unlock( queue_name_id_base_p, access_key );

    //  All done.
    return( queue_rc );
}

/****************************************************************************/
/**
 *  Return a pointer to the Message Queue base structure for the Message
 *  Queue-ID
 *
 *  @param  queue_id        A message queue ID number (handle)
 *
 *  @return queue_rc        See queue_rc_e for a list of return codes.
 *
 *  @note
 *
 ****************************************************************************/

struct  queue_cb_t *
QUEUE__find_queue_cb(
    int                             queue_id
    )
{
    /**
     *  @param  queue_rc        Return code                                 */
    enum    queue_rc_e              queue_rc;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;
    /**
     *  @param  access_key      Lock key for a list                         */
    int                             access_key;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = QUEUE_RC_SUCCESS;

    //  Prevent other threads from modifying the queue list.
    access_key = list_user_lock( queue_name_id_base_p );

    /************************************************************************
     *  Locate the queue name in the list of message queues.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Not entirely sure why this is here (Empty queue ? )
        queue_cb_p = list_fget_first( queue_name_id_base_p, access_key );

        //  Loop through all message queues.
        for ( queue_cb_p = list_fget_first( queue_name_id_base_p, access_key );
              queue_cb_p != NULL;
              queue_cb_p = list_fget_next( queue_name_id_base_p,
                                           queue_cb_p,
                                           access_key ) )
        {
            //  Is this the queue name we are looking for ?
            if ( queue_cb_p->queue_id == queue_id )
            {
                //  YES:    We are done looking.
                break;
            }
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow other threads access to the queue list again.
    list_user_unlock( queue_name_id_base_p, access_key );

    //  All done.
    return( queue_cb_p );
}

/****************************************************************************/
/**
 *  Return the number of messages on the messaging queue.
 *
 *  @param  queue_id        A message queue ID number (handle)
 *
 *  @return queue_msg_count The number of messages on the messaging queue.
 *
 *  @note
 *
 ****************************************************************************/

int
QUEUE__get_count(
    int                             queue_id
    )
{
    enum    queue_rc_e              queue_rc;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = QUEUE_RC_SUCCESS;

    //  Set the Queue State pointer to NULL
    queue_cb_p = NULL;

    /************************************************************************
     *  Locate the Queue control block for the queue.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Get the queue base for the requested Queue-ID
        queue_cb_p = QUEUE__find_queue_cb( queue_id );

        //  Did we find a Queue-ID match ?
        if ( queue_cb_p == NULL )
        {
            //  NO:     It doesn't exist.
            queue_rc = QUEUE_RC_QUEUE_NAME_NOT_PRESENT;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  All done.
    return( queue_cb_p->queue_state.queue_msg_count );
}

/****************************************************************************/
/**
 *  Put a message on the message queue.
 *
 *  @param  queue_id        A message queue ID number (handle)
 *  @param  message_p       Pointer to the message that goes into the queue.
 *
 *  @return queue_rc        See queue_rc_e for a list of return codes.
 *
 *  @note
 *
 ****************************************************************************/

int
QUEUE__put_payload(
    int                             queue_id,
    void                        *   void_p
    )
{
    int                             queue_rc;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = true;

    //  Set the Queue State pointer to NULL
    queue_cb_p = NULL;

    /************************************************************************
     *  Locate the Queue control block for the queue.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == true )
    {
        //  Get the queue base for the requested Queue-ID
        queue_cb_p = QUEUE__find_queue_cb( queue_id );

        //  Did we find a Queue-ID match ?
        if ( queue_cb_p == NULL )
        {
            //  NO:     It doesn't exist.
            queue_rc = QUEUE_RC_QUEUE_NAME_NOT_PRESENT;
        }
    }

    /************************************************************************
     *  Append the new payload to the end of the queue
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == true )
    {
        //  Lock the queue to this thread.
        pthread_mutex_lock( &queue_cb_p->queue_lock );

        //  Append the new payload to the end of the queue
        queue_rc = list_put_last( queue_cb_p->queue_base_p, void_p );

        //  Decrement the number of messages in the queue.
        queue_cb_p->queue_state.queue_msg_count += 1;
    }

    /************************************************************************
     *  Signal the receive thread there is a new message
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == true )
    {
        //  Is the receive thread waiting for another payload ?
        if ( queue_cb_p->msg_queue_state == MSGQSTATE_RCV_WAITING )
        {
            //  YES:    Send it a signal.
            QUEUE__send_signal( queue_cb_p );
        }

        //  Release the queue lock.
        pthread_mutex_unlock( &queue_cb_p->queue_lock );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  All done.
    return( queue_rc );
}

/****************************************************************************/
/**
 *  Get the next message from a queue.
 *
 *  @param  queue_id        A message queue ID number (handle)
 *
 *  @return message_p       A pointer to a message payload.
 *
 *  @note
 *
 ****************************************************************************/

void    *
QUEUE__get_payload(
    int                             queue_id
    )
{
    /**
     *  @param  queue_rc        Return code                                 */
    enum    queue_rc_e              queue_rc;
    /**
     *  @param  queue_cb_p      Pointer to a message queue control block    */
    struct  queue_cb_t          *   queue_cb_p;
    /**
     *  @param  void_p          Pointer to the return information           */
    void                        *   void_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default return code.
    queue_rc = QUEUE_RC_SUCCESS;

    //  Set the Queue State pointer to NULL
    queue_cb_p = NULL;

    //  Just in case there is a problem.
    void_p = NULL;

    /************************************************************************
     *  Locate the Queue control block for the queue.
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Get the queue base for the requested Queue-ID
        queue_cb_p = QUEUE__find_queue_cb( queue_id );

        //  Did we find a Queue-ID match ?
        if ( queue_cb_p == NULL )
        {
            //  NO:     It doesn't exist.
            queue_rc = QUEUE_RC_QUEUE_NAME_NOT_PRESENT;
        }
    }

    /************************************************************************
     *  Get the next message from the queue
     ************************************************************************/

    //  Should we continue ?
    if ( queue_rc == QUEUE_RC_SUCCESS )
    {
        //  Lock the queue to this thread.
        pthread_mutex_lock( &queue_cb_p->queue_lock );

        //  Is there anything on in the queue ?
        if ( queue_cb_p->queue_state.queue_msg_count == 0 )
        {
            //  NO:     Wait for something to get.
            QUEUE__wait_signal( queue_cb_p );
        }

        //  There had better be something there now.  Get it.
        void_p = list_get_first( queue_cb_p->queue_base_p );

        //  Delete the payload from the message queue.
        list_delete( queue_cb_p->queue_base_p, void_p );

        //  Decrement the number of messages in the queue.
        queue_cb_p->queue_state.queue_msg_count -= 1;

        //  Release the queue lock.
        pthread_mutex_unlock( &queue_cb_p->queue_lock );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Return the message pointer.
    return( void_p );
}

/****************************************************************************/
