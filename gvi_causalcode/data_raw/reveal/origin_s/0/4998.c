void vp9_tokenize_initialize ( ) {
 vp9_dct_value_tokens_ptr = dct_value_tokens + DCT_MAX_VALUE ;
 vp9_dct_value_cost_ptr = dct_value_cost + DCT_MAX_VALUE ;
 tokenize_init_one ( dct_value_tokens + DCT_MAX_VALUE , vp9_extra_bits , dct_value_cost + DCT_MAX_VALUE , DCT_MAX_VALUE ) ;

 vp9_dct_value_cost_high10_ptr = dct_value_cost_high10 + DCT_MAX_VALUE_HIGH10 ;
 tokenize_init_one ( dct_value_tokens_high10 + DCT_MAX_VALUE_HIGH10 , vp9_extra_bits_high10 , dct_value_cost_high10 + DCT_MAX_VALUE_HIGH10 , DCT_MAX_VALUE_HIGH10 ) ;
 vp9_dct_value_tokens_high12_ptr = dct_value_tokens_high12 + DCT_MAX_VALUE_HIGH12 ;
 vp9_dct_value_cost_high12_ptr = dct_value_cost_high12 + DCT_MAX_VALUE_HIGH12 ;
 tokenize_init_one ( dct_value_tokens_high12 + DCT_MAX_VALUE_HIGH12 , vp9_extra_bits_high12 , dct_value_cost_high12 + DCT_MAX_VALUE_HIGH12 , DCT_MAX_VALUE_HIGH12 ) ;
