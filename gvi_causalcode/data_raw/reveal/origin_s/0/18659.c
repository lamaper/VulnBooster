static void astream_part_reset ( struct attachment_istream * astream ) {
 struct attachment_istream_part * part = & astream -> part ;
 if ( part -> temp_output != NULL ) o_stream_destroy ( & part -> temp_output ) ;
 if ( part -> temp_fd != - 1 ) i_close_fd ( & part -> temp_fd ) ;
 i_free_and_null ( part -> content_type ) ;
 i_free_and_null ( part -> content_disposition ) ;
 if ( part -> part_buf != NULL ) buffer_free ( & part -> part_buf ) ;
 i_zero ( part ) ;
 part -> temp_fd = - 1 ;
 hash_format_reset ( astream -> set . hash_format ) ;
 }