static inline int mpc8_get_mod_golomb ( GetBitContext * gb , int m ) {
 if ( mpc8_cnk_len [ 0 ] [ m ] < 1 ) return 0 ;
 return mpc8_dec_base ( gb , 1 , m + 1 ) ;
 }