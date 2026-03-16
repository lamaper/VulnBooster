static FILE * dumpstoredtable ( SplineFont * sf , uint32 tag , int * len ) {
 struct ttf_table * tab = SFFindTable ( sf , tag ) ;
 FILE * out ;
 if ( tab == NULL && sf -> mm != NULL && sf -> mm -> apple ) tab = SFFindTable ( sf -> mm -> normal , tag ) ;
 if ( tab == NULL ) {
 * len = 0 ;
 return ( NULL ) ;
 }
 out = tmpfile ( ) ;
 fwrite ( tab -> data , 1 , tab -> len , out ) ;
 if ( ( tab -> len & 1 ) ) putc ( '\0' , out ) ;
 if ( ( tab -> len + 1 ) & 2 ) putshort ( out , 0 ) ;
 * len = tab -> len ;
 return ( out ) ;
 }