static char * Tag2String ( uint32 tag ) {
 static char buffer [ 8 ] ;
 buffer [ 0 ] = tag >> 24 ;
 buffer [ 1 ] = tag >> 16 ;
 buffer [ 2 ] = tag >> 8 ;
 buffer [ 3 ] = tag ;
 buffer [ 4 ] = 0 ;
 return ( buffer ) ;
 }