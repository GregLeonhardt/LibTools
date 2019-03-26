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

#define ALLOC_FILE              ( "ALLOCATE STORAGE FOR FILE" )

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
#include <ctype.h>              //  Determine the type contained
#include <fcntl.h>              //  Manipulate file descriptor
#include <sys/stat.h>           //  Get file status
#include <sys/time.h>           //  gettimeofday()
#include <sys/types.h>          //  Defines data types used in system source
#include <time.h>               //  Functions for manipulating date and time
#include <langinfo.h>           //  Identify items of langinfo data
#include <dirent.h>             //  Facilitate directory traversing
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  My Tools Library
                                //*******************************************
#include "file_lib.h"           //  API for all FILE__*             PRIVATE
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
#define SYS_CMD_L               ( 1024 )
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
/**
 *  @param  bytes_read_last     Number of bytes read last count             */
float                               bytes_read_last;
/**
 *  @param  bytes_read_last     Total number of bytes read                  */
float                               total_bytes_read;
/**
 *  @param  time_now            Seconds since the Epoch                     */
struct  timeval                     time_now;
/**
 *  @param  time_last           Seconds since the Epoch                     */
struct  timeval                     time_last;
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  The file_open_read function is called once for each file.  It only
 *  opens the file and does NOT read any data from it.
 *
 *  @param  filename            A pointer to a character string containing
 *                              the file name of the input file.
 *
 *  @return file_fp             Upon successful completion the file pointer is
 *                              returned else NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

