static bool data_has_8bit ( const unsigned char * data , size_t size ) {
 size_t i ;
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 if ( ( data [ i ] & 0x80 ) != 0 ) return TRUE ;
 }
 return FALSE ;
 }