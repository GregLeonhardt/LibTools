/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains public function that makeup the external
 *  library components of the 'store' library.
 *
 *  @note
 *      The 'store' interface provides an application to place things in
 *      a storage container then access and/or update the data when the
 *      application is run again.
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_STORE          ( "ALLOCATE STORAGE FOR STORE" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <string.h>             //  Functions for managing strings
#include <unistd.h>             //  Access to the POSIX operating system API
                                //*******************************************
#include <stdlib.h>
/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  My Tools Library
                                //*******************************************
#include <sqlite3.h>            //  Everything SqLite-3
                                //*******************************************
#include "store_lib.h"          //  API for all STORE__*            PRIVATE
                                //*******************************************

/****************************************************************************
 * Private API Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private API Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private API Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private API Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Public API Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Initialize the 'store' interface.
 *
 *  @param  void                No parameters are passed in.
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
store_init(
    void
    )
{
    /**
     *  @param  sqlite_rc       Return code from a SqLite function call     */
    int                             sqlite_rc;
    /**
     *  @param  path_p          Pointer to the directory path               */
    char                        *   path_p;
    /**
     *  @param  sqlite_cmd_p    Pointer to a command buffer                 */
    char                        *   sqlite_cmd_p;
    /**
     *  @param  sqlite_err_p    Pointer to an error message                 */
    char                        *   sqlite_err_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Get the LibTools directory path
    path_p = file_path_to_lib( );

    //  Append the Translations file name to the path
    strncat( path_p, "/", FILE_NAME_L );
    strncat( path_p, "store.db", FILE_NAME_L );

    /************************************************************************
     *  Create the tools directory if it doesn't already exist
     ************************************************************************/

    //  @ToDo:  Some code is needed here

    /************************************************************************
     *  Open the dBase
     ************************************************************************/

    sqlite_rc = sqlite3_open( path_p, &store_db );

    if( sqlite_rc != SQLITE_OK )
    {
        log_write( MID_WARNING, "store_init",
                   "Can't open database: %s\n", sqlite3_errmsg( store_db ) );
        sqlite3_close( store_db );
        exit( -1 );
    }

    /************************************************************************
     *  Create table
     ************************************************************************/

    //  Create SQL statement
    sqlite_cmd_p = "CREATE TABLE IF NOT EXISTS DATA_STORE("  \
                   "VAR_NAME      CHAR( 16 )  NOT NULL PRIMARY KEY," \
                   "VAR_VALUE     CHAR( 50 )  NOT NULL );";

    //  Execute SQL statement
    sqlite_rc = sqlite3_exec( store_db, sqlite_cmd_p, STORE__callback, 0, &sqlite_err_p);

    if( sqlite_rc != SQLITE_OK )
    {
        log_write( MID_WARNING, "store_init",
                   "SQL error: %s\n", sqlite_err_p);
        sqlite3_free( sqlite_err_p );
    }
    else
    {
        log_write( MID_INFO, "store_init",
                   "Successfully created table 'DATA_STORE'\n" );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Release memory used to hold the file path
    mem_free( path_p );

    //  DONE!
}

/****************************************************************************/
/**
 *  Initialize the 'store' interface.
 *
 *  @param  void                No parameters are passed in.
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

char    *
store_get(
    char                        *   name_p
    )
{
    /**
     *  @param  value_p         Pointer to return data string               */
    char                        *   value_p;
    /**
     *  @param  sqlite_rc       Return code from a SqLite function call     */
    int                             sqlite_rc;
    /**
     *  @param  sqlite_cmd      Buffer to hold a SqLite command             */
    char                            sqlite_cmd[ SQLITE_CMD_L ];
    /**
     *  @param  sqlite_cmd_p    Pointer to a command buffer                 */
    char                        *   sqlite_cmd_p;
    /**
     *  @param  sqlite_res_p    SqLite statement handle                     */
    sqlite3_stmt                *   sqlite_res_p;
    /**
     *  @param  sqlite_step     SqLite step value                           */
    int                             sqlite_step;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  The assumption is that the value get function will fail
    value_p = NULL;

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Build the SqLite command statement
    snprintf( sqlite_cmd, sizeof( sqlite_cmd ),
              "SELECT VAR_NAME, VAR_VALUE FROM DATA_STORE WHERE VAR_NAME = '%s'", name_p );
    sqlite_cmd_p = sqlite_cmd;

    sqlite_rc = sqlite3_prepare_v2( store_db, sqlite_cmd_p, -1, &sqlite_res_p, 0 );

    if( sqlite_rc == SQLITE_OK )
    {
        sqlite3_bind_int( sqlite_res_p, 1, 3);
    }
    else
    {
      log_write( MID_WARNING, "store_get",
                 "Failed to execute statement: %s\n",
                 sqlite3_errmsg( store_db ) );
    }

    sqlite_step = sqlite3_step( sqlite_res_p );

    if ( sqlite_step == SQLITE_ROW )
    {
        //  Save the RECIPE-ID.
        value_p = text_copy_to_new( (char*)sqlite3_column_text( sqlite_res_p, 1 ) );
    }

    sqlite3_finalize( sqlite_res_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( value_p );
}

/****************************************************************************/
/**
 *  Initialize the 'store' interface.
 *
 *  @param  void                No parameters are passed in.
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
store_put(
    char                        *   name_p,
    char                        *   value_p
    )
{
    /**
     *  @param  sqlite_rc       Return code from a SqLite function call     */
    int                             sqlite_rc;
    /**
     *  @param  sqlite_cmd      Buffer to hold a SqLite command             */
    char                            sqlite_cmd[ SQLITE_CMD_L ];
    /**
     *  @param  sqlite_cmd_p    Pointer to a command buffer                 */
    char                        *   sqlite_cmd_p;
    /**
     *  @param  sqlite_err_p    Pointer to an error message                 */
    char                        *   sqlite_err_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Create SQL statement
    snprintf( sqlite_cmd, sizeof( sqlite_cmd ),
            "INSERT INTO DATA_STORE ( VAR_NAME, VAR_VALUE ) VALUES ( '%s', '%s' );",
            name_p, value_p );
    sqlite_cmd_p = &(sqlite_cmd[ 0 ]);

    //  Execute SQL statement
    sqlite_rc = sqlite3_exec( store_db, sqlite_cmd_p, STORE__callback,
                              0, &sqlite_err_p );

    //   Does the key already exist ?
    if( sqlite_rc == SQLITE_CONSTRAINT )
    {
        //   YES:    We need to update in place of insert
        snprintf( sqlite_cmd, sizeof( sqlite_cmd ),
                    "UPDATE DATA_STORE SET VAR_VALUE = '%s' "
                    "WHERE VAR_NAME = '%s';", value_p, name_p );
        sqlite_cmd_p = &(sqlite_cmd[ 0 ]);


        //  Execute SQL statement
        sqlite_rc = sqlite3_exec( store_db, sqlite_cmd_p, STORE__callback,
                                  0, &sqlite_err_p );
    }

    if( sqlite_rc != SQLITE_OK )
    {
        log_write( MID_WARNING, "store_put",
                  "SQL error: %s\n", sqlite_err_p );
        sqlite3_free( sqlite_err_p );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
