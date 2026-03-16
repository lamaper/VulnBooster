static inline void set_mv_intra ( AVSContext * h ) {
 h -> mv [ MV_FWD_X0 ] = ff_cavs_intra_mv ;
 set_mvs ( & h -> mv [ MV_FWD_X0 ] , BLK_16X16 ) ;
 h -> mv [ MV_BWD_X0 ] = ff_cavs_intra_mv ;
 set_mvs ( & h -> mv [ MV_BWD_X0 ] , BLK_16X16 ) ;
 if ( h -> cur . f -> pict_type != AV_PICTURE_TYPE_B ) h -> col_type_base [ h -> mbidx ] = I_8X8 ;
 }