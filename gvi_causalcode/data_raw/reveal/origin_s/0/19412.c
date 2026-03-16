static int astream_part_finish ( struct attachment_istream * astream , const char * * error_r ) {
 struct attachment_istream_part * part = & astream -> part ;
 struct istream_attachment_info info ;
 struct istream * input ;
 struct ostream * output ;
 string_t * digest_str ;
 const unsigned char * data ;
 size_t size ;
 int ret = 0 ;
 if ( o_stream_nfinish ( part -> temp_output ) < 0 ) {
 * error_r = t_strdup_printf ( "write(%s) failed: %s" , o_stream_get_name ( part -> temp_output ) , o_stream_get_error ( part -> temp_output ) ) ;
 return - 1 ;
 }
 i_zero ( & info ) ;
 info . start_offset = astream -> part . start_offset ;
 info . encoded_size = part -> base64_bytes ;
 digest_str = t_str_new ( 128 ) ;
 hash_format_write ( astream -> set . hash_format , digest_str ) ;
 info . hash = str_c ( digest_str ) ;
 if ( ! part -> base64_failed ) {
 if ( part -> base64_state == BASE64_STATE_0 && part -> base64_bytes > 0 ) {
 part -> base64_state = BASE64_STATE_EOM ;
 }
 if ( part -> base64_state == BASE64_STATE_EOM ) {
 if ( astream_decode_base64 ( astream ) < 0 ) part -> base64_failed = TRUE ;
 }
 else {
 part -> base64_failed = TRUE ;
 }
 }
 info . part = astream -> cur_part ;
 if ( ! part -> base64_failed ) {
 info . base64_blocks_per_line = part -> base64_line_blocks ;
 info . base64_have_crlf = part -> base64_have_crlf ;
 str_truncate ( digest_str , 0 ) ;
 hash_format_write ( astream -> set . hash_format , digest_str ) ;
 info . hash = str_c ( digest_str ) ;
 }
 else {
 info . encoded_size = part -> temp_output -> offset ;
 }
 if ( astream -> set . open_attachment_ostream ( & info , & output , error_r , astream -> context ) < 0 ) return - 1 ;
 input = i_stream_create_fd ( part -> temp_fd , IO_BLOCK_SIZE , FALSE ) ;
 while ( i_stream_read_data ( input , & data , & size , 0 ) > 0 ) {
 o_stream_nsend ( output , data , size ) ;
 i_stream_skip ( input , size ) ;
 }
 if ( input -> stream_errno != 0 ) {
 * error_r = t_strdup_printf ( "read(%s) failed: %s" , i_stream_get_name ( input ) , i_stream_get_error ( input ) ) ;
 ret = - 1 ;
 }
 i_stream_destroy ( & input ) ;
 if ( astream -> set . close_attachment_ostream ( output , ret == 0 , error_r , astream -> context ) < 0 ) ret = - 1 ;
 return ret ;
 }