static inline void * ruby_zalloc ( size_t n ) {
 void * p = ruby_xmalloc ( n ) ;
 memset ( p , 0 , n ) ;
 return p ;
 }