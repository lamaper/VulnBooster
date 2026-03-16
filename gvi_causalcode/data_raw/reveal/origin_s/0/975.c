void PNGAPI png_set_sRGB_gAMA_and_cHRM ( png_structp png_ptr , png_infop info_ptr , int intent ) {





 if ( png_ptr == NULL || info_ptr == NULL ) return ;
 png_set_sRGB ( png_ptr , info_ptr , intent ) ;

 png_set_gAMA ( png_ptr , info_ptr , file_gamma ) ;

 png_set_gAMA_fixed ( png_ptr , info_ptr , int_file_gamma ) ;

 int_white_y = 32900L ;
 int_red_x = 64000L ;
 int_red_y = 33000L ;
 int_green_x = 30000L ;
 int_green_y = 60000L ;
 int_blue_x = 15000L ;
 int_blue_y = 6000L ;
 png_set_cHRM_fixed ( png_ptr , info_ptr , int_white_x , int_white_y , int_red_x , int_red_y , int_green_x , int_green_y , int_blue_x , int_blue_y ) ;

 white_y = ( float ) .3290 ;
 red_x = ( float ) .64 ;
 red_y = ( float ) .33 ;
 green_x = ( float ) .30 ;
 green_y = ( float ) .60 ;
 blue_x = ( float ) .15 ;
 blue_y = ( float ) .06 ;
 png_set_cHRM ( png_ptr , info_ptr , white_x , white_y , red_x , red_y , green_x , green_y , blue_x , blue_y ) ;
