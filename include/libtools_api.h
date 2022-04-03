/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

#ifndef LIBTOOLS_API_H
#define LIBTOOLS_API_H

/******************************** JAVADOC ***********************************/
/**
 *  This file contains definitions (etc.) that apply to external library
 *  components of the 'LibTools' library.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/


/****************************************************************************
 * System APIs
 ****************************************************************************/

                                //*******************************************
#include <stdio.h>              //  Standard I/O definitions
#include <pthread.h>            //  All thread related functions
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <sqlite3.h>            //  Everything SqLite
                                //*******************************************

/****************************************************************************
 * Library Public Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
//  File
//----------------------------------------------------------------------------
#define LOG_DIR_NAME                ( ".LibTools" )
#define MAX_LINE_L                  (   1024 )
#define END_OF_FILE                 ((char*) -1 )
#define FILE_NAME_L                 (    512 )
#define FILE_DATE_L                 (     80 )
#define FILE_SIZE_L                 (     10 )
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Log
//----------------------------------------------------------------------------
#define MID_FATAL                   ( 0x8000 )
#define MID_WARNING                 ( 0x4000 )
#define MID_INFO                    ( 0x2000 )
#define MID_DEBUG_3                 ( 0x1000 )
#define MID_DEBUG_2                 ( 0x0800 )
#define MID_DEBUG_1                 ( 0x0400 )
#define MID_DEBUG_0                 ( 0x0200 )
#define MID_LOGONLY                 ( 0x0100 )
#define MID_TEMPORARY               ( 0x0080 )

#define MID_VOID                    ( 0x0000 )
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  QUEUE
//----------------------------------------------------------------------------
#define QUEUE_NAME_L                (     16 )
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  SHA1
//----------------------------------------------------------------------------
#define SHA1_DIGEST_SIZE            (     20 )
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  TCPIP
//----------------------------------------------------------------------------
#define TCPIP_TARGET_NAME_L         (    255 )  //  Network name of the target.
//----------------------------------------------------------------------------
#define TCPIP_ADDRESS_L             (     15 )  //  IP address XXX.XXX.XXX.XXX
//----------------------------------------------------------------------------
#define TCPIP_DNS_RETRY_WAIT        (      5 )  //  Seconds
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Public Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//  File
//----------------------------------------------------------------------------
enum    read_text_options_e
{
    RTO_NONE                    =    0x00,
    RTO_STRIP_CRLF              =    0x01,
    RTO_INVALID                 =    0xFF
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Queue
//---------------------------------------------------------------------------
enum    queue_rc_e
{
    QUEUE_RC_SUCCESS                =   0,
    QUEUE_RC_QUEUE_NAME_TOO_SHORT   =  -1,
    QUEUE_RC_QUEUE_NAME_TOO_LONG    =  -2,
    QUEUE_RC_QUEUE_NAME_EXISTS      =  -3,
    QUEUE_RC_QUEUE_NAME_NOT_PRESENT =  -4,
    QUEUE_RC_NO_MATCHING_QUEUE_ID   =  -5,
    QUEUE_RC_QUEUE_IS_EMPTY         =  -6
};
#if 1
//---------------------------------------------------------------------------
enum    queue_state_e
{
    QUEUE_STATE_BUSY                =   0,
    QUEUE_STATE_IDLE                =   1
};
#endif
//---------------------------------------------------------------------------
enum  queue_get_mode_e
{
    QUEUE_WAIT                      =   0,
    QUEUE_NO_WAIT                   =   1
};
//---------------------------------------------------------------------------

/****************************************************************************
 * Library Public Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
//  File
//----------------------------------------------------------------------------
struct  file_info_t
{
    char                            dir_name[  FILE_NAME_L + 1 ];
    char                            file_name[ FILE_NAME_L + 1 ];
    char                            date_time[ FILE_DATE_L + 1 ];
    char                            file_size[ FILE_SIZE_L + 1 ];
};
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  List
//---------------------------------------------------------------------------
struct  list_base_t;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Queue
//---------------------------------------------------------------------------
struct  queue_state_t
{
    int                             queue_msg_count;
};
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  SHA1
//----------------------------------------------------------------------------
typedef struct
{
    uint32_t                        state[   5 ];
    uint32_t                        count[   2 ];
    uint8_t                         buffer[ 64 ];
}   SHA1_CTX;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  TCPIP
//----------------------------------------------------------------------------
struct  tcpip_t
{
/**
 *  @param  port_number         Receive socket port number.
 */
    int                             port_number;
