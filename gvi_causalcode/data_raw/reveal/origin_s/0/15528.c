static bool byte_increment ( unsigned char * ptr , int len ) {
 if ( * ptr >= 255 ) return false ;
 ( * ptr ) ++ ;
 return true ;
 }