static void convert_to_rgb32 ( uint8_t * dst , const uint8_t * src , int width , int loco ) {
 if ( loco ) convert_to_rgb32_loco ( dst , src , width , 1 ) ;
 else convert_to_rgb32_loco ( dst , src , width , 0 ) ;
 }