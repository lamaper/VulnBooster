hb_unicode_funcs_t * hb_icu_get_unicode_funcs ( void ) {
 static const hb_unicode_funcs_t _hb_icu_unicode_funcs = {
 HB_OBJECT_HEADER_STATIC , NULL , true , {

 }
 ;

 UErrorCode icu_err = U_ZERO_ERROR ;
 hb_atomic_ptr_cmpexch ( & normalizer , NULL , unorm2_getNFCInstance ( & icu_err ) ) ;
 }

 }