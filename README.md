LibTools is a library of functions I found myself creating and copying over and over.  I finally decided to put them all into a single static library and elimate the redundancy.  Then I got carried off with the whole library thing and started dumping everything that might some day be usefull in another project.

Base64 is a text-to-binary and binary-to-text encoding/decoding scheme that represent binary data (more specifically, a sequence of 8-bit bytes) in an ASCII string format by translating the data into a radix-64 representation.
 * base64_encode
 * base64_decode

Not a lot going on in any og the _file_ functions.  It was simply easier to call a library function that has error checking etc. built in.
 * file_open_read
 * file_open_write
 * file_open_write_no_dup
 * file_open_append
 * file_close
 * file_read_text
 * file_read_data
 * file_stat
 * file_ls
 * file_path_to_lib
 * file_unzip
 * file_dir_exist

More or less a ripoff of the html2txt application.  The input is in html format and the output has all the html formatting stripped out.
 * html2txt
 * html2txt_str_2_char

A complete (or as much as I have ever needed) set of tools for managing a link list.  In this implementation the link list **ONLY** manages pointers to the data the list is managing.
 * list_new
 * list_kill
 * list_get_first
 * list_get_next
 * list_get_prev
 * list_get_last
 * list_put_first
 * list_put_last
 * my_list_delete
 * list_query_count
 * list_user_lock
 * list_user_unlock
 * list_fget_first
 * list_fget_next
 * list_fget_prev
 * list_fget_last
 * list_fput_last
 * list_fdelete
 * list_debug_dump_list

Just a loggong tool where messages may be written to a terminal and/or a log file.
 * log_init
 * log_write

Nothing magical here.  These functions are not much more than a wrapper around malloc and free, that is until you discover a memory leak.  There are imbedded tools that can assist in tracking down trhe leak so it can be fixed.  Naturally this comes with a small performance impact.
 * mem_init
 * mem_malloc
 * mem_free
 * mem_sizeof
 * mem_dump

Create and manage messaging queues to pass information between threads.
 * queue_init
 * queue_new
 * queue_get_id
 * queue_get_count
 * queue_put_payload
 * queue_get_payload

So SHA-1 is old and broken.  That being said I have been using it for years to create checksums for pieces of data to manage their uniqueness.
 * sha1_init
 * sha1_update
 * sha1_final
 * sha1_sum

Used to manage application parameters where they may be stored and retrieved the next time the application is run.
 * store_init
 * store_get
 * store_put

As you have probably guessed this is nothing more than a set of function calls to open/close, send/receive informatin across a TCP/IP interface.
 * tcpip_init
 * tcpip_rcv_open
 * tcpip_rcv_connection_open
 * tcpip_snd_open
 * tcpip_close
 * tcpip_snd_data
 * tcpip_rcv_data
 * tcpip_get_data

A set of text minipulation and management tools.
 * text_atox
 * text_space_fill
 * text_to_uppercase
 * text_to_lowercase
 * text_to_int
 * text_skip_past_whitespace
 * text_remove_crlf
 * text_strip_whitespace
 * text_is_blank_line
 * get_cmd_line_parm
 * is_cmd_line_parm
 * text_copy_to_new
 * text_title_case
 * text_next_word
 * text_datastring_to_ascii
 * text_insert
 * text_remove
 * text_replace
 * text_center

Again, not much more then a wrapper around the posix threading tools.  The tools just take some of the work out of using threads.
 * thread_new
 * thread_flow_init
 * thread_resume
 * thread_wait

Some time ago I was in need of a token manager and this is what came out of it.  I can't say it has been of much use since then.
 * token_init
 * token_get
 * token_free
