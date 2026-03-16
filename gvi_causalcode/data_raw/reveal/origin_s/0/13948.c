YV12_BUFFER_CONFIG * vp9_scale_if_required ( VP9_COMMON * cm , YV12_BUFFER_CONFIG * unscaled , YV12_BUFFER_CONFIG * scaled ) {
 if ( cm -> mi_cols * MI_SIZE != unscaled -> y_width || cm -> mi_rows * MI_SIZE != unscaled -> y_height ) {
 scale_and_extend_frame_nonnormative ( unscaled , scaled ) ;
 return scaled ;
 }
 else {
 return unscaled ;
 }
 }