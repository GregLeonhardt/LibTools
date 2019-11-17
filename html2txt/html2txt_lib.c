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

#define _GNU_SOURCE

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
    {   "html",          4, HTML_TAG_DEL_DEL,   0   },  //  00
    {   "blockquote",   10, HTML_TAG_DEL_DEL,   0   },  //  01
    {   "marquee",       7, HTML_TAG_DEL_DEL,   0   },  //  02

    {   "frameset",      8, HTML_TAG_DEL_DEL,   0   },  //  03
    {   "noframes",      8, HTML_TAG_DEL_DEL,   0   },  //  04
    {   "textarea",      8, HTML_TAG_DEL_DEL,   0   },  //  05

    {   "marquee",       7, HTML_TAG_DEL_CRLF,  0   },  //  06

    {   "option",        6, HTML_TAG_DEL_DEL,   0   },  //  07
    {   "select",        6, HTML_TAG_DEL_DEL,   0   },  //  08
    {   "source",        6, HTML_TAG_DEL_DEL,   0   },  //  09
    {   "strike",        6, HTML_TAG_DEL_DEL,   0   },  //  10
    {   "strong",        6, HTML_TAG_DEL_DEL,   0   },  //  11
    {   "center",        6, HTML_TAG_DEL_DEL,   0   },  //  12

    {   "input",         5, HTML_TAG_DEL_DEL,   0   },  //  13
    {   "small",         5, HTML_TAG_DEL_DEL,   0   },  //  14
//  {   "style",         5, HTML_TAG_DEL_DEL,   0   },  //      Has it's own function
    {   "table",         5, HTML_TAG_DEL_DEL,   0   },  //  15
    {   "tbody",         5, HTML_TAG_DEL_DEL,   0   },  //  16

    {   "body",          4, HTML_TAG_DEL_DEL,   0   },  //  17
    {   "font",          4, HTML_TAG_DEL_DEL,   0   },  //  18
    {   "form",          4, HTML_TAG_DEL_DEL,   0   },  //  19
    {   "head",          4, HTML_TAG_DEL_DEL,   0   },  //  20
    {   "link",          4, HTML_TAG_DEL_DEL,   0   },  //  21
    {   "list",          4, HTML_TAG_DEL_DEL,   0   },  //  22
    {   "meta",          4, HTML_TAG_DEL_DEL,   0   },  //  23
    {   "nobr",          4, HTML_TAG_DEL_CRLF,  0   },  //  24
    {   "span",          4, HTML_TAG_DEL_DEL,   0   },  //  25

    {   "div",           3, HTML_TAG_DEL_CRLF,  0   },  //  26
    {   "img",           3, HTML_TAG_DEL_DEL,   0   },  //  27
    {   "pre",           3, HTML_TAG_DEL_DEL,   0   },  //  28
    {   "sub",           3, HTML_TAG_DEL_DEL,   0   },  //  29
    {   "sup",           3, HTML_TAG_DEL_DEL,   0   },  //  30
    {   "wbr",           3, HTML_TAG_DEL_DEL,   0   },  //  31
