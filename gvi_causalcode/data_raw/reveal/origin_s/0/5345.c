static char * rfc1867_angle ( tvbuff_t * tvb , int offset , const char * nsew ) {
 guint32 angle ;
 char direction ;
 guint32 degrees , minutes , secs , tsecs ;
 static char buf [ 10 + 1 + 3 + 1 + 2 + 1 + 3 + 1 + 2 + 1 + 3 + 1 + 3 + 1 + 1 + 1 ] ;
 angle = tvb_get_ntohl ( tvb , offset ) ;
 if ( angle < 0x80000000U ) {
 angle = 0x80000000U - angle ;
 direction = nsew [ 1 ] ;
 }
 else {
 angle = angle - 0x80000000U ;
 direction = nsew [ 0 ] ;
 }
 tsecs = angle % 1000 ;
 angle = angle / 1000 ;
 secs = angle % 60 ;
 angle = angle / 60 ;
 minutes = angle % 60 ;
 degrees = angle / 60 ;
 g_snprintf ( buf , sizeof ( buf ) , "%u deg %u min %u.%03u sec %c" , degrees , minutes , secs , tsecs , direction ) ;
 return buf ;
 }