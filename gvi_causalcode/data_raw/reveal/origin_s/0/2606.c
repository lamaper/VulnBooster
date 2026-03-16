static FILE * dumpsavedtable ( struct ttf_table * tab ) {
 FILE * out ;
 if ( tab == NULL ) return ( NULL ) ;
 out = tmpfile ( ) ;
 fwrite ( tab -> data , 1 , tab -> len , out ) ;
 if ( ( tab -> len & 1 ) ) putc ( '\0' , out ) ;
 if ( ( tab -> len + 1 ) & 2 ) putshort ( out , 0 ) ;
 return ( out ) ;
 }