static int tablefilematch ( struct taboff * tab , FILE * ttc , struct alltabs * all , int pos ) {
 int i , ch1 , ch2 ;
 struct taboff * test ;
 unsigned len ;
 for ( i = 0 ;
 i < pos ;
 ++ i ) {
 test = findtabindir ( & all [ i ] . tabdir , tab -> tag ) ;
 if ( test == NULL || test -> data == ( void * ) ( intpt ) - 1 || test -> length != tab -> length ) continue ;
 rewind ( tab -> data ) ;
 fseek ( ttc , test -> offset , SEEK_SET ) ;
 for ( len = 0 ;
 len < tab -> length && ( ch1 = getc ( tab -> data ) ) != EOF && ( ch2 = getc ( ttc ) ) != EOF ;
 ++ len ) {
 if ( ch1 != ch2 ) break ;
 }
 if ( len == tab -> length ) {
 rewind ( tab -> data ) ;
 fseek ( ttc , 0 , SEEK_END ) ;
 return ( i ) ;
 }
 }
 rewind ( tab -> data ) ;
 fseek ( ttc , 0 , SEEK_END ) ;
 return ( - 1 ) ;
 }