/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains private functions that makeup the internal
 *  library components of the 'html2txt' library.
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
#include <string.h>             //  Functions for managing strings
#include <ctype.h>              //  Determine the type contained
#include <stdlib.h>             //  ANSI standard library.
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
 * Enumerations local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Definitions local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
#define HTML_TAG_L              (   16 )
#define HTML_TAG_BEG_DEL        ( 0x10 )
#define HTML_TAG_BEG_CRLF       ( 0x20 )
#define HTML_TAG_END_DEL        ( 0x01 )
#define HTML_TAG_END_CRLF       ( 0x02 )
#define HTML_TAG_DEL_CRLF       ( HTML_TAG_BEG_DEL  | HTML_TAG_END_CRLF )
#define HTML_TAG_DEL_DEL        ( HTML_TAG_BEG_DEL  | HTML_TAG_END_DEL  )
#define HTML_TAG_CRLF_DEL       ( HTML_TAG_BEG_CRLF | HTML_TAG_END_DEL  )
#define HTML_TAG_CRLF_CRLF      ( HTML_TAG_BEG_CRLF | HTML_TAG_END_CRLF )
#define HTML_TAG_END            ( 0x00 )
//----------------------------------------------------------------------------

/****************************************************************************
 * Structures local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
struct  html_tag_t
{
    char                        name[ HTML_TAG_L ];
    int                         name_l;
    int                         task;
    int                         count;
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Storage Allocation local to this file
 ****************************************************************************/

//----------------------------------------------------------------------------
struct  html_tag_t              html_tag_list[ ] =
{
    {   "html",          4, HTML_TAG_DEL_DEL,   0   },
    {   "blockquote",   10, HTML_TAG_DEL_DEL,   0   },
    {   "marquee",       7, HTML_TAG_DEL_DEL,   0   },

    {   "frameset",      8, HTML_TAG_DEL_DEL,   0   },
    {   "noframes",      8, HTML_TAG_DEL_DEL,   0   },
    {   "textarea",      8, HTML_TAG_DEL_DEL,   0   },

    {   "marquee",       7, HTML_TAG_DEL_CRLF,  0   },

    {   "option",        6, HTML_TAG_DEL_DEL,   0   },
    {   "select",        6, HTML_TAG_DEL_DEL,   0   },
    {   "source",        6, HTML_TAG_DEL_DEL,   0   },
    {   "strike",        6, HTML_TAG_DEL_DEL,   0   },
    {   "strong",        6, HTML_TAG_DEL_DEL,   0   },

    {   "input",         5, HTML_TAG_DEL_DEL,   0   },
    {   "small",         5, HTML_TAG_DEL_DEL,   0   },
//  {   "style",         5, HTML_TAG_DEL_DEL,   0   },  //  Has it's own function
    {   "table",         5, HTML_TAG_DEL_DEL,   0   },
    {   "tbody",         5, HTML_TAG_DEL_DEL,   0   },

    {   "body",          4, HTML_TAG_DEL_DEL,   0   },
    {   "font",          4, HTML_TAG_DEL_DEL,   0   },
    {   "form",          4, HTML_TAG_DEL_DEL,   0   },
    {   "head",          4, HTML_TAG_DEL_DEL,   0   },
    {   "link",          4, HTML_TAG_DEL_DEL,   0   },
    {   "list",          4, HTML_TAG_DEL_DEL,   0   },
    {   "meta",          4, HTML_TAG_DEL_DEL,   0   },
    {   "nobr",          4, HTML_TAG_DEL_CRLF,  0   },
    {   "span",          4, HTML_TAG_DEL_DEL,   0   },

    {   "div",           3, HTML_TAG_DEL_CRLF,  0   },
    {   "img",           3, HTML_TAG_DEL_DEL,   0   },
    {   "pre",           3, HTML_TAG_DEL_DEL,   0   },
    {   "sub",           3, HTML_TAG_DEL_DEL,   0   },
    {   "sup",           3, HTML_TAG_DEL_DEL,   0   },
    {   "wbr",           3, HTML_TAG_DEL_DEL,   0   },
    {   "!--",           3, HTML_TAG_DEL_DEL,   0   },

    {   "br",            2, HTML_TAG_CRLF_CRLF, 0   },
    {   "dd",            2, HTML_TAG_DEL_DEL,   0   },
    {   "dl",            2, HTML_TAG_DEL_DEL,   0   },
    {   "dt",            2, HTML_TAG_DEL_DEL,   0   },
    {   "em",            2, HTML_TAG_DEL_DEL,   0   },
    {   "h1",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "h2",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "h3",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "h4",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "h5",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "h6",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "hr",            2, HTML_TAG_DEL_DEL,   0   },
    {   "ol",            2, HTML_TAG_DEL_DEL,   0   },
    {   "li",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "ul",            2, HTML_TAG_DEL_DEL,   0   },
    {   "td",            2, HTML_TAG_DEL_DEL,   0   },
    {   "th",            2, HTML_TAG_DEL_DEL,   0   },
    {   "tr",            2, HTML_TAG_DEL_CRLF,  0   },
    {   "tt",            2, HTML_TAG_DEL_DEL,   0   },

