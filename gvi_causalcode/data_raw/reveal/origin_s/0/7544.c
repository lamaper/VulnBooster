static Selectivity regex_selectivity ( const char * patt , int pattlen , bool case_insensitive , int fixed_prefix_len ) {
 Selectivity sel ;
 if ( pattlen > 0 && patt [ pattlen - 1 ] == '$' && ( pattlen == 1 || patt [ pattlen - 2 ] != '\\' ) ) {
 sel = regex_selectivity_sub ( patt , pattlen - 1 , case_insensitive ) ;
 }
 else {
 sel = regex_selectivity_sub ( patt , pattlen , case_insensitive ) ;
 sel *= FULL_WILDCARD_SEL ;
 }
 if ( fixed_prefix_len > 0 ) sel /= pow ( FIXED_CHAR_SEL , fixed_prefix_len ) ;
 CLAMP_PROBABILITY ( sel ) ;
 return sel ;
 }