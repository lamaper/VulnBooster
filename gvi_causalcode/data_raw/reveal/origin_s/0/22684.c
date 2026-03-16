static void binkb_init_bundle ( BinkContext * c , int bundle_num ) {
 c -> bundle [ bundle_num ] . cur_dec = c -> bundle [ bundle_num ] . cur_ptr = c -> bundle [ bundle_num ] . data ;
 c -> bundle [ bundle_num ] . len = 13 ;
 }