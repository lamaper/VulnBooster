static inline int get_penalty_factor ( int lambda , int lambda2 , int type ) {
 switch ( type & 0xFF ) {
 default : case FF_CMP_SAD : return lambda >> FF_LAMBDA_SHIFT ;
 case FF_CMP_DCT : return ( 3 * lambda ) >> ( FF_LAMBDA_SHIFT + 1 ) ;
 case FF_CMP_SATD : case FF_CMP_DCT264 : return ( 2 * lambda ) >> FF_LAMBDA_SHIFT ;
 case FF_CMP_RD : case FF_CMP_PSNR : case FF_CMP_SSE : case FF_CMP_NSSE : return lambda2 >> FF_LAMBDA_SHIFT ;
 case FF_CMP_BIT : return 1 ;
 }
 }