static int cmp_fpel_internal ( MpegEncContext * s , const int x , const int y , const int size , const int h , int ref_index , int src_index , me_cmp_func cmp_func , me_cmp_func chroma_cmp_func , const int flags ) {
 if ( flags & FLAG_DIRECT ) {
 return cmp_direct_inline ( s , x , y , 0 , 0 , size , h , ref_index , src_index , cmp_func , chroma_cmp_func , flags & FLAG_QPEL ) ;
 }
 else {
 return cmp_inline ( s , x , y , 0 , 0 , size , h , ref_index , src_index , cmp_func , chroma_cmp_func , 0 , flags & FLAG_CHROMA ) ;
 }
 }