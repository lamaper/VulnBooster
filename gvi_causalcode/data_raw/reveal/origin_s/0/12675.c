int WriteTTFFont ( char * fontname , SplineFont * sf , enum fontformat format , int32 * bsizes , enum bitmapformat bf , int flags , EncMap * map , int layer ) {
 FILE * ttf ;
 int ret ;
 if ( strstr ( fontname , "://" ) != NULL ) {
 if ( ( ttf = tmpfile ( ) ) == NULL ) return ( 0 ) ;
 }
 else {
 if ( ( ttf = fopen ( fontname , "wb+" ) ) == NULL ) return ( 0 ) ;
 }
 ret = _WriteTTFFont ( ttf , sf , format , bsizes , bf , flags , map , layer ) ;
 if ( strstr ( fontname , "://" ) != NULL && ret ) ret = URLFromFile ( fontname , ttf ) ;
 if ( ret && ( flags & ttf_flag_glyphmap ) ) DumpGlyphToNameMap ( fontname , sf ) ;
 if ( fclose ( ttf ) == - 1 ) return ( 0 ) ;
 return ( ret ) ;
 }