static FILE * NeedsUCS4Table ( SplineFont * sf , int * ucs4len , EncMap * map ) {
 int i = 0 , j , group ;
 FILE * format12 ;
 SplineChar * sc ;
 EncMap * freeme = NULL ;
 struct altuni * altuni ;
 if ( map -> enc -> is_unicodefull ) i = 0x10000 ;
 else if ( map -> enc -> is_custom ) i = 0 ;
 else i = map -> enc -> char_cnt ;
 for ( ;
 i < map -> enccount ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) ) {
 if ( sf -> glyphs [ map -> map [ i ] ] -> unicodeenc >= 0x10000 ) break ;
 for ( altuni = sf -> glyphs [ map -> map [ i ] ] -> altuni ;
 altuni != NULL && ( altuni -> unienc < 0x10000 || altuni -> vs != - 1 || altuni -> fid != 0 ) ;
 altuni = altuni -> next ) ;
 if ( altuni != NULL ) break ;
 }
 }
 if ( i >= map -> enccount ) return ( NULL ) ;
 if ( ! map -> enc -> is_unicodefull ) map = freeme = EncMapFromEncoding ( sf , FindOrMakeEncoding ( "ucs4" ) ) ;
 format12 = tmpfile ( ) ;
 if ( format12 == NULL ) return ( NULL ) ;
 putshort ( format12 , 12 ) ;
 putshort ( format12 , 0 ) ;
 putlong ( format12 , 0 ) ;
 putlong ( format12 , 0 ) ;
 putlong ( format12 , 0 ) ;
 group = 0 ;
 for ( i = 0 ;
 i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ i ] ] ) && sf -> glyphs [ map -> map [ i ] ] -> unicodeenc != - 1 ) {
 sc = sf -> glyphs [ map -> map [ i ] ] ;
 for ( j = i + 1 ;
 j < map -> enccount && map -> map [ j ] != - 1 && SCWorthOutputting ( sf -> glyphs [ map -> map [ j ] ] ) && sf -> glyphs [ map -> map [ j ] ] -> unicodeenc != - 1 && sf -> glyphs [ map -> map [ j ] ] -> ttf_glyph == sc -> ttf_glyph + j - i ;
 ++ j ) ;
 -- j ;
 putlong ( format12 , i ) ;
 putlong ( format12 , j ) ;
 putlong ( format12 , sc -> ttf_glyph ) ;
 ++ group ;
 i = j ;
 }
 * ucs4len = ftell ( format12 ) ;
 fseek ( format12 , 4 , SEEK_SET ) ;
 putlong ( format12 , * ucs4len ) ;
 putlong ( format12 , 0 ) ;
 putlong ( format12 , group ) ;
 rewind ( format12 ) ;
 if ( freeme != NULL ) EncMapFree ( freeme ) ;
 return ( format12 ) ;
 }