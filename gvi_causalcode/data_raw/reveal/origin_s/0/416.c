static void decode_cabac_residual_dc_internal_422 ( H264Context * h , int16_t * block , int cat , int n , const uint8_t * scantable , int max_coeff ) {
 decode_cabac_residual_internal ( h , block , cat , n , scantable , NULL , max_coeff , 1 , 1 ) ;
 }