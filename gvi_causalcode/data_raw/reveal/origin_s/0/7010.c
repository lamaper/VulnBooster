static hb_bool_t hb_icu_unicode_compose ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t a , hb_codepoint_t b , hb_codepoint_t * ab , void * user_data HB_UNUSED ) {

 UChar32 ret = unorm2_composePair ( normalizer , a , b ) ;
 if ( ret < 0 ) return false ;
 * ab = ret ;
 return true ;
 }

 unsigned int len ;
 hb_bool_t ret , err ;
 UErrorCode icu_err ;
 len = 0 ;
 err = false ;
 U16_APPEND ( utf16 , len , ARRAY_LENGTH ( utf16 ) , a , err ) ;
 if ( err ) return false ;
 U16_APPEND ( utf16 , len , ARRAY_LENGTH ( utf16 ) , b , err ) ;
 if ( err ) return false ;
 icu_err = U_ZERO_ERROR ;
 len = unorm_normalize ( utf16 , len , UNORM_NFC , 0 , normalized , ARRAY_LENGTH ( normalized ) , & icu_err ) ;
 if ( U_FAILURE ( icu_err ) ) return false ;
 if ( u_countChar32 ( normalized , len ) == 1 ) {
 U16_GET_UNSAFE ( normalized , 0 , * ab ) ;
 ret = true ;
 }
 else {
 ret = false ;
 }
 return ret ;
 }