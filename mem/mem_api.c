/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains public function that makeup the external
 *  library components of the 'mem' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_MEM               ( "ALLOCATE STORAGE FOR MEM" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
                                //*******************************************
#include <stdlib.h>             //  ANSI standard library.
#include <string.h>             //  Functions for managing strings
#include <ctype.h>              //  Determine the type contained
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

/****************************************************************************/
/**
 *  The template function is called bla bla bla.
 *
 *  @param  void                No parameters are passed in.
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
mem_init(
    void
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Create a new list
    malloc_info_p = list_new( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/


}

/****************************************************************************/
/**
 *  Allocate and initialize a buffer.
 *
 *  @param  size                The amount of memory (in bytes) requested.
 *
 *  @return memory_p            Pointer to the allocated memory.
 *
 *  @note
 *      It is assumed that the caller of this function will be using the
 *      requested memory.  Thus, if the memory allocation fails the entire
 *      module will be terminated.
 *
 ****************************************************************************/

void *
mem_malloc(
    int                             size
    )
{
    /**
     *  Pointer to the allocated memory                                 */
    char                        *   memory_p;
    /**
     *  @param  malloc_data_p   Pointer to a sizeof structure               */
    struct  malloc_data_t       *   malloc_data_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the allocated memory pointer to NULL
    memory_p = NULL;

    /************************************************************************
     *  Allocate memory as requested.
     ************************************************************************/

    //  Allocate the requested number of bytes.
    memory_p = (char*)malloc( size );

    //  Was the memory allocation successful ?
    if ( memory_p == NULL )
    {
        //  NO:     A very bad situation indeed.
        log_write( MID_FATAL, "mem_malloc",
                   "Unable to allocate memory!\n" );
    }

    //  Now that we have established that memory was actually allocated,
    //  initialize it.
    memset( memory_p, 0x00, size );

    /************************************************************************
     *  Update the malloc information list
     ************************************************************************/

    //  Allocate a new malloc data structure
    malloc_data_p = (struct malloc_data_t*)malloc( sizeof( struct malloc_data_t ) );

    //  Was the memory allocation successful ?
    if ( malloc_data_p == NULL )
    {
        //  NO:     A very bad situation indeed.
        log_write( MID_FATAL, "mem_malloc",
                   "Unable to allocate memory for a new malloc data structure!\n" );
    }

    //  Save the pointer
    malloc_data_p->address = memory_p;

    //  Save the size
    malloc_data_p->size = size;

    //  Append to the malloc information list
    list_put_last( malloc_info_p, malloc_data_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Log the release of some memory
    log_write( MID_DEBUG_0, "mem_malloc",
               "[ %p ] %04X\n", memory_p, size );

    //  DONE!
    return( (void*)memory_p );
}

/****************************************************************************/
/**
 *  Release previously allocated storage.
 *
 *  @param  memory_p            Pointer to allocated memory.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
mem_free(
    void                        *   memory_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Release (free) the memory
     ************************************************************************/

    //  Is there an address to free ?
    if ( memory_p != NULL )
    {
        //  YES:    Log the release of some memory
        log_write( MID_DEBUG_0, "mem_free",
                   "[ %p ]\n", memory_p );

        //  Remove the malloc information from the information list
        MEM__info_remove( memory_p );

        //  Allocate the requested number of bytes.
        free( memory_p );
    }
    else
    {
        log_write( MID_FATAL, "mem_free", "Attempting to free a buffer @ 'NILL'\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
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

int
mem_sizeof(
    void                        *   address
    )
{
    /**
     *  @param  malloc_data_p   Pointer to the information structure        */
    struct  malloc_data_t       *   malloc_data_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Get the 'sizeof' the addressed buffer
    malloc_data_p = MEM__info_get( address );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( malloc_data_p->size );
}

/****************************************************************************/
/**
 *  Dump the list of allocated memory.
 *
 *  @param  void                No information is passed to this function
 *
 *  @return void                No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
mem_dump(
    void
    )
{
    /**
     *  @param  malloc_data_k   List Lock Key                               */
    int                             malloc_data_k;
    /**
     *  @param  malloc_data_p   Pointer to the information structure        */
    struct  malloc_data_t       *   malloc_data_p;
    /** @param  count           Number of buffers allocated                 */
    static int                      count;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Is this the very first time here ?
    if ( count == 0 )
    {
        //  YES:    Save the current stack size
        count = list_query_count( malloc_info_p );
    }

    //  Has there been a change in the memory stack size ?
    else
    if ( list_query_count( malloc_info_p ) > count )
    {
        //  YES:    Then go ahead and dump the stack
        count = list_query_count( malloc_info_p );

        log_write( MID_DEBUG_2, "mem_dump", "There are %d buffers allocated\n",
                   list_query_count( malloc_info_p ) );

        //  Lock the list for fast(er) access
        malloc_data_k = list_user_lock( malloc_info_p );

        //  Scan the list for the search address
        for( malloc_data_p = list_fget_first( malloc_info_p, malloc_data_k );
             malloc_data_p != NULL;
             malloc_data_p = list_fget_next( malloc_info_p, malloc_data_p, malloc_data_k ) )
        {
            char * tmp_p;
            //  Log this allocated buffer
            log_write( MID_DEBUG_2, "mem_dump", "[%p] - %4X\n",
                       malloc_data_p->address, malloc_data_p->size );

            tmp_p = (char*)malloc_data_p->address;

            //  Is this a text buffer ?
            if (    ( malloc_data_p->size > 4 )
                 && ( isprint( tmp_p[ 0 ] ) != 0 )
                 && ( isprint( tmp_p[ 1 ] ) != 0 )
                 && ( isprint( tmp_p[ 2 ] ) != 0 )
                 && ( isprint( tmp_p[ 3 ] ) != 0 ) )
            {
                //  Log the data
                log_write( MID_DEBUG_2, "mem_dump", "\t\t'%s'\n", tmp_p );
            }
        }

        //  UnLock the list
        list_user_unlock( malloc_info_p, malloc_data_k );

        //  Stop
        log_write( MID_FATAL, "mem_dump",
                   "Application is stopped to investigate a memory leak.\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
