static void update_mbgraph_mb_stats ( VP9_COMP * cpi , MBGRAPH_MB_STATS * stats , YV12_BUFFER_CONFIG * buf , int mb_y_offset , YV12_BUFFER_CONFIG * golden_ref , const MV * prev_golden_ref_mv , YV12_BUFFER_CONFIG * alt_ref , int mb_row , int mb_col ) {
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 int intra_error ;
 VP9_COMMON * cm = & cpi -> common ;
 x -> plane [ 0 ] . src . buf = buf -> y_buffer + mb_y_offset ;
 x -> plane [ 0 ] . src . stride = buf -> y_stride ;
 xd -> plane [ 0 ] . dst . buf = get_frame_new_buffer ( cm ) -> y_buffer + mb_y_offset ;
 xd -> plane [ 0 ] . dst . stride = get_frame_new_buffer ( cm ) -> y_stride ;
 intra_error = find_best_16x16_intra ( cpi , & stats -> ref [ INTRA_FRAME ] . m . mode ) ;
 if ( intra_error <= 0 ) intra_error = 1 ;
 stats -> ref [ INTRA_FRAME ] . err = intra_error ;
 if ( golden_ref ) {
 int g_motion_error ;
 xd -> plane [ 0 ] . pre [ 0 ] . buf = golden_ref -> y_buffer + mb_y_offset ;
 xd -> plane [ 0 ] . pre [ 0 ] . stride = golden_ref -> y_stride ;
 g_motion_error = do_16x16_motion_search ( cpi , prev_golden_ref_mv , & stats -> ref [ GOLDEN_FRAME ] . m . mv , mb_row , mb_col ) ;
 stats -> ref [ GOLDEN_FRAME ] . err = g_motion_error ;
 }
 else {
 stats -> ref [ GOLDEN_FRAME ] . err = INT_MAX ;
 stats -> ref [ GOLDEN_FRAME ] . m . mv . as_int = 0 ;
 }
 if ( alt_ref ) {
 int a_motion_error ;
 xd -> plane [ 0 ] . pre [ 0 ] . buf = alt_ref -> y_buffer + mb_y_offset ;
 xd -> plane [ 0 ] . pre [ 0 ] . stride = alt_ref -> y_stride ;
 a_motion_error = do_16x16_zerozero_search ( cpi , & stats -> ref [ ALTREF_FRAME ] . m . mv ) ;
 stats -> ref [ ALTREF_FRAME ] . err = a_motion_error ;
 }
 else {
 stats -> ref [ ALTREF_FRAME ] . err = INT_MAX ;
 stats -> ref [ ALTREF_FRAME ] . m . mv . as_int = 0 ;
 }
 }