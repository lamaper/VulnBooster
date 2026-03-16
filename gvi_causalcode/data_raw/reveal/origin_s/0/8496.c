static void mdb_writewait ( Operation * op , slap_callback * sc ) {
 ww_ctx * ww = sc -> sc_private ;
 if ( ! ww -> flag ) {
 mdb_rtxn_snap ( op , ww ) ;
 }
 }