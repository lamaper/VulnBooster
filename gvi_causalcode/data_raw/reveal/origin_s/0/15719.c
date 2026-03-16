int64 fe_recvint64 ( char * buf ) {
 int64 result ;
 uint32 h32 ;
 uint32 l32 ;
 memcpy ( & h32 , buf , 4 ) ;
 memcpy ( & l32 , buf + 4 , 4 ) ;
 h32 = ntohl ( h32 ) ;
 l32 = ntohl ( l32 ) ;
 result = h32 ;
 result <<= 32 ;
 result |= l32 ;
 return result ;
 }