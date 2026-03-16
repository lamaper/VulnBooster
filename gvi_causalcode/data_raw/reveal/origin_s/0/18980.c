static int minima_cmp ( const void * a , const void * b ) {
 const Minima * da = ( const Minima * ) a ;
 const Minima * db = ( const Minima * ) b ;
 return da -> height - db -> height ;
 }