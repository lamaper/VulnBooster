static void init_scan_tables ( H264Context * h ) {
 int i ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {

 h -> field_scan [ i ] = T ( field_scan [ i ] ) ;

 for ( i = 0 ;
 i < 64 ;
 i ++ ) {

 h -> zigzag_scan8x8_cavlc [ i ] = T ( zigzag_scan8x8_cavlc [ i ] ) ;
 h -> field_scan8x8 [ i ] = T ( field_scan8x8 [ i ] ) ;
 h -> field_scan8x8_cavlc [ i ] = T ( field_scan8x8_cavlc [ i ] ) ;

 if ( h -> sps . transform_bypass ) {
 memcpy ( h -> zigzag_scan_q0 , zigzag_scan , sizeof ( h -> zigzag_scan_q0 ) ) ;
 memcpy ( h -> zigzag_scan8x8_q0 , ff_zigzag_direct , sizeof ( h -> zigzag_scan8x8_q0 ) ) ;
 memcpy ( h -> zigzag_scan8x8_cavlc_q0 , zigzag_scan8x8_cavlc , sizeof ( h -> zigzag_scan8x8_cavlc_q0 ) ) ;
 memcpy ( h -> field_scan_q0 , field_scan , sizeof ( h -> field_scan_q0 ) ) ;
 memcpy ( h -> field_scan8x8_q0 , field_scan8x8 , sizeof ( h -> field_scan8x8_q0 ) ) ;
 memcpy ( h -> field_scan8x8_cavlc_q0 , field_scan8x8_cavlc , sizeof ( h -> field_scan8x8_cavlc_q0 ) ) ;
 }
 else {
 memcpy ( h -> zigzag_scan_q0 , h -> zigzag_scan , sizeof ( h -> zigzag_scan_q0 ) ) ;
 memcpy ( h -> zigzag_scan8x8_q0 , h -> zigzag_scan8x8 , sizeof ( h -> zigzag_scan8x8_q0 ) ) ;
 memcpy ( h -> zigzag_scan8x8_cavlc_q0 , h -> zigzag_scan8x8_cavlc , sizeof ( h -> zigzag_scan8x8_cavlc_q0 ) ) ;
 memcpy ( h -> field_scan_q0 , h -> field_scan , sizeof ( h -> field_scan_q0 ) ) ;
 memcpy ( h -> field_scan8x8_q0 , h -> field_scan8x8 , sizeof ( h -> field_scan8x8_q0 ) ) ;
 memcpy ( h -> field_scan8x8_cavlc_q0 , h -> field_scan8x8_cavlc , sizeof ( h -> field_scan8x8_cavlc_q0 ) ) ;
 }
 }