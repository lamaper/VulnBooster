static int archive_read_format_ar_cleanup ( struct archive_read * a ) {
 struct ar * ar ;
 ar = ( struct ar * ) ( a -> format -> data ) ;
 if ( ar -> strtab ) free ( ar -> strtab ) ;
 free ( ar ) ;
 ( a -> format -> data ) = NULL ;
 return ( ARCHIVE_OK ) ;
 }