FILE    *
file_open_read(
    char                        *   file_name
    )
{
    /**
     *  @parm   file_fp         File pointer                                */
    FILE                        *   file_fp;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  File open and verification
     ************************************************************************/

    //  Open the input file for read only
    file_fp = fopen( file_name, "r");

    //  Was the file open successful ?
    if ( file_fp == NULL)
    {
        //  The file open failed.  Change the return code to FAIL
        log_write( MID_FATAL, "file_open_read",
                   "Unable to open file '%s' for read\n",
                   file_name );
    }
    else
    {
        //  Log the event
        log_write( MID_INFO, "file_open_read",
                   "successfully opened file: '%s'\n",
                   file_name );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( file_fp );
}

/****************************************************************************/
/**
 *  The file_open_write function is called once for each file.  It only
 *  opens the file and does NOT write any data to it.
 *
 *  @param  filename            A pointer to a character string containing
 *                              the file name of the input file.
 *
 *  @return file_fp             Upon successful completion the file pointer is
 *                              returned else NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

FILE    *
file_open_write(
    char                        *   file_name
    )
{
    /**
     *  @parm   file_fp         File pointer                                */
    FILE                        *   file_fp;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  File open and verification
     ************************************************************************/

    //  Open the input file for read only
    file_fp = fopen( file_name, "w");

    //  Was the file open successful ?
    if ( file_fp == NULL)
    {
        //  The file open failed.  Change the return code to FAIL
        log_write( MID_FATAL, "file_open_write",
                   "Unable to open file '%s' for write\n",
                   file_name );
    }
    else
    {
        //  Log the event
        log_write( MID_INFO, "file_open_write",
                   "File '%s' successfully opened\n",
                   file_name );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( file_fp );
}

/****************************************************************************/
/**
 *  The file_open_append function is called once for each file.  It only
 *  opens the file and does NOT read or write any data from/to it.
 *
 *  @param  filename            A pointer to a character string containing
 *                              the file name of the input file.
 *
 *  @return file_fp             Upon successful completion the file pointer is
 *                              returned else NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

FILE    *
file_open_append(
    char                        *   file_name
    )
{
    /**
     *  @parm   file_fp         File pointer                                */
    FILE                        *   file_fp;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  File open and verification
     ************************************************************************/

    //  Open the input file for read only
    file_fp = fopen( file_name, "a");

    //  Was the file open successful ?
    if ( file_fp == NULL)
    {
        //  The file open failed.  Change the return code to FAIL
        log_write( MID_FATAL, "file_open_append",
                   "Unable to open file '%s' for append\n",
                   file_name );
    }
    else
    {
        //  Log the event
        log_write( MID_DEBUG_0, "file_open_append",
                   "File '%s' successfully opened\n",
                   file_name );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( file_fp );
}

/****************************************************************************/
/**
 *  The file_close function is will close a previously opened file.
 *
 *  @param  file_fp             Pointer to the previously opened file.
 *
 *  @return void                No return information from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
file_close(
    FILE                        *   file_fp
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  File Close
     ************************************************************************/

    //  Close a previously opened file
    fclose( file_fp );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Read a single line of test from the file.
 *
 *  @param  in_buffer_p         Pointer to a file previously opened for read.
 *
 *  @return data                Pointer to the data read from the file.
 *                              END_OF_FILE at End-Of-File
 *
 *  @note
 *
 ****************************************************************************/

char    *
file_read_text(
    FILE                        *   file_fp,
    enum    read_text_options_e     options
   )
{
    /**
     *  @param  in_line         Local buffer to store read data             */
    char                            in_line[ MAX_LINE_L ];
    /**
     *  @param  in_line_p       Pointer to the read data buffer             */
    char                        *   in_line_p;
    /**
     *  @param  tmp_data_1_p    Pointer to a temporary data buffer          */
    char                        *   tmp_data_1_p;
    /**
     *  @param  tmp_data_2_p    Pointer to a temporary data buffer          */
    char                        *   tmp_data_2_p;
    /**
     *  @param  eof_p           End-Of-File pointer (NULL == EOF)           */
    char                        *   eof_p;
    /**
     *  @param  eol             End-Of-Line flag                            */
    int                             eol;
    /**
     *  @param  found           TRUE = found, FALSE = not found             */
    int                             found;
    /**
     *  @param  bytes_read      Total number of bytes read                  */
    float                           bytes_read;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //   Not at End-Of-Line yet.
    eol = false;

    //  Clean the input buffer
    memset( in_line, '\0',  sizeof( in_line ) );

    //  Initialize the buffer pointers
    in_line_p       = NULL;
    tmp_data_1_p    = NULL;
    tmp_data_2_p    = NULL;

    /************************************************************************
     *  Read a new line of text
     ************************************************************************/

    //  Continue to read until End-Of-Line is reached
    while( eol == false )
    {
        //  Read another line of text from the input file
        eof_p = fgets( in_line, sizeof( in_line ), file_fp );

        //  Are we at End-Of-File ?
        if ( eof_p == NULL )
        {
            //  YES:    Are we at End-Of-File ?
            in_line_p = END_OF_FILE;

            //  We are done here!
            break;
        }
        else
        {
            //  NO:     Update the total number of bytes read.
            total_bytes_read += strlen( in_line );

            //  What time is it ?
            gettimeofday( &time_now, NULL );

            //  Is the first time through here ?
            if ( time_last.tv_sec == 0 )
            {
                //  YES:    Update the last display time
                time_last.tv_sec = time_now.tv_sec;
            }

            //  Is it time to display ?
            if ( ( time_last.tv_sec + 60 ) <= time_now.tv_sec )
            {
                //  YES:    Update the last display time
                time_last.tv_sec = time_now.tv_sec;

                //  Is this the first time ?
                if ( bytes_read_last > 0 )
                {
                    //  NO:     Calculate the transfer rate.
                    bytes_read = total_bytes_read - bytes_read_last;

                    //  Log the transfer rate
                    log_write( MID_DEBUG_0, "file_read_text",
                               "Transfer rate: %3.2f KB/s\n",
                               ( ( bytes_read / 1000 ) / 60 ) );
                }

                //  Save the current count
                bytes_read_last = total_bytes_read;
            }

            //  Remove the CR/LF characters (if present)
            text_remove_crlf( in_line );

            //  Remove any trailing whitespace from the end of the line
            text_strip_whitespace( in_line );

            //  Move the read data to a temporary buffer
            tmp_data_2_p = text_copy_to_new( in_line );
        
            log_write( MID_DEBUG_1, "file_api.c", "Line: %d\n", __LINE__ );

            //  Is there already data in the read data buffer ?
            if ( tmp_data_1_p == NULL )
            {
                //  NO:     Transfer data from the tmp buffer to the read data buffer.
                tmp_data_1_p = tmp_data_2_p;

                //  clear the temporary data pointer
                tmp_data_2_p = NULL;
            }
            else
            {
                /**
                 *  @param  copy_of_p       Pointer to a temporary buffer   */
                char                        *   copy_of_p;
                /**
                 *  @param  data_l          Size (in bytes) of the data     */
                int                             data_l;

                //  YES:    Calculate the size needed for the two buffers.
                data_l = strlen( tmp_data_1_p ) + strlen( tmp_data_2_p ) + 1;

                //  Allocate a new buffer for the two lines.
                copy_of_p = mem_malloc( data_l );

                log_write( MID_DEBUG_1, "file_api.c", "Line: %d\n", __LINE__ );

                //  Copy the two lines of text to the new buffer
                strncpy( copy_of_p, tmp_data_1_p, data_l );
                strncat( copy_of_p, tmp_data_2_p, data_l );

                //  Free the unused data buffer(s)
                mem_free( tmp_data_1_p );
                mem_free( tmp_data_2_p );

                //  This is now the new temporary data 1 buffer
                tmp_data_1_p = copy_of_p;
            }
        }
        //  Does line of data end with an equals sign '=' ?
        if (    ( tmp_data_1_p != NULL )
             && ( tmp_data_1_p[ strlen( tmp_data_1_p ) - 1 ] == '=' )
             && ( tmp_data_1_p[ strlen( tmp_data_1_p ) - 2 ] != '=' ) )
        {
            //  YES:    Strip off the equals sign
            tmp_data_1_p[ strlen( tmp_data_1_p ) - 1 ] = '\0';
        }
        else
        {
            //  NO:     This is the end of the text line
            eol = true;

            //  Set the return data pointer
            in_line_p = tmp_data_1_p;
        }
    }

    /********************************************************************
     *  Change character coding from quoted printable
     ********************************************************************/

    //  Are we at End-Of-File "
    if (    ( in_line_p != END_OF_FILE )
         && ( in_line_p != NULL        ) )
    {
        //  Initialize the search pointer
        tmp_data_2_p = in_line_p;

        do
        {
            /**
             *  @param  xlate_char      The translated character                */
            long int                        xlate_char;
            /**
             *  @param  data_l          Size (in bytes) of the data             */
            int                             data_l;

            //  Set the found flag to it's default state.
            found = false;

            //  Look for the first character of a quoted printable string
            tmp_data_1_p = strchr( tmp_data_2_p, '=' );

            //  Did we find one ?
            if ( tmp_data_1_p != NULL )
            {

                //  Is the format correct ?
                if (    (           tmp_data_1_p[ 0 ] == '=' )
                     && ( isxdigit( tmp_data_1_p[ 1 ] ) != 0 )
                     && ( isxdigit( tmp_data_1_p[ 2 ] ) != 0 ) )
                {
                    /**
                     *  @param  in_line         Temporary for HEX to ASCII  */
                    char                            hex_data[ 3 ];

                    //  YES:    change the state of the found flag
                    found = true;

                    //  Clear the buffer and copy the hex data string
                    memset( hex_data, '\0', sizeof( hex_data ) );
                    memcpy( hex_data, &tmp_data_1_p[ 1 ], 2 );

                    //  Convert the string to a single character
                    xlate_char = strtol( hex_data, NULL, 16 );

                    //  Is this x'BD (1/2)
                    if ( xlate_char == 0xBD )
                    {
                        //  YES:    Write it out
                        tmp_data_1_p[ 0 ] = '1';
                        tmp_data_1_p[ 1 ] = '/';
                        tmp_data_1_p[ 2 ] = '2';
                    }

                    //  Is this x'BC (1/4)
                    if ( xlate_char == 0xBC )
                    {
                        //  YES:    Write it out
                        tmp_data_1_p[ 0 ] = '1';
                        tmp_data_1_p[ 1 ] = '/';
                        tmp_data_1_p[ 2 ] = '4';
                    }

                    //  Is this x'BE (3/4)
                    if ( xlate_char == 0xBC )
                    {
                        //  YES:    Write it out
                        tmp_data_1_p[ 0 ] = '3';
                        tmp_data_1_p[ 1 ] = '/';
                        tmp_data_1_p[ 2 ] = '4';
                    }

                    else
                    {
                        //  None of the above. write the converted character
                        tmp_data_1_p[ 0 ] = (char)xlate_char;

                        //  Find the string length of the remaining data
                        data_l = strlen( &tmp_data_1_p[ 3 ] );

                        //  Is there anything else in the string ?
                        if ( data_l > 0 )
                        {
                            /**
                             *  @param  ndx             Offset into a buffer        */
                            int                             ndx;

                            //  @note:  I have an interesting problem with the following.
                            //  Both the 'strcpy' and 'memcpy' are corrupting data.
                            //  Before:     "B0. Prepare a 9\\" pie pan with cooking spray and flour; set aside. T"
                            //  strcpy:     ". Prepare 9\\" p pie pan with cooking spray and flour; set aside. T"
                            //  memcpy:     ". Prepare a  pie pan with cooking spray and flour; set aside. . T"
                            //  EXPECTED:   ". Prepare a 9\\" pie pan with cooking spray and flour; set aside. T"
                            //  YES:    Left shift the remainder of the string
                            for( ndx = 1; tmp_data_1_p[ ndx ] != '\0'; ndx += 1 )
                            {
                                tmp_data_1_p[ ndx ] = tmp_data_1_p[ ndx + 2 ];
                            }

                            //  Set the new search starting pointer
                            tmp_data_2_p = &tmp_data_1_p[ 1 ];
                        }
                        else
                        {
                            //  NO:     Terminate the string here
                            tmp_data_1_p[ 1 ] = '\0';
                        }
                    }
                }
            }

        }   while( found == true );
    }

    //  Remove the CR/LF characters (if present)
    //  @NOTE:  The line may have ended with =0D
    if (    ( in_line_p != NULL         )
         && ( in_line_p != END_OF_FILE  ) )
    {
        text_remove_crlf( in_line_p );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( in_line_p );
}

/****************************************************************************/
/**
 *  The file_stat function is called once for each file.  It only opens the
 *  file and does NOT read any data from it.
 *
 *  @param  full_file_name_p    Pointer to the fully qualified file name.
 *  @param  file_name_p         Pointer to File name.
 *
 *  @return                     Upon successful completion PASS is returned
 *                              else FAIL is returned
 *
 *  @note
 ****************************************************************************/

struct  file_info_t *
file_stat(
    char                        *   full_file_name_p,
    char                        *   file_name_p
    )
{
    /**
     *  @param  file_rc         Return Code                                 */
    int                             file_rc;
    /**
     *  @param  statbuf         File statistics data                        */
    struct  stat                    statbuf;
    /**
     *  @param  tm              Time structure                              */
    struct  tm                  *   tm;
    /**
     *  @param  file_info_p     Pointer to file information             */
//  struct  file_info_t             file_info;
    /**
     *  @param  file_info_p     Pointer to file information             */
    struct  file_info_t    *        file_info_p;
    /**
     *  @parm   tmp_char_p          Pointer to a character buffer           */
    char                        *   tmp_char_p;
    /**
     *  @param  dir_name        Buffer to hold the directory name           */
    char                            dir_name[ FILE_NAME_L ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Allocate a structure to save the file information
    file_info_p = mem_malloc( sizeof( struct file_info_t ) );

    log_write( MID_DEBUG_1, "file_api.c", "Line: %d\n", __LINE__ );

    /************************************************************************
     *  Function Body
     ************************************************************************/

    //  Copy the full file name to the directory name buffer
    strncpy( dir_name, full_file_name_p, sizeof( dir_name ) - 1 );

    //  Is the last character of the full file name a '/' ?
    if ( dir_name[ strlen( dir_name ) - 1 ] == '/' )
    {
        //  YES:    Remove it from the string
        dir_name[ strlen( dir_name ) - 1 ] = '\0';
    }

    //  Is there a directory in the full file name ?
    if ( strrchr( dir_name, '/' ) == NULL )
    {
        //  NO:     Just use the full file name
        strncpy( file_info_p->file_name, dir_name,
                 sizeof( file_info_p->file_name ) - 1 );
        strncpy( file_info_p->dir_name, ".",
                 sizeof( file_info_p->dir_name ) - 1 );
    }
    else
    {
        //  YES:    Split the directory path from the file name
        tmp_char_p = strrchr( dir_name, '/' );

        //  NULL terminate the directory path string
        tmp_char_p[ 0 ] = '\0';

        //  Save file name string
        strncpy( file_info_p->dir_name, dir_name,
                 sizeof( file_info_p->dir_name ) - 1 );

        //  Save file name string
        strncpy( file_info_p->file_name, &tmp_char_p[ 1 ],
                 sizeof( file_info_p->file_name ) - 1 );
    }

    //  Get statistics for the file name
    file_rc = stat( full_file_name_p, &statbuf );

    //  Were we successful at getting the statistics data ?
    if ( file_rc != -1 )
    {
        //  YES:    File Size
        snprintf( file_info_p->file_size, sizeof( file_info_p->file_size ),
                "%ld", statbuf.st_size );

        //  File Creation Tile
        tm = localtime( &statbuf.st_mtime );
        strftime( file_info_p->date_time,
                  sizeof( file_info_p->date_time ),
                  nl_langinfo( D_T_FMT ),
                  tm );
    }
    else
    {
        //  NO:     Set the return pointer to NULL to show the failure
        mem_free( file_info_p );

        file_info_p = NULL;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  TTFN!
    return ( file_info_p );
}

/****************************************************************************/
/**
 *  Create a recursive list of files in a directory tree.
 *
 *  @param  fd_name             A directory name.
 *  @param  file_list_p         Pointer to a list for the list of files
 *  @param  include_ext_p       Pointer to a file extension to include
 *
 *  @return void                No return information from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
file_ls(
    struct  list_base_t         *   file_list_p,
    char                        *   fd_name,
    char                        *   include_ext_p
    )
{
    /**
     *  @param  dp              Directory pointer                           */
    DIR                         *   dp;
    /**
     *  @param  entry           Directory information structure             */
    struct  dirent              *   entry;
    /**
     *  @param  statbuf         File or Directory state data                */
    struct  stat                    statbuf;
    /**
     *  @param  full_file_name  Fully qualified file name                   */
    char                            full_file_name[ MAX_LINE_L ];
    /**
     *  @param  file_info_p     Pointer to a file information structure     */
    struct  file_info_t         *   file_info_p;
    /**
     *  @param  stat_data_p     Pointer to a file statistics structure  */
    struct  file_info_t         *   stat_data_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Log the progress
    log_write( MID_DEBUG_0, "file_next",
               "Scanning: '%s'\n",
               fd_name );

    /************************************************************************
     *  Function Body
     ************************************************************************/

    //  Attempt to open a directory
    if ( ( dp = opendir( fd_name ) ) == NULL )
    {
        log_write( MID_FATAL, "file_next",
                   "File or Directory '%s' does not exist.\n",
                    fd_name );
    }
    //  Directory:
    while( ( entry = readdir( dp ) ) != NULL )
    {
        //  Will the full name fit in the buffer ?
        if (   ( strlen( fd_name ) + strlen( entry->d_name ) )
             < ( sizeof( full_file_name ) - 2 ) )
        {
            //  YES:    Expand the name
            snprintf( full_file_name, sizeof( full_file_name ),
                      "%s/%s", fd_name, entry->d_name );
        }
        else
        {
            //  NO:     Error message
            log_write( MID_INFO, "file_next",
                       "Full file name is larger than the allocated buffer\n" );
            log_write( MID_FATAL, "file_next",
                       "%s/%s\n", fd_name, entry->d_name );
        }

        // Test for a directory or a file name.
        lstat( full_file_name, &statbuf );

        //  Is this a directory ?
        if ( S_ISDIR( statbuf.st_mode ) )
        {

            /****************************************************************
             *  Exclude these directories
             ****************************************************************/

            //  YES:    Does the directory name match any of the following ?
            if (    ( strcmp( entry->d_name, "."        ) == 0 )
                 || ( strcmp( entry->d_name, ".."       ) == 0 ) )
            {
                //  YES:    Exclude it from processing.
                continue;
            }

            //  Build a file list for this directory
            file_ls( file_list_p, full_file_name, include_ext_p );
        }
        else
        {
            //  Is there a extension exclude type ?
            if ( include_ext_p != NULL )
            {
                /**
                 *  @param  period_p        Pointer to the last period      */
                char                        *   period_p;
                /**
                 *  @param  extention       Buffer to hold file extention   */
                char                            extention[ 10 ];

                //  YES:    Locate the start of the file extention
                period_p = strrchr( full_file_name, '.' );

                //  Is there a file extention ?
                if ( period_p != NULL )
                {
                    //  YES:    Copy the file extention to a new buffer
                    strncpy( extention, ++period_p, sizeof( extention ) );

                    //  Make the file extention all lowercase
                    text_to_lowercase( extention );

                    //  Compare the file extention to the include extention.
                    if ( strncmp( include_ext_p, extention, strlen( include_ext_p ) ) != 0 )
                    {
                        //  NO:     This isn't an include file extention
                        continue;
                    }
                }
            }
            //  NO:     Allocate a structure to save the file information
            file_info_p = mem_malloc( sizeof( struct file_info_t ) );

            log_write( MID_DEBUG_1, "file_api.c", "Line: %d\n", __LINE__ );

            //  Get the file statics data
            stat_data_p = file_stat( full_file_name, entry->d_name );

            //  Clean th destination buffers
            memset( file_info_p->dir_name,  '\0', sizeof( file_info_p->dir_name  ) );
            memset( file_info_p->file_name, '\0', sizeof( file_info_p->file_name ) );
            memset( file_info_p->date_time, '\0', sizeof( file_info_p->date_time ) );
            memset( file_info_p->file_size, '\0', sizeof( file_info_p->file_size ) );

            //  Save the file information
            strncpy(  file_info_p->dir_name,
                      fd_name,
                      sizeof( file_info_p->dir_name  ) - 1 );

            strncpy(  file_info_p->file_name,
                      stat_data_p->file_name,
                      sizeof( file_info_p->file_name ) - 1 );

            strncpy(  file_info_p->date_time,
                      stat_data_p->date_time,
                      sizeof( file_info_p->date_time ) - 1 );

            strncpy(  file_info_p->file_size,
                      stat_data_p->file_size,
                      sizeof( file_info_p->file_size ) - 1 );

            //  Add the new file to the list
            list_put_last( file_list_p, file_info_p );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  At the end of the directory, close it.
    closedir( dp );

    //  DONE!
}

/****************************************************************************/
/**
 *  Returns a pointer to a text string with the directory path to the
 *  .LibTools directory.
 *
 *  @param  void                No information is passed into this function
 *
 *  @return path_p              Pointer to the directory path
 *
 *  @note
 *
 ****************************************************************************/

char    *
file_path_to_lib(
    void
    )
{
    /**
     *  @param  path_p          Pointer to the directory path               */
    char                        *   path_p;
    /**
     *  @param  tmp_p           Pointer to a temporary buffer               */
    char                        *   tmp_p;

    /************************************************************************
     *  Function Exit
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Allocate storage for the directory path.
    path_p = mem_malloc( FILE_NAME_L + 1 );

    //  Get the home directory path
    tmp_p = getenv( "HOME" );

    //  Did we get it ?
    if ( tmp_p != NULL )
    {
        //  YES:    Build the full path
        snprintf( path_p, FILE_NAME_L,
                  "%s/%s", tmp_p, LOG_DIR_NAME );
    }
    else
    {
        //  NO:     This is bad.
        log_write( MID_FATAL, "file_path_to_lib",
                   "Environment variable 'HOME' is not set.\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( path_p );
}

/****************************************************************************/
/**
 *  Recursively find and extract all "*.zip" files in the target directory.
 *
 *  @param  dir_p               Pointer to the starting directory
 *
 *  @return void                No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
file_unzip(
    char                        *   path_p
    )
{
    /**
     *  @param  found_zip       Flag showing a "*.zip" file was found.      */
    int                             found_zip;
    /**
     *  @param  file_list       Pointer to a list of files                  */
    struct  list_base_t         *   file_list_p;
    /**
     *  @param  file_info_p     Pointer to a file information structure     */
    struct  file_info_t         *   file_info_p;
    /**
     *  @param  file_name       Buffer to hold the directory/file name      */
    char                            file_name[ ( FILE_NAME_L * 3 ) ];
    /**
     *  @param  extract_to      Name of the directory to extract into       */
    char                            extract_to[ ( FILE_NAME_L * 3 ) ];
    /**
     *  @param  tmp_p           Temporary data pointer                      */
    char                        *   tmp_p;
    /**
     *  @param  command         System command buffer                       */
    char                            command[ SYS_CMD_L ];
    /**
     *  @param  extention       Buffer to hold file extention               */
    char                            extention[ 10 ];

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Create the file-list
    file_list_p = list_new( );

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Keep looping until there are no more "*.zip" files
    do
    {
        //  Assume that we will NOT find a "*.zip" file
        found_zip = false;

        //  Build the file list
        file_ls( file_list_p, path_p, "zip" );

        //  Scan the list
        for( file_info_p = list_get_first( file_list_p );
             file_info_p != NULL;
             file_info_p = list_get_next( file_list_p, file_info_p ) )
        {
            //  Remove it from the list
            list_delete( file_list_p, file_info_p );

            //  Will the fully qualified file name will fit in the buffer ?
            if (     (   ( strlen( file_info_p->dir_name  ) )
                       + ( strlen( file_info_p->file_name ) ) )
                  >= ( sizeof( file_name ) ) )
            {
                //  NO:     This is bad..
                log_write( MID_WARNING, "file_unzip",
                              "The file name is too big for the buffer provided. \n" );
                log_write( MID_FATAL, "file_unzip",
                              "'%s/%s'\n",
                              file_info_p->dir_name, file_info_p->file_name );
            }
            else
            {
                //  YES:    build the full file name.
                snprintf( file_name, sizeof( file_name ) - 1,
                           "%s/%s",
                           file_info_p->dir_name, file_info_p->file_name );
                snprintf( extract_to, sizeof( extract_to ) - 1,
                           "%s/%s",
                           file_info_p->dir_name, file_info_p->file_name );
            }

            //  Find the file extention
            tmp_p = strrchr( extract_to, '.' );

            //  Is there one ?
            if ( tmp_p != NULL )
            {
                //  YES:    Copy the file extention to a new buffer
                strncpy( extention, ++tmp_p, sizeof( extention ) );

                //  Make the file extention all lowercase
                text_to_lowercase( extention );

                //  Is this a "*.zip" file ?
                if ( strncmp( extention, "zip", 3 ) == 0 )
                {
                    //  YES:    Null terminate at the period
                    (--tmp_p)[ 0 ] = '\0';

                    //  Make a new directory for the uncompressed file(s).
                    if ( mkdir( extract_to, S_IRWXU | S_IRWXG | S_IRWXO ) == 0 )
                    {
                        //  YES:    Log it.
                        log_write( MID_INFO, "file_unzip",
                                  "Extracting: '%s'\n", file_name );

                        // Build the unzip command
                        snprintf( command, sizeof ( command ),
                                 "unzip -q -o %s -d %s",
                                 file_name,
                                 extract_to );

                        // Uncompress the file into the new directory
                        system( command );

                        //  Finally, delete the zip file.
                        remove( file_name );

                        //  Change the flag, we extracted a "*.zip" file
                        found_zip = true;
                    }
                }
            }

            //  Release storage for the File Information structure
            mem_free( file_info_p );
        }

    }   while( found_zip == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Create the file-list
    list_kill( file_list_p );

    //  DONE!
}

/****************************************************************************/
