/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  The 'List' library provide the ability to create, destroy, append
 *  to, remove from and search a list of pointers.
 *
 *  The link list itself does not store any actual data.  It simply creates a
 *  list pf pointers to the data.
 *
 *  The "fast" access function calls were developed because of the time that
 *  was being consumed by continuously searching for the previous pointer for
 *  the  "next" and "prev" functions.  The link list management functions has
 *  no way of knowing if multiple execution threads are simultaneously
 *  scanning the list, each scan had to start fresh and search for the last
 *  access cell then pick up the 'next' or prev' cell.  The "fast" access
 *  method ensures this doesn't happen by allowing the execution thread to
 *  "lock" access to the list.  For this reason the "fast" access mode (used
 *  for large tables). Call must first call list_user_lock() any of the f_get
 *  functions can be used.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_LINKLIST          ( "ALLOCATE STORAGE FOR LINK-LIST" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <sys/types.h>          //  getpid()
#include <unistd.h>             //  Access to the POSIX operating system API
#include <stdlib.h>             //  ANSI standard library.
#include <string.h>             //  Functions for managing strings
#include <time.h>               //  Date and time standard library.
#include <sys/file.h>           //  apply or remove an advisory lock on
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "list_lib.h"           //  API for all LIST__*             PRIVATE
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
struct  log_file_t
{
    /**
     *  File control structure.                                             */
    FILE                        *   log_file_fp;
    /**
     *  File descriptor ID                                                  */
    int                             fd;
    /**
     *  File lock structure                                                 */
    struct  flock                   lock;
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
    pthread_mutex_t                 thread_lock;
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Create a new link-list base structure.
 *
 *  @param  void
 *
 *  @return list_base_p         Pointer to the newly created link-list.
 *
 *  @note
 *
 ****************************************************************************/

struct  list_base_t   *
list_new(
    void
    )
{
    struct  list_base_t         *   list_base_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_base_p = NULL;

    /************************************************************************
     *  Append the payload to the end of the link list
     ************************************************************************/

    //  Allocate storage for the new link-list base structure.
    list_base_p = (struct list_base_t*)malloc( sizeof( struct list_base_t ) );

    //  Was the allocation successful ?
    if ( list_base_p != NULL )
    {
        //  YES:    Initialize the structure
        memset( list_base_p, 0x00, sizeof( struct list_base_t ) );

        //  Initialize the access lock
        pthread_mutex_init ( &list_base_p->access_lock, 0 );

        //  And set the structure identification tag.
        list_base_p->tag = LIST_TAG_VALUE;
    }
    else
    {
        //  NO:     Kill everything
        log_write( MID_FATAL, "list_new",
                   "    Unable to allocate storage for a new list_"
                   "base_t structure.\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_base_p );
}

/****************************************************************************/
/**
 *  Delete the link-list base structure.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully deleted
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_kill(
    struct  list_base_t         *   list_base_p
    )
{
    int                             list_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_rc = false;

    /************************************************************************
     *  Delete the link-list base structure.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Is the link-list empty ?
        if (    ( list_base_p->first_p == NULL )
             && ( list_base_p->last_p  == NULL ) )
        {
            //  YES:    Good, delete the base structure.
            memset( list_base_p, 0x00, sizeof( struct list_base_t ) );

            free( list_base_p );

            //  Change the return code.
            list_rc = true;
        }
        else
        {
            //  NO:     Warn the user of the error.
            log_write( MID_WARNING, "list_kill",
                       "WARNING: An attempt is being made to delete "
                       "link-list base '%p' that is not empty\n",
                       list_base_p );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
/**
 *  Get the first bucket pointer from the link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return payload_p           Pointer to the first payload bucket on the
 *                              link-list.  When the link-list is empty, NULL
 *                              is returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_get_first(
    struct  list_base_t         *   list_base_p
    )
{
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the first bucket pointer from the link-list.
     ************************************************************************/

    payload_p = LIST__get_first( list_base_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!
    return( payload_p );
}

/****************************************************************************/
/**
 *  Get the next bucket pointer from the link-list relative to payload_p.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to a payload bucket.
 *
 *  @return list_bucket_p       Pointer to the next payload bucket on the
 *                              link-list.  When payload_p is the last bucket
 *                              in the link-list, NULL is returned.  When
 *                              payload_p is not in the link-list, a pointer
 *                              to the first bucket on the link-list is
 *                              returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_get_next(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    void                        *   found_payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the next bucket pointer from the link-list relative to payload_p.
     ************************************************************************/

    found_payload_p = LIST__get_next( list_base_p, payload_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!
    return( found_payload_p );
}

/****************************************************************************/
/**
 *  Get the previous bucket pointer from the link-list relative to payload_p.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to a payload bucket.
 *
 *  @return list_bucket_p       Pointer to the next payload bucket on the
 *                              link-list.  When payload_p is the first bucket
 *                              in the link-list, NULL is returned.  When
 *                              payload_p is not in the link-list, a pointer
 *                              to the last bucket on the link-list is
 *                              returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_get_prev(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    void                        *   found_payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the previous bucket pointer from the link-list relative to
     *  payload_p.
     ************************************************************************/

    found_payload_p = LIST__get_prev( list_base_p, payload_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!
    return( found_payload_p );
}

/****************************************************************************/
/**
 *  Get the last bucket pointer from the link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return payload_p           Pointer to the last payload bucket on the
 *                              link-list.  When the link-list is empty, NULL
 *                              is returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_get_last(
    struct  list_base_t         *   list_base_p
    )
{
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the last bucket pointer from the link-list.
     ************************************************************************/

    payload_p = LIST__get_last( list_base_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!

    return( payload_p );
}

/****************************************************************************/
/**
 *  Add a new payload to the beginning of a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to the payload that will be added
 *                              to the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_put_first(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    int                             list_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the last bucket pointer from the link-list.
     ************************************************************************/

    list_rc = LIST__put_first( list_base_p, payload_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!

    return( list_rc );
}

/****************************************************************************/
/**
 *  Add a new payload to the end of a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to the payload that will be added
 *                              to the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_put_last(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    int                             list_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    /************************************************************************
     *  Get the last bucket pointer from the link-list.
     ************************************************************************/

    list_rc = LIST__put_last( list_base_p, payload_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!

    return( list_rc );
}

/****************************************************************************/
/**
 *  Delete payload bucket from a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to the payload that will be added
 *                              to the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_delete(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    int                             list_rc;
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    //  Assume fail and change the return code upon success.
    list_rc = false;

    /************************************************************************
     *  Delete payload bucket from a link-list
     ************************************************************************/

#if 0
    //  Delete it.
    list_rc = LIST__delete( list_base_p, payload_p );
#else
    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Search the link-list for payload.
        for ( list_bucket_p = list_base_p->first_p;
              list_bucket_p != NULL;
              list_bucket_p = list_bucket_p->next_p )
        {

            //  Is this the payload we are looking for ?
            if ( list_bucket_p->payload_p == payload_p )
            {
                //  YES:    Exit the search loop.
                break;
            }

        }

        //  Was 'payload_p' located ?
        if ( list_bucket_p != NULL )
        {
            //  YES:    Delete it.
            list_rc = LIST__delete( list_base_p, list_bucket_p );

        }
        else
        {
            //  NO:     Warn the user of the error.
            log_write( MID_WARNING, "LIST__delete",
                       "WARNING: An attempt is being made to delete "
                       "payload '%p' base '%p' but payload '%p' does "
                       "not exist\n",
                       payload_p, list_base_p, payload_p );
        }
    }
#endif

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
/**
 *  Query the number of messages on the queue.
 *
 *  @param  list_base_p        Pointer to the base of the link list.
 *
 *  @return list_count         The number of messages on the queue.
 *
 *  @note
 *
 ****************************************************************************/

int
list_query_count(
    struct  list_base_t         *   list_base_p
    )
{
    int                             list_count;
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Prevent thread collisions.
    pthread_mutex_lock( &list_base_p->access_lock );

    //  Set the number of messages we have located.
    list_count = 0;

    /************************************************************************
     *  Follow the list from start to finish.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Search the link-list
        for ( list_bucket_p = list_base_p->first_p;
              list_bucket_p != NULL;
              list_bucket_p = list_bucket_p->next_p )
        {
            //  Increment the number of messages found.
            list_count += 1;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Allow access from other threads.
    pthread_mutex_unlock( &list_base_p->access_lock );

    //  DONE!
    return( list_count );
}

/****************************************************************************/
/**
 *  Place a user lock on the table.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return access_key          Verification of the owner of the lock.
 *
 *  @note
 *
 ****************************************************************************/

int
list_user_lock(
    struct  list_base_t         *   list_base_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Follow the list from start to finish.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Lock access to the table.
        pthread_mutex_lock( &list_base_p->access_lock );

        //  Save the access key in the table.
        list_base_p->access_key = token_get( );

        //  Save the bucket pointer as the fast key.
        LIST__get_first( list_base_p );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_base_p->access_key );
}

/****************************************************************************/
/**
 *  Release a user lock on the table.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  access_key          Verification of the owner of the lock.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
list_user_unlock(
    struct  list_base_t         *   list_base_p,
    int                             access_key
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Follow the list from start to finish.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if (    ( list_base_p->access_key !=          0 )
             && ( list_base_p->access_key == access_key ) )
        {
            //  YES:    Release the token
            token_free( list_base_p->access_key );

            //  Clear the table locked lock.
            list_base_p->access_key = 0;

            //  UnLock the table.
            pthread_mutex_unlock( &list_base_p->access_lock );

        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_user_unlock",
                       "WARNING: Called with an invalid access key.\n" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Get the first bucket pointer from the link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  access_key          Verification of the owner of the lock.
 *
 *  @return payload_p           Pointer to the first payload bucket on the
 *                              link-list.  When the link-list is empty, NULL
 *                              is returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_fget_first(
    struct  list_base_t         *   list_base_p,
    int                             access_key
    )
{
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Reset the payload pointer
    payload_p = NULL;

    /************************************************************************
     *  Get the first bucket pointer from the table.
     ************************************************************************/

    //  Are we starting with a valid base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  Get the first bucket pointer from the link-list.
               payload_p = LIST__get_first( list_base_p );
        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_fget_first",
                       "WARNING: Called without locking the table.\n" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( payload_p );
}

/****************************************************************************/
/**
 *  Get the next bucket pointer from the link-list relative to payload_p.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  access_key          Verification of the owner of the lock.
 *  @param  payload_p           Pointer to a payload bucket.
 *
 *  @return list_bucket_p       Pointer to the next payload bucket on the
 *                              link-list.  When payload_p is the last bucket
 *                              in the link-list, NULL is returned.  When
 *                              payload_p is not in the link-list, a pointer
 *                              to the first bucket on the link-list is
 *                              returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_fget_next(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    )
{
    void                        *   found_payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default bucket pointer.
    found_payload_p = NULL;

    /************************************************************************
     *  Get the next bucket pointer from the table relative to payload_p.
     ************************************************************************/

    //  Are we starting with a valid base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  YES:    Have we gotten anything from the list yet ?
            if ( list_base_p->f_key_p == NULL )
            {
                //  NO:     Use the first bucket
                list_base_p->f_key_p = list_base_p->first_p;
            }
            else
            {
                //  YES:    Get the next bucket in the link-list.
                list_base_p->f_key_p = list_base_p->f_key_p->next_p;
            }

            //  Was there something there ?
            if ( list_base_p->f_key_p != NULL )
            {
                //  YES:    Set the payload pointer.
                found_payload_p = list_base_p->f_key_p->payload_p;
            }
        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_fget_next",
                       "WARNING: Called without locking the table.\n" );
        }
    }

    /************************************************************************
     *  Get the next bucket pointer from the link-list relative to payload_p.
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( found_payload_p );
}

/****************************************************************************/
/**
 *  Get the previous bucket pointer from the link-list relative to payload_p.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  access_key          Verification of the owner of the lock.
 *  @param  payload_p           Pointer to a payload bucket.
 *
 *  @return list_bucket_p       Pointer to the next payload bucket on the
 *                              link-list.  When payload_p is the first bucket
 *                              in the link-list, NULL is returned.  When
 *                              payload_p is not in the link-list, a pointer
 *                              to the last bucket on the link-list is
 *                              returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_fget_prev(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    )
{
    void                        *   found_payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default bucket pointer.
    found_payload_p = NULL;

    /************************************************************************
     *  Get the previous bucket pointer from the table relative to payload_p.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  YES:    Have we gotten anything from the list yet ?
            if ( list_base_p->f_key_p == NULL )
            {
                //  NO:     Use the last bucket
                list_base_p->f_key_p = list_base_p->last_p;
            }
            else
            {
                //  YES:    Get the next bucket in the link-list.
                list_base_p->f_key_p = list_base_p->f_key_p->prev_p;
            }

            //  Was there something there ?
            if ( list_base_p->f_key_p != NULL )
            {
                //  YES:    Set the payload pointer.
                found_payload_p = list_base_p->f_key_p->payload_p;
            }
        }
        else
        {
                //  NO:     Write a warning message to the log.
                log_write( MID_WARNING, "list_fget_prev",
                           "WARNING: Called without locking the table.\n" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( found_payload_p );
}

/****************************************************************************/
/**
 *  Get the last bucket pointer from the link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  access_key          Verification of the owner of the lock.
 *
 *  @return payload_p           Pointer to the last payload bucket on the
 *                              link-list.  When the link-list is empty, NULL
 *                              is returned.
 *
 *  @note
 *
 ****************************************************************************/

