static void segmentation_test_function ( VP8_COMP * cpi ) {
 unsigned char * seg_map ;
 signed char feature_data [ MB_LVL_MAX ] [ MAX_MB_SEGMENTS ] ;
 CHECK_MEM_ERROR ( seg_map , vpx_calloc ( cpi -> common . mb_rows * cpi -> common . mb_cols , 1 ) ) ;
 set_segmentation_map ( cpi , seg_map ) ;
 enable_segmentation ( cpi ) ;
 feature_data [ MB_LVL_ALT_Q ] [ 0 ] = 0 ;
 feature_data [ MB_LVL_ALT_Q ] [ 1 ] = 4 ;
 feature_data [ MB_LVL_ALT_Q ] [ 2 ] = 0 ;
 feature_data [ MB_LVL_ALT_Q ] [ 3 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 0 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 1 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 2 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 3 ] = 0 ;
 set_segment_data ( cpi , & feature_data [ 0 ] [ 0 ] , SEGMENT_DELTADATA ) ;
 vpx_free ( seg_map ) ;
 seg_map = 0 ;
 }