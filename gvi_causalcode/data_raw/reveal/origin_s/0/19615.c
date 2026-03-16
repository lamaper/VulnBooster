int ff_cavs_next_mb ( AVSContext * h ) {
 int i ;
 h -> flags |= A_AVAIL ;
 h -> cy += 16 ;
 h -> cu += 8 ;
 h -> cv += 8 ;
 for ( i = 0 ;
 i <= 20 ;
 i += 4 ) h -> mv [ i ] = h -> mv [ i + 2 ] ;
 h -> top_mv [ 0 ] [ h -> mbx * 2 + 0 ] = h -> mv [ MV_FWD_X2 ] ;
 h -> top_mv [ 0 ] [ h -> mbx * 2 + 1 ] = h -> mv [ MV_FWD_X3 ] ;
 h -> top_mv [ 1 ] [ h -> mbx * 2 + 0 ] = h -> mv [ MV_BWD_X2 ] ;
 h -> top_mv [ 1 ] [ h -> mbx * 2 + 1 ] = h -> mv [ MV_BWD_X3 ] ;
 h -> mbidx ++ ;
 h -> mbx ++ ;
 if ( h -> mbx == h -> mb_width ) {
 / ew mb line h -> flags = B_AVAIL | C_AVAIL ;
 h -> pred_mode_Y [ 3 ] = h -> pred_mode_Y [ 6 ] = NOT_AVAIL ;
 for ( i = 0 ;
 i <= 20 ;
 i += 4 ) h -> mv [ i ] = un_mv ;
 h -> mbx = 0 ;
 h -> mby ++ ;
 h -> cy = h -> cur . f -> data [ 0 ] + h -> mby * 16 * h -> l_stride ;
 h -> cu = h -> cur . f -> data [ 1 ] + h -> mby * 8 * h -> c_stride ;
 h -> cv = h -> cur . f -> data [ 2 ] + h -> mby * 8 * h -> c_stride ;
 if ( h -> mby == h -> mb_height ) {
 return 0 ;
 }
 }
 return 1 ;
 }