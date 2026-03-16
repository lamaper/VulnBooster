static bfd_boolean srec_write_header ( bfd * abfd ) {
 unsigned int len = strlen ( abfd -> filename ) ;
 if ( len > 40 ) len = 40 ;
 return srec_write_record ( abfd , 0 , ( bfd_vma ) 0 , ( bfd_byte * ) abfd -> filename , ( bfd_byte * ) abfd -> filename + len ) ;
 }