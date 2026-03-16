void ff_cavs_init_mb ( AVSContext * h ) {
 int i ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) {
 h -> mv [ MV_FWD_B2 + i ] = h -> top_mv [ 0 ] [ h -> mbx * 2 + i ] ;
 h -> mv [ MV_BWD_B2 + i ] = h -> top_mv [ 1 ] [ h -> mbx * 2 + i ] ;
 }
 h -> pred_mode_Y [ 1 ] = h -> top_pred_Y [ h -> mbx * 2 + 0 ] ;
 h -> pred_mode_Y [ 2 ] = h -> top_pred_Y [ h -> mbx * 2 + 1 ] ;
 if ( ! ( h -> flags & B_AVAIL ) ) {
 h -> mv [ MV_FWD_B2 ] = un_mv ;
 h -> mv [ MV_FWD_B3 ] = un_mv ;
 h -> mv [ MV_BWD_B2 ] = un_mv ;
 h -> mv [ MV_BWD_B3 ] = un_mv ;
 h -> pred_mode_Y [ 1 ] = h -> pred_mode_Y [ 2 ] = NOT_AVAIL ;
 h -> flags &= ~ ( C_AVAIL | D_AVAIL ) ;
 }
 else if ( h -> mbx ) {
 h -> flags |= D_AVAIL ;
 }
 if ( h -> mbx == h -> mb_width - 1 ) h -> flags &= ~ C_AVAIL ;
 if ( ! ( h -> flags & C_AVAIL ) ) {
 h -> mv [ MV_FWD_C2 ] = un_mv ;
 h -> mv [ MV_BWD_C2 ] = un_mv ;
 }
 if ( ! ( h -> flags & D_AVAIL ) ) {
 h -> mv [ MV_FWD_D3 ] = un_mv ;
 h -> mv [ MV_BWD_D3 ] = un_mv ;
 }
 }