static int astream_open_output ( struct attachment_istream * astream ) {
 int fd ;
 i_assert ( astream -> part . temp_fd == - 1 ) ;
 fd = astream -> set . open_temp_fd ( astream -> context ) ;
 if ( fd == - 1 ) return - 1 ;
 astream -> part . temp_fd = fd ;
 astream -> part . temp_output = o_stream_create_fd ( fd , 0 , FALSE ) ;
 o_stream_cork ( astream -> part . temp_output ) ;
 return 0 ;
 }