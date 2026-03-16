static int get_sha1_hex_from_objpath ( const char * path , unsigned char * sha1 ) {
 char hex [ 40 ] ;
 if ( strlen ( path ) != 41 ) return - 1 ;
 memcpy ( hex , path , 2 ) ;
 path += 2 ;
 path ++ ;
 memcpy ( hex , path , 38 ) ;
 return get_sha1_hex ( hex , sha1 ) ;
 }