/**
 *  @param  server_name         The server name (or IP address)
 *                              of a remote server.
 */
    char                            server_name[ TCPIP_TARGET_NAME_L + 1 ];
/**
 *  @param  socket_fd           The TCP/IP socket numner.
 */
    int                             socket_fd;
/**
 *  @param  connection_fd       The TCP/IP connection numner.
 */
    int                             connection_fd;
/**
 *  @param  socket_fd           The TCP/IP socket numner used to receive
 *                              data
 */
    int                             read_socket_fd;
/**
 *  @param  socket_fd           The TCP/IP socket numner used to send data
 *                              May also be used for receiving data on a
 *                              bidirectional communications socket with
 *                              tcpip_rcv_data().
 */
    int                             write_socket_fd;
/**
 *  @param  rmt_port_name       Connected to: port name
 */
    char                            rmt_port_name[ TCPIP_TARGET_NAME_L + 1 ];
/**
 *  @param  rmt_port_number     Connected to: port number
 */
    int                              rmt_port_number;
/**
 *  @param  rcv_data_l          Number of data bytes received.
 */
    int                             rcv_data_l;
/**
 *  @param  snd_data_l          Number of data bytes sent.
 */
    int                             snd_data_l;
};

//----------------------------------------------------------------------------
//  THREAD
//----------------------------------------------------------------------------
/**
 *  @param  thread_wait         Thread wait/resume structure                */
