void PNGAPI png_set_hIST ( png_structp png_ptr , png_infop info_ptr , png_uint_16p hist ) {
 int i ;
 png_debug1 ( 1 , "in %s storage function" , "hIST" ) ;
 if ( png_ptr == NULL || info_ptr == NULL ) return ;
 if ( info_ptr -> num_palette == 0 || info_ptr -> num_palette > PNG_MAX_PALETTE_LENGTH ) {
 png_warning ( png_ptr , "Invalid palette size, hIST allocation skipped." ) ;
 return ;
 }


 if ( png_ptr -> hist == NULL ) {
 png_warning ( png_ptr , "Insufficient memory for hIST chunk data." ) ;
 return ;
 }
 for ( i = 0 ;
 i < info_ptr -> num_palette ;
 i ++ ) png_ptr -> hist [ i ] = hist [ i ] ;
 info_ptr -> hist = png_ptr -> hist ;
 info_ptr -> valid |= PNG_INFO_hIST ;


