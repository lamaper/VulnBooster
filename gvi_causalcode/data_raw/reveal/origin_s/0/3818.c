int file_is_y4m ( const char detect [ 4 ] ) {
 if ( memcmp ( detect , "YUV4" , 4 ) == 0 ) {
 return 1 ;
 }
 return 0 ;
 }