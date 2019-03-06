/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains private functions that makeup the internal
 *  library components of the 'mem' library.
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
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "mem_lib.h"            //  API for all MEM__*              PRIVATE
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
 *  Lookup and return the size of a memory buffer previously allocated using
 *  list_malloc( size );
 *
 *  @param  address             Pointer to the previously allocated memory.
 *
 *  @return size                The size (in bytes) of the addressed buffer.
 *
 *  @note
 *
 ****************************************************************************/

struct  malloc_data_t   *
MEM__info_get(
    void                        *   address
    )
{
    /**
     *  @param  malloc_data_k   List Lock Key                               */
    int                             malloc_data_k;
    /**
     *  @param  malloc_data_p   Pointer to the information structure        */
    struct  malloc_data_t       *   malloc_data_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Lock the list for fast(er) access
    malloc_data_k = list_user_lock( malloc_info_p );

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Scan the list for the search address
    for( malloc_data_p = list_fget_first( malloc_info_p, malloc_data_k );
         malloc_data_p != NULL;
         malloc_data_p = list_fget_next( malloc_info_p, malloc_data_p, malloc_data_k ) )
    {
        //  Do the addresses match ?
        if( malloc_data_p->address == address )
        {
            //  YES:    This is it, stop looking
            break;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  UnLock the list
    list_user_unlock( malloc_info_p, malloc_data_k );

    //  DONE!
    return( malloc_data_p );
}

/****************************************************************************/
/**
 *  Lookup and return the size of a memory buffer previously allocated using
 *  list_malloc( size );
 *
 *  @param  address             Pointer to the previously allocated memory.
 *
 *  @return size                The size (in bytes) of the addressed buffer.
 *
 *  @note
 *
 ****************************************************************************/

void
MEM__info_remove(
    void                        *   address
    )
{
    /**
     *  @param  malloc_data_k   List Lock Key                               */
    int                             malloc_data_k;
    /**
     *  @param  malloc_data_p   Pointer to the information structure        */
    struct  malloc_data_t       *   malloc_data_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Lock the list for fast(er) access
    malloc_data_k = list_user_lock( malloc_info_p );

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Scan the list for the search address
    for( malloc_data_p = list_fget_first( malloc_info_p, malloc_data_k );
         malloc_data_p != NULL;
         malloc_data_p = list_fget_next( malloc_info_p, malloc_data_p, malloc_data_k ) )
    {
        //  Do the addresses match ?
        if( malloc_data_p->address == address )
        {
            //  Remove it from the information list
            list_fdelete( malloc_info_p, malloc_data_p, malloc_data_k );

            //  Release it's storage
            free( malloc_data_p );

            //  This is it, stop looking
            break;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  UnLock the list
    list_user_unlock( malloc_info_p, malloc_data_k );

    //  DONE!
}

/****************************************************************************/
