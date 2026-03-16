static int compute_rd_thresh_factor ( int qindex ) {
 const int q = ( int ) ( pow ( vp9_dc_quant ( qindex , 0 ) / 4.0 , RD_THRESH_POW ) * 5.12 ) ;
 return MAX ( q , 8 ) ;
 }