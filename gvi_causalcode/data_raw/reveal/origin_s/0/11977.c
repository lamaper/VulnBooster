static const char * debug_ntoa ( u32 address ) {
 static char buf [ 32 ] ;
 u32 a = ntohl ( address ) ;
 evutil_snprintf ( buf , sizeof ( buf ) , "%d.%d.%d.%d" , ( int ) ( u8 ) ( ( a >> 24 ) & 0xff ) , ( int ) ( u8 ) ( ( a >> 16 ) & 0xff ) , ( int ) ( u8 ) ( ( a >> 8 ) & 0xff ) , ( int ) ( u8 ) ( ( a ) & 0xff ) ) ;
 return buf ;
 }