    {   "a",             1, HTML_TAG_DEL_DEL,   0   },
    {   "b",             1, HTML_TAG_DEL_DEL,   0   },
    {   "i",             1, HTML_TAG_DEL_DEL,   0   },
    {   "p",             1, HTML_TAG_DEL_CRLF,  0   },
    {   "u",             1, HTML_TAG_DEL_DEL,   0   },
    {   "0000000000",   99, HTML_TAG_END,       0   }
};
//----------------------------------------------------------------------------
/**
 *  @param  html_char           Table with all the translations             */
struct  html_char_t                 html_table[ ] =
{
//  HTML         HEX            Description
//  ENTITY       CODE
    {   "&quot;",    0x22   },  //  '"' - quotation mark
    {   "&num;",     0x23   },  //  '#' - number sign
    {   "&dollar;",  0x24   },  //  '$' - dollar sign
    {   "&percnt;",  0x25   },  //  '%' - percent sign
    {   "&amp;",     0x26   },  //  '&' - ampersand
    {   "&apos;",    0x27   },  //  ''' - apostrophe
    {   "&lpar;",    0x28   },  //  '(' - left parenthesis
    {   "&rpar;",    0x29   },  //  ')' - right parenthesis
    {   "&ast;",     0x2A   },  //  '*' - asterisk
    {   "&plus;",    0x2B   },  //  '+' - plus sign
    {   "&comma;",   0x2C   },  //  ',' - comma
    {   "&minus;",   0x2D   },  //  '-' - hyphen-minus
    {   "&period;",  0x2E   },  //  '.' - full stop; period
    {   "&sol;",     0x2F   },  //  '/' - solidus; slash
    {   "&colon;",   0x3A   },  //  ':' - colon
    {   "&semi;",    0x3B   },  //  ';' - semicolon
    {   "&lt;",      0x3C   },  //  '<' - less-than
    {   "&equals;",  0x3D   },  //  '=' - equals
    {   "&gt;",      0x3E   },  //  '>' - greater-than sign
    {   "&quest;",   0x3F   },  //  '?' - question mark
    {   "&commat;",  0x40   },  //  '@' - at sign; commercial at
    {   "&lsqb;",    0x5B   },  //  '[' - left square bracket
    {   "&bsol;",    0x5C   },  //  '\' - backslash
    {   "&rsqb;",    0x5D   },  //  ']' - right square bracket
    {   "&hat;",     0x5E   },  //  '^' - circumflex accent
    {   "&lowbar;",  0x5F   },  //  '_' - low line
    {   "&grave;",   0x60   },  //  '`' - grave accent
    {   "&lcub;",    0x7B   },  //  '{' - left curly bracket
    {   "&verbar;",  0x7C   },  //  '|' - vertical bar
    {   "&rcub;",    0x7D   },  //  '}' - right curly bracket
    {   "&tilde;",   0x7E   },  //  '~' - tilde
    {   "&nbsp;",    0xC0   },  //  ' ' - no-break space
    {   "&iexcl;",   0xC1   },  //  '¡' - inverted exclamation mark
    {   "&cent;",    0xC2   },  //  '¢' - cent sign
    {   "&pound;",   0xC3   },  //  '£' - pound sterling sign
    {   "&curren;",  0xC4   },  //  '¤' - general currency sign
    {   "&yen;",     0xC5   },  //  '¥' - yen sign
    {   "&brvbar;",  0xC6   },  //  '¦' - broken (vertical) bar
    {   "&sect;",    0xC7   },  //  '§' - section sign
    {   "&uml;",     0xC8   },  //  '¨' - umlaut (dieresis)
    {   "&copy;",    0xC9   },  //  '©' - copyright sign
    {   "&ordf;",    0xCA   },  //  'ª' - ordinal indicator, feminine
    {   "&laquo;",   0xCB   },  //  '«' - angle quotation mark, left
    {   "&not;",     0xCC   },  //  '¬' - not sign
    {   "&shy;",     0xCD   },  //  ' ' - soft hyphen
    {   "&reg;",     0xCE   },  //  '®' - registered sign
    {   "&macr;",    0xCF   },  //  '¯' - macron
    {   "&deg;",     0xB0   },  //  '°' - degree sign
    {   "&plusmn;",  0xB1   },  //  '±' - plus-or-minus sign
    {   "&sup2;",    0xB2   },  //  '²' - superscript two
    {   "&sup3;",    0xB3   },  //  '³' - superscript three
    {   "&acute;",   0xB4   },  //  '´' - acute accent
    {   "&micro;",   0xB5   },  //  'µ' - micro sign
    {   "&para;",    0xB6   },  //  '¶' - pilcrow (paragraph sign)
    {   "&middot;",  0xB7   },  //  ' ' - middle dot
    {   "&cedil;",   0xB8   },  //  '¸' - cedilla
    {   "&sup1;",    0xB9   },  //  '¹' - superscript one
    {   "&ordm;",    0xBA   },  //  'º' - ordinal indicator, masculine
    {   "&raquo;",   0xBB   },  //  '»' - angle quotation mark, right
    {   "&frac14;",  0xBC   },  //  '¼' - fraction one-quarter
    {   "&frac12;",  0xBD   },  //  '½' - fraction one-half
    {   "&frac34;",  0xBE   },  //  '¾' - fraction three-quarters
    {   "&iquest;",  0xBF   },  //  '¿' - inverted question mark
    {   "&agrave;",  0xC0   },  //  'À' - capital A, grave accent
    {   "&aacute;",  0xC1   },  //  'Á' - capital A, acute accent
    {   "&acirc;",   0xC2   },  //  'Â' - capital A, circumflex accent
    {   "&atilde;",  0xC3   },  //  'Ã' - capital A, tilde
    {   "&auml;",    0xC4   },  //  'Ä' - capital A, dieresis or umlaut mark
    {   "&aring;",   0xC5   },  //  'Å' - capital A, ring
    {   "&aElig;",   0xC6   },  //  'Æ' - capital AE diphthong (ligature)
    {   "&ccedil;",  0xC7   },  //  'Ç' - capital C, cedilla
    {   "&egrave;",  0xC8   },  //  'È' - capital E, grave accent
    {   "&eacute;",  0xC9   },  //  'É' - capital E, acute accent
    {   "&ecirc;",   0xCA   },  //  'Ê' - capital E, circumflex accent
    {   "&euml;",    0xCB   },  //  'Ë' - capital E, dieresis or umlaut mark
    {   "&igrave;",  0xCC   },  //  'Ì' - capital I, grave accent
    {   "&iacute;",  0xCD   },  //  'Í' - capital I, acute accent
    {   "&icirc;",   0xCE   },  //  'Î' - capital I, circumflex accent
    {   "&iuml;",    0xCF   },  //  'Ï' - capital I, dieresis or umlaut mark
    {   "&eth;",     0xD0   },  //  'Ð' - capital Eth, Icelandic
    {   "&ntilde;",  0xD1   },  //  'Ñ' - capital N, tilde
    {   "&ograve;",  0xD2   },  //  'Ò' - capital O, grave accent
    {   "&oacute;",  0xD3   },  //  'Ó' - capital O, acute accent
    {   "&ocirc;",   0xD4   },  //  'Ô' - capital O, circumflex accent
    {   "&otilde;",  0xD5   },  //  'Õ' - capital O, tilde
    {   "&ouml;",    0xD6   },  //  'Ö' - capital O, dieresis or umlaut mark
    {   "&times;",   0xD7   },  //  '×' - multiply sign
    {   "&oslash;",  0xD8   },  //  'Ø' - capital O, slash
    {   "&ugrave;",  0xD9   },  //  'Ù' - capital U, grave accent
    {   "&uacute;",  0xDA   },  //  'Ú' - capital U, acute accent
    {   "&ucirc;",   0xDB   },  //  'Û' - capital U, circumflex accent
    {   "&uuml;",    0xDC   },  //  'Ü' - capital U, dieresis or umlaut mark
    {   "&yacute;",  0xDD   },  //  'Ý' - capital Y, acute accent
    {   "&thorn;",   0xDE   },  //  'Þ' - capital THORN, Icelandic
    {   "&szlig;",   0xDF   },  //  'ß' - small sharp s, German (sz ligature)
    {   "&agrave;",  0xE0   },  //  'à' - small a, grave accent
    {   "&aacute;",  0xE1   },  //  'á' - small a, acute accent
    {   "&acirc;",   0xE2   },  //  'â' - small a, circumflex accent
    {   "&atilde;",  0xE3   },  //  'ã' - small a, tilde
    {   "&auml;",    0xE4   },  //  'ä' - small a, dieresis or umlaut mark
    {   "&aring;",   0xE5   },  //  'å' - small a, ring
    {   "&aelig;",   0xE6   },  //  'æ' - small ae diphthong (ligature)
    {   "&ccedil;",  0xE7   },  //  'ç' - small c, cedilla
    {   "&egrave;",  0xE8   },  //  'è' - small e, grave accent
    {   "&eacute;",  0xE9   },  //  'é' - small e, acute accent
    {   "&ecirc;",   0xEA   },  //  'ê' - small e, circumflex accent
    {   "&euml;",    0xEB   },  //  'ë' - small e, dieresis or umlaut mark
    {   "&igrave;",  0xEC   },  //  'ì' - small i, grave accent
    {   "&iacute;",  0xED   },  //  'í' - small i, acute accent
    {   "&icirc;",   0xEE   },  //  'î' - small i, circumflex accent
    {   "&iuml;",    0xEF   },  //  'ï' - small i, dieresis or umlaut mark
    {   "&eth;",     0xF0   },  //  'ð' - small eth, Icelandic
    {   "&ntilde;",  0xF1   },  //  'ñ' - small n, tilde
    {   "&ograve;",  0xF2   },  //  'ò' - small o, grave accent
    {   "&oacute;",  0xF3   },  //  'ó' - small o, acute accent
    {   "&ocirc;",   0xF4   },  //  'ô' - small o, circumflex accent
    {   "&otilde;",  0xF5   },  //  'õ' - small o, tilde
    {   "&ouml;",    0xF6   },  //  'ö' - small o, dieresis or umlaut mark
    {   "&divide;",  0xF7   },  //  '÷' - divide sign
    {   "&oslash;",  0xF8   },  //  'ø' - small o, slash
    {   "&ugrave;",  0xF9   },  //  'ù' - small u, grave accent
    {   "&uacute;",  0xFA   },  //  'ú' - small u, acute accent
    {   "&ucirc;",   0xFB   },  //  'û' - small u, circumflex accent
    {   "&uuml;",    0xFC   },  //  'ü' - small u, dieresis or umlaut mark
    {   "&yacute;",  0xFD   },  //  'ý' - small y, acute accent
    {   "&thorn;",   0xFE   },  //  'þ' - small thorn, Icelandic
    {   "&yuml;",    0xFF   },  //  'ÿ' - small y, dieresis or umlaut mark

