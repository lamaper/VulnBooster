void fe_sendint64 ( int64 i , char * buf ) {
 uint32 n32 ;
 n32 = ( uint32 ) ( i >> 32 ) ;
 n32 = htonl ( n32 ) ;
 memcpy ( & buf [ 0 ] , & n32 , 4 ) ;
 n32 = ( uint32 ) i ;
 n32 = htonl ( n32 ) ;
 memcpy ( & buf [ 4 ] , & n32 , 4 ) ;
 }