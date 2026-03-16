void vp9_default_coef_probs ( VP9_COMMON * cm ) {
 vp9_copy ( cm -> fc . coef_probs [ TX_4X4 ] , default_coef_probs_4x4 ) ;
 vp9_copy ( cm -> fc . coef_probs [ TX_8X8 ] , default_coef_probs_8x8 ) ;
 vp9_copy ( cm -> fc . coef_probs [ TX_16X16 ] , default_coef_probs_16x16 ) ;
 vp9_copy ( cm -> fc . coef_probs [ TX_32X32 ] , default_coef_probs_32x32 ) ;
 }