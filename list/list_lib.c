/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains private tools to manage a link list used internally
 *  by the 'linklist' library.
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
#include <stdlib.h>             //  ANSI standard library.
#include <string.h>             //  Functions for managing strings
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
 * Enumerations local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Definitions local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

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
 *  Verification that a link-list base pointer is actually pointing to
 *  a link-list base.
 *
 *  @param  list_base_p         Pointer to the base of the link list.
 *
 *  @return list_rc             TRUE when list_base_p is pointing to a
 *                              link-list, else FALSE.
 *
 *  @note
 *
 ****************************************************************************/

int
LIST__verify(
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
     *  Add a new payload to the begining of a link-list.
     ************************************************************************/

    //  Is the link-list pase pointer valid ?
    if (    ( list_base_p      !=           NULL )
         && ( list_base_p->tag == LIST_TAG_VALUE ) )
    {
        //  YES:    Change the return code to TRUE
        list_rc = true;
    }
    else
    {
        //  NO:     Something is badly broken.
        log_write( MID_FATAL, "LL_verify",
                   "    The list_base_p pointer is not valid.\n" );
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
LIST__get_first(
    struct  list_base_t         *   list_base_p
    )
{
    struct  list_bucket_t       *   list_bucket_p;
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_bucket_p  = NULL;
    payload_p      = NULL;

    /************************************************************************
     *  Get the first bucket pointer from the link-list.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Get the first bucket in the link-list.
        list_bucket_p = list_base_p->first_p;

        //  Was there something there ?
        if ( list_bucket_p != NULL )
        {
            //  YES:    Set the payload pointer.
            payload_p = list_bucket_p->payload_p;
        }
    }

    /************************************************************************
     *  Save the bucket pointer for fast mode.
     ************************************************************************/

    //  Save the bucket pointer as the fast key.
    list_base_p->f_key_p = list_bucket_p;

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
LIST__get_next(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Start the search from the first bucket.
    list_bucket_p = list_base_p->first_p;

    /************************************************************************
     *  Scan the list for a match to 'payload_p'
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Search the link-list for payload.
        for ( ;
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
        if ( list_bucket_p == NULL )
        {
            //  NO:     Return the first bucket in the link-list.

            //  NOTE:   This module is designed to be used by multiple
            //          threads.  This 'reset' logic is present for the
            //          case where a thread is searching the list for
            //          something and another thread has deleted the bucket
            //          used in the search.  By resetting the search to the
            //          begining the search there will be some duplication
            //          but it will be able to reach the end.
            list_bucket_p = list_base_p->first_p;
        }
        else
        {
            //  YES:    Get the next bucket.
            list_bucket_p = list_bucket_p->next_p;
        }
    }

    /************************************************************************
     *  Set the return payload pointer
     ************************************************************************/

    //  Dis we reach the end of the list ?
    if ( list_bucket_p == NULL )
    {
        //  YES:    Set the return payload pointer to NULL
        payload_p = NULL;
    }
    else
    {
        //  NO:     set the found payload pointer as the return pointer.
        payload_p = list_bucket_p->payload_p;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( payload_p );
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
LIST__get_prev(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Start the search from the last bucket.
    list_bucket_p = list_base_p->last_p;

    /************************************************************************
     *  Get the previous bucket pointer from the link-list relative
     *  to payload_p.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Search the link-list for payload.
        for ( ;
              list_bucket_p != NULL;
              list_bucket_p = list_bucket_p->prev_p )
        {

            //  Is this the payload we are looking for ?
            if ( list_bucket_p->payload_p == payload_p )
            {
                //  YES:    Exit the search loop.
                break;
            }

        }

        //  Was 'payload_p' located ?
        if ( list_bucket_p == NULL )
        {
            //  NO:     Return the last bucket in the link-list.

            //  NOTE:   This module is designed to be used by multiple
            //          threads.  This 'reset' logic is present for the
            //          case where a thread is searching the list for
            //          something and another thread has deleted the bucket
            //          used in the search.  By resetting the search to the
            //          end the search there will be some duplication
            //          but it will be able to reach the beginning.
            list_bucket_p = list_base_p->last_p;
        }
        else
        {
            //  YES:    Get the next bucket.
            list_bucket_p = list_bucket_p->prev_p;
        }
    }

    /************************************************************************
     *  Set the return payload pointer
     ************************************************************************/

    //  Dis we reach the start of the list without finding the bucket ?
    if ( list_bucket_p == NULL )
    {
        //  YES:    Set the return payload pointer to NULL
        payload_p = NULL;
    }
    else
    {
        //  NO:     set the found payload pointer as the return pointer.
        payload_p = list_bucket_p->payload_p;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_bucket_p->payload_p );
}

/****************************************************************************/
/**
 *  Get the last bucket pointer from the link-list
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
LIST__get_last(
    struct  list_base_t         *   list_base_p
    )
{
    struct  list_bucket_t       *   list_bucket_p;
    void                        *   payload_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_bucket_p  = NULL;
    payload_p      = NULL;

    /************************************************************************
     *  Append the payload to the end of the link list
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Get the last bucket in the link-list.
        list_bucket_p = list_base_p->last_p;

        //  Was there something there ?
        if ( list_bucket_p != NULL )
        {
            //  YES:    Set the payload pointer.
            payload_p = list_bucket_p->payload_p;
        }
    }

    /************************************************************************
     *  Save the bucket pointer for fast mode.
     ************************************************************************/

    //  Save the bucket pointer as the fast key.
    list_base_p->f_key_p = list_bucket_p;

    /************************************************************************
     *  Function Exit
     ************************************************************************/

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
LIST__put_first(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    int                             list_rc;
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_rc = false;

    /************************************************************************
     *  Add a new payload to the begining of a link-list.
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Allocate storage for a new bucket.
        list_bucket_p = (struct list_bucket_t*)malloc( sizeof( struct list_bucket_t ) );

        //  Was the allocation successful ?
        if ( list_bucket_p != NULL )
        {
            //  YES:    Initialize the structure
            memset( list_bucket_p, 0x00, sizeof( struct list_bucket_t ) );

            //  Set the payload pointer
            list_bucket_p->payload_p = payload_p;

            //  Is the link-list currently empty ?
            if ( list_base_p->first_p == NULL )
            {
                //  YES:    Add as the first bucket.
                list_base_p->first_p = list_bucket_p;
                list_base_p->last_p  = list_bucket_p;
            }
            else
            {
                //  NO:     Insert as the first.
                list_bucket_p->next_p        = list_base_p->first_p;
                list_base_p->first_p->prev_p = list_bucket_p;
                list_base_p->first_p         = list_bucket_p;
            }

            //  Change the return code to successful.
            list_rc = true;
        }
        else
        {
            //  NO:     Kill everything
            log_write( MID_FATAL, "LL_put_first",
                       "    Function 'll_put_first() was unable to "
                       "allocate storage for a new list_bucket_t "
                       "structure.\n");
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
LIST__put_last(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    )
{
    int                             list_rc;
    struct  list_bucket_t       *   list_bucket_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_rc = false;

    /************************************************************************
     *  Append the payload to the end of the link list
     ************************************************************************/

    //  Are we starting with a valid link-list base pointer ?
    if ( LIST__verify( list_base_p ) == true )
    {
        //  YES:    Allocate storage for a new bucket.
        list_bucket_p = (struct list_bucket_t*)malloc( sizeof( struct list_bucket_t ) );

        //  Was the allocation successful ?
        if ( list_bucket_p != NULL )
        {
            //  YES:    Initialize the structure
            memset( list_bucket_p, 0x00, sizeof( struct list_bucket_t ) );

            //  Set the payload pointer
            list_bucket_p->payload_p = payload_p;

            //  Is the link-list currently empty ?
            if ( list_base_p->first_p == NULL )
            {
                //  YES:    Add as the first bucket.
                list_base_p->first_p = list_bucket_p;
                list_base_p->last_p  = list_bucket_p;
            }
            else
            {
                //  NO:     Insert as the first.
                list_bucket_p->prev_p       = list_base_p->last_p;
                list_base_p->last_p->next_p = list_bucket_p;
                list_base_p->last_p         = list_bucket_p;
            }

            //  Change the return code to successful.
            list_rc = true;

        }
        else
        {
            //  NO:     Kill everything
            log_write( MID_FATAL, "LL_put_last",
                       "    Function 'll_put_first() was unable to "
                       "allocate storage for a new list_bucket_t "
                       "structure.\n");
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
 *                              to the link list.
 *
 *  @return list_rc             TRUE when the payload is successfully added
 *                              to the link list, else FALSE.
 *
 *  @note
 *      @ToDo: L1 Both list_delete and list_fdelete use this
 *              function.  However list_fdel already has a pointer to the
 *              bucket that needs to be deleted so it is wasting time by
 *              search for it.  Take the search code and move it to
 *              list_delete and only pass the bucket pointer here.
 *
 ****************************************************************************/

int
LIST__delete(
    struct  list_base_t         *   list_base_p,
#if 0
    void                        *   payload_p
#else
    struct  list_bucket_t       *   list_bucket_p
#endif
    )
{
    int                             list_rc;
#if 0
    struct  list_bucket_t       *   list_bucket_p;
#else
#endif

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume fail and change the return code upon success.
    list_rc = false;

    /************************************************************************
     *  Append the payload to the end of the link list
     ************************************************************************/
#if 0
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
            //  YES:

            /****************************************************************
             *  FIRST and LAST
             ****************************************************************/

            if (    ( list_bucket_p == list_base_p->first_p )
                 && ( list_bucket_p == list_base_p->last_p  ) )
            {
                list_base_p->first_p = NULL;
                list_base_p->last_p  = NULL;
            }

            /****************************************************************
             *  FIRST (but not the only)
             ****************************************************************/

            else if ( list_bucket_p == list_base_p->first_p )
            {
                list_base_p->first_p = list_bucket_p->next_p;
                list_base_p->first_p->prev_p = NULL;
            }

            /****************************************************************
             *  LAST (but not the only)
             ****************************************************************/

            else if ( list_bucket_p == list_base_p->last_p  )
            {
                list_base_p->last_p = list_bucket_p->prev_p;
                list_base_p->last_p->next_p = NULL;
            }

            /****************************************************************
             *  MIDDLE
             ****************************************************************/

            else
            {
                list_bucket_p->prev_p->next_p = list_bucket_p->next_p;
                list_bucket_p->next_p->prev_p = list_bucket_p->prev_p;
            }

            /****************************************************************
             *  Release the resources allocated by this bucket.
             ****************************************************************/

            free( list_bucket_p );

            //  Change the return code for success.
            list_rc = true;
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
#else

    /************************************************************************
     *  FIRST and LAST
     ************************************************************************/

    if (    ( list_bucket_p == list_base_p->first_p )
         && ( list_bucket_p == list_base_p->last_p  ) )
    {
        list_base_p->first_p = NULL;
        list_base_p->last_p  = NULL;
    }

    /************************************************************************
     *  FIRST (but not the only)
     ************************************************************************/

    else if ( list_bucket_p == list_base_p->first_p )
    {
        list_base_p->first_p = list_bucket_p->next_p;
        list_base_p->first_p->prev_p = NULL;
    }

    /************************************************************************
     *  LAST (but not the only)
     ************************************************************************/

    else if ( list_bucket_p == list_base_p->last_p  )
    {
        list_base_p->last_p = list_bucket_p->prev_p;
        list_base_p->last_p->next_p = NULL;
    }

    /************************************************************************
     *  MIDDLE
     ************************************************************************/

    else
    {
        list_bucket_p->prev_p->next_p = list_bucket_p->next_p;
        list_bucket_p->next_p->prev_p = list_bucket_p->prev_p;
    }

    /************************************************************************
     *  Release the resources allocated by this bucket.
     ************************************************************************/

    free( list_bucket_p );

    //  Change the return code for success.
    list_rc = true;
#endif

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( list_rc );
}

/****************************************************************************/
