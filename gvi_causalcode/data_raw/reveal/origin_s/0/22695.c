static int astream_read_next ( struct attachment_istream * astream , bool * retry_r ) {
 struct istream_private * stream = & astream -> istream ;
 struct message_block block ;
 size_t old_size , new_size ;
 const char * error ;
 int ret ;
 * retry_r = FALSE ;
 if ( stream -> pos - stream -> skip >= i_stream_get_max_buffer_size ( & stream -> istream ) ) return - 2 ;
 old_size = stream -> pos - stream -> skip ;
 switch ( message_parser_parse_next_block ( astream -> parser , & block ) ) {
 case - 1 : ret = astream_end_of_part ( astream , & error ) ;
 if ( ret > 0 ) {
 new_size = stream -> pos - stream -> skip ;
 return new_size - old_size ;
 }
 stream -> istream . eof = TRUE ;
 stream -> istream . stream_errno = stream -> parent -> stream_errno ;
 if ( ret < 0 ) {
 io_stream_set_error ( & stream -> iostream , "%s" , error ) ;
 stream -> istream . stream_errno = EIO ;
 }
 astream -> cur_part = NULL ;
 return - 1 ;
 case 0 : return 0 ;
 default : break ;
 }
 if ( block . part != astream -> cur_part && astream -> cur_part != NULL ) {
 if ( astream_end_of_part ( astream , & error ) < 0 ) {
 io_stream_set_error ( & stream -> iostream , "%s" , error ) ;
 stream -> istream . stream_errno = EIO ;
 return - 1 ;
 }
 }
 astream -> cur_part = block . part ;
 if ( block . hdr != NULL ) {
 astream_parse_header ( astream , block . hdr ) ;
 }
 else if ( block . size == 0 ) {
 if ( astream_want_attachment ( astream , block . part ) ) {
 astream -> part . state = MAIL_ATTACHMENT_STATE_MAYBE ;
 astream -> part . start_offset = stream -> parent -> v_offset ;
 }
 }
 else {
 astream_add_body ( astream , & block ) ;
 }
 new_size = stream -> pos - stream -> skip ;
 * retry_r = new_size == old_size ;
 return new_size - old_size ;
 }