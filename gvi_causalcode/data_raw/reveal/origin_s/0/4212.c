static void zero_stats ( FIRSTPASS_STATS * section ) {
 section -> frame = 0.0 ;
 section -> intra_error = 0.0 ;
 section -> coded_error = 0.0 ;
 section -> sr_coded_error = 0.0 ;
 section -> pcnt_inter = 0.0 ;
 section -> pcnt_motion = 0.0 ;
 section -> pcnt_second_ref = 0.0 ;
 section -> pcnt_neutral = 0.0 ;
 section -> MVr = 0.0 ;
 section -> mvr_abs = 0.0 ;
 section -> MVc = 0.0 ;
 section -> mvc_abs = 0.0 ;
 section -> MVrv = 0.0 ;
 section -> MVcv = 0.0 ;
 section -> mv_in_out_count = 0.0 ;
 section -> new_mv_count = 0.0 ;
 section -> count = 0.0 ;
 section -> duration = 1.0 ;
 section -> spatial_layer_id = 0 ;
 }