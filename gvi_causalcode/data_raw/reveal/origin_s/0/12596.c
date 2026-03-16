static void binkb_init_bundles ( BinkContext * c ) {
 int i ;
 for ( i = 0 ;
 i < BINKB_NB_SRC ;
 i ++ ) binkb_init_bundle ( c , i ) ;
 }