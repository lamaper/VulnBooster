static int cmp_simple ( MpegEncContext * s , const int x , const int y , int ref_index , int src_index , me_cmp_func cmp_func , me_cmp_func chroma_cmp_func ) {
 return cmp_inline ( s , x , y , 0 , 0 , 0 , 16 , ref_index , src_index , cmp_func , chroma_cmp_func , 0 , 0 ) ;
 }