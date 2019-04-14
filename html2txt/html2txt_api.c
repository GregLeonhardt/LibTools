/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains public function that makeup the external
 *  library components of the 'html2txt' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_HTML2TXT          ( "ALLOCATE STORAGE FOR HTML2TXT" )

/****************************************************************************
 * System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <string.h>             //  Functions for managing strings
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  My Tools Library
                                //*******************************************
#include "html2txt_lib.h"       //  API for all HTML2TXT__*         PRIVATE
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
 *  The html2txt function will remove all HTML tags rendering the text output.
 *
 *  @param  html_p              Pointer to the HTML source buffer.
 *
 *  @return render_p            Upon successful completion a pointer to
 *                              a buffer containing the rendered text.
 *                              Upon failure, NULL is returned.
 *
 *  @note
 *      For this function to properly work, the entire HTML page must be
 *      passed in a single buffer.
 *
 *  @note
 *      The return is a pointer to a new buffer containing the rendered
 *      output.  The buffer was allocated by this function and must eventually
 *      be released by the caller.
 *
 *  @note
 *      The source data buffer will remain unaltered by this function.
 *
 ****************************************************************************/

char    *
html2txt(
    char                        *   html_p
    )
{
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  work_p          Pointer to a work buffer                    */
    char                        *   work_p;
    /**
     *  @param  tmp_p           Pointer to a temporary buffer               */
    char                        *   tmp_p;
    /**
     *  @parm   html_l          Size of the HTML data string                */
    int                             html_l;
    /**
     *  @parm   work_l          Size of the work data string                */
    int                             work_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the return pointer assuming a failure
    render_p = NULL;

    //  Get the size of the HTML buffer
    html_l = strlen( html_p );

    //  Set the size of the work buffer
    work_l = html_l * 2;

    //  Allocate the work buffer
    work_p = mem_malloc( work_l + 1 );
    log_write( MID_DEBUG_1, "html2txt_api.c", "Line: %d\n", __LINE__ );

    //  Allocate the temporary buffer
    tmp_p = mem_malloc( work_l + 1 );
    log_write( MID_DEBUG_1, "html2txt_api.c", "Line: %d\n", __LINE__ );

    //  Copy the source data buffer to the work data buffer.
    memcpy( work_p, html_p, html_l );

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Delete CR & LF
    work_p = HTML2TXT__remove_crlf( work_p, tmp_p, work_l );

    //  Delete consecutive spaces
    work_p = HTML2TXT__remove_spaces( work_p, tmp_p, work_l );

    //  Delete HTML style
    work_p = HTML2TXT__remove_style( work_p, tmp_p, work_l );

    //  Delete HTML tags
    work_p = HTML2TXT__tag_scan( work_p, tmp_p, work_l );

    //  Convert HTML and UNICODE strings to characters.
    HTML2TXT__str_2_char( work_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Set the return buffer pointer
    render_p = work_p;

    //  We are done with the temporary buffer so release it.
    mem_free( tmp_p );

    //  DONE!
    return( render_p );
}

/****************************************************************************/
/**
 *  The html_str_2_char function will search a buffer for a HTML special
 *  character string [example &equals;] and replace it in the buffer with
 *  the character it represents.  In this example it will be a '=' equal
 *  sign.
 *
 *  @param  html_p              Pointer to the HTML source buffer.
 *
 *  @return count               Number of character conversions that occurred.
 *
 *  @note
 *      The conversion will always take a string of at minimum four (4)
 *      characters and reduce it to a single character resulting in the
 *      buffer containing fewer characters after the conversion.
 *
 ****************************************************************************/

void
html2txt_str_2_char(
    char                        *   html_p
    )
{
    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Call the internal function
    HTML2TXT__str_2_char( html_p );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
