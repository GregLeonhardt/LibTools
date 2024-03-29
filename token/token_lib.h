/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

#ifndef TOKEN_LIB_H
#define TOKEN_LIB_H

/******************************** JAVADOC ***********************************/
/**
 *  This file contains definitions (etc.) that apply to internal library
 *  components of the 'token' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#ifdef ALLOC_TOKEN
   #define TOKEN_EXT
#else
   #define TOKEN_EXT        extern
#endif

/****************************************************************************
 * System APIs
 ****************************************************************************/

                                //*******************************************
#include <time.h>               //  POSIX time
#include <pthread.h>            //  POSIX threads
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
                                //*******************************************

/****************************************************************************
 * Library Private Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
/**
 *  @param  TOKEN_MIN           First token number to be used               */
#define TOKEN_MIN               (    1 )
/**
 *  @param  TOKEN_MAX           Total number of token IDs available         */
#define TOKEN_MAX               (  256 )
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Private Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Private Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
/**
 *  @param  token_t             Token table structure definition            */
struct  token_t
{
    int                             state;
    time_t                          allocation_time;
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Private Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
/**
 *  @param  token_last      The last used token ID                          */
TOKEN_EXT
int                             token_last;
//---------------------------------------------------------------------------
/**
 *  @param  token_lock      Manage single threaded access                   */
TOKEN_EXT
pthread_mutex_t                 token_lock;
//---------------------------------------------------------------------------
/**
 *  @param  token_tbl       Structure holding the token allocation table    */
TOKEN_EXT
struct  token_t                 token_tbl[ TOKEN_MAX ];
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Private Prototypes
 ****************************************************************************/

//----------------------------------------------------------------------------
int
TOKEN__get(
    void
    );
//----------------------------------------------------------------------------
void
TOKEN__free(
    int                             token_id
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    TOKEN_LIB_H
