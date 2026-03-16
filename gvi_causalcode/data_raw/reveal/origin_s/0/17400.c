static void i_stream_attachment_extractor_close ( struct iostream_private * stream , bool close_parent ) {
 struct attachment_istream * astream = ( struct attachment_istream * ) stream ;
 struct message_part * parts ;
 if ( astream -> parser != NULL ) {
 if ( message_parser_deinit ( & astream -> parser , & parts ) < 0 ) i_unreached ( ) ;
 }
 hash_format_deinit_free ( & astream -> set . hash_format ) ;
 if ( astream -> pool != NULL ) pool_unref ( & astream -> pool ) ;
 if ( close_parent ) i_stream_close ( astream -> istream . parent ) ;
 }