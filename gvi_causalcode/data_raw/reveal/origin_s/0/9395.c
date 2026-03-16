static int do_16x16_zerozero_search ( VP9_COMP * cpi , int_mv * dst_mv ) {
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 unsigned int err ;
 err = vp9_sad16x16 ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , xd -> plane [ 0 ] . pre [ 0 ] . buf , xd -> plane [ 0 ] . pre [ 0 ] . stride ) ;
 dst_mv -> as_int = 0 ;
 return err ;
 }