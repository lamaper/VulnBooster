struct istream * i_stream_create_attachment_extractor ( struct istream * input , struct istream_attachment_settings * set , void * context ) {
 struct attachment_istream * astream ;
 i_assert ( set -> min_size > 0 ) ;
 i_assert ( set -> hash_format != NULL ) ;
 i_assert ( set -> open_attachment_ostream != NULL ) ;
 i_assert ( set -> close_attachment_ostream != NULL ) ;
 astream = i_new ( struct attachment_istream , 1 ) ;
 astream -> part . temp_fd = - 1 ;
 astream -> set = * set ;
 astream -> context = context ;
 astream -> retry_read = TRUE ;
 set -> hash_format = NULL ;
 astream -> istream . max_buffer_size = input -> real_stream -> max_buffer_size ;
 astream -> istream . read = i_stream_attachment_extractor_read ;
 astream -> istream . iostream . close = i_stream_attachment_extractor_close ;
 astream -> istream . istream . readable_fd = FALSE ;
 astream -> istream . istream . blocking = input -> blocking ;
 astream -> istream . istream . seekable = FALSE ;
 astream -> pool = pool_alloconly_create ( "istream attachment" , 1024 ) ;
 astream -> parser = message_parser_init ( astream -> pool , input , 0 , MESSAGE_PARSER_FLAG_INCLUDE_MULTIPART_BLOCKS | MESSAGE_PARSER_FLAG_INCLUDE_BOUNDARIES ) ;
 return i_stream_create ( & astream -> istream , input , i_stream_get_fd ( input ) ) ;
 }