static int srec_get_byte ( bfd * abfd , bfd_boolean * errorptr ) {
 bfd_byte c ;
 if ( bfd_bread ( & c , ( bfd_size_type ) 1 , abfd ) != 1 ) {
 if ( bfd_get_error ( ) != bfd_error_file_truncated ) * errorptr = TRUE ;
 return EOF ;
 }
 return ( int ) ( c & 0xff ) ;
 }