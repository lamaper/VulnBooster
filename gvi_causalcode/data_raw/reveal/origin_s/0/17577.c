static Picture * remove_long ( H264Context * h , int i , int ref_mask ) {
 Picture * pic ;
 pic = h -> long_ref [ i ] ;
 if ( pic ) {
 if ( unreference_pic ( h , pic , ref_mask ) ) {
 assert ( h -> long_ref [ i ] -> long_ref == 1 ) ;
 h -> long_ref [ i ] -> long_ref = 0 ;
 h -> long_ref [ i ] = NULL ;
 h -> long_ref_count -- ;
 }
 }
 return pic ;
 }