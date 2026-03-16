static void dumppost ( struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 int pos , i , j , shouldbe ;
 int shorttable = ( format == ff_otf || format == ff_otfcid || ( at -> gi . flags & ttf_flag_shortps ) ) ;
 uint32 here ;
 at -> post = tmpfile ( ) ;
 putlong ( at -> post , shorttable ? 0x00030000 : 0x00020000 ) ;
 putfixed ( at -> post , sf -> italicangle ) ;
 putshort ( at -> post , sf -> upos - sf -> uwidth / 2 ) ;
 putshort ( at -> post , sf -> uwidth ) ;
 putlong ( at -> post , at -> isfixed ) ;
 putlong ( at -> post , 0 ) ;
 putlong ( at -> post , 0 ) ;
 putlong ( at -> post , 0 ) ;
 putlong ( at -> post , 0 ) ;
 if ( ! shorttable ) {
 here = ftell ( at -> post ) ;
 putshort ( at -> post , at -> maxp . numGlyphs ) ;
 shouldbe = 0 ;
 for ( i = 0 , pos = 0 ;
 i < at -> maxp . numGlyphs ;
 ++ i ) {
 if ( at -> gi . bygid [ i ] != - 1 && sf -> glyphs [ at -> gi . bygid [ i ] ] != NULL ) {
 SplineChar * sc = sf -> glyphs [ at -> gi . bygid [ i ] ] ;
 while ( i > shouldbe ) {
 if ( shouldbe == 0 ) putshort ( at -> post , 0 ) ;
 else if ( shouldbe == 1 ) putshort ( at -> post , 1 ) ;
 else if ( shouldbe == 2 ) putshort ( at -> post , 2 ) ;
 else putshort ( at -> post , 0 ) ;
 ++ shouldbe ;
 }
 if ( strcmp ( sc -> name , ".notdef" ) == 0 ) putshort ( at -> post , 0 ) ;
 else {
 for ( j = 0 ;
 j < 258 ;
 ++ j ) if ( strcmp ( sc -> name , ttfstandardnames [ j ] ) == 0 ) break ;
 if ( j != 258 ) putshort ( at -> post , j ) ;
 else {
 putshort ( at -> post , pos + 258 ) ;
 ++ pos ;
 }
 }
 ++ shouldbe ;
 }
 }
 if ( shouldbe != at -> maxp . numGlyphs ) {
 fseek ( at -> post , here , SEEK_SET ) ;
 putshort ( at -> post , shouldbe ) ;
 fseek ( at -> post , 0 , SEEK_END ) ;
 }
 if ( pos != 0 ) {
 for ( i = 0 ;
 i < at -> maxp . numGlyphs ;
 ++ i ) if ( at -> gi . bygid [ i ] != - 1 ) {
 SplineChar * sc = sf -> glyphs [ at -> gi . bygid [ i ] ] ;
 if ( strcmp ( sc -> name , ".notdef" ) == 0 ) ;
 else {
 for ( j = 0 ;
 j < 258 ;
 ++ j ) if ( strcmp ( sc -> name , ttfstandardnames [ j ] ) == 0 ) break ;
 if ( j != 258 ) ;
 else dumppstr ( at -> post , sc -> name ) ;
 }
 }
 }
 }
 at -> postlen = ftell ( at -> post ) ;
 if ( ( at -> postlen & 3 ) != 0 ) for ( j = 4 - ( at -> postlen & 3 ) ;
 j > 0 ;
 -- j ) putc ( '\0' , at -> post ) ;
 }