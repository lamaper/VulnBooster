static FILE * open_outfile ( const char * name ) {
 if ( strcmp ( "-" , name ) == 0 ) {
 set_binary_mode ( stdout ) ;
 return stdout ;
 }
 else {
 FILE * file = fopen ( name , "wb" ) ;
 if ( ! file ) fatal ( "Failed to output file %s" , name ) ;
 return file ;
 }
 }