struct
thread_flow_t
{
    // Declaration of thread condition structure.
    pthread_cond_t              signal;

    // Declaration of thread mutex structure.
    pthread_mutex_t             lock;
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Library Public Storage Allocation
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Library Public Prototypes
 ****************************************************************************/

//---------------------------------------------------------------------------
//  Base64
//---------------------------------------------------------------------------
char    *
base64_encode(
    char                        *   data_p
    );
//----------------------------------------------------------------------------
char    *
base64_decode(
    char                        *   data_p
    );
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  File
//---------------------------------------------------------------------------
FILE    *
file_open_read(
    char                        *   file_name
    );
//----------------------------------------------------------------------------
FILE    *
file_open_write(
    char                        *   file_name
    );
//----------------------------------------------------------------------------
FILE    *
file_open_write_no_dup(
    char                        *   file_name,
    char                        *   dup_name
    );
//----------------------------------------------------------------------------
FILE    *
file_open_append(
    char                        *   file_name
    );
//----------------------------------------------------------------------------
void
file_close(
    FILE                        *   file_fp
    );
//---------------------------------------------------------------------------
char    *
file_read_text(
    FILE                        *   file_fp,
    enum    read_text_options_e     options
   );
//---------------------------------------------------------------------------
size_t
file_read_data(
    FILE                        *   file_fp,
    char                        *   buffer_p,
    size_t                          size
   );
//---------------------------------------------------------------------------
struct  file_info_t *
file_stat(
    char                        *   full_file_name,
    char                        *   file_name
    );
//---------------------------------------------------------------------------
void
file_ls(
    struct  list_base_t         *   file_list_p,
    char                        *   fd_name,
    char                        *   include_ext_p
    );
//---------------------------------------------------------------------------
char    *
file_path_to_lib(
    void
    );
//---------------------------------------------------------------------------
int
file_unzip(
    char                        *   path_p
    );
//---------------------------------------------------------------------------
int
file_dir_exist(
    char                        *   path_p,
    int                             create
    );
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  html2txt
//----------------------------------------------------------------------------
char    *
html2txt(
    char                        *   html_p
    );
//---------------------------------------------------------------------------
void
html2txt_str_2_char(
    char                        *   html_p
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  List
//---------------------------------------------------------------------------
struct  list_base_t   *
list_new(
    void
    );
//---------------------------------------------------------------------------
int
list_kill(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------
void    *
list_get_first(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------
void    *
list_get_next(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    );
//---------------------------------------------------------------------------
void    *
list_get_prev(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    );
//---------------------------------------------------------------------------
void    *
list_get_last(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------
int
list_put_first(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    );
//---------------------------------------------------------------------------
int
list_put_last(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    );
//---------------------------------------------------------------------------
int
list_delete_payload(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p
    );
//---------------------------------------------------------------------------
int
list_query_count(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------
//  Fast access mode (used for large tables).  Call must first call
//  list_user_lock() then list_fget_first() followed by looping
//  list_fget_next() or list_fget_prev(). When the search is complete a
//  final call to list_user_unlock() is needed.
//---------------------------------------------------------------------------
int
list_user_lock(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------
void
list_user_unlock(
    struct  list_base_t         *   list_base_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
void    *
list_fget_first(
    struct  list_base_t         *   list_base_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
void    *
list_fget_next(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
void    *
list_fget_prev(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
void    *
list_fget_last(
    struct  list_base_t         *   list_base_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
int
list_fput_last(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
int
list_fdelete(
    struct  list_base_t         *   list_base_p,
    void                        *   payload_p,
    int                             access_key
    );
//---------------------------------------------------------------------------
int
list_debug_dump_list(
    struct  list_base_t         *   list_base_p
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Log
//---------------------------------------------------------------------------
void
log_init(
    char                        *   log_file_name
    );
//---------------------------------------------------------------------------
void
log_write(
    uint16_t                        message_id,
    const char                  *   function_name,
    const char                  *   message_p, ...
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Mem
//---------------------------------------------------------------------------
void
mem_init(
    void
    );
//---------------------------------------------------------------------------
void *
mem_malloc(
    int                             size
    );
//---------------------------------------------------------------------------
void
mem_free(
    void                        *   memory_p
    );
//----------------------------------------------------------------------------
int
mem_sizeof(
    void                        *   address
    );
//---------------------------------------------------------------------------
void
mem_dump(
    void
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Queue
//---------------------------------------------------------------------------
enum queue_rc_e
queue_init(
    );
//---------------------------------------------------------------------------
int
queue_new(
    char                        *   queue_name_p,
    int                             queue_depth
    );
//---------------------------------------------------------------------------
int
queue_get_id(
    char                        *   queue_name_p
    );
//---------------------------------------------------------------------------
int
queue_get_count(
    int                             queue_id
    );
//---------------------------------------------------------------------------
enum queue_rc_e
queue_put_payload(
    int                             queue_id,
    void                        *   void_p
    );
//---------------------------------------------------------------------------
void *
queue_get_payload(
    int                             queue_id
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  SHA1
//---------------------------------------------------------------------------
void
sha1_init(
    SHA1_CTX                    *   context
    );
//---------------------------------------------------------------------------
void
sha1_update(
    SHA1_CTX                    *   context,
    const char                  *   data,
    const size_t                    len
    );
//---------------------------------------------------------------------------
void
sha1_final(
    SHA1_CTX                    *   context,
    char                            digest[ SHA1_DIGEST_SIZE ]
    );
//---------------------------------------------------------------------------
int
sha1_sum(
    char                        *   sum_p,
    char                        *   num1_p,
    char                        *   num2_p
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  STORE
//---------------------------------------------------------------------------
void
store_init(
    void
    );
//---------------------------------------------------------------------------
char    *
store_get(
    char                        *   name_p
    );
//---------------------------------------------------------------------------
void
store_put(
    char                        *   name_p,
    char                        *   value_p
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  TCPIP
//---------------------------------------------------------------------------
void
tcpip_init(
    void
    );
//---------------------------------------------------------------------------
int
tcpip_rcv_open(
    struct  tcpip_t             *   tcpip_p
    );
//---------------------------------------------------------------------------
int
tcpip_rcv_connection_open(
    struct  tcpip_t             *   tcpip_p
    );
//---------------------------------------------------------------------------
int
tcpip_snd_open(
    struct  tcpip_t             *   tcpip_p
    );
//---------------------------------------------------------------------------
void
tcpip_close(
    struct  tcpip_t             *   tcpip_p
    );
//---------------------------------------------------------------------------
int
tcpip_snd_data(
    struct  tcpip_t             *   tcpip_p,
    void                        *   data_p,
    int                             data_l
    );
//---------------------------------------------------------------------------
int
tcpip_rcv_data(
    struct  tcpip_t             *   tcpip_p,
    void                        *   void_buffer_p,
    int                             rcv_buffer_l
    );
//---------------------------------------------------------------------------
int
tcpip_get_data(
    struct  tcpip_t             *   tcpip_p,
    void                        *   void_buffer_p,
    int                             rcv_buffer_l
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  TEXT
//---------------------------------------------------------------------------
int
text_atox(
    char                        *   hex_string_p
    );
//---------------------------------------------------------------------------
void
text_space_fill(
    char                        *   data_p,
    int                             data_l
    );
//---------------------------------------------------------------------------
void
text_to_uppercase(
    char                        *   text_p
    );
//---------------------------------------------------------------------------
void
text_to_lowercase(
    char                        *   text_p
    );
//---------------------------------------------------------------------------
int
text_to_int(
    char                        *   text_p
    );
//---------------------------------------------------------------------------
long
text_to_long(
    char                        *   text_p
    );
//---------------------------------------------------------------------------
char    *
text_skip_past_whitespace(
    char                        *   line_of_text_p
    );
//---------------------------------------------------------------------------
void
text_remove_crlf(
    char                        *   line_of_text_p
    );
//---------------------------------------------------------------------------
void
text_strip_whitespace(
    char                        *   line_of_text_p
    );
//---------------------------------------------------------------------------
int
text_is_blank_line(
    char                        *   line_of_text_p
    );
//---------------------------------------------------------------------------
int
text_is_binary(
    char                    *   data_p,
    int                         data_l
    );
//---------------------------------------------------------------------------
char *
get_cmd_line_parm(
    int                             argc,
    char                        **  argv,
    const char                  *   search_string_p
    );
//---------------------------------------------------------------------------
int
is_cmd_line_parm(
    int                             argc,
    char                        **  argv,
    const char                  *   search_string_p
    );
//---------------------------------------------------------------------------
char    *
text_copy_to_new(
    char                        *   text_p
    );
//---------------------------------------------------------------------------
int
text_title_case(
    char                        *   out_string_p,
    char                        *   in_string_p
    );
//---------------------------------------------------------------------------
char *
text_next_word(
    char                          *  src_string_p,
    char                          *  dst_string_p
    );
//---------------------------------------------------------------------------
void
text_datastring_to_ascii(
    char                        *   src_data_p
    );
//---------------------------------------------------------------------------
void
text_insert(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    int                             text_ndx,
    char                        *   text_data_p
    );
//---------------------------------------------------------------------------
void
text_remove(
    char                        *   text_buffer_p,
    int                             text_ndx,
    int                             text_remove_l
    );
//---------------------------------------------------------------------------
void
text_replace(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    int                             text_ndx,
    char                        *   text_data_p,
    int                             text_remove_l
    );
//---------------------------------------------------------------------------
void
text_center(
    char                        *   text_buffer_p,
    int                             text_buffer_l,
    char                        *   text_data_p
    );
//---------------------------------------------------------------------------
char    *
text_join(
    char                        *   string_1_p,
    char                        *   string_2_p,
    int                             free_1,
    int                             free_2
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Thread
//---------------------------------------------------------------------------
void
thread_new(
    void                            (*function_p)( void * ),
    void                        *   parm_p
    );
//---------------------------------------------------------------------------
void
thread_flow_init(
    struct  thread_flow_t       *   thread_flow_p
    );
//---------------------------------------------------------------------------
void
thread_resume(
    struct  thread_flow_t       *   thread_flow_p
    );
//---------------------------------------------------------------------------
void
thread_wait(
    struct  thread_flow_t       *   thread_flow_p
    );
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Token
//---------------------------------------------------------------------------
void
token_init(
    void
    );
//---------------------------------------------------------------------------
int
token_get(
    void
    );
//---------------------------------------------------------------------------
void
token_free(
    int                             token_id
    );
//---------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    LIBTOOLS_API_H
