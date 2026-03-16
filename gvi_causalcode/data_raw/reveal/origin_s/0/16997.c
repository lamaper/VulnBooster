int _WriteTTFFont ( FILE * ttf , SplineFont * sf , enum fontformat format , int32 * bsizes , enum bitmapformat bf , int flags , EncMap * map , int layer ) {
 struct alltabs at ;
 int i , anyglyphs ;
 short_too_long_warned = 0 ;
 locale_t tmplocale ;
 locale_t oldlocale ;
 switch_to_c_locale ( & tmplocale , & oldlocale ) ;
 if ( format == ff_otfcid || format == ff_cffcid ) {
 if ( sf -> cidmaster ) sf = sf -> cidmaster ;
 }
 else {
 if ( sf -> subfontcnt != 0 ) sf = sf -> subfonts [ 0 ] ;
 }
 if ( sf -> subfontcnt == 0 ) {
 anyglyphs = false ;
 for ( i = sf -> glyphcnt - 1 ;
 i >= 0 ;
 -- i ) {
 if ( SCWorthOutputting ( sf -> glyphs [ i ] ) ) {
 anyglyphs = true ;
 if ( sf -> glyphs [ i ] -> unicodeenc != - 1 ) break ;
 }
 }
 if ( ! anyglyphs && ! sf -> internal_temp ) {
 ff_post_error ( _ ( "No Encoded Glyphs" ) , _ ( "Warning: Font contained no glyphs" ) ) ;
 }
 if ( format != ff_ttfsym && ! ( flags & ttf_flag_symbol ) && ! sf -> internal_temp ) {
 if ( i < 0 && anyglyphs ) {
 if ( map -> enccount <= 256 ) {
 char * buts [ 3 ] ;
 buts [ 0 ] = _ ( "_Yes" ) ;
 buts [ 1 ] = _ ( "_No" ) ;
 buts [ 2 ] = NULL ;
 if ( ff_ask ( _ ( "No Encoded Glyphs" ) , ( const char * * ) buts , 0 , 1 , _ ( "This font contains no glyphs with unicode encodings.\nWould you like to use a \"Symbol\" encoding instead of Unicode?" ) ) == 0 ) flags |= ttf_flag_symbol ;
 }
 else ff_post_error ( _ ( "No Encoded Glyphs" ) , _ ( "This font contains no glyphs with unicode encodings.\nYou will probably not be able to use the output." ) ) ;
 }
 }
 }
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) sf -> glyphs [ i ] -> ttf_glyph = - 1 ;
 memset ( & at , '\0' , sizeof ( struct alltabs ) ) ;
 ATinit ( & at , sf , map , flags , layer , format , bf , bsizes ) ;
 if ( format == ff_cff || format == ff_cffcid ) {
 dumpcff ( & at , sf , format , ttf ) ;
 }
 else {
 if ( initTables ( & at , sf , format , bsizes , bf ) ) dumpttf ( ttf , & at ) ;
 }
 switch_to_old_locale ( & tmplocale , & oldlocale ) ;
 if ( at . error || ferror ( ttf ) ) return ( 0 ) ;

 struct stat buf ;
 fstat ( fileno ( ttf ) , & buf ) ;
 fchmod ( fileno ( ttf ) , S_IXUSR | buf . st_mode ) ;
 }

 }