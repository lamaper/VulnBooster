static u_short create_keyword_scanner ( void ) {
 u_short scanner ;
 u_short i ;
 sst_highwater = 1 ;
 scanner = 0 ;
 for ( i = 0 ;
 i < COUNTOF ( ntp_keywords ) ;
 i ++ ) {
 current_keyword = ntp_keywords [ i ] . key ;
 scanner = create_scan_states ( ntp_keywords [ i ] . key , ntp_keywords [ i ] . token , ntp_keywords [ i ] . followedby , scanner ) ;
 }
 return scanner ;
 }