    {   "END",       0x00   },  //  'E' - Table end.
};
//----------------------------------------------------------------------------


/****************************************************************************
 * LIB Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Remove Carriage Return & Line Feed
 *
 *  @param  work_p              Pointer to the HTML source buffer.
 *  @param  tmp_p               Pointer to a temporary buffer.
 *  @param  buffer_l            size of both buffers.
 *
 *  @return render_p            Upon successful completion a pointer to
 *                              a buffer containing the rendered text.
 *                              Upon failure, NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

char    *
HTML2TXT__remove_crlf(
    char                        *   html_p,
    char                        *   tmp_p,
    int                             buffer_l
    )
{
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  altered         Flag indicating the buffer was altered      */
    int                             altered;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the return pointer assuming a failure
    render_p = NULL;

    //  Duplicate the HTML buffer into the temporary buffer.
    memcpy( tmp_p, html_p, buffer_l );

    /************************************************************************
     *  Find and remove Carriage Returns
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( html_offset_p, '\r' );
        tmp_offset_p  = strchr( tmp_offset_p,  '\r' );

        //  Did we find a Carriage Return in the buffer ?
        if( html_offset_p != NULL )
        {
            //  YES:    Copy the remaining temporary buffer to the HTML buffer
            tmp_offset_p += 1;
            strncpy( html_offset_p, tmp_offset_p,
                     strlen( tmp_offset_p ) + 1 );
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Find and remove Line Feed
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( html_offset_p, '\n' );
        tmp_offset_p  = strchr( tmp_offset_p,  '\n' );

        //  Did we find a Line Feed in the buffer ?
        if( html_offset_p != NULL )
        {
            //  YES:    Copy the remaining temporary buffer to the HTML buffer
            tmp_offset_p += 1;
            strncpy( html_offset_p, tmp_offset_p,
                     strlen( tmp_offset_p ) + 1 );
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Set the return buffer pointer
    render_p = html_p;

    //  DONE!
    return( render_p );
}

/****************************************************************************/
/**
 *  Remove consecutive spaces leaving only the first space.
 *
 *  @param  work_p              Pointer to the HTML source buffer.
 *  @param  tmp_p               Pointer to a temporary buffer.
 *  @param  buffer_l            size of both buffers.
 *
 *  @return render_p            Upon successful completion a pointer to
 *                              a buffer containing the rendered text.
 *                              Upon failure, NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

char    *
HTML2TXT__remove_spaces(
    char                        *   html_p,
    char                        *   tmp_p,
    int                             buffer_l
    )
{
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  altered         Flag indicating the buffer was altered      */
    int                             altered;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the return pointer assuming a failure
    render_p = NULL;

    //  Duplicate the HTML buffer into the temporary buffer.
    memcpy( tmp_p, html_p, buffer_l );

    /************************************************************************
     *  Remove consecutive spaces
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( html_offset_p, ' ' );
        tmp_offset_p  = strchr( tmp_offset_p,  ' ' );

        //  Did we find a space in the buffer ?
        if( html_offset_p != NULL )
        {
            //  YES:    Is the next character also a space ?
            if( html_offset_p[ 1 ] == ' ' )
            {
                //  YES:    Find the last consecutive space in the work buffer
                for( tmp_offset_p += 1;
                     tmp_offset_p[ 0 ] == ' ';
                     tmp_offset_p += 1 )
                {
                    //  Nothing to do here; the above statement will walk
                    //  the pointer to the next non-space character.
                }
                //  Copy the remaining temporary buffer to the HTML buffer
                html_offset_p += 1;
                strncpy( html_offset_p, tmp_offset_p, strlen( tmp_offset_p ) + 1 );
            }
            else
            {
                //  NO:     Move the pointers past the space.
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Remove redundant spaces
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the end of a HTML tag in both buffers.
        html_offset_p = strchr( html_offset_p, '>' );
        tmp_offset_p  = strchr( tmp_offset_p,  '>' );

        //  Did we find a space in the buffer ?
        if( html_offset_p != NULL )
        {
            //  YES:    Is the next character a space ?
            if( html_offset_p[ 1 ] == ' ' )
            {
                //  YES:    Find the last consecutive space in the work buffer
                for( tmp_offset_p += 1;
                     tmp_offset_p[ 0 ] == ' ';
                     tmp_offset_p += 1 )
                {
                    //  Nothing to do here; the above statement will walk
                    //  the pointer to the next non-space character.
                }
                //  Copy the remaining temporary buffer to the HTML buffer
                html_offset_p += 1;
                strncpy( html_offset_p, tmp_offset_p, strlen( tmp_offset_p ) + 1 );
            }
            else
            {
                //  NO:     Move the pointers past the space.
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Cleanup HTML
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the end of a HTML tag in both buffers.
        html_offset_p = strchr( html_offset_p, '<' );
        tmp_offset_p  = strchr( tmp_offset_p,  '<' );

        //  Did we find a space in the buffer ?
        if( html_offset_p != NULL )
        {
            //  YES:    Is the next character a space ?
            if( html_offset_p[ 1 ] == ' ' )
            {
                //  YES:    Find the last consecutive space in the work buffer
                for( tmp_offset_p += 1;
                     tmp_offset_p[ 0 ] == ' ';
                     tmp_offset_p += 1 )
                {
                    //  Nothing to do here; the above statement will walk
                    //  the pointer to the next non-space character.
                }
                //  Copy the remaining temporary buffer to the HTML buffer
                html_offset_p += 1;
                strncpy( html_offset_p, tmp_offset_p, strlen( tmp_offset_p ) + 1 );
            }
            else
            {
                //  NO:     Move the pointers past the space.
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Set the return buffer pointer
    render_p = html_p;

    //  DONE!
    return( render_p );
}

/****************************************************************************/
/**
 *  Remove HTML tags from the buffer
 *
 *  @param  work_p              Pointer to the HTML source buffer.
 *  @param  tmp_p               Pointer to a temporary buffer.
 *  @param  buffer_l            size of both buffers.
 *
 *  @return render_p            Upon successful completion a pointer to
 *                              a buffer containing the rendered text.
 *                              Upon failure, NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

char    *
HTML2TXT__remove_style(
    char                        *   html_p,
    char                        *   tmp_p,
    int                             buffer_l
    )
{
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  altered         Flag indicating the buffer was altered      */
    int                             altered;
    /**
     *  @param  compare_beg     A buffer with lower case data to compare to */
    char                            compare_beg[ 10 ];
    /**
     *  @param  compare_end     A buffer with lower case data to compare to */
    char                            compare_end[ 10 ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the return pointer assuming a failure
    render_p = NULL;

    //  Duplicate the HTML buffer into the temporary buffer.
    memcpy( tmp_p, html_p, buffer_l );

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( html_offset_p, '<' );
        tmp_offset_p  = strchr( tmp_offset_p,  '<' );

        //  Did we find the start of a tag in the buffer ?
        if( html_offset_p != NULL )
        {
            //  Fill the compare buffer from the HTML buffer
            memset( compare_beg, '\0', sizeof( compare_beg ) );
            memcpy( compare_beg, html_offset_p, ( sizeof( compare_beg ) - 1 ) );
            text_to_lowercase( compare_beg );

            //  Is this a tag that needs to be changed ?
            if(    ( strncmp( compare_beg, "<style>",        7 ) == 0 )
                || ( strncmp( compare_beg, "<style ",        7 ) == 0 ) )
            {
                //  YES:    Locate the end of the style block
                tmp_offset_p += 1;
                tmp_offset_p  = strchr( tmp_offset_p,  '<' );

                //  Fill the compare buffer from the HTML buffer
                memset( compare_end, '\0', sizeof( compare_end ) );
                memcpy( compare_end, tmp_offset_p, ( sizeof( compare_end ) - 1 ) );
                text_to_lowercase( compare_end );

                //  Did we locate the end tag ?
                if( strncmp( compare_end, "</style>", 8 ) == 0 )
                {
                    //  YES:    Now find the end of the end tag
                    tmp_offset_p = strchr( tmp_offset_p, '>' );

                    //  Copy the remaining temporary buffer to the HTML buffer
                    tmp_offset_p += 1;
                    strncpy( html_offset_p,
                             tmp_offset_p,
                             strlen( tmp_offset_p ) + 1 );
                }
            }
            else
            {
                //  NO:     Move the pointers past the space.
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     There are no more spaces in the buffer
            altered = false;
        }

    }   while( altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Set the return buffer pointer
    render_p = html_p;

    //  DONE!
    return( render_p );
}

/****************************************************************************/
/**
 *  Find and convert to text HTML tags.
 *
 *  @param  work_p              Pointer to the HTML source buffer.
 *  @param  tmp_p               Pointer to a temporary buffer.
 *  @param  buffer_l            size of both buffers.
 *
 *  @return render_p            Upon successful completion a pointer to
 *                              a buffer containing the rendered text.
 *                              Upon failure, NULL is returned.
 *
 *  @note
 *
 ****************************************************************************/

char    *
HTML2TXT__tag_scan(
    char                        *   html_p,
    char                        *   tmp_p,
    int                             buffer_l
    )
{
    /**
     *  @param  render_p        Pointer to the rendered text                */
    char                        *   render_p;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  altered         Flag indicating the buffer was altered      */
    int                             altered;
    /**
     *  @param  html_tag        A buffer holding the HTML tag from the array*/
    char                            html_tag[ 32 ];
    /**
     *  @param  compare         A buffer with lower case data to compare to */
    char                            compare[ 32 ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the return pointer assuming a failure
    render_p = NULL;

    //  Duplicate the HTML buffer into the temporary buffer.
    memcpy( tmp_p, html_p, buffer_l );

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    /************************************************************************
     *  Function
     ************************************************************************/

    //  Loop through the buffer as many times as needed.
    do
    {
        //  Assume there is more to do.
        altered = true;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( html_offset_p, '<' );
        tmp_offset_p  = strchr( tmp_offset_p,  '<' );

        //  Did we find the start of a tag in the buffer ?
        if( html_offset_p != NULL )
        {
            /**
             *  @param  ndx             Index into the array table          */
            int                             ndx;
            /**
             *  @param  type            HTML tag type to build              */
            int                             format;
            /**
             *  @param  found           Flag showing if the tag was found   */
            int                             found;
            /**
             *  @param  process_type    Identifies what to do with the tag  */
            int                             process_type;

            //  Fill the compare buffer from the HTML buffer
            memset( compare, '\0', sizeof( compare ) );
            memcpy( compare, html_offset_p, ( sizeof( compare ) - 1 ) );
            text_to_lowercase( compare );

            //  Initialize the table index.
            ndx = 0;

            //  Search for a match for this {possible} tag
            do
            {
                //  The assumption is that the tag is not located.
                found = false;

                //  Search the array using the three tag format types
                for( format = 0; format < 3; format += 1 )
                {
                    //  Clean out the HTML tag buffer
                    memset( html_tag, '\0', sizeof( html_tag ) );

                    //  What type of tag are we working with ?
                    switch( format )
                    {
                        case    0:      //  Start                   <html>
                        {
                            snprintf( html_tag, sizeof( html_tag ),
                                      "<%s>", html_tag_list[ ndx ].name );
                        }   break;

                        case    1:      //  Open ended start        <html ...>
                        {
                            snprintf( html_tag, sizeof( html_tag ),
                                      "<%s ", html_tag_list[ ndx ].name );
                        }   break;

                        case    2:      //  End                     </html>
                        {
                            snprintf( html_tag, sizeof( html_tag ),
                                      "</%s>", html_tag_list[ ndx ].name );
                        }   break;
                    }

                    //  Does this tag match the one from the buffer ?
                    if( strncmp( compare, html_tag, strlen( html_tag ) ) == 0 )
                    {
                        //  YES:    Increment the number of times found
                        html_tag_list[ ndx ].count += 1;

                        //  Change the found tag so we can move on to..
                        found = true;

                        //  Stop searching
                        break;
                    }
                }

                //  Did we locate the tag in our table ?
                if( found == false )
                {
                    //  NO:     move on to the next tag in the table
                    ndx += 1;

                    //  Did we reach the end of the tag list ?
                    if( html_tag_list[ ndx ].task == HTML_TAG_END )
                    {
                        //  Move the pointer past the start
                        html_offset_p += 1;
                        tmp_offset_p  += 1;

                        //  YES:    This tag isn't in the list
                        break;
                    }
                }

            }   while( found == false );

            //  Was a match for the tag located ?
            if( found == true )
            {
                //  YES:    What should we do with the source data ?
                if( format == 0 || format == 1 )
                {
                    process_type = ( html_tag_list[ ndx ].task >> 4 ) & 0x0F;
                }
                else
                {
                    process_type =   html_tag_list[ ndx ].task        & 0x0F;
                }

                //  YES:    What should we do with it ?
                switch( process_type )
                {
                    case    HTML_TAG_END_DEL:
                    {
                        //  Locate the end of the tag
                        tmp_offset_p = strchr( tmp_offset_p, '>' );

                        //  Copy the remaining temporary buffer to the HTML buffer
                        tmp_offset_p += 1;
                        strncpy( html_offset_p,
                                 tmp_offset_p,
                                 strlen( tmp_offset_p ) + 1 );
                    }   break;

                    case    HTML_TAG_END_CRLF:
                    {
                        //  Insert a Carriage Return
                        html_offset_p[ 0 ] = '\n';

                        //  Locate the end of the tag
                        tmp_offset_p  = strchr( tmp_offset_p,  '>' );

                        //  Copy the remaining temporary buffer to the HTML buffer
                        html_offset_p += 1;
                        tmp_offset_p += 1;
                        strncpy( html_offset_p,
                                 tmp_offset_p,
                                 strlen( tmp_offset_p ) + 1 );
                    }   break;
                }
            }
        }
        else
        {
            //  NO:     We are at the end of the buffer
            altered = false;
        }

    }   while(  altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Set the return buffer pointer
    render_p = html_p;

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
HTML2TXT__str_2_char(
    char                        *   html_p
    )
{
    /**
     *  @param  altered         The HTML buffer was altered in this pass    */
    int                             altered;
    /**
     *  @param  html_table_ndx  Index into the HTML conversion table        */
    int                             html_table_ndx;
    /**
     *  @param  tmp_p           Pointer to a temporary data buffer          */
    char                        *   tmp_p;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  compare         A place to put a lowercase version          */
    char                            compare[ 10 ];
    /**
     *  @param  value           HTML code value                             */
    int                             value;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Allocate the work buffer
    tmp_p = mem_malloc( strlen( html_p ) + 1 );

    //  Duplicate the html buffer in the temporary buffer
    memcpy( tmp_p, html_p, strlen( html_p ) );

    /************************************************************************
     *  Look for character strings 'Entity', 'HTML code', or 'HTML hex code'
     ************************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    while( 1 )
    {
        //  Initialize the flag
        altered = false;

        //  Locate the start of a Character Name string
        html_offset_p = strchr( html_offset_p, '&' );
        tmp_offset_p  = strchr( tmp_offset_p,  '&' );

        //  Did we find it ?
        if( html_offset_p != NULL )
        {

            /****************************************************************
             *  HTML Entity string
             ****************************************************************/

            //  YES:    Fill the compare buffer from the HTML buffer
            memset( compare, '\0', sizeof( compare ) );
            memcpy( compare, html_offset_p, ( sizeof( compare ) - 1 ) );
            text_to_lowercase( compare );

            //  Loop through all entries in the HTML conversion table
            for( html_table_ndx = 0;
                 html_table[ html_table_ndx ].hex_code != 0;
                 html_table_ndx += 1 )
            {

                //  Is the string a match to HTML or Numeric ?
                if( strncmp( compare,
                             html_table[ html_table_ndx ].html_entity,
                             strlen( html_table[ html_table_ndx ].html_entity ) ) == 0 )
                {
                    //  YES:    Replace the string
                    html_offset_p[ 0 ] = html_table[ html_table_ndx ].hex_code;

                    //  Look for the end of the string
                    tmp_offset_p  = strchr( tmp_offset_p,  ';' );

                    //  Overlay the remainder of the string
                    html_offset_p += 1;
                    tmp_offset_p += 1;
                    strncpy( html_offset_p,
                             tmp_offset_p,
                             strlen( tmp_offset_p ) + 1 );

                    //  Change the flag showing the buffer is altered
                    altered = true;

                    //  This one is done
                    break;
                }
            }

            //  Already done ?
            if( altered == false )
            {

                /************************************************************
                 *  HTML Code string
                 ************************************************************/

                //  NO:     Is this decimal code ?
                if(    (    (          html_offset_p[ 1 ]   ==  '#' )
                         && ( isdigit( html_offset_p[ 2 ] ) !=   0  )
                         && ( isdigit( html_offset_p[ 3 ] ) !=   0  )
                         && (          html_offset_p[ 4 ]   ==  ';' ) )
                    || (    (          html_offset_p[ 1 ]   ==  '#' )
                         && ( isdigit( html_offset_p[ 2 ] ) !=   0  )
                         && ( isdigit( html_offset_p[ 3 ] ) !=   0  )
                         && ( isdigit( html_offset_p[ 4 ] ) !=   0  )
                         && (          html_offset_p[ 5 ]   ==  ';' ) ) )
                {
                    //  NO:     Get the decimal value
                    value = atoi( &(html_offset_p[ 2 ] ) );

                    //  Store the hex character
                    html_offset_p[ 0 ] = (char)value;

                    //  Look for the end of the string
                    tmp_offset_p  = strchr( tmp_offset_p,  ';' );

                    //  Copy the remaining temporary buffer to the HTML buffer
                    html_offset_p += 1;
                    tmp_offset_p += 1;
                    strncpy( html_offset_p,
                             tmp_offset_p,
                             strlen( tmp_offset_p ) + 1 );

                    //  Change the flag showing the buffer is altered
                    altered = true;
                }

                /************************************************************
                 *  HTML HEX Code string
                 ************************************************************/

                else
                if(    (           html_offset_p[ 1 ]   ==  '#' )
                    && ( tolower(  html_offset_p[ 2 ] ) ==  'x' )
                    && ( isxdigit( html_offset_p[ 3 ] ) !=   0  )
                    && ( isxdigit( html_offset_p[ 4 ] ) !=   0  )
                    && (           html_offset_p[ 5 ]   ==  ';' ) )
                {
                    //  YES:    Null terminate the hex string
                    //  @note   The remainder of the text is going to be overlayed
                    //          with the left-shift.
                    html_offset_p[ 5 ] = '\0';

                    //  Get the hex value
                    sscanf( &(html_offset_p[ 3 ]), "%X", &value );

                    //  Write the character into the string.
                    html_offset_p[ 0 ] = (char)value;

                    //  Look for the end of the string
                    tmp_offset_p  = strchr( tmp_offset_p,  ';' );

                    //  Copy the remaining temporary buffer to the HTML buffer
                    html_offset_p += 1;
                    tmp_offset_p += 1;
                    strncpy( html_offset_p,
                             tmp_offset_p,
                             strlen( tmp_offset_p ) + 1 );

                    //  Change the flag showing the buffer is altered
                    altered = true;
                }
            }

            //  Did we find something to alter ?
            if( altered == false )
            {
                //  YES:    Advance the pointer to continue the search
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     No (more) ampersands in the buffer
            break;
        }

    }

    /********************************************************************
     *  UNICODE Strings
     ********************************************************************/

    //  Initialize the pointers
    html_offset_p = html_p;
    tmp_offset_p = tmp_p;

    while( 1 )
    {
        //  Initialize the flag
        altered = false;

        //  Locate the start of a Character Name string
        html_offset_p = strchr( html_offset_p, '+' );
        tmp_offset_p  = strchr( tmp_offset_p,  '+' );

        //  Did we find it ?
        if(    ( html_offset_p != NULL )
            && ( tmp_offset_p  != NULL ) )
        {
            //  YES:    Fill the compare buffer from the HTML buffer
            memset( compare, '\0', sizeof( compare ) );
            memcpy( compare, &(html_offset_p[ -1 ]), ( sizeof( compare ) - 1 ) );
            text_to_uppercase( compare );

            //  Is the previous character a "U"
            if( compare[ 0 ] ==  'U' )
            {
                //  The next two characters MUST be digits.
                if(    ( isxdigit( html_offset_p[ 1 ] ) != 0 )
                    && ( isxdigit( html_offset_p[ 2 ] ) != 0 ) )
                {
                    //  YES:    Fix the offset pointers
                    html_offset_p -= 1;
                    tmp_offset_p  += 3;

                    //  Null terminate the hex string
                    //  @note   The remainder of the text is going to be
                    //          overlay with the left-shift.
                    if( isxdigit( compare[ 4 ] ) == 0 )
                    {
                        html_offset_p[ 4 ] = '\0';
                    }
                    else
                    if( isxdigit( compare[ 5 ] ) == 0 )
                    {
                        html_offset_p[ 5 ] = '\0';
                    }
                    else
                    if( isxdigit( compare[ 6 ] ) == 0 )
                    {
                        html_offset_p[ 6 ] = '\0';
                    }
                    else
                    if( isxdigit( compare[ 7 ] ) == 0 )
                    {
                        html_offset_p[ 7 ] = '\0';
                    }

                    //  Get the hex value
                    sscanf( &(html_offset_p[ 2 ]), "%X", &value );

                    //  Store the character
                    html_offset_p[ 0 ] = (char)value;

                    //  Copy the remaining temporary buffer to the HTML buffer
                    html_offset_p += 1;
                    tmp_offset_p += 1;
                    strncpy( html_offset_p,
                             tmp_offset_p,
                             strlen( tmp_offset_p ) + 1 );

                    //  Change the flag showing the buffer is altered
                    altered = true;
                }
            }

            //  Was anything altered ?
            if( altered == false )
            {
                //  NO:     Move the pointers past the space.
                html_offset_p += 1;
                tmp_offset_p  += 1;
            }
        }
        else
        {
            //  NO:     Nothing else to compare to
            break;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Release the temporary buffer
    mem_free( tmp_p );

    //  DONE!
}

/****************************************************************************/
