static int mpc8_get_mask ( GetBitContext * gb , int size , int t ) {
 int mask = 0 ;
 if ( t && t != size ) mask = mpc8_dec_enum ( gb , FFMIN ( t , size - t ) , size ) ;
 if ( ( t << 1 ) > size ) mask = ~ mask ;
 return mask ;
 }