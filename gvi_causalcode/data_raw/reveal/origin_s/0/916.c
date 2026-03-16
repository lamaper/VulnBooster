void vp9_set_segment_data ( struct segmentation * seg , signed char * feature_data , unsigned char abs_delta ) {
 seg -> abs_delta = abs_delta ;
 vpx_memcpy ( seg -> feature_data , feature_data , sizeof ( seg -> feature_data ) ) ;
 }