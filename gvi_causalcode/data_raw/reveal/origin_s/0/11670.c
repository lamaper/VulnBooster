static int pic_num_extract ( H264Context * h , int pic_num , int * structure ) {
 * structure = h -> picture_structure ;
 if ( FIELD_PICTURE ) {
 if ( ! ( pic_num & 1 ) ) * structure ^= PICT_FRAME ;
 pic_num >>= 1 ;
 }
 return pic_num ;
 }