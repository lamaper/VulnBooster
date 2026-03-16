static inline void ip_tr_mc_map ( __be32 addr , char * buf ) {
 buf [ 0 ] = 0xC0 ;
 buf [ 1 ] = 0x00 ;
 buf [ 2 ] = 0x00 ;
 buf [ 3 ] = 0x04 ;
 buf [ 4 ] = 0x00 ;
 buf [ 5 ] = 0x00 ;
 }