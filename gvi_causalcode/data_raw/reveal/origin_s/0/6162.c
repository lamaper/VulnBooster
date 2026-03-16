static void read_bundle ( GetBitContext * gb , BinkContext * c , int bundle_num ) {
 int i ;
 if ( bundle_num == BINK_SRC_COLORS ) {
 for ( i = 0 ;
 i < 16 ;
 i ++ ) read_tree ( gb , & c -> col_high [ i ] ) ;
 c -> col_lastval = 0 ;
 }
 if ( bundle_num != BINK_SRC_INTRA_DC && bundle_num != BINK_SRC_INTER_DC ) read_tree ( gb , & c -> bundle [ bundle_num ] . tree ) ;
 c -> bundle [ bundle_num ] . cur_dec = c -> bundle [ bundle_num ] . cur_ptr = c -> bundle [ bundle_num ] . data ;
 }