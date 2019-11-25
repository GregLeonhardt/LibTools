/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains public function that makeup the external
 *  library components of the 'text' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_TEXT              ( "ALLOCATE STORAGE FOR TEXT" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <ctype.h>              //  Determine the type contained
#include <stdlib.h>             //  ANSI standard library.
#include <string.h>             //  Functions for managing strings
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "text_lib.h"           //  API for all TEXT__*             PRIVATE
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
 *  Convert an ASCII string into HEX value.
 *      This function translates an ASCII string into its HEX value.
 *      Example: The ASCII string = "1A2b3f" would return 0x001A2B3F
 *
 *  @param  hex_string_p        A pointer to an ASCII string
 *
 *  @return hex_value
 *
 *  @note
 *
 ****************************************************************************/

int
text_atox(
    char                        *   hex_string_p
    )
{
    uint32_t                        hex_value;
    uint32_t                        index;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Zero out the return value
    hex_value = 0;

    /************************************************************************
     *  Convert an ASCII string into HEX value
     ************************************************************************/

    //  Loop through all characters in the string
    for( index = 0;
          isxdigit( hex_string_p[ index ]);
          index++ )
    {
        if( isalpha( hex_string_p[ index ]) )
        {
            hex_value =
                ( hex_value * 16) + ( toupper( hex_string_p[ index ]) - '7');
        }
        else
        {
            hex_value =
                ( hex_value * 16) + (          hex_string_p[ index ] - '0');
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( hex_value );
}

/****************************************************************************/
/**
 *  Space fill a string for 'length' bytes.
 *
 *  @param  data_p              Pointer to a string.
 *  @param  data_l              Desired string length in bytes.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_space_fill(
    char                        *   data_p,
    int                             data_l
    )
{
    int                             s_pad_position;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Space fill a string for 'length' bytes
     ************************************************************************/

    //  Pad out the RtdName
    for( s_pad_position = strlen( data_p );
          s_pad_position < data_l;
          s_pad_position ++ )
    {
        data_p[ s_pad_position ] = ' ';
    }
    //  NULL terminate the string
    data_p[ data_l ] = '\0';

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Convert a text string to UPPERCASE.
 *
 *  @param  text_p              Pointer to the data string.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_to_uppercase(
    char                        *   text_p
    )
{
    int                             index;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Convert a text string to UPPERCASE
     ************************************************************************/

    for( index = 0;
          text_p[ index ] != '\0';
          index ++ )
    {
        if( islower( text_p[ index ] ) )
        {
            text_p[ index ] = toupper( text_p[ index ] );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Convert a text string to lowercase.
 *
 *  @param  text_p              Pointer to the data string.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_to_lowercase(
    char                        *   text_p
    )
{
    int                             index;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Convert a text string to UPPERCASE
     ************************************************************************/

    for( index = 0;
          text_p[ index ] != '\0';
          index ++ )
    {
        if( isupper( text_p[ index ] ) )
        {
            text_p[ index ] = tolower( text_p[ index ] );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Convert a text string to an integer.
 *
 *  @param  text_p              Pointer to the data string.
 *
 *  @return integer
 *
 *  @note
 *
 ****************************************************************************/

int
text_to_int(
    char                        *   text_p
    )
{
    int                             integer;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Convert a text string to an integer
     ************************************************************************/

    //  Does the text string start with '0x' ?
    if(    ( toupper( text_p[ 0 ] ) == '0' )
        && ( toupper( text_p[ 1 ] ) == 'X' ) )
    {
        //  YES:    Convert a hex string.
        integer = text_atox( &text_p[ 2 ] );
    }
    else
    {
        //  NO:     Do a straight conversion
        integer = atoi( text_p );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( integer );
}

/****************************************************************************/
/**
 *  Skip over leading whitespace
 *
 *  @param  line_of_text_p      Pointer to the data string.
 *
 *  @return line_of_text_p
 *
 *  @note
 *
 ****************************************************************************/

char    *
text_skip_past_whitespace(
    char                        *   line_of_text_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Call the internal function
    return( TEXT__skip_past_whitespace( line_of_text_p ) );
}

/****************************************************************************/
/**
 *  Strip off any terminating CR and / or LF characters.
 *
 *  @param  line_of_text_p      Pointer to the data string.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_remove_crlf(
    char                        *   line_of_text_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Strip off any terminating CR and / or LF characters
     ************************************************************************/

    //  Call the internal function
    TEXT__remove_crlf( line_of_text_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Strip off any trailing white space from a string.
 *
 *  @param  line_of_text_p      Pointer to the data string.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_strip_whitespace(
    char                        *   line_of_text_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Strip off any trailing white space from a string
     ************************************************************************/

    //  Call the internal function
    TEXT__strip_whitespace( line_of_text_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Test the line of text for a zero length or only whitespace characters.
 *
 *  @param  line_of_text_p  Pointer to the data string.
 *
 *  @return                     TRUE  = Zero length or only whitespace
 *                              FALSE = Non whitespace characters found
 *
 *  @note
 *
 ****************************************************************************/

int
text_is_blank_line(
    char                        *   line_of_text_p
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Call the internal function
    return( TEXT__is_blank_line( line_of_text_p ) );
}

/****************************************************************************/
/**
 *  The get_cmd_line_parm will scan the list of command line parameters
 *  for one matching the search string.  When it is located, a pointer to
 *  the next string is returned.  If the string is not located NULL is
 *  returned.
 *
 *  @param  argc                Number of parameters
 *  @param  argv                List of pointers.
 *  @param  search_string       The parameter we are looking for.
 *
 *  @return value_string_p
 *
 *  @note
 *
 ****************************************************************************/

char *
get_cmd_line_parm(
    int                             argc,
    char                        **  argv,
    const char                  *   search_string_p
    )
{
    char                        *   value_string_p;
    int                             argv_index;
    char                            local_search_string[ 256 ];
    char                            local_parm_buffer[ 256 ];
    char                            compare_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  If the parameter is not located, return a null pointer
    value_string_p = NULL;

    /************************************************************************
     *  Look for a specific command line parameter
     ************************************************************************/

    //  Copy the search string to a temporary working buffer.
    strncpy( local_search_string,
             search_string_p,
             sizeof( local_search_string ) );

    //  Make the search string all upper case.
    text_to_uppercase( local_search_string );

    //  Scan through all command line parameters
    for( argv_index = 1;
          argv_index < argc;
          argv_index ++ )
    {
        //  Is the first character of the parameter a dash '-'
        if( argv[ argv_index ][ 0 ] == '-' )
        {
            //  YES:    Copy the parameter to a temporary working buffer.
            strncpy( local_parm_buffer,
                     &argv[ argv_index ][ 1 ],
                     sizeof( local_parm_buffer ) );

            //  Make the text all upper case.
            text_to_uppercase( local_parm_buffer );

            //  Is the search string larger than the parm buffer ?
            if( strlen( local_search_string ) > ( strlen( local_parm_buffer ) - 1 ) )
            {
                //  YES:    Use the length of the search string
                compare_l = strlen( local_search_string );
            }
            else
            {
                //  NO:     Use the length of the parm buffer
                compare_l = strlen( local_parm_buffer ) - 1;
            }

            //  Is the search string the same as the parameter string ?
            if( strncmp( local_search_string, local_parm_buffer, compare_l ) == 0 )
            {
                //  YES:    Is there is at least one more parameter ?
                if( argc > ( argv_index + 1 ) )
                {
                    //  YES:    Get the pointer to the next parameter
                    value_string_p = argv[ ++ argv_index ];
                }
                else
                {
                    //  NO:     Return the search string
                    value_string_p = argv[ argv_index ];
                }

                //  Stop looking now that we have it.
                break;
            }
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Return with a pointer to the parameter data
    return( value_string_p );
}


/****************************************************************************/
/**
 *  Copy to new buffer
 *
 *  @param  text_p          Pointer to the data string.
 *
 *  @return copy_of_p       Pointer to the new copy
 *
 *  @note
 *
 ****************************************************************************/

char    *
text_copy_to_new(
    char                        *   text_p
    )
{
    /**
     *  @param copy_of_p        Pointer to the copied data                  */
    char                        *   copy_of_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Allocate and initialize a new buffer.
    //  NOTE:   The '+1' is for the null termination character.
    copy_of_p = mem_malloc( strlen( text_p ) + 1 );
    log_write( MID_DEBUG_1, "text_api.c", "Line: %d\n", __LINE__ );

    //  Copy the information to the new buffer
    memcpy( copy_of_p, text_p, strlen( text_p ) );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Call the internal function
    return( copy_of_p );
}

/****************************************************************************/
/**
 *  The title_case function is used to convert a character string
 *  to title case.
 *
 *  @param  out_string_p        A pointer to output string buffer.
 *  @param  in_string_p         A pointer to input string buffer.
 *
 *  @return                     Upon successful completion TRUE is returned
 *                              else FALSE is returned
 *
 ****************************************************************************/

int
text_title_case(
    char                        *   out_string_p,
    char                        *   in_string_p
    )
{
    /**
     *  @param  text_rc         The return code for this function           */
    int                             text_rc;
    /**
     *  @param  first_word      TRUE for the first word of the title        */
    int                             first_word;
    /**
     *  @param  first_character TRUE for the first character of a word      */
    int                             first_character;
    /**
     *  @param  inside_brackets TRUE if this word is inside ( )             */
    int                             inside_brackets;
    /**
     *  @param  in_ndx          Character index into the input buffer       */
    int                             in_ndx;
    /**
     *  @param  temp_char_p     Temporary character buffer pointer          */
    char                        *   temp_char_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  The assumption is that this function will pass
    text_rc = true;

    //  Initialize variables
    first_word = true;
    first_character = true;
    inside_brackets = false;
    in_ndx = 0;

    /************************************************************************
     *  Function Body
     ************************************************************************/

    //  Scan through the input title string
    for( in_ndx = 0;
         in_string_p[ in_ndx ] != '\0';
         in_ndx += 1 )
    {
        //  This should reset the first word flag
        if( first_character == false )
        {
            first_word = false;
        }
        //  Is this the first word of the string ?
        if( first_word != true )
        {
            //  NO:     Should this word be changed to Title Case ?
            if(    ( strncmp( &in_string_p[ in_ndx ], "A ", 2 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "a ", 2 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "In ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "IN ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "in ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "Or ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "OR ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "or ", 3 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "The ", 4 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "THE ", 4 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "the ", 4 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "And ", 4 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "AND ", 4 ) == 0 )
                || ( strncmp( &in_string_p[ in_ndx ], "and ", 4 ) == 0 ) )
            {
                //  NO:     Set the flag off
                first_character = false;
            }
        }
        //  Should the next character be in UPPER CASE ?
        if(    ( first_character == true )
            || ( inside_brackets == true ) )
        {
            //  YES:    Change the character to UPPER CASE
            out_string_p[ in_ndx ] = toupper( in_string_p[ in_ndx ] );

            //  Change the flag so everything else is lower case.
            first_character = false;
        }
        else
        {
            //  Change the character to lower case
            out_string_p[ in_ndx ] = tolower( in_string_p[ in_ndx ] );
        }
        //  Should the next character be set to UPPER CASE ?
        if(    ( in_string_p[ in_ndx ] == ' ' ) //  Space
            || (    ( in_string_p[ in_ndx ] == '\'' )
                 && ( in_string_p[ in_ndx + 2 ] != ' ' ) )
            || ( in_string_p[ in_ndx ] == '\"' )
            || ( in_string_p[ in_ndx ] == '.' )
            || ( in_string_p[ in_ndx ] == '[' )
            || ( in_string_p[ in_ndx ] == '<' )
            || ( in_string_p[ in_ndx ] == '&' )
            || ( in_string_p[ in_ndx ] == '/' )
            || ( in_string_p[ in_ndx ] == '(' )
            || ( in_string_p[ in_ndx ] == '-' ) )
        {
            //  YES:    Change the character to UPPER CASE
            first_character = true;
        }

        /********************************************************************
         *  Everything inside brackets is UPPER CASE unless there is
         *  a space in there.  Then normal rules apply.
         ********************************************************************/

        //  Is this an opening brace ( '(' ) ?
        if( in_string_p[ in_ndx ] == '(' )
        {
            //  YES:    Scan for the closing brace ( ')' ).
            for( inside_brackets = true, temp_char_p = &in_string_p[ in_ndx ];
                 temp_char_p[ 0 ] != ')' && inside_brackets != false;
                 temp_char_p++ )
            {
                //  Is this a space ' ' or End-of-Line ?
                if(    ( temp_char_p[ 0 ] == ' '  )
                    || ( temp_char_p[ 0 ] == '\0' ) )
                {
                    //  YES:    Change the flag so it will NOT be changed.
                    inside_brackets = false;
                }
            }
        }

        //  Is this a closing brace ( ')' )
        if( in_string_p[ in_ndx ] == ')' )
        {
            //  NO:     Change the flag so it will NOT be changed.
            inside_brackets = false;
        }

    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( text_rc );
}

/****************************************************************************/
/**
 *  Locates the next word of text in the input buffer and copies it
 *  to dst_string_p.
 *
 *  @param  src_string_p        Pointer to a text string that will be scanned
 *                              for a continuous string of printable characters.
 *  @param  dst_string_p        Pointer to a buffer where the new string of
 *                              text will be stored.
 *
 *  @return                     null when called and the inout buffer is empty
 *                              else, apoints the the end of the current word.
 *
 *  @note
 *
 ****************************************************************************/

char *
text_next_word(
    char                          *  src_string_p,
    char                          *  dst_string_p
    )
{
    char                          *  new_dst_string_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Body
     ************************************************************************/

    //  Initialize the destination buffer
    dst_string_p[ 0 ] = '\0';

    //  Skip over any leading white space
    for( new_dst_string_p = src_string_p;
         (    ( isblank( new_dst_string_p[ 0 ] ) != 0 )
           && ( new_dst_string_p[ 0 ] != '\0' ) );
         new_dst_string_p ++ )
    {
    }
    //  Did we just jump to the end of the line ?
    if( new_dst_string_p[ 0 ] != '\0' )
    {
        //  NO:     Skip over any leading white space
        for ( ;
              (    ( isblank( new_dst_string_p[ 0 ] ) == 0 )
                && ( new_dst_string_p[ 0 ] != '\0' ) );
              new_dst_string_p++ )
        {
            //  Copy a character from the source string buffer to the
            //         destination string buffer.
            strncat( dst_string_p, new_dst_string_p, 1 );
        }
    }
    else
    {
        //  The source buffer is empty
        new_dst_string_p = NULL;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( new_dst_string_p );
}

/****************************************************************************/
/**
 *  Find and convert a hex data string '<xx> to ASCII.
 *
 *  @param  text_p              Pointer to the data string.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_datastring_to_ascii(
    char                        *   src_data_p
    )
{
    /**
     *  @param  src_data_l      Size of the source data buffer              */
    int                             src_data_l;
    /**
     *  @param  tmp_p           Pointer to a temporary buffer               */
    char                        *   tmp_p;
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  altered         Flag indicating the buffer was altered      */
    int                             altered;
    /**
     *  @param  render_offset_p Index pointer inside the render buffer      */
    char                        *   render_offset_p;
    /**
     *  @param  tmp_offset_p    Index pointer inside the temporary buffer   */
    char                        *   tmp_offset_p;
    /**
     *  @param  xlate_char      ASCII character translation                 */
    char                            xlate_char;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  The size of the source data buffer
    src_data_l = ( strlen( src_data_p ) + 1 );

    //  Allocate a temporary data buffer
    render_p = mem_malloc( src_data_l );
    log_write( MID_DEBUG_1, "text_api.c", "Line: %d\n", __LINE__ );

    //  Allocate a temporary data buffer
    tmp_p = mem_malloc( src_data_l );
    log_write( MID_DEBUG_1, "text_api.c", "Line: %d\n", __LINE__ );

    //  Make two copies of the source data
    memcpy( render_p, src_data_p, src_data_l );
    memcpy( tmp_p,    src_data_p, src_data_l );

    /************************************************************************
     *  Find and convert a hex data string '<xx> to ASCII.
     ************************************************************************/

    //  Initialize the offset pointers
    render_offset_p = render_p;
    tmp_offset_p    = tmp_p;

    do
    {
        //  Set/Reset the altered flag to 'ALTERED'
        altered = true;

        //  Search for a potential hex data string
        render_offset_p = strchr( render_offset_p, '<' );
        tmp_offset_p    = strchr( tmp_offset_p,    '<' );

        //  Did we find a starting character ?
        if(    ( render_offset_p != NULL )
            && ( tmp_offset_p    != NULL ) )
        {
            //  YES:    Is this actually a hex string ?
            if(    ( isxdigit( render_offset_p[ 1 ] ) !=  0  )
                && ( isxdigit( render_offset_p[ 2 ] ) !=  0  )
                && (           render_offset_p[ 3 ]   == '>' ) )
            {
                //  YES:    Convert hex to ASCII
                if(      render_offset_p[ 1 ] <= '0' && render_offset_p[ 1 ] <= '9' )
                    xlate_char = ( render_offset_p[ 1 ] - '0'          ) * 16;
                else if( render_offset_p[ 1 ] <= 'A' && render_offset_p[ 1 ] <= 'F' )
                    xlate_char = ( ( render_offset_p[ 1 ] - 'A' ) + 10 ) * 16;
                else if( render_offset_p[ 1 ] <= 'a' && render_offset_p[ 1 ] <= 'f' )
                    xlate_char = ( ( render_offset_p[ 1 ] - 'a' ) + 10 ) * 16;
                if(      render_offset_p[ 2 ] <= '0' && render_offset_p[ 2 ] <= '9' )
                    xlate_char += render_offset_p[ 2 ] - '0';
                else if( render_offset_p[ 2 ] <= 'A' && render_offset_p[ 2 ] <= 'F' )
                    xlate_char += ( render_offset_p[ 2 ] - 'A' ) + 10;
                else if( render_offset_p[ 2 ] <= 'a' && render_offset_p[ 2 ] <= 'f' )
                    xlate_char += ( render_offset_p[ 2 ] - 'a' ) + 10;

                //  Replace
                render_offset_p[ 0 ] = xlate_char;

                //  Compact
                strcpy( ++render_offset_p, &(tmp_offset_p[ 4 ]) );

                //  Cleanup the end of the buffer
                memset( &(render_p[ strlen( render_p ) ]), '\0', 3 );

                //  Move past the last search match
                tmp_offset_p += 1;
            }
            else
            {
                //  NO:     Keep looking
                render_offset_p += 1;
                tmp_offset_p    += 1;
            }
        }
        else
        {
            //  NO:     No more potential hex strings in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Replace the source data with the rendered data
    memset( src_data_p, '\0', src_data_l );
    memcpy( src_data_p, render_p, src_data_l );

    //  Release the allocated buffer
    mem_free( tmp_p );
    mem_free( render_p );

    //  DONE!
}

/****************************************************************************/
/**
 *  Insert text_data_p into text_buffer_p at text_ndx.
 *
 *  @param  text_buffer_p       Pointer to the data buffer.
 *  @param  text_buffer_l       Size (in bytes) of the text buffer.
 *  @param  text_ndx            Index to insert data.
 *  @param  text_data_p         Pointer to the data to insert.
 *
 *  @return void
 *
 *  @note
 *      If the buffer is not large enough to add insert the new data a
 *      hard fault is thrown.
 *  @note
 *      Sometime in the future I will want to replace the text_ndx with a text
 *      string that is to be replaced.
 *      THIS WILL NOT WORK!
 *      There may be two strings that will match the "search string" and the
 *      second string is the one to be replaced but the first will be located
 *      and replaced in error.
 *
 ****************************************************************************/

void
text_insert(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    int                             text_ndx,
    char                        *   text_data_p
    )
{
    /**
     *  @param  tmp_p           Pointer to a temporary data buffer          */
    char                        *   tmp_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Allocate the temporary data buffer
    tmp_p = mem_malloc( text_buffer_l );

    /************************************************************************
     *  Verify the data will fit
     ************************************************************************/

    //  Is there enough room in the buffer ?
    if ( text_buffer_l < ( strlen( text_buffer_p ) + strlen( text_data_p ) ) )
    {
        //  NO:     This is a fatal error.
        log_write( MID_WARNING, "text_insert", "%s\n",
                   "Text buffer is not large enough for the inserted text" );
        log_write( MID_FATAL, "text_api.c", "Line: %d\n", __LINE__ );
    }

    /************************************************************************
     *  Insert the data
     ************************************************************************/

    //  Are we inserting from the buffer head ?
    if ( text_ndx != 0 )
    {
        //  NO:     Then copy the buffer head to the temporary data buffer.
        memcpy( tmp_p, text_buffer_p, text_ndx );
    }

    //  Insert the new data string into the temporary buffer
    strncat( tmp_p, text_data_p, ( text_buffer_l - strlen( tmp_p ) ) );

    //  Are we inserting a tail to the buffer ?
    if ( text_ndx < strlen( text_buffer_p ) )
    {
        //  NO:     Copy the buffer tail to the temporary data buffer.
        strncat( tmp_p, &text_buffer_p[ text_ndx ],
                 ( text_buffer_l - strlen( tmp_p ) ) );
    }

    //  Wipe the source buffer clean
    memset( text_buffer_p, '\0', text_buffer_l );

    //  Finally, put the new string in the old buffer.
    memcpy( text_buffer_p, tmp_p, strlen( tmp_p ) );

    /************************************************************************
     *  Function Cleanup
     ************************************************************************/

    mem_free( tmp_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Remove text_data_l bytes from text_buffer_p at text_ndx.
 *
 *  @param  text_buffer_p       Pointer to the data buffer.
 *  @param  text_ndx            Index to insert data.
 *  @param  text_remove_l       Number of bytes to remove from the buffer.
 *
 *  @return void
 *
 *  @note
 *      Sometime in the future I will want to replace the text_ndx with a text
 *      string that is to be replaced.
 *      THIS WILL NOT WORK!
 *      There may be two strings that will match the "search string" and the
 *      second string is the one to be replaced but the first will be located
 *      and replaced in error.
 *
 ****************************************************************************/

void
text_remove(
    char                        *   text_buffer_p,
    int                             text_ndx,
    int                             text_remove_l
    )
{
    /**
     *  @param  tmp_p           Pointer to a temporary data buffer          */
    char                        *   tmp_p;
    /**
     *  @param  text_buffer_l   Number of bytes in the text data buffer     */
    int                             text_buffer_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  set the size of the text buffer.
    text_buffer_l = strlen( text_buffer_p );

    //  Allocate the temporary data buffer
    tmp_p = mem_malloc( text_buffer_l + 1 );

    /************************************************************************
     *  Remove the data
     ************************************************************************/

    //  Are we removing from the buffer head ?
    if ( text_ndx != 0 )
    {
        //  NO:     Then copy the buffer head to the temporary data buffer.
        memcpy( tmp_p, text_buffer_p, text_ndx );
    }

    //  Are we removing the tail of the buffer ?
    if ( ( text_ndx + text_remove_l ) < text_buffer_l )
    {
        //  NO:     Copy the buffer tail to the temporary data buffer.
        strncat( &tmp_p[ text_ndx ],
                 &text_buffer_p[ text_ndx + text_remove_l ],
                 ( text_buffer_l - strlen( tmp_p ) ) );
    }

    //  Wipe the source buffer clean
    memset( text_buffer_p, '\0', text_buffer_l );

    //  Finally, put the new string in the old buffer.
    memcpy( text_buffer_p, tmp_p, strlen( tmp_p ) );

    /************************************************************************
     *  Function Cleanup
     ************************************************************************/

    mem_free( tmp_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Insert text_data_p into text_buffer_p at text_ndx.
 *
 *  @param  text_buffer_p       Pointer to the data buffer.
 *  @param  text_buffer_l       Size (in bytes) of the text buffer.
 *  @param  text_ndx            Index to insert data.
 *  @param  text_data_p         Pointer to the data to insert.
 *  @param  text_remove_l       Number of bytes to remove from the buffer.
 *
 *  @return void
 *
 *  @note
 *      If the buffer is not large enough to add insert the new data a
 *      hard fault is thrown.
 *  @note
 *      Sometime in the future I will want to replace the text_ndx with a text
 *      string that is to be replaced.
 *      THIS WILL NOT WORK!
 *      There may be two strings that will match the "search string" and the
 *      second string is the one to be replaced but the first will be located
 *      and replaced in error.
 *
 ****************************************************************************/

void
text_replace(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    int                             text_ndx,
    char                        *   text_data_p,
    int                             text_remove_l
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Insert the data
     ************************************************************************/

    //  Remove the old text
    text_remove( text_buffer_p, text_ndx, text_remove_l );

    //  Insert the new text
    text_insert( text_buffer_p, text_buffer_l, text_ndx, text_data_p );

    /************************************************************************
     *  Function Cleanup
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Center a text string in a buffer
 *
 *  @param  text_buffer_p       Pointer to the data buffer.
 *  @param  text_buffer_l       Size (in bytes) of the text buffer.
 *  @param  text_data_p         Pointer to the data to insert.
 *
 *  @return void
 *
 *  @note
 *
 ****************************************************************************/

void
text_center(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    char                        *   text_data_p
    )
{
    /**
     *  @param  num_of_space    Number of spaces to insert                  */
    int                             num_of_space;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Zero out the destination buffer
    memset( text_buffer_p, '\0', text_buffer_l );
    
    //  The number of leading spaces needed
    num_of_space = ( text_buffer_l - strlen( text_data_p ) / 2 );

    /************************************************************************
     *  Insert the data
     ************************************************************************/

    //  Fill in the leading spaces
    memset( text_buffer_p, ' ', num_of_space );
    
    //  Now append the text.
    strncat( text_buffer_p, text_data_p, ( text_buffer_l - num_of_space ) ); 

    /************************************************************************
     *  Function Cleanup
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