void    *
list_fget_last(
    struct  list_base_t        *    list_base_p,
    int                             access_key
    )
{
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Get the last bucket pointer from the link-list relative to payload_p.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  Get the last bucket pointer from the link-list.
            payload_p = LIST__get_last( list_base_p );
        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_fget_last",
                       "WARNING: Called without locking the table.\n" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!

    return( payload_p );
}

/****************************************************************************/
/**
 *  Add a new payload to the end of a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to a payload bucket.
 *  @param  access_key          Verification of the owner of the lock.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_fput_last(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    )
{
    int                             list_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Get the last bucket pointer from the link-list relative to payload_p.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  Get the last bucket pointer from the link-list.
            list_rc = LIST__put_last( list_base_p, payload_p );
        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_fput_last",
                       "WARNING: Called without locking the table.\n" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
/**
 *  Delete payload bucket from a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *  @param  payload_p           Pointer to the payload that will be added
 *  @param  access_key          Verification of the owner of the lock.
 *                              to the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_fdelete(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    )
{
    /**
     *  Function Return Code                                                */
    int                             list_rc;
    /**
     *  Fast search pointer                                                 */
    struct  list_bucket_t       *   f_key_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    log_write( MID_DEBUG_0, "list_fdelete",
               "ENTER:   f_key_p: %p\n", list_base_p->f_key_p );

    /************************************************************************
     *  Delete payload bucket from a link-list
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Did the caller use the correct access key ?
        if ( list_base_p->access_key == access_key )
        {
            //  YES:    Is this the first bucket on the list ?
            if ( list_base_p->f_key_p->prev_p == NULL )
            {
                //  YES:    Reset the fast key pointer.
                f_key_p = NULL;
            }
            else
            {
                //  NO:     Then make the previous bucket the current bucket
                f_key_p = list_base_p->f_key_p->prev_p;
            }

            //  Delete the current bucket.
#if 0       //  @ToDo   20171024    Decide how to do this
            list_rc = LIST__delete( list_base_p, payload_p );
#else
            list_rc = LIST__delete( list_base_p,
                                    list_base_p->f_key_p );
#endif

            //  Save the old previous pointer as the current pointer.
            list_base_p->f_key_p = f_key_p;
        }
        else
        {
            //  NO:     Write a warning message to the log.
            log_write( MID_WARNING, "list_fdelete",
                       "WARNING: Called without locking the table.\n" );
        }
    }


    log_write( MID_DEBUG_0, "list_fdelete",
               "EXIT:    f_key_p: %p\n", list_base_p->f_key_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
/**
 *  Add a new payload to the end of a link-list.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
list_debug_dump_list(
    struct  list_base_t         *   list_base_p
    )
{
    int                             list_rc;
    int                             ndx;

    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Just assume that everything is going to work.
    list_rc = true;

    //  Set the starting index level.
    ndx = 0;

    /************************************************************************
     *  Get the last bucket pointer from the link-list relative to payload_p.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Write the table header
        log_write( MID_DEBUG_0, "list_debug_dump_list",
                   "NDX Bucket:    Next:      Prev:      Payload:\n" );

        //  Go through the entire list.
        for ( list_bucket_p = list_base_p->first_p;
              list_bucket_p != NULL;
              list_bucket_p = list_bucket_p->next_p )
        {
            //  Show the data for this bucket.
            log_write( MID_DEBUG_0, "-----",
                       "%03d %9p: %9p  %9p  ( %9p )\n",
                       ndx ++, list_bucket_p,
                       list_bucket_p->next_p,
                       list_bucket_p->prev_p,
                       list_bucket_p->payload_p);
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
