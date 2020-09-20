/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  The 'log' API is a set of function calls that provide logging, both
 *  on the terminal and in a log file.
 *
 *  @note
 *      LOG_DIR_NAME        ~/.LibTools     Set in libtools_api.h
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
#include <pthread.h>            //  mutex management
#include <sys/file.h>           //  apply or remove an advisory lock on
                                //  an open file
#include <stdlib.h>             //  ANSI standard library.
#include <string.h>             //  Functions for managing strings
#include <unistd.h>             //  Access to the POSIX operating system API
#include <sys/time.h>           //  gettimeofday()
#include <sys/stat.h>           //  Get file status
#include <stdarg.h>             //  va_list
#include <errno.h>              //  errno
#include <fcntl.h>              //
#include <stdarg.h>             //  va_list
#include <dirent.h>             //  Facilitate directory traversing
                                //*******************************************
/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "log_lib.h"            //  API for all LOG__*              PRIVATE
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
#define LOG_EVERYTHING  (  MID_FATAL | MID_WARNING | MID_INFO               \
                         | MID_DEBUG_3 | MID_DEBUG_2 | MID_DEBUG_1 | MID_DEBUG_0 )
#define LOG_MEM_LEAK    (  MID_FATAL | MID_WARNING | MID_INFO               \
                         | MID_DEBUG_2 | MID_DEBUG_1 | MID_DEBUG_0 )
//  The following two are meant to be the default log masks
#define LOG_DISPLAY     (  MID_FATAL | MID_WARNING | MID_INFO )
#define LOG_PRINT       (  MID_FATAL | MID_WARNING | MID_INFO | MID_LOGONLY )
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
    char                            full_log_file_name[ FILE_NAME_L ];
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
 *  Open and lock the log file.  If the log file is currently locked,
 *  wait for it to be unlocked before returning to the caller.
 *
 *  @param  message_id          Type of message to be logged. (LOG, ECAM, UUI)
 *
 *  @return log_file_p          Pointer to a log_file control structure.
 *
 ****************************************************************************/

