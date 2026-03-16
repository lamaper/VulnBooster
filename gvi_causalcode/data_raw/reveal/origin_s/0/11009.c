struct archive_string * archive_strcat ( struct archive_string * as , const void * p ) {
 return archive_strncat ( as , p , 0x1000000 ) ;
 }