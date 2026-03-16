static inline int is_specified_interface ( char * interface , const char * interface_prefix ) {
 return ! strncmp ( interface , interface_prefix , strlen ( interface_prefix ) ) ;
 }