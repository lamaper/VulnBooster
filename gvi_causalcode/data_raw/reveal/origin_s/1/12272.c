int vp9_compute_rd_mult ( const VP9_COMP * cpi , int qindex ) {
 const int q = vp9_dc_quant ( qindex , 0 ) ;
 int rdmult = 88 * q * q / 24 ;
 if ( cpi -> oxcf . pass == 2 && ( cpi -> common . frame_type != KEY_FRAME ) ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 const FRAME_UPDATE_TYPE frame_type = gf_group -> update_type [ gf_group -> index ] ;
 const int boost_index = MIN ( 15 , ( cpi -> rc . gfu_boost / 100 ) ) ;
 rdmult = ( rdmult * rd_frame_type_factor [ frame_type ] ) >> 7 ;
 rdmult += ( ( rdmult * rd_boost_factor [ boost_index ] ) >> 7 ) ;
 }
 return rdmult ;
 }