//  {   "!--",           3, HTML_TAG_DEL_DEL,   0   },  //      Has it's own function

    {   "br",            2, HTML_TAG_CRLF_CRLF, 0   },  //  32
    {   "dd",            2, HTML_TAG_DEL_DEL,   0   },  //  33
    {   "dl",            2, HTML_TAG_DEL_DEL,   0   },  //  34
    {   "dt",            2, HTML_TAG_DEL_DEL,   0   },  //  35
    {   "em",            2, HTML_TAG_DEL_DEL,   0   },  //  36
    {   "h1",            2, HTML_TAG_DEL_CRLF,  0   },  //  37
    {   "h2",            2, HTML_TAG_DEL_CRLF,  0   },  //  38
    {   "h3",            2, HTML_TAG_DEL_CRLF,  0   },  //  39
    {   "h4",            2, HTML_TAG_DEL_CRLF,  0   },  //  40
    {   "h5",            2, HTML_TAG_DEL_CRLF,  0   },  //  41
    {   "h6",            2, HTML_TAG_DEL_CRLF,  0   },  //  42
    {   "hr",            2, HTML_TAG_DEL_DEL,   0   },  //  43
    {   "ol",            2, HTML_TAG_DEL_DEL,   0   },  //  44
    {   "li",            2, HTML_TAG_DEL_CRLF,  0   },  //  45
    {   "ul",            2, HTML_TAG_DEL_DEL,   0   },  //  46
    {   "td",            2, HTML_TAG_DEL_DEL,   0   },  //  47
    {   "th",            2, HTML_TAG_DEL_DEL,   0   },  //  48
    {   "tr",            2, HTML_TAG_DEL_CRLF,  0   },  //  49
    {   "tt",            2, HTML_TAG_DEL_DEL,   0   },  //  50

    {   "a",             1, HTML_TAG_DEL_DEL,   0   },  //  51
    {   "b",             1, HTML_TAG_DEL_DEL,   0   },  //  52
    {   "i",             1, HTML_TAG_DEL_DEL,   0   },  //  53
    {   "p",             1, HTML_TAG_CRLF_CRLF, 0   },  //  54
    {   "u",             1, HTML_TAG_DEL_DEL,   0   },  //  55
    {   "0000000000",   99, HTML_TAG_END,       0   }   //  56
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
 *  Locate the end of the current tag.
 *
 *  @param  html_p              Pointer to the HTML source buffer.
 *
 *  @return tag_end_p           Upon successful completion a pointer to
 *                              The last character of a tag, else NULL
 *                              is returned.
 *
 *  @note
 *
 ****************************************************************************/

