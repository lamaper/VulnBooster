static int do_16x16_motion_search ( VP9_COMP * cpi , const MV * ref_mv , int_mv * dst_mv , int mb_row , int mb_col ) {
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 unsigned int err , tmp_err ;
 MV tmp_mv ;
 err = vp9_sad16x16 ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , xd -> plane [ 0 ] . pre [ 0 ] . buf , xd -> plane [ 0 ] . pre [ 0 ] . stride ) ;
 dst_mv -> as_int = 0 ;
 tmp_err = do_16x16_motion_iteration ( cpi , ref_mv , & tmp_mv , mb_row , mb_col ) ;
 if ( tmp_err < err ) {
 err = tmp_err ;
 dst_mv -> as_mv = tmp_mv ;
 }
 if ( ref_mv -> row != 0 || ref_mv -> col != 0 ) {
 unsigned int tmp_err ;
 MV zero_ref_mv = {
 0 , 0 }
 , tmp_mv ;
 tmp_err = do_16x16_motion_iteration ( cpi , & zero_ref_mv , & tmp_mv , mb_row , mb_col ) ;
 if ( tmp_err < err ) {
 dst_mv -> as_mv = tmp_mv ;
 err = tmp_err ;
 }
 }
 return err ;
 }