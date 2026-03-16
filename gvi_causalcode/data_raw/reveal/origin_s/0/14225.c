int vp9_get_mvpred_var ( const MACROBLOCK * x , const MV * best_mv , const MV * center_mv , const vp9_variance_fn_ptr_t * vfp , int use_mvcost ) {
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 const MV mv = {
 best_mv -> row * 8 , best_mv -> col * 8 }
 ;
 unsigned int unused ;
 return vfp -> vf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , best_mv ) , in_what -> stride , & unused ) + ( use_mvcost ? mv_err_cost ( & mv , center_mv , x -> nmvjointcost , x -> mvcost , x -> errorperbit ) : 0 ) ;
 }