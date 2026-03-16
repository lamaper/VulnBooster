static double uprv_delta ( UTimer * timer1 , UTimer * timer2 ) {
 double t1 , t2 ;
 t1 = ( double ) timer1 -> start . tv_sec + ( double ) timer1 -> start . tv_usec / ( 1000 * 1000 ) ;
 t2 = ( double ) timer2 -> start . tv_sec + ( double ) timer2 -> start . tv_usec / ( 1000 * 1000 ) ;
 return ( t2 - t1 ) ;
 }