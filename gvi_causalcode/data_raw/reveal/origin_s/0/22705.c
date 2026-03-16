static int resize_key_frame ( VP8_COMP * cpi ) {

 if ( cpi -> oxcf . allow_spatial_resampling && ( cpi -> oxcf . end_usage == USAGE_STREAM_FROM_SERVER ) ) {
 int UNINITIALIZED_IS_SAFE ( hr ) , UNINITIALIZED_IS_SAFE ( hs ) ;
 int UNINITIALIZED_IS_SAFE ( vr ) , UNINITIALIZED_IS_SAFE ( vs ) ;
 int new_width , new_height ;
 if ( cpi -> buffer_level < ( cpi -> oxcf . resample_down_water_mark * cpi -> oxcf . optimal_buffer_level / 100 ) ) {
 cm -> horiz_scale = ( cm -> horiz_scale < ONETWO ) ? cm -> horiz_scale + 1 : ONETWO ;
 cm -> vert_scale = ( cm -> vert_scale < ONETWO ) ? cm -> vert_scale + 1 : ONETWO ;
 }
 else if ( cpi -> buffer_level > ( cpi -> oxcf . resample_up_water_mark * cpi -> oxcf . optimal_buffer_level / 100 ) ) {
 cm -> horiz_scale = ( cm -> horiz_scale > NORMAL ) ? cm -> horiz_scale - 1 : NORMAL ;
 cm -> vert_scale = ( cm -> vert_scale > NORMAL ) ? cm -> vert_scale - 1 : NORMAL ;
 }
 Scale2Ratio ( cm -> horiz_scale , & hr , & hs ) ;
 Scale2Ratio ( cm -> vert_scale , & vr , & vs ) ;
 new_width = ( ( hs - 1 ) + ( cpi -> oxcf . Width * hr ) ) / hs ;
 new_height = ( ( vs - 1 ) + ( cpi -> oxcf . Height * vr ) ) / vs ;
 if ( ( cm -> Width != new_width ) || ( cm -> Height != new_height ) ) {
 cm -> Width = new_width ;
 cm -> Height = new_height ;
 vp8_alloc_compressor_data ( cpi ) ;
 scale_and_extend_source ( cpi -> un_scaled_source , cpi ) ;
 return 1 ;
 }
 }

 }