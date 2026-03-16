static unsigned int hb_icu_unicode_decompose_compatibility ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t u , hb_codepoint_t * decomposed , void * user_data HB_UNUSED ) {
 UChar utf16 [ 2 ] , normalized [ 2 * HB_UNICODE_MAX_DECOMPOSITION_LEN + 1 ] ;
 unsigned int len ;
 int32_t utf32_len ;
 hb_bool_t err ;
 UErrorCode icu_err ;
 len = 0 ;
 err = false ;
 U16_APPEND ( utf16 , len , ARRAY_LENGTH ( utf16 ) , u , err ) ;
 if ( err ) return 0 ;
 icu_err = U_ZERO_ERROR ;
 len = unorm_normalize ( utf16 , len , UNORM_NFKD , 0 , normalized , ARRAY_LENGTH ( normalized ) , & icu_err ) ;
 if ( icu_err ) return 0 ;
 icu_err = U_ZERO_ERROR ;
 u_strToUTF32 ( ( UChar32 * ) decomposed , HB_UNICODE_MAX_DECOMPOSITION_LEN , & utf32_len , normalized , len , & icu_err ) ;
 if ( icu_err ) return 0 ;
 return utf32_len ;
 }