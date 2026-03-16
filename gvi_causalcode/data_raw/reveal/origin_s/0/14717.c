static unsigned int get_sby_perpixel_variance ( VP9_COMP * cpi , const struct buf_2d * ref , BLOCK_SIZE bs ) {
 unsigned int sse ;
 const unsigned int var = cpi -> fn_ptr [ bs ] . vf ( ref -> buf , ref -> stride , VP9_VAR_OFFS , 0 , & sse ) ;
 return ROUND_POWER_OF_TWO ( var , num_pels_log2_lookup [ bs ] ) ;
 }