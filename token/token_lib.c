/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains private tools to manage a link list used internally
 *  by the 'file' library.
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

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "token_lib.h"          //  API for all TOKEN__*            PRIVATE
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
 *  Allocate the next unused token ID.
 *
 *  @param  void
 *
 *  @return token_rc            TRUE when successful, else FALSE
 *
 *  @note
 *
 ****************************************************************************/

int
TOKEN__get(
    void
    )
{
    /**
     *  @paran  count           Number of used tokens                       */
    int                             count;
    /**
     *  @paran  token_val       Token value                                 */
    int                             token_val;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Lock the token to prevent other threads from accessing it.
    pthread_mutex_lock( &token_lock );

    //  Assume we can't find an unused token
    token_val = 0;

    /************************************************************************
     *  Locate the next available token
     ************************************************************************/

    //  Scan the available list for the next unused token
    for ( count = TOKEN_MIN;
          count < TOKEN_MAX;
          count ++ )
    {
        //  Are we at the end of the table and need to wrap back to the start ?
        if ( ( ++ token_last ) >= TOKEN_MAX )
        {
            //  YES:    Reset the table index to the start
            token_last = TOKEN_MIN;
        }

        //  Is this token in use ?
        if ( token_tbl[ token_last ].state == false )
        {
            //  NO:     Change the token state from Available to In-Use.
            token_tbl[ token_last ].state = true;

            //  Set the allocation time.
            token_tbl[ token_last ].allocation_time = time( 0 );

            //  Set the token value
            token_val = token_last;

            //  We are done here.
            break;
        }
    }

    //  Did we locate an available token ?
    if ( token_val == 0 )
    {
        //  NO:     There are no tokens available.
        //          I guess that TOKEN_MAX needs to be larger.
        log_write( MID_FATAL, "TOKEN__get",
                   "Out of available tokens\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    // Release the token lock allowing other threads access.
    pthread_mutex_unlock( &token_lock );

    //  DONE!
    return( token_val );
}

/****************************************************************************/
/**
 *  Deallocate a token ID.
 *
 *  @param  token_id            The token that is to be released
 *
 *  @return void
 *
 *  @note
 *      REVIEW-DONE:    2014-06-01
 *
 ****************************************************************************/

void
TOKEN__free(
    int                             token_id
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Lock the token to prevent other threads from accessing it.
    pthread_mutex_lock( &token_lock );

    /************************************************************************
     *  Deallocate the token ID
     ************************************************************************/

    //  Is the token currently in use ?
    if ( token_tbl[ token_id ].state == false )
    {
        //  NO:     We can't deallocate a token that isn't in use.
        log_write( MID_WARNING, "TOKEN__free",
                   "Token-ID '%04d' is not currently in use.\n",
                    token_id );
    }

    //  Deallocate the token ID
    token_tbl[ token_id ].state = false;

    //  Zero out the allocation time.
    token_tbl[ token_id ].allocation_time = 0;

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    // Release the token lock allowing other threads access.
    pthread_mutex_unlock( &token_lock );
}

/****************************************************************************/
