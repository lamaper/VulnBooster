static bfd_boolean srec_read_section ( bfd * abfd , asection * section , bfd_byte * contents ) {
 int c ;
 bfd_size_type sofar = 0 ;
 bfd_boolean error = FALSE ;
 bfd_byte * buf = NULL ;
 size_t bufsize = 0 ;
 if ( bfd_seek ( abfd , section -> filepos , SEEK_SET ) != 0 ) goto error_return ;
 while ( ( c = srec_get_byte ( abfd , & error ) ) != EOF ) {
 bfd_byte hdr [ 3 ] ;
 unsigned int bytes ;
 bfd_vma address ;
 bfd_byte * data ;
 if ( c == '\r' || c == '\n' ) continue ;
 BFD_ASSERT ( c == 'S' ) ;
 if ( bfd_bread ( hdr , ( bfd_size_type ) 3 , abfd ) != 3 ) goto error_return ;
 BFD_ASSERT ( ISHEX ( hdr [ 1 ] ) && ISHEX ( hdr [ 2 ] ) ) ;
 bytes = HEX ( hdr + 1 ) ;
 if ( bytes * 2 > bufsize ) {
 if ( buf != NULL ) free ( buf ) ;
 buf = ( bfd_byte * ) bfd_malloc ( ( bfd_size_type ) bytes * 2 ) ;
 if ( buf == NULL ) goto error_return ;
 bufsize = bytes * 2 ;
 }
 if ( bfd_bread ( buf , ( bfd_size_type ) bytes * 2 , abfd ) != bytes * 2 ) goto error_return ;
 address = 0 ;
 data = buf ;
 switch ( hdr [ 0 ] ) {
 default : BFD_ASSERT ( sofar == section -> size ) ;
 if ( buf != NULL ) free ( buf ) ;
 return TRUE ;
 case '3' : address = HEX ( data ) ;
 data += 2 ;
 -- bytes ;
 case '2' : address = ( address << 8 ) | HEX ( data ) ;
 data += 2 ;
 -- bytes ;
 case '1' : address = ( address << 8 ) | HEX ( data ) ;
 data += 2 ;
 address = ( address << 8 ) | HEX ( data ) ;
 data += 2 ;
 bytes -= 2 ;
 if ( address != section -> vma + sofar ) {
 BFD_ASSERT ( sofar == section -> size ) ;
 if ( buf != NULL ) free ( buf ) ;
 return TRUE ;
 }
 -- bytes ;
 while ( bytes -- != 0 ) {
 contents [ sofar ] = HEX ( data ) ;
 data += 2 ;
 ++ sofar ;
 }
 break ;
 }
 }
 if ( error ) goto error_return ;
 BFD_ASSERT ( sofar == section -> size ) ;
 if ( buf != NULL ) free ( buf ) ;
 return TRUE ;
 error_return : if ( buf != NULL ) free ( buf ) ;
 return FALSE ;
 }