char    *
HTML2TXT__locate_tag_end(
    char                        *   html_p
    )
{
    /**
     *  @param  tag_end_p       Tag End pointer                             */
    char                        *   tag_end_p;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the starting point
    tag_end_p = html_p;

    /************************************************************************
     *  Find and remove Carriage Returns
     ************************************************************************/

    //  Is this a comment tag ?
    if ( strncmp( html_p, "<!--", 4 ) == 0 )
    {
        //  Find the end of the comment.
        tag_end_p = strstr( html_p, "-->" );

        //  Locate the tag end character
        tag_end_p = strchr( tag_end_p, '>' );

    }
    else
    {
        //  NO:     Lets find the end
        tag_end_p = strchr( html_p, '>' );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( tag_end_p );
}

/****************************************************************************/
/**
 *  Test the current string for a valid HTML tag.  When a valid HTML tag is
 *  discovered, unneeded spaces are removed.
 *
 *  @param  html_p              Pointer to the beginning of the HTML buffer.
 *  @param  tag_p               Pointer to the beginning of the possible tag.
 *  @param  format              0 & 1 = Start tag, 2 = end tag.
 *
 *  @return tag_start_p         When 'tag_p' is pointing to a valid HTML tag
 *                              a pointer to the first character of the tag
 *                              is returned.  Else NULL is returned.
 *
 *  @note
 *      Format 0    -   <tag>
 *      Format 1    -   <tag ... >
 *      Format 3    -   </tag>
 *
 ****************************************************************************/

char    *
HTML2TXT__tag_clean(
    char                        *   html_p,
    char                        *   tag_start_p,
    int                             tag_l,
    int                             format
    )
{
    /**
     *  @param  tmp_start_p     Pointer to the start of the tag             */
    char                        *   tmp_start_p;
    /**
     *  @param  tmp_end_p       Pointer to the end of the tag               */
    char                        *   tmp_end_p;
    /**
     *  @param  delete_offset   Offset to data to be removed.               */
    int                             delete_offset;
    /**
     *  @param  end_offset      Offset to end of the tag.                   */
    int                             end_offset;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the default delete offset.
    delete_offset = 1;

    //  Set the default end offset.
    end_offset = 1;

    /************************************************************************
     *  Remove spaces from the start of a tag.
     ************************************************************************/

    for ( tmp_start_p = &tag_start_p[ -1 ];
          tmp_start_p >= html_p;
          tmp_start_p -= 1 )
    {
        //  Is this a blank character ?
        if ( isblank( tmp_start_p[ 0 ] ) == 0 )
        {
            //  NO:     We are done looking
            break;
        }
    }

    //  Could this be a HTML end-tag ?
    if (    ( format               == 2   )
         && ( tmp_start_p[ 0 ] == '/' ) )
    {
        //  YES:    Are there blank characters to be removed ?
        if ( ( tag_start_p - tmp_start_p ) > delete_offset )
        {
            //  YES:    Remove them
            text_remove( tmp_start_p, delete_offset,
                         ( tag_start_p - tmp_start_p - 1 ) );
        }
        //  Clean between '<' and '/' ?
        tmp_start_p = HTML2TXT__tag_clean( html_p, tmp_start_p, tag_l, -1 );
    }

    //  Is this a valid HTML start tag ?
    else
    if ( tmp_start_p[ 0 ] == '<' )
    {
        //  YES:    Are there blank characters to be removed ?
        if ( ( tag_start_p - tmp_start_p ) > delete_offset )
        {
            //  YES:    Remove them
            text_remove( tmp_start_p, delete_offset,
                         ( tag_start_p - tmp_start_p - 1 ) );
        }
    }
    else
    {
        //  NO:     Not a valid HTML tag
        tmp_start_p = NULL;
    }

    /************************************************************************
     *  Remove spaces from the end of a tag.
     ************************************************************************/

    //  Should we remove spaces from the end of the tag ?
    if(    ( tmp_start_p != NULL )
        && (    ( format == 0 )
             || ( format == 2 ) ) )
    {
        //  YES:    Is this a format 2 tag search
        if ( format == 2 )
        {
            //  YES:    Increase the end offset
            end_offset += 1;
        }

        //  YES:
        for ( tmp_end_p = &tmp_start_p[ tag_l + end_offset ];
              tmp_end_p[ 0 ] != '\0';
              tmp_end_p += 1 )
        {
            //  Is this a blank character ?
            if ( isblank( tmp_end_p[ 0 ] ) == 0 )
            {
                //  NO:     We are done looking
                break;
            }
        }

        //  Is this a valid HTML start tag ?
        if ( tmp_end_p[ 0 ] == '>'  )
        {
            //  YES:    Are there blank characters to be removed ?
            if ( ( tmp_end_p - &tmp_start_p[ tag_l + end_offset ] ) > 1 )
            {
                //  YES:    Remove them
                text_remove( tmp_start_p, ( tag_l + end_offset ),
                            ( tmp_end_p - &tmp_start_p[ tag_l + end_offset ] ) );
            }
        }
        else
        {
            //  NO:     Not a valid HTML tag
            tmp_start_p = NULL;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( tmp_start_p );
}

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
        if ( html_offset_p != NULL )
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
        if ( html_offset_p != NULL )
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
 *  Remove HTML comments <!-- through -->
 *
 *  @param  html_p              Pointer to the HTML source buffer.
 *
 *  @return void                There is no return code for this function.
 *
 *  @note
 *
 ****************************************************************************/

void
HTML2TXT__remove_comments(
    char                        *   html_p
    )
{
    /**
     *  @param  comment_start_p Pointer to the start of a comment.          */
    char                        *   comment_start_p;
    /**
     *  @param  comment_end_p   Pointer to the end of a comment.            */
    char                        *   comment_end_p;
    /**
     *  @param  comment_l       Size of the comment string.                 */
    int                             comment_l;
    /**
     *  @param  found           Flag indicating a blank character was found */
    int                             found;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the start of the buffer
    comment_start_p = html_p;

    /************************************************************************
     *  Remove consecutive spaces
     ************************************************************************/

    //  Loop through the buffer as many times as needed.
    do
    {
        //  The assumption is that we ar done here.
        found = false;

        //  Scan the HTML buffer for the start of a comment
        comment_start_p = strstr( comment_start_p, "<!--" );

        //  Did we find a comment start ?
        if( comment_start_p != NULL )
        {
            //  YES:    Scan the HTML buffer for the end of a comment
            comment_end_p = strstr( comment_start_p, "-->" );

            //  Did we find a comment end ?
            if ( comment_end_p != NULL )
            {
                //  YES:    Set the comment size
                comment_l = ( (comment_end_p - comment_start_p ) + 3 );

                //  Remove the comment from the buffer
                text_remove( comment_start_p, 0, comment_l );

                //  Change the flag to show a comment was found
                found = true;
            }
        }

    }   while( found == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
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
    char                        *   tmp_p,      //  @TODO   Remove - Unused
    int                             buffer_l
    )
{
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  found           Flag indicating a blank character was found */
    int                             found;
    /**
     *  @param  delete_l        Number of spaces to be deleted              */
    int                             delete_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Set the start of the buffer
    html_offset_p = html_p;

    /************************************************************************
     *  Remove consecutive spaces
     ************************************************************************/

    //  Loop through the buffer as many times as needed.
    do
    {
        //  The assumption is that we ar done here.
        found = false;

        //  Locate the next space in both buffers.
        html_offset_p = strchr( &html_offset_p[ 1 ], ' ' );

        //  Did we find a space in the buffer ?
        if ( html_offset_p != NULL )
        {
            //  YES:    Count the number of sequential spaces
            for( delete_l = 0;
                 isblank( html_offset_p[ delete_l ] ) != 0;
                 delete_l += 1 )
            {
                //  Nothing to do here; the above statement will walk
                //  the pointer to the next non-space character.
            }

            //  Is there more then one blank character ?
            if ( delete_l > 1 )
            {
                //  YES:    Delete all but the first blank character.
                text_remove( html_offset_p, 1, ( delete_l - 1 ) );
            }

            //  A blank was found.  Do another pass.
            found = true;
        }

    }   while( found == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( html_p );
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
    char                        *   tmp_p,      //  @TODO   Remove - Unused
    int                             buffer_l
    )
{
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
     *  @param  replace_l       Size of the string to be deleted.           */
    int                             delete_l;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Loop through the buffer as many times as needed.
    do
    {
        //  The flag will be changed when a '<style...' is removed.
        altered = false;

        //  Locate the next '<style' string
        html_offset_p = strcasestr( html_p, "<style" );

        //  Did we find it ?
        if( html_offset_p != NULL )
        {
            /****************************************************************
             *  <style> ... </style>
             *  <style ... />
             *  <style ... > ... </style>
             ****************************************************************/

            //  YES:    <style> ... </style> ?
            if (    ( html_offset_p[ 6 ]== '>' )
                 || ( html_offset_p[ 7 ]== '>' ) )
            {
                //  YES:    Find the end '</style>' tag
                tmp_offset_p = strcasestr( html_offset_p, "</style>" );

                //  Did we find it ?
                if ( tmp_offset_p != NULL )
                {
                    //  YES:    Set the remove length.
                    delete_l = ( ( tmp_offset_p + 8 ) - html_offset_p );
                }
                else
                {
                    //  Invalid HTML code
                    log_write( MID_INFO,  "html2txt_lib.c", "%s\n", html_offset_p );
                    log_write( MID_FATAL, "html2txt_lib.c", "Line: %d\n", __LINE__ );
                }
            }
            //  YES:
            else
            if ( html_offset_p[ 6 ]== ' ' )
            {
                tmp_offset_p = strchr( html_offset_p, '>' );

                //  Did we find the end of the start tag ?
                if ( tmp_offset_p != NULL )
                {
                    //  YES:    Is it a '/>' ?
                    if ( tmp_offset_p[ -1 ] == '/' )
                    {
                        //  YES:    <style ... /> ?
                        delete_l = ( tmp_offset_p - html_offset_p );
                    }
                    else
                    {
                        //  NO:     <style ... > ... </style>
                        tmp_offset_p = strcasestr( html_offset_p, "</style>" );

                        //  Did we find it ?
                        if ( tmp_offset_p != NULL )
                        {
                            //  YES:    Set the remove length.
                            delete_l = ( ( tmp_offset_p + 8 ) - html_offset_p );
                        }
                        else
                        {
                            //  Invalid HTML code
                            log_write( MID_INFO,  "html2txt_lib.c", "%s\n", html_offset_p );
                            log_write( MID_FATAL, "html2txt_lib.c", "Line: %d\n", __LINE__ );
                        }
                    }
                }
                else
                {
                    //  Invalid HTML code
                    log_write( MID_INFO,  "html2txt_lib.c", "%s\n", html_offset_p );
                    log_write( MID_FATAL, "html2txt_lib.c", "Line: %d\n", __LINE__ );
                }
            }
            else
            {
                //  Invalid HTML code
                log_write( MID_INFO,  "html2txt_lib.c", "%s\n", html_offset_p );
                log_write( MID_FATAL, "html2txt_lib.c", "Line: %d\n", __LINE__ );
            }

            //  Now delete the '<style> ... </style>' from the buffer.
            text_remove( html_offset_p, 0, delete_l );

            //  Change the flag to show it was found and deleted.
            altered = true;
        }

    }   while( altered == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( html_p );
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
    char                        *   tmp_p,      //  @TODO   Remove - Unused
    int                             buffer_l
    )
{
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  found           Flag indicating something was found         */
    int                             found;
    /**
     *  @param  html_tag        A buffer holding the HTML tag from the array*/
    char                            html_tag[ 32 ];
    /**
     *  @param  ndx             Index into the array table                  */
    int                             ndx;
    /**
     *  @param  type            HTML tag type to build                      */
    int                             format;
    /**
     *  @param  process_type    Tells us what to do with the tag            */
    int                             process_type;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function
     ************************************************************************/

    //  Loop through the search table
    for ( ndx = 0;
          html_tag_list[ ndx ].name_l != 99;
          ndx += 1 )
    {
{
    //  DEBUG TRAP CODE
    if ( ndx == 54 ) {
        tmp_offset_p = html_tag_list[ ndx ].name; }
}
        //  Search the array using the three tag format types
        for( format = 0;
             format < 3;
             format += 1 )
        {
            //  Clean out the HTML tag buffer
            memset( html_tag, '\0', sizeof( html_tag ) );

            //  Reset the buffer starting point.
            html_offset_p = html_p;

            //  Set the search string
            snprintf( html_tag, sizeof( html_tag ),
                      "%s", html_tag_list[ ndx ].name );

            //  Loop through the buffer as many times as needed.
            do
            {
                //  The assume is that we are done.
                found = false;

                //  Locate the next possible tag.
                html_offset_p = strcasestr( html_offset_p, html_tag );

                //  Did we find a match to the tag name ?
                if ( html_offset_p != NULL )
                {
                    //  Clean up the start of the tag
                    tmp_offset_p = HTML2TXT__tag_clean( html_p,
                                                        html_offset_p,
                                                        strlen( html_tag ),
                                                        format );

                    //  Is this the start of a valid HTML tag ?
                    if ( tmp_offset_p != NULL )
                    {
                        //  Update the pointer with the new tag start location
                        html_offset_p = tmp_offset_p;

                        //  What should we do with the source data ?
                        if ( format == 0 || format == 1 )
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
                            //  Remove the tag_start and the tag_end
                            case    HTML_TAG_END_DEL:
                            {
                                //  Locate the end of the tag
                                tmp_offset_p = HTML2TXT__locate_tag_end( html_offset_p );

                                //  Did we locate the end of the tag ?
                                if ( tmp_offset_p != NULL )
                                {
                                    //  YES:    Now delete the '<style> ... </style>' from the buffer.
                                    text_remove( html_offset_p, 0,
                                                 ( tmp_offset_p - html_offset_p + 1 ) );
                                }
                                else
                                {
                                    //  NO:     Not good.  Delete the remainder
                                    //          of the buffer
                                    html_offset_p[ 0 ] = '\0';
                                }

                                //  A HTML tag was found and removed
                                found = true;

                            }   break;

                            case    HTML_TAG_END_CRLF:
                            {
                                //  Insert a Carriage Return
                                html_offset_p[ 0 ] = '\n';

                                //  Locate the end of the tag
                                tmp_offset_p = HTML2TXT__locate_tag_end( html_offset_p );

                                //  Did we locate the end of the tag ?
                                if ( tmp_offset_p != NULL )
                                {
                                    //  YES:    Now delete the '<style> ... </style>' from the buffer.
                                text_remove( html_offset_p, 1,
                                             ( tmp_offset_p - html_offset_p     ) );

                                }
                                else
                                {
                                    //  NO:     Not good.  Delete the remainder
                                    //          of the buffer
                                    html_offset_p[ 0 ] = '\0';
                                }
                                //  A HTML tag was found and removed
                                found = true;

                            }   break;
                        }
                    }
                    else
                    {
                        //  Not a valid HTML tag but something was found.
                        found = true;

                        //  Advance the search start so we don't look at the
                        //  same thing over and over and over and over ...
                        html_offset_p += 1;
                    }
                }

            }   while(  found == true );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( html_p );
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
     *  @param  found           Flag indicating the search was locatd       */
    int                             found;
    /**
     *  @param  html_table_ndx  Index into the HTML conversion table        */
    int                             html_table_ndx;
    /**
     *  @param  html_offset_p   Pointer to the first space in HTML buffer   */
    char                        *   html_offset_p;
    /**
     *  @param  tmp_offset_p    Pointer to the last space in the tmp buffer */
    char                        *   tmp_offset_p;
    /**
     *  @param  replace_l       Size of the replace string                  */
    int                             replace_l;
    /**
     *  @param  insert_str      Date to be inserted                         */
    char                            insert_str[ 10 ];

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Replace all 'html_entry' strings with it's hex code.
     ************************************************************************/

    //  Loop through all entries in the HTML conversion table
    for( html_table_ndx = 0;
         html_table[ html_table_ndx ].hex_code != 0;
         html_table_ndx += 1 )
    {
        //  Loop until all translations are done.
        do
        {
            //  The flag will be changed when something is translated.
            found = false;

            //  Look for this string in the HTML buffer
            tmp_offset_p = strcasestr( html_table[ html_table_ndx ].html_entity,
                                       html_p );

            //  Did we find the string ?
            if ( tmp_offset_p != NULL )
            {
                //  YES:    Create a string of the insert character
                insert_str[ 0 ] = html_table[ html_table_ndx ].hex_code;
                insert_str[ 1 ] = '\0';

                //  Replace the string with the character
                text_replace( tmp_offset_p,
                              strlen( tmp_offset_p ),
                              0,
                              insert_str,
                              strlen( html_table[ html_table_ndx ].html_entity ) );

                //  Change the flag to show something was found and translated
                found = true;
            }

        }   while ( found == true );
    }

    /************************************************************************
     *  Replace all HTML-Character [&#nn] strings with it's hex code.
     ************************************************************************/

    //  Set the start point to search
    html_offset_p = html_p;

    //  Loop until all translations are done.
    do
    {
        //  The flag will be changed when something is translated.
        found = false;

        //  Locate the next potential code string
        tmp_offset_p = strchr( html_offset_p, '&' );

        //  Did we find something to test ?
        if ( tmp_offset_p != NULL )
        {
            //  YES:    Is this decimal code ?
            if (    (    (          tmp_offset_p[ 1 ]   ==  '#' )
                      && ( isdigit( tmp_offset_p[ 2 ] ) !=   0  )
                      && ( isdigit( tmp_offset_p[ 3 ] ) !=   0  )
                      && (          tmp_offset_p[ 4 ]   ==  ';' ) )
                 || (    (          tmp_offset_p[ 1 ]   ==  '#' )
                      && ( isdigit( tmp_offset_p[ 2 ] ) !=   0  )
                      && ( isdigit( tmp_offset_p[ 3 ] ) !=   0  )
                      && ( isdigit( tmp_offset_p[ 4 ] ) !=   0  )
                      && (          tmp_offset_p[ 5 ]   ==  ';' ) ) )
            {
                //  YES:    Create a string of the insert character
                insert_str[ 0 ] = atoi( &( tmp_offset_p[ 1 ] ) );
                insert_str[ 1 ] = '\0';

                //  Is the replace string length equal to four ?
                if ( tmp_offset_p[ 4 ] == ';' )
                {
                    //  YES:    Set the length to four
                    replace_l = 5;
                }
                else
                {
                    //  NO:     Then set the replace length to five
                    replace_l = 6;
                }

                //  Replace the string with the character
                text_replace( tmp_offset_p,
                              strlen( tmp_offset_p ),
                              0,
                              insert_str,
                              replace_l );

                //  Update the search starting position
                html_offset_p = tmp_offset_p;

                //  Change the flag to show something was found and translated
                found = true;
            }
            else
            {
                //  NO:     Look again from here.
                found = true;

                //  Move the search pointer to avoid an infinite loop.
                html_offset_p = &tmp_offset_p[ 1 ];
            }
        }

    }   while ( found == true );

    /************************************************************************
     *  Replace all HTML-Character [&#Xnn] strings with it's hex code.
     ************************************************************************/

    //  Set the start point to search
    html_offset_p = html_p;

    //  Loop until all translations are done.
    do
    {
        //  The flag will be changed when something is translated.
        found = false;

        //  Locate the next potential code string
        tmp_offset_p = strchr( html_offset_p, '&' );

        //  Did we find something to test ?
        if ( tmp_offset_p != NULL )
        {
            //  YES:    Is this decimal code ?
            if (    (          tmp_offset_p[ 1 ]   ==  '#' )
                 && ( tolower( tmp_offset_p[ 2 ] ) ==  'x' )
                 && ( isdigit( tmp_offset_p[ 3 ] ) !=   0  )
                 && ( isdigit( tmp_offset_p[ 4 ] ) !=   0  )
                 && (          tmp_offset_p[ 5 ]   ==  ';' ) )
            {
                //  YES:    Translate the string
                insert_str[ 0 ] = tmp_offset_p[ 3 ];
                insert_str[ 1 ] = tmp_offset_p[ 4 ];
                insert_str[ 2 ] = '\0';
                sscanf( insert_str, "%X", (int*)insert_str );

                //  Replace the string with the character
                text_replace( tmp_offset_p,
                              strlen( tmp_offset_p ),
                              0,
                              insert_str,
                              5 );

                //  Update the search starting position
                html_offset_p = tmp_offset_p;

                //  Change the flag to show something was found and translated
                found = true;
            }
            else
            {
                //  NO:     Look again from here.
                found = true;

                //  Move the search pointer to avoid an infinite loop.
                html_offset_p = &tmp_offset_p[ 1 ];
            }
        }

    }   while ( found == true );

    /************************************************************************
     *  Replace all 'html_entry' strings with it's hex code.
     ************************************************************************/

    //  Set the start point to search
    html_offset_p = html_p;

    //  Loop until all translations are done.
    do
    {
        //  The flag will be changed when something is translated.
        found = false;

        //  Locate the next potential code string
        tmp_offset_p = strchr( html_offset_p, '#' );

        //  Did we find something to test ?
        if ( tmp_offset_p != NULL )
        {
            //  YES:    Is this decimal code ?
            if (    (           tmp_offset_p[ 0 ]   ==  '#' )
                 && ( tolower(  tmp_offset_p[ 1 ] ) ==  'x' )
                 && ( isxdigit( tmp_offset_p[ 2 ] ) !=   0  )
                 && ( isxdigit( tmp_offset_p[ 3 ] ) !=   0  )
                 && (           tmp_offset_p[ 4 ]   ==  ';' ) )
            {
                //  YES:    Translate the string
                insert_str[ 0 ] = tmp_offset_p[ 2 ];
                insert_str[ 1 ] = tmp_offset_p[ 3 ];
                insert_str[ 2 ] = '\0';
                sscanf( insert_str, "%X", (int*)insert_str );

                //  Replace the string with the character
                text_replace( tmp_offset_p,
                              strlen( tmp_offset_p ),
                              0,
                              insert_str,
                              replace_l );

                //  Update the search starting position
                html_offset_p = tmp_offset_p;

                //  Change the flag to show something was found and translated
                found = true;
            }
        }

    }   while ( found == true );

    /********************************************************************
     *  Translate UNICODE Strings
     ********************************************************************/

    //  Set the start point to search
    html_offset_p = html_p;

    //  Loop until all translations are done.
    do
    {
        //  The flag will be changed when something is translated.
        found = false;

        //  Locate the next potential UNICODE string
        tmp_offset_p = strcasestr( html_offset_p, "U+" );

        //  Did we find something to test ?
        if ( tmp_offset_p != NULL )
        {
            //  YES:    Figure out the size of the replace string
            memset( insert_str, '\0', sizeof( insert_str ) );
            for ( replace_l = 2;
                  ( isdigit( tmp_offset_p[ replace_l ] ) != 0 );
                  replace_l += 1 )
            {
                //  Buffer overflow protection
                if ( replace_l < 8 )
                {
                    //  Copy the numeric text character
                    insert_str[ replace_l - 2 ] = tmp_offset_p[ replace_l ];
                }
            };

            //  Is this a valid UNICODE string ?
            if (    ( replace_l > 4 )
                 && ( replace_l < 8 ) )
            {
                //  YES:    Translate the string
                sscanf( insert_str, "%X", (int*)insert_str );

                //  Replace the string with the character
                text_replace( tmp_offset_p,
                              strlen( tmp_offset_p ),
                              0,
                              insert_str,
                              replace_l );
            }
            else
            {
                //  NO:     Move the pointer past the stuff we already found.
                tmp_offset_p += replace_l;
            }
            //  Update the search starting position
            html_offset_p = tmp_offset_p;

            //  Change the flag to show something was found and translated
            found = true;
        }

    }   while ( found == true );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
