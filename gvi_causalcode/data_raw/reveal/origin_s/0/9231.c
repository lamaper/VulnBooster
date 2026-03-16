void ff_cavs_init_pic ( AVSContext * h ) {
 int i ;
 for ( i = 0 ;
 i <= 20 ;
 i += 4 ) h -> mv [ i ] = un_mv ;
 h -> mv [ MV_BWD_X0 ] = ff_cavs_dir_mv ;
 set_mvs ( & h -> mv [ MV_BWD_X0 ] , BLK_16X16 ) ;
 h -> mv [ MV_FWD_X0 ] = ff_cavs_dir_mv ;
 set_mvs ( & h -> mv [ MV_FWD_X0 ] , BLK_16X16 ) ;
 h -> pred_mode_Y [ 3 ] = h -> pred_mode_Y [ 6 ] = NOT_AVAIL ;
 h -> cy = h -> cur . f -> data [ 0 ] ;
 h -> cu = h -> cur . f -> data [ 1 ] ;
 h -> cv = h -> cur . f -> data [ 2 ] ;
 h -> l_stride = h -> cur . f -> linesize [ 0 ] ;
 h -> c_stride = h -> cur . f -> linesize [ 1 ] ;
 h -> luma_scan [ 2 ] = 8 * h -> l_stride ;
 h -> luma_scan [ 3 ] = 8 * h -> l_stride + 8 ;
 h -> mbx = h -> mby = h -> mbidx = 0 ;
 h -> flags = 0 ;
 }