int _WriteType42SFNTS ( FILE * type42 , SplineFont * sf , enum fontformat format , int flags , EncMap * map , int layer ) {
 struct alltabs at ;
 int i ;
 locale_t tmplocale ;
 locale_t oldlocale ;
 switch_to_c_locale ( & tmplocale , & oldlocale ) ;
 if ( sf -> subfontcnt != 0 ) sf = sf -> subfonts [ 0 ] ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) sf -> glyphs [ i ] -> ttf_glyph = - 1 ;
 memset ( & at , '\0' , sizeof ( struct alltabs ) ) ;
 ATinit ( & at , sf , map , flags , layer , format , bf_none , NULL ) ;
 at . applemode = false ;
 at . opentypemode = false ;
 if ( initTables ( & at , sf , format , NULL , bf_none ) ) dumptype42 ( type42 , & at , format ) ;
 free ( at . gi . loca ) ;
 switch_to_old_locale ( & tmplocale , & oldlocale ) ;
 if ( at . error || ferror ( type42 ) ) return ( 0 ) ;
 return ( 1 ) ;
 }