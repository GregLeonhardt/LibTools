/*******************************  COPYRIGHT  ********************************/
/*
 *  Copyright (c) 2017 Gregory N. Leonhardt All rights reserved.
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains the source code for publicly accessible functions
 *  of the 'tcpip' library.
 *
 *  @note
 *      SERVER: Open a receive port and listen for requests from a client.
 *
 *      CLIENT: Open a transmission port to a server to send requests.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define ALLOC_TCPIP             ( "ALLOCATE STORAGE FOR TCPIP" )

/****************************************************************************
 *  System Function API
 ****************************************************************************/

                                //*******************************************
#include <stdint.h>             //  Alternative storage types
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <pthread.h>            //  pthread_mutex_ pthread_cond_
#include <string.h>             //  String copying, searching, etc.
#include <unistd.h>             //  Access to the POSIX operating system API
#include <errno.h>              //  errno
#include <netdb.h>              //  gethostbyname()
#include <sys/types.h>          //  inet_ntop(), inet_pton(), send(), recv()
#include <sys/socket.h>         //  inet_ntop(), inet_pton(), send(), recv()
#include <arpa/inet.h>          //  inet_ntop(), inet_pton()
#include <netinet/in.h>         //  htons()
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
#include <libtools_api.h>       //  Everything public
                                //*******************************************
#include "tcpip_lib.h"          //  API for all TCPIP__*            PRIVATE
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

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Storage Allocation
 ****************************************************************************/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Initialization function for all 'tcpip_*' functions
 *
 *  @param  void
 *
 *  @return void
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

void
tcpip_init(
    void
    )
{
    //  Initialize the thread lock for TCP/IP
    pthread_mutex_init( &tcpip_lock, 0 );
}

/****************************************************************************/
/**
 *  Create a new receive socket connection and start listening for a
 *  connection on it.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *
 *  @return tcpip_rc            FALSE if an error is detected.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_rcv_socket_open(
    struct  tcpip_t       *   tcpip_p
    )
{
    int                             tcpip_rc;
    struct  sockaddr_in             local_addr;
    struct  hostent             *   local_host_info_p;
    int                             retry;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Lock for single threaded operations
    pthread_mutex_lock( &tcpip_lock );

    //  Clear the connection fd
    tcpip_p->connection_fd = 0;

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_rcv_socket_open",
               "'%p' Opening a receive socket on port number '%05d'\n",
               tcpip_p, tcpip_p->port_number  );

    /************************************************************************
     *  Open a server port and start to listen.
     ************************************************************************/

    do
    {

        /********************************************************************
         *  Function initialization
         ********************************************************************/

        //  Pointers
        local_host_info_p = NULL;

        //  Variables
        tcpip_rc = -1;

        // Assume success and set flags when errors are detected.
        retry = false;

        /********************************************************************
         *  SOCKET
         ********************************************************************/

        // Should we continue?
        if ( retry == false )
        {
            // YES:  Create a new socket
            tcpip_p->socket_fd = socket( AF_INET, SOCK_STREAM, 0 );

            // Was the socket open successful?
            if ( tcpip_p->socket_fd < 0 )
            {
                //  NO:     Sleep a while to let the system recover.
                sleep( 30 );

                //  Let's try this again
                retry = true;
            }
        }

        /********************************************************************
         *  GetHostByName
         ********************************************************************/

        // Should we continue?
        if ( retry == false )
        {
            // YES:  Identify the local host NIC
            local_host_info_p = gethostbyname( "localhost" );

            // If "gethostbyname" returns a null pointer, it couldn't
            // get the requested information.
            if ( local_host_info_p == NULL )
            {
                //  NO:     Log the error
                log_write( MID_WARNING, "tcpip_rcv_socket_open",
                           "Unable to GetHostByName data for localhost.%d - %s\n",
                           tcpip_p->port_number, strerror( errno ) );

                //  Sleep a while to let the system recover.
                sleep( 30 );

                //  Let's try this again
                retry = true;

                // Close the current Socket
                close( tcpip_p->socket_fd );
                tcpip_p->socket_fd = 0;
            }
        }

        /********************************************************************
         *  Bind
         ********************************************************************/

        // Should we continue?
        if ( retry == false )
        {
            local_addr.sin_family       = AF_INET;
            local_addr.sin_addr.s_addr  = htonl( INADDR_ANY );
            local_addr.sin_port         = htons( tcpip_p->port_number );

            // bind( ) returns -1 on failure
            tcpip_rc = bind( tcpip_p->socket_fd,
                             (struct sockaddr *)&local_addr,
                             sizeof( local_addr ) );

            // bind( ) returns -1 on failure
            if ( tcpip_rc == -1 )
            {
                // NO:   Failed to bind to the port.
                log_write( MID_WARNING, "tcpip_rcv_socket_open",
                           "Unable to bind the socket localhost.%d - %s\n",
                           tcpip_p->port_number, strerror( errno ) );

                // Is the "Address already in use"?
                if ( errno == EADDRINUSE )
                {
                    // YES:  Sleep and try again
                    sleep( 15 );

                    //  Enable retrying the socket open.
                    retry = true;

                    // Close the current Socket
                    close( tcpip_p->socket_fd );
                    tcpip_p->socket_fd = 0;
                }
                else
                {
                    //  NO:
                    log_write( MID_FATAL, "tcpip_rcv_socket_open",
                               "Unable to bind socket on localhost:%05d\n",
                               tcpip_p->port_number );
                }
            }
        }


        /********************************************************************
         *  Listen
         ********************************************************************/

        // Should we continue?
        if ( retry == false )
        {
            // YES:  Begin to listen for connections
            listen( tcpip_p->socket_fd, 1 );
        }
    }
    while ( retry != false );

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Release the lock
    pthread_mutex_unlock( &tcpip_lock );

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_rcv_socket_open",
               "'%p' Receive socket '%03d' opened.\n",
               tcpip_p, tcpip_p->socket_fd  );

    //  Fix the return code
    if ( tcpip_rc == -1 )
    {
        tcpip_rc = false;
    }
    else
    {
        tcpip_rc = true;
    }

    //  Socket open is complete
    return( tcpip_rc );
}

