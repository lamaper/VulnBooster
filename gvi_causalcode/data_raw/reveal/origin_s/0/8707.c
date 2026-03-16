void ufile_flush_io ( UFILE * f ) {
 if ( ( ! f ) || ( ! f -> fFile ) ) {
 return ;
 }
 u_file_write_flush ( NULL , 0 , f , TRUE , FALSE ) ;
 }