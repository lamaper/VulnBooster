void PNGAPI png_set_cHRM_fixed ( png_structp png_ptr , png_infop info_ptr , png_fixed_point white_x , png_fixed_point white_y , png_fixed_point red_x , png_fixed_point red_y , png_fixed_point green_x , png_fixed_point green_y , png_fixed_point blue_x , png_fixed_point blue_y ) {
 png_debug1 ( 1 , "in %s storage function" , "cHRM fixed" ) ;
 if ( png_ptr == NULL || info_ptr == NULL ) return ;

 info_ptr -> int_x_white = white_x ;
 info_ptr -> int_y_white = white_y ;
 info_ptr -> int_x_red = red_x ;
 info_ptr -> int_y_red = red_y ;
 info_ptr -> int_x_green = green_x ;
 info_ptr -> int_y_green = green_y ;
 info_ptr -> int_x_blue = blue_x ;
 info_ptr -> int_y_blue = blue_y ;

 info_ptr -> y_white = ( float ) ( white_y / 100000. ) ;
 info_ptr -> x_red = ( float ) ( red_x / 100000. ) ;
 info_ptr -> y_red = ( float ) ( red_y / 100000. ) ;
 info_ptr -> x_green = ( float ) ( green_x / 100000. ) ;
 info_ptr -> y_green = ( float ) ( green_y / 100000. ) ;
 info_ptr -> x_blue = ( float ) ( blue_x / 100000. ) ;
 info_ptr -> y_blue = ( float ) ( blue_y / 100000. ) ;

 }
 }