static inline bool is_ra ( hb_codepoint_t u ) {
 for ( unsigned int i = 0 ;
 i < ARRAY_LENGTH ( ra_chars ) ;
 i ++ ) if ( u == ra_chars [ i ] ) return true ;
 return false ;
 }