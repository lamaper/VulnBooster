void clean_comment_data ( char * buffer ) {
 int x ;
 int y ;
 y = ( int ) strlen ( buffer ) ;
 for ( x = 0 ;
 x < y ;
 x ++ ) {
 if ( buffer [ x ] == ';
' || buffer [ x ] == '\n' || buffer [ x ] == '\r' ) buffer [ x ] = ' ' ;
 }
 return ;
 }