/****************************************************************************/
/**
 *  Opens a server socket read connection.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *
 *  @return tcpip_rc            FALSE if an error is detected.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_rcv_connection_open(
    struct  tcpip_t       *   tcpip_p
    )
{
    int                             tcpip_rc;
    struct  sockaddr_in             dest_addr;
    socklen_t                       dest_addr_len;
    int                             retry;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_rcv_connection_open",
               "'%p' Opening a receive connection on socket '%03d'\n",
               tcpip_p, tcpip_p->socket_fd  );

    //  This is the size of the sockaddr_in structure.
    dest_addr_len = sizeof( dest_addr );

    //  Variables
    tcpip_rc = 0;
    tcpip_p->connection_fd = 0;

    /************************************************************************
     *  Open a new TCP/IP connection from another server.
     ************************************************************************/

    do
    {
        //  Set or reset the retry flag.
        retry = false;

        /********************************************************************
         *  Accept a new connection on the socket.
         ********************************************************************/

        tcpip_p->connection_fd = accept( tcpip_p->socket_fd,
                                         (struct sockaddr*)&dest_addr,
                                         &dest_addr_len );

        // Test for accepet failure
        if ( tcpip_p->connection_fd < 0 )
        {
            log_write( MID_WARNING, "tcpip_rcv_connection_open:",
                       "Unable to connect to create socket. errno( %s )\n",
                       strerror( errno ) );

            //  Set retry TRUE.
            retry = true;
        }
        else
        {
            //  Set the socket ID for write and read data
            tcpip_p->read_socket_fd  = tcpip_p->connection_fd;
            tcpip_p->write_socket_fd = tcpip_p->connection_fd;
        }

        /********************************************************************
         *  Open a server port and start to listen.
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == false )
        {
            // Save the connection information
            snprintf( tcpip_p->rmt_port_name, TCPIP_TARGET_NAME_L,
                      "%s", inet_ntoa( dest_addr.sin_addr ) );
            tcpip_p->rmt_port_number = htons( dest_addr.sin_port );
        }
    }
    while ( retry == true );

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_rcv_connection_open",
               "'%p' Receive connection '%03d' opened.\n",
               tcpip_p, tcpip_p->connection_fd  );

    //  Fix the return code
    if ( tcpip_rc == -1 )
    {
        tcpip_rc = false;
    }
    else
    {
        tcpip_rc = true;
    }

    //  Socket open is complete
    return ( tcpip_rc );
}

/****************************************************************************/
/**
 *  Create and open a TCP/IP socket for writing data to a remote server.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *
 *  @return tcpip_rc            FALSE if an error is detected.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_snd_open(
    struct  tcpip_t       *   tcpip_p
    )
{
    int                             tcpip_rc;
    char                            ip_number[ TCPIP_ADDRESS_L + 1 ];
    struct  sockaddr_in             remote_socket;
    struct  hostent             *   server_name_info_p;
    int                             xfer_l;
    int                             retry;

    /************************************************************************
     *  Function initialization
     ************************************************************************/

    //  Lock for single threaded operations
    pthread_mutex_lock( &tcpip_lock );

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_snd_open",
               "'%p' Opening a send socket to '%s:%03d'.\n",
               tcpip_p,
               tcpip_p->rmt_port_name,
               tcpip_p->rmt_port_number );

    //  Pointers
    server_name_info_p = NULL;

    //  Variables
    tcpip_rc = true;
    tcpip_p->socket_fd = 0;

    /************************************************************************
     *  Open a new TCP/IP socket to the target server.
     ************************************************************************/

    do
    {
        //  Set or reset the retry flag.
        retry = false;

        /********************************************************************
         *  socket( )
         ********************************************************************/

        tcpip_p->socket_fd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        //  Was the socket open successful ?
        if ( tcpip_p->socket_fd > 0 )
        {
            //  YES:    Set the socket ID for write and read data.
            tcpip_p->read_socket_fd  = tcpip_p->socket_fd;
            tcpip_p->write_socket_fd = tcpip_p->socket_fd;
        }
        else
        {
            //  NO:     Write an error message
            log_write( MID_WARNING, "tcpip_snd_open",
                       "Can't create TCP socket.\n" );

            //  Set retry TRUE.
            retry = true;
        }

        /********************************************************************
         *  gethostbyname( )
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == false )
        {
            server_name_info_p = gethostbyname( tcpip_p->rmt_port_name );

            //  Was the gethostbyname successful ?
            if ( server_name_info_p == NULL )
            {
                //  NO:     Write an error message
                log_write( MID_WARNING, "tcpip_snd_open",
                           "Can't get IP address for '%s'.  "
                           "Will retry in a few seconds.\n",
                           tcpip_p->rmt_port_name );

                //  Wait a few seconds before trying again.
                sleep( TCPIP_DNS_RETRY_WAIT );

                //  Set retry TRUE.
                retry = true;
            }
        }

        /********************************************************************
         *  inet_ntop( )
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == false )
        {
            //  YES:    Clear out the character string.
            memset( ip_number, 0, sizeof( ip_number ) );

            if ( inet_ntop( AF_INET,
                            (void *)server_name_info_p->h_addr_list[ 0 ],
                            ip_number,
                            TCPIP_ADDRESS_L ) == NULL )
            {
                log_write( MID_WARNING, "tcpip_snd_open",
                           "Can't resolve destination IP name\n" );

                //  Set retry TRUE.
                retry = true;
            }
        }

        /********************************************************************
         *  inet_pton( )
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == false )
        {
            //  YES:    Clear out the remote socket structure.
            memset( (char*)&remote_socket, 0x00, sizeof( struct sockaddr_in ) );

            remote_socket.sin_family = AF_INET;

            xfer_l = inet_pton( AF_INET,
                                ip_number,
                                (void *)( &( remote_socket.sin_addr.s_addr ) ) );

            //  Were we able to get the remote information ?
            if ( xfer_l < 0 )
            {
                //  NO:     Write an error message.
                log_write( MID_WARNING, "tcpip_snd_open",
                           "Can't set remote_socket.sin_addr.s_addr\n" );

                //  Set retry TRUE.
                retry = true;
            }
            //  Did we get the remote address ?
            else if ( xfer_l == 0 )
            {
                //  NO:     Write an error message.
                log_write( MID_WARNING, "tcpip_snd_open",
                           "'%s' is not a valid IP address\n",
                           ip_number );

                //  Set retry TRUE.
                retry = true;
            }
        }

        /********************************************************************
         *  htons( )
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == false )
        {
            //  YES:
            remote_socket.sin_port = htons( tcpip_p->rmt_port_number );

            //  Can we get a connection to the remote server ?
            if ( connect( tcpip_p->socket_fd,
                          (struct sockaddr *)&remote_socket,
                          sizeof( struct sockaddr ) ) < 0 )
            {
                //  NO:     Write an error message.
                log_write( MID_WARNING, "tcpip_snd_open",
                           "Could not connect to '%s' @ %s:%d\n",
                           server_name_info_p->h_name,
                           ip_number,
                           tcpip_p->rmt_port_number );

                //  Set retry TRUE.
                retry = true;
            }
        }

        /********************************************************************
         *  Cleanup if there was an error opening the socket.
         ********************************************************************/

        //  Is everything successful to this point ?
        if ( retry == true )
        {
            //  NO:     Close the socket that was opened.
            close( tcpip_p->socket_fd );

            //  Clear the socket ID for write and read data.
            tcpip_p->read_socket_fd  = 0;
            tcpip_p->write_socket_fd = 0;

            //  Sleep a while to let the system recover.
            sleep( 30 );
        }
    }
    while ( retry == true );

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Release the lock
    pthread_mutex_unlock( &tcpip_lock );

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_snd_open",
               "'%p' Send socket '%03d' opened to '%s' @ '%s:%d'.\n",
               tcpip_p,
               tcpip_p->socket_fd,
               server_name_info_p->h_name,
               ip_number,
               tcpip_p->rmt_port_number );

    //  Fix the return code
    if ( tcpip_rc == -1 )
    {
        tcpip_rc = false;
    }
    else
    {
        tcpip_rc = true;
    }

    //  Socket open is complete
    return ( tcpip_rc );
}

