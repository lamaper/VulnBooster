static FILE * NeedsUCS2Table ( SplineFont * sf , int * ucs2len , EncMap * map , int issymbol ) {
 uint32 * avail = malloc ( 65536 * sizeof ( uint32 ) ) ;
 int i , j , l ;
 int segcnt , cnt = 0 , delta , rpos ;
 struct cmapseg {
 uint16 start , end ;
 uint16 delta ;
 uint16 rangeoff ;
 }
 * cmapseg ;
 uint16 * ranges ;
 SplineChar * sc ;
 FILE * format4 = tmpfile ( ) ;
 memset ( avail , 0xff , 65536 * sizeof ( uint32 ) ) ;
 if ( map -> enc -> is_unicodebmp || map -> enc -> is_unicodefull ) {
 int gid ;
 for ( i = 0 ;
 i < 65536 && i < map -> enccount ;
 ++ i ) if ( ( gid = map -> map [ i ] ) != - 1 && sf -> glyphs [ gid ] != NULL && sf -> glyphs [ gid ] -> ttf_glyph != - 1 ) {
 avail [ i ] = gid ;
 ++ cnt ;
 }
 }
 else {
 struct altuni * altuni ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) {
 if ( ( sc = sf -> glyphs [ i ] ) != NULL && sc -> ttf_glyph != - 1 ) {
 if ( sc -> unicodeenc >= 0 && sc -> unicodeenc <= 0xffff ) {
 avail [ sc -> unicodeenc ] = i ;
 ++ cnt ;
 }
 for ( altuni = sc -> altuni ;
 altuni != NULL ;
 altuni = altuni -> next ) {
 if ( altuni -> unienc <= 0xffff && altuni -> vs == - 1 && altuni -> fid == 0 ) {
 avail [ altuni -> unienc ] = i ;
 ++ cnt ;
 }
 }
 }
 }
 }
 if ( issymbol ) {
 memset ( avail , 0xff , 0xf020 * sizeof ( uint32 ) ) ;
 memset ( avail + 0xf100 , 0xff , 0x0eff * sizeof ( uint32 ) ) ;
 }
 j = - 1 ;
 for ( i = segcnt = 0 ;
 i < 65536 ;
 ++ i ) {
 if ( avail [ i ] != 0xffffffff && j == - 1 ) {
 j = i ;
 ++ segcnt ;
 }
 else if ( j != - 1 && avail [ i ] == 0xffffffff ) j = - 1 ;
 }
 cmapseg = calloc ( segcnt + 1 , sizeof ( struct cmapseg ) ) ;
 ranges = malloc ( cnt * sizeof ( int16 ) ) ;
 j = - 1 ;
 for ( i = segcnt = 0 ;
 i < 65536 ;
 ++ i ) {
 if ( avail [ i ] != 0xffffffff && j == - 1 ) {
 j = i ;
 cmapseg [ segcnt ] . start = j ;
 ++ segcnt ;
 }
 else if ( j != - 1 && avail [ i ] == 0xffffffff ) {
 cmapseg [ segcnt - 1 ] . end = i - 1 ;
 j = - 1 ;
 }
 }
 if ( j != - 1 ) cmapseg [ segcnt - 1 ] . end = i - 1 ;
 cmapseg [ segcnt ] . start = cmapseg [ segcnt ] . end = 0xffff ;
 cmapseg [ segcnt ++ ] . delta = 1 ;
 rpos = 0 ;
 for ( i = 0 ;
 i < segcnt - 1 ;
 ++ i ) {
 l = avail [ cmapseg [ i ] . start ] ;
 sc = sf -> glyphs [ l ] ;
 delta = sc -> ttf_glyph - cmapseg [ i ] . start ;
 for ( j = cmapseg [ i ] . start ;
 j <= cmapseg [ i ] . end ;
 ++ j ) {
 l = avail [ j ] ;
 sc = sf -> glyphs [ l ] ;
 if ( delta != sc -> ttf_glyph - j ) break ;
 }
 if ( j > cmapseg [ i ] . end ) cmapseg [ i ] . delta = delta ;
 else {
 cmapseg [ i ] . rangeoff = ( rpos + ( segcnt - i ) ) * sizeof ( int16 ) ;
 for ( j = cmapseg [ i ] . start ;
 j <= cmapseg [ i ] . end ;
 ++ j ) {
 l = avail [ j ] ;
 sc = sf -> glyphs [ l ] ;
 ranges [ rpos ++ ] = sc -> ttf_glyph ;
 }
 }
 }
 free ( avail ) ;
 putshort ( format4 , 4 ) ;
 putshort ( format4 , ( 8 + 4 * segcnt + rpos ) * sizeof ( int16 ) ) ;
 putshort ( format4 , 0 ) ;
 putshort ( format4 , 2 * segcnt ) ;
 for ( j = 0 , i = 1 ;
 i <= segcnt ;
 i <<= 1 , ++ j ) ;
 putshort ( format4 , i ) ;
 putshort ( format4 , j - 1 ) ;
 putshort ( format4 , 2 * segcnt - i ) ;
 for ( i = 0 ;
 i < segcnt ;
 ++ i ) putshort ( format4 , cmapseg [ i ] . end ) ;
 putshort ( format4 , 0 ) ;
 for ( i = 0 ;
 i < segcnt ;
 ++ i ) putshort ( format4 , cmapseg [ i ] . start ) ;
 for ( i = 0 ;
 i < segcnt ;
 ++ i ) putshort ( format4 , cmapseg [ i ] . delta ) ;
 for ( i = 0 ;
 i < segcnt ;
 ++ i ) putshort ( format4 , cmapseg [ i ] . rangeoff ) ;
 for ( i = 0 ;
 i < rpos ;
 ++ i ) putshort ( format4 , ranges [ i ] ) ;
 free ( ranges ) ;
 free ( cmapseg ) ;
 * ucs2len = ftell ( format4 ) ;
 return ( format4 ) ;
 }