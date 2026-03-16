static void setup_converter ( struct archive_string_conv * sc ) {
 sc -> nconverter = 0 ;
 if ( sc -> flag & SCONV_UTF8_LIBARCHIVE_2 ) {
 add_converter ( sc , strncat_from_utf8_libarchive2 ) ;
 return ;
 }
 if ( sc -> flag & SCONV_TO_UTF16 ) {
 if ( sc -> flag & SCONV_FROM_UTF8 ) {
 add_converter ( sc , archive_string_append_unicode ) ;
 return ;
 }

 if ( sc -> flag & SCONV_TO_UTF16BE ) add_converter ( sc , win_strncat_to_utf16be ) ;
 else add_converter ( sc , win_strncat_to_utf16le ) ;
 return ;
 }

 add_converter ( sc , iconv_strncat_in_locale ) ;
 return ;
 }

 if ( sc -> flag & SCONV_TO_UTF16BE ) add_converter ( sc , best_effort_strncat_to_utf16be ) ;
 else add_converter ( sc , best_effort_strncat_to_utf16le ) ;
 }
 else sc -> nconverter = 0 ;
 return ;
 }
 if ( sc -> flag & SCONV_FROM_UTF16 ) {
 if ( sc -> flag & SCONV_NORMALIZATION_D ) add_converter ( sc , archive_string_normalize_D ) ;
 else if ( sc -> flag & SCONV_NORMALIZATION_C ) add_converter ( sc , archive_string_normalize_C ) ;
 if ( sc -> flag & SCONV_TO_UTF8 ) {
 if ( ! ( sc -> flag & ( SCONV_NORMALIZATION_D | SCONV_NORMALIZATION_C ) ) ) add_converter ( sc , archive_string_append_unicode ) ;
 return ;
 }

 if ( sc -> flag & SCONV_FROM_UTF16BE ) add_converter ( sc , win_strncat_from_utf16be ) ;
 else add_converter ( sc , win_strncat_from_utf16le ) ;
 return ;
 }

 add_converter ( sc , iconv_strncat_in_locale ) ;
 return ;
 }

 else if ( ( sc -> flag & ( SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE ) ) == ( SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE ) ) add_converter ( sc , best_effort_strncat_from_utf16le ) ;
 else sc -> nconverter = 0 ;
 return ;
 }
 if ( sc -> flag & SCONV_FROM_UTF8 ) {
 if ( sc -> flag & SCONV_NORMALIZATION_D ) add_converter ( sc , archive_string_normalize_D ) ;
 else if ( sc -> flag & SCONV_NORMALIZATION_C ) add_converter ( sc , archive_string_normalize_C ) ;
 if ( sc -> flag & SCONV_TO_UTF8 ) {
 if ( ! ( sc -> flag & ( SCONV_NORMALIZATION_D | SCONV_NORMALIZATION_C ) ) ) add_converter ( sc , strncat_from_utf8_to_utf8 ) ;
 return ;
 }
 }

 add_converter ( sc , strncat_in_codepage ) ;
 return ;
 }

 add_converter ( sc , iconv_strncat_in_locale ) ;
 if ( ( sc -> flag & SCONV_FROM_CHARSET ) && ( sc -> flag & SCONV_TO_UTF8 ) ) {
 if ( sc -> flag & SCONV_NORMALIZATION_D ) add_converter ( sc , archive_string_normalize_D ) ;
 }
 return ;
 }

 else sc -> nconverter = 0 ;
 }