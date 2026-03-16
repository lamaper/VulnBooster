static int tcomp ( const void * _t1 , const void * _t2 ) {
 struct taboff * t1 = * ( ( struct taboff * * ) _t1 ) , * t2 = * ( ( struct taboff * * ) _t2 ) ;
 return ( t1 -> orderingval - t2 -> orderingval ) ;
 }