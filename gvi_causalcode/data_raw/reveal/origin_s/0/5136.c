static inline int mutex_lock ( pthread_mutex_t * mutex ) {
 while ( pthread_mutex_trylock ( mutex ) ) ;
 return 0 ;
 }