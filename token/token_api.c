/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  The 'file' library provide the ability to open close and delete files
 *  on the systems file system.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_TOKEN             ( "ALLOCATE STORAGE FOR TOKEN" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <ctype.h>              //  islower() toupper()
#include <stdlib.h>             //  ANSI standard library.
#include <time.h>               //  Date and time standard library.
#include <string.h>             //  String copying, searching, etc.
#include <pthread.h>            //  POSIX threads
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
 * Private Enumerations
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Definitions
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Structures
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Storage Allocation
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Initializes the token management utilities.
 *
 *  @param  void
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
token_init(
    void
    )
{
    /**
     *  @param  ndx             Token table index                           */
    int                             ndx;

    //  Initialize the token lock.
    pthread_mutex_init( &token_lock,  0 );

    //  Initialize all tokens as currently available
    for ( ndx = 0;
          ndx < TOKEN_MAX;
          ndx ++ )
    {
        //  Set the token state to available.
        token_tbl[ ndx ].state = false;

        //  Zero out the allocation time.
        token_tbl[ ndx ].allocation_time = 0;
    }

    //  Initialize the last used token ID to the valid first ID.
    token_last = 0;
}

/****************************************************************************/
/**
 *  Allocate the next unused token ID.
 *
 *  @param  mcb_p               Pointer to a Module Control Block (MCB).
 *  @param  imc_header_p        Pointer to InterModule Communications header.
 *
 *  @return token               The allocated token.
 *
 *  @note
 *
 ****************************************************************************/

int
token_get(
    void
    )
{
    int                             token;

    token = TOKEN__get( );

    log_write( MID_DEBUG_0, "token_get",
               "Token allocation = %04d\n", token );

    //  DONE!
    return( token );
}

/****************************************************************************/
/**
 *  Deallocate a token ID.
 *
 *  @param  mcb_p               Pointer to a Module Control Block (MCB).
 *  @param  imc_header_p        Pointer to InterModule Communications header.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
token_free(
    int                             token_id
    )
{
    //  Release the token.
    TOKEN__free( token_id );

    log_write( MID_DEBUG_0, "token_free",
               "Token %04d is released;\n", token_id );
}

/****************************************************************************/
