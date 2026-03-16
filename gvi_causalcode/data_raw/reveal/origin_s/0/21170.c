static void separate_arf_mbs ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int mb_col , mb_row , offset , i ;
 int mi_row , mi_col ;
 int ncnt [ 4 ] = {
 0 }
 ;
 int n_frames = cpi -> mbgraph_n_frames ;
 int * arf_not_zz ;
 CHECK_MEM_ERROR ( cm , arf_not_zz , vpx_calloc ( cm -> mb_rows * cm -> mb_cols * sizeof ( * arf_not_zz ) , 1 ) ) ;
 if ( n_frames > cpi -> rc . frames_till_gf_update_due ) n_frames = cpi -> rc . frames_till_gf_update_due ;
 for ( i = n_frames - 1 ;
 i >= 0 ;
 i -- ) {
 MBGRAPH_FRAME_STATS * frame_stats = & cpi -> mbgraph_stats [ i ] ;
 for ( offset = 0 , mb_row = 0 ;
 mb_row < cm -> mb_rows ;
 offset += cm -> mb_cols , mb_row ++ ) {
 for ( mb_col = 0 ;
 mb_col < cm -> mb_cols ;
 mb_col ++ ) {
 MBGRAPH_MB_STATS * mb_stats = & frame_stats -> mb_stats [ offset + mb_col ] ;
 int altref_err = mb_stats -> ref [ ALTREF_FRAME ] . err ;
 int intra_err = mb_stats -> ref [ INTRA_FRAME ] . err ;
 int golden_err = mb_stats -> ref [ GOLDEN_FRAME ] . err ;
 if ( altref_err > 1000 || altref_err > intra_err || altref_err > golden_err ) {
 arf_not_zz [ offset + mb_col ] ++ ;
 }
 }
 }
 }
 for ( mi_row = 0 ;
 mi_row < cm -> mi_rows ;
 mi_row ++ ) {
 for ( mi_col = 0 ;
 mi_col < cm -> mi_cols ;
 mi_col ++ ) {
 if ( arf_not_zz [ mi_row / 2 * cm -> mb_cols + mi_col / 2 ] ) {
 ncnt [ 0 ] ++ ;
 cpi -> segmentation_map [ mi_row * cm -> mi_cols + mi_col ] = 0 ;
 }
 else {
 cpi -> segmentation_map [ mi_row * cm -> mi_cols + mi_col ] = 1 ;
 ncnt [ 1 ] ++ ;
 }
 }
 }
 if ( 1 ) {
 if ( cm -> MBs ) cpi -> static_mb_pct = ( ncnt [ 1 ] * 100 ) / ( cm -> mi_rows * cm -> mi_cols ) ;
 else cpi -> static_mb_pct = 0 ;
 vp9_enable_segmentation ( & cm -> seg ) ;
 }
 else {
 cpi -> static_mb_pct = 0 ;
 vp9_disable_segmentation ( & cm -> seg ) ;
 }
 vpx_free ( arf_not_zz ) ;
 }