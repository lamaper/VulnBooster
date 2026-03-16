static hb_bool_t hb_icu_unicode_decompose ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t ab , hb_codepoint_t * a , hb_codepoint_t * b , void * user_data HB_UNUSED ) {

 UChar decomposed [ 4 ] ;
 int len ;
 UErrorCode icu_err = U_ZERO_ERROR ;
 len = unorm2_getRawDecomposition ( normalizer , ab , decomposed , ARRAY_LENGTH ( decomposed ) , & icu_err ) ;
 if ( U_FAILURE ( icu_err ) || len < 0 ) return false ;
 len = u_countChar32 ( decomposed , len ) ;
 if ( len == 1 ) {
 U16_GET_UNSAFE ( decomposed , 0 , * a ) ;
 * b = 0 ;
 return * a != ab ;
 }
 else if ( len == 2 ) {
 len = 0 ;
 U16_NEXT_UNSAFE ( decomposed , len , * a ) ;
 U16_NEXT_UNSAFE ( decomposed , len , * b ) ;
 }
 return true ;
 }

 unsigned int len ;
 hb_bool_t ret , err ;
 UErrorCode icu_err ;
 len = 0 ;
 err = false ;
 U16_APPEND ( utf16 , len , ARRAY_LENGTH ( utf16 ) , ab , err ) ;
 if ( err ) return false ;
 icu_err = U_ZERO_ERROR ;
 len = unorm_normalize ( utf16 , len , UNORM_NFD , 0 , normalized , ARRAY_LENGTH ( normalized ) , & icu_err ) ;
 if ( U_FAILURE ( icu_err ) ) return false ;
 len = u_countChar32 ( normalized , len ) ;
 if ( len == 1 ) {
 U16_GET_UNSAFE ( normalized , 0 , * a ) ;
 * b = 0 ;
 ret = * a != ab ;
 }
 else if ( len == 2 ) {
 len = 0 ;
 U16_NEXT_UNSAFE ( normalized , len , * a ) ;
 U16_NEXT_UNSAFE ( normalized , len , * b ) ;
 UChar recomposed [ 20 ] ;
 icu_err = U_ZERO_ERROR ;
 unorm_normalize ( normalized , len , UNORM_NFC , 0 , recomposed , ARRAY_LENGTH ( recomposed ) , & icu_err ) ;
 if ( U_FAILURE ( icu_err ) ) return false ;
 hb_codepoint_t c ;
 U16_GET_UNSAFE ( recomposed , 0 , c ) ;
 if ( c != * a && c != ab ) {
 * a = c ;
 * b = 0 ;
 }
 ret = true ;
 }
 else {
 U16_PREV_UNSAFE ( normalized , len , * b ) ;
 UChar recomposed [ 18 * 2 ] ;
 icu_err = U_ZERO_ERROR ;
 len = unorm_normalize ( normalized , len , UNORM_NFC , 0 , recomposed , ARRAY_LENGTH ( recomposed ) , & icu_err ) ;
 if ( U_FAILURE ( icu_err ) ) return false ;
 if ( unlikely ( u_countChar32 ( recomposed , len ) != 1 ) ) return false ;
 U16_GET_UNSAFE ( recomposed , 0 , * a ) ;
 ret = true ;
 }
 return ret ;
 }