static void set_default_lf_deltas ( VP8_COMP * cpi ) {
 cpi -> mb . e_mbd . mode_ref_lf_delta_enabled = 1 ;
 cpi -> mb . e_mbd . mode_ref_lf_delta_update = 1 ;
 vpx_memset ( cpi -> mb . e_mbd . ref_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . ref_lf_deltas ) ) ;
 vpx_memset ( cpi -> mb . e_mbd . mode_lf_deltas , 0 , sizeof ( cpi -> mb . e_mbd . mode_lf_deltas ) ) ;
 cpi -> mb . e_mbd . ref_lf_deltas [ INTRA_FRAME ] = 2 ;
 cpi -> mb . e_mbd . ref_lf_deltas [ LAST_FRAME ] = 0 ;
 cpi -> mb . e_mbd . ref_lf_deltas [ GOLDEN_FRAME ] = - 2 ;
 cpi -> mb . e_mbd . ref_lf_deltas [ ALTREF_FRAME ] = - 2 ;
 cpi -> mb . e_mbd . mode_lf_deltas [ 0 ] = 4 ;
 if ( cpi -> oxcf . Mode == MODE_REALTIME ) cpi -> mb . e_mbd . mode_lf_deltas [ 1 ] = - 12 ;
 else cpi -> mb . e_mbd . mode_lf_deltas [ 1 ] = - 2 ;
 cpi -> mb . e_mbd . mode_lf_deltas [ 2 ] = 2 ;
 cpi -> mb . e_mbd . mode_lf_deltas [ 3 ] = 4 ;
 }