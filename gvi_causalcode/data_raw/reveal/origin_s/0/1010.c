void putfixed ( FILE * file , real dval ) {
 int val ;
 int mant ;
 val = floor ( dval ) ;
 mant = floor ( 65536. * ( dval - val ) ) ;
 val = ( val << 16 ) | mant ;
 putlong ( file , val ) ;
 }