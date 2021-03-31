LibTools is a library of functions I found myself creating and copying over and over.  I finally decided to put them all into a single static library and elimate the redundancy.  Then I got carried off with the whole library thing and started dumping everything that might some day be usefull in another project.

Base64 is a text-to-binary and binary-to-text encoding/decoding scheme that represent binary data (more specifically, a sequence of 8-bit bytes) in an ASCII string format by translating the data into a radix-64 representation.
 1. base64_encode
 1. base64_decode


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



# html2txt

# html2txt_str_2_char

# list_new

# list_kill

# list_get_first

# list_get_next

# list_get_prev

# list_get_last

# list_put_first

# list_put_last

# my_list_delete

# list_query_count

# list_user_lock

# list_user_unlock

# list_fget_first

# list_fget_next

# list_fget_prev

# list_fget_last

# list_fput_last

# list_fdelete

# list_debug_dump_list

# log_init

# log_write

# mem_init

# mem_malloc

# mem_free

# mem_sizeof

# mem_dump

# queue_init

# queue_new

# queue_get_id

# queue_get_count

# queue_put_payload

# queue_get_payload

# sha1_init

# sha1_update

# sha1_final

# sha1_sum

# store_init

# store_get

# store_put

# tcpip_init

# tcpip_rcv_open

# tcpip_rcv_connection_open

# tcpip_snd_open

# tcpip_close

# tcpip_snd_data

# tcpip_rcv_data

# tcpip_get_data

# text_atox

# text_space_fill

# text_to_uppercase

# text_to_lowercase

# text_to_int

# text_skip_past_whitespace

# text_remove_crlf

# text_strip_whitespace

# text_is_blank_line

# get_cmd_line_parm

# is_cmd_line_parm

# text_copy_to_new

# text_title_case

# text_next_word

# text_datastring_to_ascii

# text_insert

# text_remove

# text_replace

# text_center

# thread_new

# thread_flow_init

# thread_resume

# thread_wait

# token_init

# token_get

# token_free
