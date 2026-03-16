inline static bool is_localhost ( const char * name , int len ) {
 static const char local [ ] = "127.0.0.1" ;
 return ( len == ( sizeof ( local ) - 1 ) ) && ( memcmp ( name , local , len ) == 0 ) ;
 }