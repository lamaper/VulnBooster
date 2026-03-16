static inline void mc_part_std ( AVSContext * h , int chroma_height , int delta , uint8_t * dest_y , uint8_t * dest_cb , uint8_t * dest_cr , int x_offset , int y_offset , qpel_mc_func * qpix_put , h264_chroma_mc_func chroma_put , qpel_mc_func * qpix_avg , h264_chroma_mc_func chroma_avg , cavs_vector * mv ) {
 qpel_mc_func * qpix_op = qpix_put ;
 h264_chroma_mc_func chroma_op = chroma_put ;
 dest_y += 2 * x_offset + 2 * y_offset * h -> l_stride ;
 dest_cb += x_offset + y_offset * h -> c_stride ;
 dest_cr += x_offset + y_offset * h -> c_stride ;
 x_offset += 8 * h -> mbx ;
 y_offset += 8 * h -> mby ;
 if ( mv -> ref >= 0 ) {
 AVFrame * ref = h -> DPB [ mv -> ref ] . f ;
 mc_dir_part ( h , ref , chroma_height , delta , 0 , dest_y , dest_cb , dest_cr , x_offset , y_offset , qpix_op , chroma_op , mv ) ;
 qpix_op = qpix_avg ;
 chroma_op = chroma_avg ;
 }
 if ( ( mv + MV_BWD_OFFS ) -> ref >= 0 ) {
 AVFrame * ref = h -> DPB [ 0 ] . f ;
 mc_dir_part ( h , ref , chroma_height , delta , 1 , dest_y , dest_cb , dest_cr , x_offset , y_offset , qpix_op , chroma_op , mv + MV_BWD_OFFS ) ;
 }
 }