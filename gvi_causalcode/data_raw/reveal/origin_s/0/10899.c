static int astream_decode_base64 ( struct attachment_istream * astream ) {
 struct attachment_istream_part * part = & astream -> part ;
 buffer_t * extra_buf = NULL ;
 struct istream * input , * base64_input ;
 struct ostream * output ;
 const unsigned char * data ;
 size_t size ;
 ssize_t ret ;
 buffer_t * buf ;
 int outfd ;
 bool failed = FALSE ;
 if ( part -> base64_bytes < astream -> set . min_size || part -> temp_output -> offset > part -> base64_bytes + BASE64_ATTACHMENT_MAX_EXTRA_BYTES ) {
 return - 1 ;
 }
 if ( part -> base64_line_blocks == 0 ) {
 part -> base64_line_blocks = part -> cur_base64_blocks ;
 i_assert ( part -> base64_line_blocks > 0 ) ;
 }
 outfd = astream -> set . open_temp_fd ( astream -> context ) ;
 if ( outfd == - 1 ) return - 1 ;
 buf = buffer_create_dynamic ( default_pool , 1024 ) ;
 input = i_stream_create_fd ( part -> temp_fd , IO_BLOCK_SIZE , FALSE ) ;
 base64_input = i_stream_create_limit ( input , part -> base64_bytes ) ;
 output = o_stream_create_fd_file ( outfd , 0 , FALSE ) ;
 o_stream_cork ( output ) ;
 hash_format_reset ( astream -> set . hash_format ) ;
 size_t bytes_needed = 1 ;
 while ( ( ret = i_stream_read_bytes ( base64_input , & data , & size , bytes_needed ) ) > 0 ) {
 buffer_set_used_size ( buf , 0 ) ;
 if ( base64_decode ( data , size , & size , buf ) < 0 ) {
 i_error ( "istream-attachment: BUG: " "Attachment base64 data unexpectedly broke" ) ;
 failed = TRUE ;
 break ;
 }
 i_stream_skip ( base64_input , size ) ;
 o_stream_nsend ( output , buf -> data , buf -> used ) ;
 hash_format_loop ( astream -> set . hash_format , buf -> data , buf -> used ) ;
 bytes_needed = i_stream_get_data_size ( base64_input ) + 1 ;
 }
 if ( ret != - 1 ) {
 i_assert ( failed ) ;
 }
 else if ( base64_input -> stream_errno != 0 ) {
 i_error ( "istream-attachment: read(%s) failed: %s" , i_stream_get_name ( base64_input ) , i_stream_get_error ( base64_input ) ) ;
 failed = TRUE ;
 }
 if ( o_stream_nfinish ( output ) < 0 ) {
 i_error ( "istream-attachment: write(%s) failed: %s" , o_stream_get_name ( output ) , o_stream_get_error ( output ) ) ;
 failed = TRUE ;
 }
 buffer_free ( & buf ) ;
 i_stream_unref ( & base64_input ) ;
 o_stream_unref ( & output ) ;
 if ( input -> v_offset != part -> temp_output -> offset && ! failed ) {
 extra_buf = buffer_create_dynamic ( default_pool , 1024 ) ;
 while ( ( ret = i_stream_read_data ( input , & data , & size , 0 ) ) > 0 ) {
 buffer_append ( extra_buf , data , size ) ;
 i_stream_skip ( input , size ) ;
 }
 i_assert ( ret == - 1 ) ;
 if ( input -> stream_errno != 0 ) {
 i_error ( "istream-attachment: read(%s) failed: %s" , i_stream_get_name ( input ) , i_stream_get_error ( input ) ) ;
 failed = TRUE ;
 }
 }
 i_stream_unref ( & input ) ;
 if ( failed ) {
 i_close_fd ( & outfd ) ;
 return - 1 ;
 }
 o_stream_destroy ( & part -> temp_output ) ;
 i_close_fd ( & part -> temp_fd ) ;
 part -> temp_fd = outfd ;
 if ( extra_buf != NULL ) {
 stream_add_data ( astream , extra_buf -> data , extra_buf -> used ) ;
 buffer_free ( & extra_buf ) ;
 }
 return 0 ;
 }