void OS2FigureUnicodeRanges ( SplineFont * sf , uint32 Ranges [ 4 ] ) {
 int i , k ;
 unsigned j ;
 SplineChar * sc ;
 SplineFont * sub ;
 memset ( Ranges , 0 , 4 * sizeof ( uint32 ) ) ;
 k = 0 ;
 do {
 sub = k < sf -> subfontcnt ? sf -> subfonts [ k ] : sf ;
 for ( i = 0 ;
 i < sub -> glyphcnt ;
 ++ i ) if ( ( sc = sub -> glyphs [ i ] ) != NULL ) {
 if ( SCWorthOutputting ( sc ) && sc -> unicodeenc != - 1 ) {
 if ( sc -> unicodeenc > 0xffff ) Ranges [ 57 >> 5 ] |= ( 1 << ( 57 & 31 ) ) ;
 for ( j = 0 ;
 j < sizeof ( uniranges ) / sizeof ( uniranges [ 0 ] ) ;
 ++ j ) if ( sc -> unicodeenc >= uniranges [ j ] [ 0 ] && sc -> unicodeenc <= uniranges [ j ] [ 1 ] ) {
 int bit = uniranges [ j ] [ 2 ] ;
 Ranges [ bit >> 5 ] |= ( 1 << ( bit & 31 ) ) ;
 break ;
 }
 }
 }
 ++ k ;
 }
 while ( k < sf -> subfontcnt ) ;
 }