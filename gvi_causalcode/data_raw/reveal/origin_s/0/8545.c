static void decode_cabac_residual_nondc_internal ( H264Context * h , int16_t * block , int cat , int n , const uint8_t * scantable , const uint32_t * qmul , int max_coeff ) {
 decode_cabac_residual_internal ( h , block , cat , n , scantable , qmul , max_coeff , 0 , 0 ) ;
 }