static int tcomp2 ( const void * _t1 , const void * _t2 ) {
 struct taboff * t1 = * ( ( struct taboff * * ) _t1 ) , * t2 = * ( ( struct taboff * * ) _t2 ) ;
 if ( t1 -> offset > t2 -> offset ) return ( 1 ) ;
 else if ( t1 -> offset < t2 -> offset ) return ( - 1 ) ;
 return ( 0 ) ;
 }