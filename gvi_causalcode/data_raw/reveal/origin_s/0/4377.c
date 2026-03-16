int fourcc_is_ivf ( const char detect [ 4 ] ) {
 if ( memcmp ( detect , "DKIF" , 4 ) == 0 ) {
 return 1 ;
 }
 return 0 ;
 }