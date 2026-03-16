void archive_string_conversion_set_opt ( struct archive_string_conv * sc , int opt ) {
 switch ( opt ) {
 case SCONV_SET_OPT_UTF8_LIBARCHIVE2X : # if ( defined ( _WIN32 ) && ! defined ( __CYGWIN__ ) ) || defined ( __STDC_ISO_10646__ ) || defined ( __APPLE__ ) ( void ) sc ;

 sc -> flag |= SCONV_UTF8_LIBARCHIVE_2 ;
 setup_converter ( sc ) ;
 }

 case SCONV_SET_OPT_NORMALIZATION_C : if ( ( sc -> flag & SCONV_NORMALIZATION_C ) == 0 ) {
 sc -> flag |= SCONV_NORMALIZATION_C ;
 sc -> flag &= ~ SCONV_NORMALIZATION_D ;
 setup_converter ( sc ) ;
 }
 break ;
 case SCONV_SET_OPT_NORMALIZATION_D : # if defined ( HAVE_ICONV ) if ( ! ( sc -> flag & SCONV_WIN_CP ) && ( sc -> flag & ( SCONV_FROM_UTF16 | SCONV_FROM_UTF8 ) ) && ! ( sc -> flag & ( SCONV_TO_UTF16 | SCONV_TO_UTF8 ) ) ) break ;

 sc -> flag |= SCONV_NORMALIZATION_D ;
 sc -> flag &= ~ SCONV_NORMALIZATION_C ;
 setup_converter ( sc ) ;
 }
 break ;
 default : break ;
 }
 }