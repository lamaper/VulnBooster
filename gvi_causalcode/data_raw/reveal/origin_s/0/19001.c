const YV12_BUFFER_CONFIG * vp9_get_scaled_ref_frame ( const VP9_COMP * cpi , int ref_frame ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const int ref_idx = cm -> ref_frame_map [ get_ref_frame_idx ( cpi , ref_frame ) ] ;
 const int scaled_idx = cpi -> scaled_ref_idx [ ref_frame - 1 ] ;
 return ( scaled_idx != ref_idx ) ? & cm -> frame_bufs [ scaled_idx ] . buf : NULL ;
 }