static inline void free_static_shapers ( void ) {
 if ( unlikely ( static_shapers != all_shapers ) ) free ( ( void * ) static_shapers ) ;
 }