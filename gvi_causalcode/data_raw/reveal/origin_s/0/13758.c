static int tagcomp ( const void * _t1 , const void * _t2 ) {
 struct taboff * t1 = * ( ( struct taboff * * ) _t1 ) , * t2 = * ( ( struct taboff * * ) _t2 ) ;
 return ( ( int ) ( t1 -> tag - t2 -> tag ) ) ;
 }