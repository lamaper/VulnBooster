void ff_cavs_inter ( AVSContext * h , enum cavs_mb mb_type ) {
 if ( ff_cavs_partition_flags [ mb_type ] == 0 ) {
 mc_part_std ( h , 8 , 0 , h -> cy , h -> cu , h -> cv , 0 , 0 , h -> cdsp . put_cavs_qpel_pixels_tab [ 0 ] , h -> h264chroma . put_h264_chroma_pixels_tab [ 0 ] , h -> cdsp . avg_cavs_qpel_pixels_tab [ 0 ] , h -> h264chroma . avg_h264_chroma_pixels_tab [ 0 ] , & h -> mv [ MV_FWD_X0 ] ) ;
 }
 else {
 mc_part_std ( h , 4 , 0 , h -> cy , h -> cu , h -> cv , 0 , 0 , h -> cdsp . put_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . put_h264_chroma_pixels_tab [ 1 ] , h -> cdsp . avg_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . avg_h264_chroma_pixels_tab [ 1 ] , & h -> mv [ MV_FWD_X0 ] ) ;
 mc_part_std ( h , 4 , 0 , h -> cy , h -> cu , h -> cv , 4 , 0 , h -> cdsp . put_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . put_h264_chroma_pixels_tab [ 1 ] , h -> cdsp . avg_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . avg_h264_chroma_pixels_tab [ 1 ] , & h -> mv [ MV_FWD_X1 ] ) ;
 mc_part_std ( h , 4 , 0 , h -> cy , h -> cu , h -> cv , 0 , 4 , h -> cdsp . put_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . put_h264_chroma_pixels_tab [ 1 ] , h -> cdsp . avg_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . avg_h264_chroma_pixels_tab [ 1 ] , & h -> mv [ MV_FWD_X2 ] ) ;
 mc_part_std ( h , 4 , 0 , h -> cy , h -> cu , h -> cv , 4 , 4 , h -> cdsp . put_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . put_h264_chroma_pixels_tab [ 1 ] , h -> cdsp . avg_cavs_qpel_pixels_tab [ 1 ] , h -> h264chroma . avg_h264_chroma_pixels_tab [ 1 ] , & h -> mv [ MV_FWD_X3 ] ) ;
 }
 }