static void rate_block ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , struct rdcost_block_args * args ) {
 int x_idx , y_idx ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & x_idx , & y_idx ) ;
 args -> rate = cost_coeffs ( args -> x , plane , block , args -> t_above + x_idx , args -> t_left + y_idx , tx_size , args -> so -> scan , args -> so -> neighbors , args -> use_fast_coef_costing ) ;
 }