struct log_file_t *
LOG__file_open(
    int                             message_id
    )
{
    /**
     *  @param  log_file_p      Pointer to a file control structure         */
    struct  log_file_t          *   log_file_p;
    /**
     *  @param  log_file_name_p Log file path and name string               */
    char                        *   log_file_name_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the name of the file logs will be written to.
    log_file_name_p = full_log_file_name;

    /************************************************************************
     *  Allocate and clean a new log file control structure.
     ************************************************************************/

    //  Allocate a new log file control structure.
    log_file_p = (struct log_file_t*)malloc( sizeof( struct log_file_t ) );

    //  Verify the storage allocation was successful
    if ( log_file_p == NULL )
    {
        //  NO:     Write an error message
        printf( "log_file_open: Unable to allocate storage for a new "
                "log file control structure.\n" );
        fflush( stdout );

        //  Kill the program.
        exit( -1 );
    }
    else
    {
        //  Initialize the new storage.
        memset( log_file_p, 0x00, sizeof( struct log_file_t ) );
    }

    /************************************************************************
     *  Open the log file for append
     ************************************************************************/

    //  Open the log file.

    log_file_p->log_file_fp = fopen( log_file_name_p, "a" );

    //  Was the file was opened successfully ?
    if ( log_file_p->log_file_fp == NULL )
    {
        //  NO:     Write an error message
        printf( "log_file_open: Unable to open log file '%s'\n",
                log_file_name_p );
        fflush( stdout );

        //  Something bad happened preventing the log file from
        //  successfully opening.
        exit( -1 );
    }
    else
    {
        //  YES:    Get the file descriptor ID.
        log_file_p->fd = fileno( log_file_p->log_file_fp );
    }

    /************************************************************************
     *  Lock the file
     ************************************************************************/

    //  Initialize the file lock structure.
    log_file_p->lock.l_type = F_WRLCK;
    log_file_p->lock.l_start = 0;
    log_file_p->lock.l_whence = SEEK_SET;
    log_file_p->lock.l_len = 0;
    log_file_p->lock.l_pid = 0;

    //  If the file is currently locked by another process, wait for it to
    //  be unlocked then lock it for this process thread.
    if ( fcntl( log_file_p->fd, F_SETLKW, &(log_file_p->lock) ) == -1 )
    {
        //  NO:     Write an error message
        printf( "log_file_open: fcntl failed when attempting to lock "
                "log file '%s'\n", log_file_name_p );
        fflush( stdout );

        exit( -1 );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( log_file_p );
}

/****************************************************************************/
/**
 *  Open and lock the log file.  If the log file is currently locked,
 *  wait for it to be unlocked before returning to the caller.
 *
 *  @param  void
 *
 *  @return log_file_fp         Log file, file pointer.
 *
 ****************************************************************************/

void
LOG__file_close(
    struct  log_file_t          *   log_file_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Unlock and close the log file
     ************************************************************************/

    log_file_p->lock.l_type = F_UNLCK;

    //  Unlock the log file.
    if ( fcntl( log_file_p->fd, F_SETLK, &(log_file_p->lock) ) == -1)
    {
        //  There was an error unlocking the log file.  Write an error
        //  message and exit.
        printf( "log_file_close: fcntl failed when attempting to unlock "
                "log file.\n" );
        fflush( stdout );

        exit( -1 );
    }

    //  Close the log file.
    fclose( log_file_p->log_file_fp );

    //  Release the log control structure.
    free( log_file_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/


/****************************************************************************
 *  Source Code
 ****************************************************************************/


/****************************************************************************/
/**
 *  Initialization for simlog.
 *
 *  @param  void
 *
 *  @return void
 *
 ****************************************************************************/

void
log_init(
    char                        *   log_file_name
    )
{
    /**
     *  @param  dir             Directory pointer                           */
    DIR                         *   dir;
    /**
     *  @param  log_dir_path    Fully qualified path to log directory       */
    char                            log_dir_path[ FILE_NAME_L ];
    /**
     *  @param  tmp_p           Pointer to a temporary buffer               */
    char                        *   tmp_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Get the home directory path
    tmp_p = getenv( "HOME" );

    //  Did we get it ?
    if ( tmp_p != NULL )
    {
        //  YES:    Build the full path
        snprintf( log_dir_path, sizeof( log_dir_path ),
                  "%s/%s", tmp_p, LOG_DIR_NAME );
    }
    else
    {
        //  NO:     This is bad.
        log_write( MID_FATAL, "log_init",
                   "Environment variable 'HOME' is not set.\n" );
    }

    /************************************************************************
     *  Format the date & time string
     ************************************************************************/

    //  Initialize the log thread lock
    pthread_mutex_init( &thread_lock, 0 );

    //  Look to see if the .LibTools directory already exists
    dir = opendir( log_dir_path );

    //  Does it already exist ?
    if ( dir != NULL )
    {
        //  YES:    Good to know, close it
        closedir( dir );
    }
    else
    {
        //  NO:     Then create it.
        mkdir( log_dir_path, 0775);
    }

    //  Build the fully qualified log directory & file name
    snprintf( full_log_file_name, sizeof( full_log_file_name ),
              "%s/%s/%s", tmp_p, LOG_DIR_NAME, log_file_name );

    //  Set the default display and print filters
    log_display_mask = ( LOG_DISPLAY );
    log_print_mask =   ( LOG_PRINT );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Write a message to the log file.
 *
 *  @param  message_p           Pointer to a message to display.
 *
 *  @return void
 *
 ****************************************************************************/

void
log_write(
    uint16_t                        message_id,
    const char                  *   function_name,
    const char                  *   message_p, ...
    )
{
    /**
     *  A text buffer to hold the current time of day.                  */
    char                            time_string[ 35 ];
    /**
     *  Buffers for various forms of time of day.                       */
    struct  tm                  *   current_time;
    struct  timeval                 time_of_day;
    time_t                          clock;
    /**
     *  A flag controlling if a message will be displayed or not.        */
    int                             mdm;
    /**
     *  A flag controlling if a message will be written or not.          */
    int                             pdm;
    /**
     *  List of parameters for formatting the output line.              */
    va_list                         message_parms;
    /**
     *  A buffer to hold the formatted output.                          */
    char                            log_buffer[ 1024 ];
    /**
     *  Pointer to the log file structure.                              */
    struct  log_file_t          *   log_file_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    // Prevent all other threads from simultaneously writing to the log.
    pthread_mutex_lock( &thread_lock );

    //  Set the default output flags
    mdm = pdm = false;

    /************************************************************************
     *  Format the date & time string
     ************************************************************************/

    //  Get the current time of day
    gettimeofday( &time_of_day, NULL );
    clock = time( NULL );
    current_time = localtime( &clock );

    //  Format a date / time string for the message output.
    snprintf( time_string, sizeof( time_string ),
              "%04d/%02d/%02d-%02d:%02d:%02d.%06d",
              current_time->tm_year + 1900,
              current_time->tm_mon + 1,
              current_time->tm_mday,
              current_time->tm_hour,
              current_time->tm_min,
              current_time->tm_sec,
              (int)time_of_day.tv_usec );

    /************************************************************************
     *  Decide if the message should be displayed.
     ************************************************************************/

    //  By default the message is not displayed or written to the log file.
    mdm = false;
    pdm = false;

    //  Should the message be displayed on the screen ?
    if (    ( ( message_id & log_display_mask ) !=         0 )
         || ( ( message_id &        MID_FATAL ) == MID_FATAL ) )
    {
        //  YES:    Set the display flag
        mdm = true;
    }

    //  Should the message be written to the log file "
    if ( ( message_id & log_print_mask ) != 0 )
    {
        //  YES:    Set the display flag
        pdm = true;
    }

    /************************************************************************
     *  Format the user message
     ************************************************************************/

    //  Build the parameter list
    va_start( message_parms, message_p );

    //  Format the message string
    vsnprintf( log_buffer, sizeof( log_buffer ), message_p, message_parms );

    //  We are done formatting the message
    va_end( message_parms );

    /************************************************************************
     *  Display the message
     ************************************************************************/

    //  Should the message be written to the monitor ?
    if ( mdm == true )
    {
        //  YES:    Display the message to stdout
        printf( "%s - %04X - %-20s %s",
                time_string, message_id, function_name, log_buffer );
        fflush( stdout );
    }

    /************************************************************************
     *  Print the message
     ************************************************************************/

    //  Should the message be written to the monitor ?
    if ( pdm == true )
    {
        //  Open the log file.
        log_file_p = LOG__file_open( message_id );

        //  The log file is open and locked.  Time to write the message.
        fprintf( log_file_p->log_file_fp, "%s - %04X - %-20s %s",
                 time_string, message_id, function_name, log_buffer );

        //  Unlock the file to allow someone else to write to it.
        LOG__file_close( log_file_p );
    }

    /************************************************************************
     *  Application termination ?
     ************************************************************************/

    //  Are we supposed to be terminating the application ?
    if ( ( message_id & MID_FATAL ) == MID_FATAL )
    {
        //  YES:    Shut it down.
        exit( -1 );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    // Release the thread lock on the log
    pthread_mutex_unlock( &thread_lock );

    //  DONE!
}

/****************************************************************************/