/****************************************************************************/
/**
 *  Closes an existing socket connection.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *
 *  @return void
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

void
tcpip_close(
    struct  tcpip_t       *   tcpip_p
    )
{
    int                             close_socket_fd;

    //  Should we close a connection or a socket ?
    if ( tcpip_p->connection_fd != 0 )
    {
        //  CONNECTION: Close the connection fd.
        close( tcpip_p->connection_fd );

        //  Save the connection fd for the message.
        close_socket_fd = tcpip_p->connection_fd;

        //  And clear the fd number.
        tcpip_p->connection_fd = 0;
    }
    else
    {
        //  SOCKET:     Close the socket fd.
        close( tcpip_p->socket_fd );

        //  Save the connection fd for the message.
        close_socket_fd = tcpip_p->socket_fd;

        //  And clear the fd numbers.
        tcpip_p->connection_fd = 0;
        tcpip_p->socket_fd     = 0;

        //  Clean the remote port name.
        memset( tcpip_p->rmt_port_name, 0x00, sizeof( tcpip_p->rmt_port_name ) );
    }

    //  Log opening a receive socket.
    log_write( MID_DEBUG_0, "tcpip_close",
               "TCP/IP: '%p' Close socket or connection '%03d'.\n",
               tcpip_p, close_socket_fd );

    //  Clean the remaing parts of the tcpip structure
    tcpip_p->rmt_port_number = 0;
    tcpip_p->rcv_data_l      = 0;
    tcpip_p->snd_data_l      = 0;
    tcpip_p->write_socket_fd = 0;
    tcpip_p->read_socket_fd  = 0;
}

/****************************************************************************/
/**
 *  Send data on a TCP/IP socket that is already opened.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *  @param  data_p              Pointer to the buffer containing the data
 *                                  that will be sent.
 *  @param  data_l              Length of the data buffer or the number of
 *                                  data bytes to send.
 *
 *  @return                     FALSE if an error is detected.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_snd_data(
    struct  tcpip_t          *   tcpip_p,
    void                        *   data_p,
    int                             data_l
    )
{
    int                             tcpip_rc;
    int                             bytes_sent;
    char                            log_text_temp[ LOG_TEXT_L ];
    char                        *   s_data_p;

    /************************************************************************
     *  Function initialization
     ************************************************************************/

    //  Log writing data to a socket.
    log_write( MID_DEBUG_0, "tcpip_snd_data",
               "'%p' Send data on socket '%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->write_socket_fd, data_p, data_l );

    //  Set the initial value for the number of bytes sent.
    tcpip_p->snd_data_l = 0;

    //  The assumption is that the send will successfully complete.
    tcpip_rc = true;

    //  Copy the data pointer
    s_data_p = (char*)data_p;

    /************************************************************************
     *  Send the data
     ************************************************************************/

    //  The entire message may not be sent in a single call to 'send'
    do
    {
        //  Send some data to the TCP/IP socket.
        bytes_sent = send( tcpip_p->write_socket_fd,
                           ( s_data_p + tcpip_p->snd_data_l ),
                           (   data_l - tcpip_p->snd_data_l ),
                           0 );

        //  Was there an error during the data send ?
        if ( bytes_sent == -1 )
        {
            //  YES:    Build and write an error message
            memset( log_text_temp, '\0', sizeof( log_text_temp ) );
            strerror_r( errno,
                        log_text_temp,
                        sizeof( log_text_temp ) );
            log_write( MID_FATAL, "tcpip_snd_data",
                       "Send failed: (%d) '%s'\n",
                       errno, log_text_temp );

            errno = EFAULT;
        }
        else
        {
            //  NO:     Update the total number of bytes sent.
            tcpip_p->snd_data_l += bytes_sent;
        }
    }
    while ( tcpip_p->snd_data_l < data_l );

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Log the completion os sending data to a socket.
    log_write( MID_DEBUG_0, "tcpip_snd_data",
               "'%p' '%d' bytes of data sent on socket "
               "'%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->snd_data_l, tcpip_p->write_socket_fd,
               data_p, data_l  );

    //  DONE!
    return ( tcpip_rc );
}

