int vp9_get_preview_raw_frame ( VP9_COMP * cpi , YV12_BUFFER_CONFIG * dest , vp9_ppflags_t * flags ) {
 VP9_COMMON * cm = & cpi -> common ;


 return - 1 ;
 }
 else {
 int ret ;


 * dest = * cm -> frame_to_show ;
 dest -> y_width = cm -> width ;
 dest -> y_height = cm -> height ;
 dest -> uv_width = cm -> width >> cm -> subsampling_x ;
 dest -> uv_height = cm -> height >> cm -> subsampling_y ;
 ret = 0 ;
 }
 else {
 ret = - 1 ;
 }

 return ret ;
 }
 }