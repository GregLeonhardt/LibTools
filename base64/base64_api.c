/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2019 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains public function that makeup the external
 *  library components of the 'base64' library.
 *
 *  @note
 *      Base64 is a group of binary-to-text encoding schemes that represent
 *      binary data in an ASCII string format by translating it into a
 *      radix-64 representation.
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_BASE64          ( "ALLOCATE STORAGE FOR BASE64" )

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
#include <stdlib.h>             //  ANSI standard library.
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  My Tools Library
                                //*******************************************
#include "base64_lib.h"          //  API for all BASE64__*          PRIVATE
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
unsigned char   encode_table[ 64 ] =
                        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                         'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                         'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                         'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                         'w', 'x', 'y', 'z', '0', '1', '2', '3',
                         '4', '5', '6', '7', '8', '9', '+', '/'
                        };
//----------------------------------------------------------------------------
unsigned char   decode_table[ 128 ] =
//     0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
{   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 1
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0x00, 0xFF, 0x3F, // 2
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 3
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, // 4
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 5
    0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, // 6
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  // 7
};
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
 *  Translates a data buffer into encoded base64.
 *
 *  @param recipe_t             Primary structure for a recipe
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

char    *
base64_encode(
    char                        *   data_p
    )
{
    /**
     *  @param  decode_data_p   Pointer to the decoded data                 */
    char                        *   encode_data_p;
    /**
     *  @param  data_l          Length in bytes of the input data           */
    int                             data_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  @ToDo: L1 This function need to be written
    log_write( MID_FATAL, "base64_encode( )",
                "@TODO: This function need to be written\n" );

    //  Set the length of the input data
    data_l = strlen( data_p );

    //  Allocate a new decode data buffer
    encode_data_p = mem_malloc( ( ( data_l / 3 ) * 4 ) + 4 );

    /************************************************************************
     *  Encode the data to a base64 string
     ************************************************************************/


    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  DONE!
    return( encode_data_p );
}

/****************************************************************************/
/**
 *  The
 *
 *  @param recipe_t             Primary structure for a recipe
 *
 *  @return void                No return code from this function.
 *
 *  @note
 *
 ****************************************************************************/

char    *
base64_decode(
    char                        *   data_p
    )
{
    /**
     *  @param  decode_data_p   Pointer to the decoded data                 */
    char                        *   decode_data_p;
    /**
     *  @param  sextet_[0-3]    The four sextets                            */
    uint8_t                         sextet_0;
    uint8_t                         sextet_1;
    uint8_t                         sextet_2;
    uint8_t                         sextet_3;
    /**
     *  @param  s_ndx           Index into the source data buffer           */
    int                             s_ndx;
    /**
     *  @param  d_ndx           Index into the destination data buffer      */
    int                             d_ndx;
    /**
     *  @param  data_l          Length in bytes of the input data           */
    int                             data_l;
    /**
     *  @param  decode_data     Three bytes o decoded data                  */
    uint64_t                        decoded_data;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the length of the input data
    data_l = strlen( data_p );

    //  Allocate a new decode data buffer
    decode_data_p = mem_malloc( ( ( data_l / 4 ) * 3 ) + 4 );

    /************************************************************************
     *  Decode the base64 string
     ************************************************************************/

    //  Set the starting index count
    s_ndx = 0;
    d_ndx = 0;

    //  Decode the complete input buffer.
    do
    {
        //  Reinitialize the decoded data
        decoded_data = 0;

        //  Clean up all sextet buffers
        sextet_0 = '=';
        sextet_1 = '=';
        sextet_2 = '=';
        sextet_3 = '=';

        //  Get sextet 0
        if ( s_ndx < data_l )
            sextet_0 = data_p[ s_ndx ++ ];

        //  Get sextet 1
        if ( s_ndx < data_l )
            sextet_1 = data_p[ s_ndx ++ ];

        //  Get sextet 2
        if ( s_ndx < data_l )
            sextet_2 = data_p[ s_ndx ++ ];

        //  Get sextet 3
        if ( s_ndx < data_l )
            sextet_3 = data_p[ s_ndx ++ ];

        //  Translate the sextets to ASCII
        decoded_data =                         decode_table[ sextet_0 ];
        decoded_data = ( decoded_data << 6 ) | decode_table[ sextet_1 ];
        decoded_data = ( decoded_data << 6 ) | decode_table[ sextet_2 ];
        decoded_data = ( decoded_data << 6 ) | decode_table[ sextet_3 ];

        //  Save the decoded data
        decode_data_p[ d_ndx++ ] = ( decoded_data & 0x00FF0000 ) >> 16;
        decode_data_p[ d_ndx++ ] = ( decoded_data & 0x0000FF00 ) >>  8;
        decode_data_p[ d_ndx++ ] = ( decoded_data & 0x000000FF )      ;

    }   while ( s_ndx < data_l );

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  DONE!
    return( decode_data_p );
}

/****************************************************************************/