/****************************************************************************/
/**
 *  Receive data from a TCP/IP socket that is already opened.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *  @param  void_buffer_p       Pointer to the buffer where data will be
 *                                  put after receiving it from the socket.
 *  @param  rcv_buffer_l        Length of the data buffer or the number of
 *                                  data bytes to receive.
 *
 *  @return                     FALSE if an error is detected.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_rcv_data(
    struct  tcpip_t          *   tcpip_p,
    void                        *   void_buffer_p,
    int                             rcv_buffer_l
    )
{
    int                             tcpip_rc;
    int                             func_rc;
    char                        *   rcv_buffer_p;
    int                             no_data_count;

    /************************************************************************
     *  Function initialization
     ************************************************************************/

    //  Log reading data from a connection.
    log_write( MID_DEBUG_0, "tcpip_rcv_data",
               "'%p' Receive data on socket '%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->write_socket_fd,
               void_buffer_p, rcv_buffer_l  );

    //  Set the default exit code assuming a successful read.
    tcpip_rc = true;
    func_rc = true;

    //  Redefine the receive buffer pointer.
    rcv_buffer_p = (char*)void_buffer_p;

    // Reset the number of data bytes read.
    tcpip_p->rcv_data_l = 0;

    //  Set the initial value of the no data counter.
    no_data_count = 0;

    /************************************************************************
     *   PreRead (peek) at the incoming message.
     *      Get enough of the message header to determine the total message
     *      length.
     ************************************************************************/

    // Loop until the header is read or an error is detected.
    while ( tcpip_p->rcv_data_l < rcv_buffer_l )
    {
        int                             bytes_read;
        int                             bytes_to_read;

        //  Is the read request greater then the TCPIP buffer ?
        if ( ( rcv_buffer_l - tcpip_p->rcv_data_l ) >= BUFSIZ )
        {
            //  YES:    Read the TCPIP buffer size.
            bytes_to_read = BUFSIZ;
        }
        else
        {
            //  NO:     Read the remaining data.
            bytes_to_read = ( rcv_buffer_l - tcpip_p->rcv_data_l );
        }
#if 0
        bytes_read = recv( tcpip_p->write_socket_fd,
                          &rcv_buffer_p[ tcpip_p->rcv_data_l ],
                          ( rcv_buffer_l - tcpip_p->rcv_data_l ),
                          MSG_DONTWAIT );
#else
        bytes_read = recv( tcpip_p->write_socket_fd,
                           &rcv_buffer_p[ tcpip_p->rcv_data_l ],
                           bytes_to_read, 0 );
#endif

        log_write( MID_DEBUG_0, "tcpip_rcv_data",
                   "Bytes_Read = %4d\n", bytes_read );

        // Was there a read error?
        if ( bytes_read == -1 )
        {
            // Was the error a result of "No Data Available"?
            if (    ( errno == ENOENT )      //  02   No such file or directory
                 || ( errno == EAGAIN ) )    //  11   Resource temporarily unavailable
            {
                // YES:  Reset the return code and try again
                bytes_read = 0;
                usleep( 100 );

                //  Should this be the end of data ?
                if ( ++no_data_count >= 2 )
                {
                    //  YES:    Stop looking for more data
                    break;
                }
            }
            else
            {
                log_write( MID_FATAL, "tcpip_rcv_data",
                           "Read TCM/IP read failed.  error:%d - %s\n",
                           errno, strerror( errno ) );
            }
        }
        //  Is this the end of the read data buffer ?
        else if ( bytes_read == 0 )
        {
            //  YES:    Let's get out of here.
            break;
        }

        //  NO:     Add the number of bytes read to the total.
        tcpip_p->rcv_data_l += bytes_read;

        //  Is the receive buffer full ?
        if ( tcpip_p->rcv_data_l >= rcv_buffer_l )
        {
            //  YES:    OOPS The receive buffer is too small to hold the
            //          entire response message.
            log_write( MID_FATAL, "tcpip_rcv_data",
                       "Read TCM/IP read failed.  The receive buffer "
                       "is full but the read isn't complete.\n" );
        }
    }

    /************************************************************************
     *  Return code update and final message to the log.
     ************************************************************************/

    //  Did we experience an error ?
    if ( func_rc != true )
    {
        //  YES:    Change the return code to fail.
        tcpip_rc = false;
    }

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Log the completion of a read from the read socket.
    log_write( MID_DEBUG_0, "tcpip_rcv_data",
               "'%p' '%d' bytes of data received from "
               "socket '%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->rcv_data_l, tcpip_p->write_socket_fd,
               void_buffer_p, rcv_buffer_l  );

    //  Receive is complete
    return ( tcpip_rc );
}

