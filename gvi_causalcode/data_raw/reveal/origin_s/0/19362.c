static void put2d14 ( FILE * file , real dval ) {
 int val ;
 int mant ;
 val = floor ( dval ) ;
 mant = floor ( 16384. * ( dval - val ) ) ;
 val = ( val << 14 ) | mant ;
 putshort ( file , val ) ;
 }