/****************************************************************************/
/**
 *
 *  Receive data from a TCP/IP socket that is already opened.
 *
 *  @param  tcpip_p             Pointer to a TCP/IP information structure.
 *  @param  void_buffer_p       Pointer to the buffer where data will be
 *                                  put after receiving it from the socket.
 *  @param  rcv_buffer_l        Length of the data buffer or the number of
 *                                  data bytes to receive.
 *
 *  @return                     Number of data bytes read.
 *
 *  @note
 *      REVIEW-DONE:    2014-05-18
 *
 ****************************************************************************/

int
tcpip_get_data(
    struct  tcpip_t          *   tcpip_p,
    void                        *   void_buffer_p,
    int                             rcv_buffer_l
    )
{
    char                        *   rcv_buffer_p;
    int                             bytes_to_read;

    /************************************************************************
     *  Function initialization
     ************************************************************************/

    //  Log reading data from a connection.
    log_write( MID_DEBUG_0, "tcpip_get_data",
               "'%p' Get data on socket '%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->read_socket_fd,
               void_buffer_p, rcv_buffer_l  );

    //  Redefine the receive buffer pointer.
    rcv_buffer_p = (char*)void_buffer_p;

    // Reset the number of data bytes read.
    tcpip_p->rcv_data_l = 0;

    /************************************************************************
     *   Read from the TCP/IP port.
     ************************************************************************/

    //  Is the read request greater then the TCPIP buffer ?
    if ( rcv_buffer_l > BUFSIZ )
    {
        //  YES:    Read the TCPIP buffer size.
        bytes_to_read = BUFSIZ;
    }
    else
    {
        //  NO:     Read the remaining data.
        bytes_to_read = rcv_buffer_l;
    }

    //  Read data from the socket.
    tcpip_p->rcv_data_l = recv( tcpip_p->read_socket_fd,
                                rcv_buffer_p,
                                bytes_to_read, 0 );

    log_write( MID_DEBUG_0, "tcpip_get_data",
               "Bytes_Read = %4d\n", tcpip_p->rcv_data_l );

    // Was there a read error?
    if ( tcpip_p->rcv_data_l == -1 )
    {
        log_write( MID_FATAL, "tcpip_get_data",
                   "Read TCP/IP read failed.  error:%d - %s\n",
                   errno, strerror( errno ) );
    }

    /************************************************************************
     *  DONE!
     ************************************************************************/

    //  Log the completion of a read from the read socket.
    log_write( MID_DEBUG_0, "tcpip_get_data",
               "'%p' '%d' bytes of data received from "
               "socket '%03d' - '%p:%05d'.\n",
               tcpip_p, tcpip_p->rcv_data_l, tcpip_p->read_socket_fd,
               void_buffer_p, rcv_buffer_l  );

    //  Receive is complete
    return ( tcpip_p->rcv_data_l );
}

/****************************************************************************/
