static void dumpcmap ( struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 int i , enccnt , issmall , hasmac ;
 uint16 table [ 256 ] ;
 SplineChar * sc ;
 int alreadyprivate = false ;
 int wasotf = format == ff_otf || format == ff_otfcid ;
 EncMap * map = at -> map ;
 int ucs4len = 0 , ucs2len = 0 , cjklen = 0 , applecjklen = 0 , vslen = 0 ;
 FILE * format12 , * format4 , * format2 , * apple2 , * format14 ;
 int mspos , ucs4pos , cjkpos , applecjkpos , vspos , start_of_macroman ;
 int modformat = format ;
 if ( ( format >= ff_ttf && format <= ff_otfdfont ) && ( at -> gi . flags & ttf_flag_symbol ) ) modformat = ff_ttfsym ;
 at -> cmap = tmpfile ( ) ;
 memset ( table , '\0' , sizeof ( table ) ) ;
 if ( ! wasotf ) {
 table [ 29 ] = table [ 8 ] = table [ 0 ] = 1 ;
 table [ 9 ] = table [ 13 ] = 2 ;
 }
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 sc = SFGetChar ( sf , MacRomanEnc [ i ] , NULL ) ;
 if ( sc != NULL && sc -> ttf_glyph != - 1 ) table [ i ] = sc -> ttf_glyph ;
 }
 if ( table [ 0 ] == 0 ) table [ 0 ] = 1 ;
 if ( modformat == ff_ttfsym ) {
 alreadyprivate = AlreadyMSSymbolArea ( sf , map ) ;
 memset ( table , '\0' , sizeof ( table ) ) ;
 if ( ! wasotf ) {
 table [ 29 ] = table [ 8 ] = table [ 0 ] = 1 ;
 table [ 9 ] = table [ 13 ] = 2 ;
 }
 if ( ! alreadyprivate ) {
 for ( i = 0 ;
 i < map -> enccount && i < 256 ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL && sc -> ttf_glyph != - 1 ) table [ i ] = sc -> ttf_glyph ;
 }
 for ( i = 0xf020 ;
 i <= 0xf0ff && i < sf -> glyphcnt ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL && sc -> ttf_glyph != - 1 && table [ i - 0xf000 ] == 0 ) table [ i - 0xf000 ] = sc -> ttf_glyph ;
 }
 }
 else {
 for ( i = 0xf020 ;
 i <= 0xf0ff && i < sf -> glyphcnt ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL && sc -> ttf_glyph != - 1 ) table [ i - 0xf000 ] = sc -> ttf_glyph ;
 }
 for ( i = 0 ;
 i < map -> enccount && i < 256 ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL && sc -> ttf_glyph != - 1 && table [ i ] == 0 ) table [ i ] = sc -> ttf_glyph ;
 }
 }
 if ( ! alreadyprivate ) {
 for ( i = 0 ;
 i < map -> enccount && i < 256 ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL ) {
 sc -> orig_pos = sc -> unicodeenc ;
 sc -> unicodeenc = 0xf000 + i ;
 }
 }
 for ( ;
 i < map -> enccount ;
 ++ i ) {
 if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL ) {
 sc -> orig_pos = sc -> unicodeenc ;
 sc -> unicodeenc = - 1 ;
 }
 }
 }
 }
 format4 = NeedsUCS2Table ( sf , & ucs2len , map , modformat == ff_ttfsym ) ;
 apple2 = NULL ;
 if ( modformat != ff_ttfsym ) {
 format12 = NeedsUCS4Table ( sf , & ucs4len , map ) ;
 format2 = Needs816Enc ( sf , & cjklen , map , & apple2 , & applecjklen ) ;
 format14 = NeedsVariationSequenceTable ( sf , & vslen ) ;
 }
 else format12 = format2 = format14 = apple2 = NULL ;
 if ( modformat == ff_ttfsym ) {
 enccnt = 2 ;
 hasmac = 0 ;
 }
 else {
 hasmac = 1 ;
 enccnt = 3 ;
 if ( format12 != NULL ) enccnt = 5 ;
 if ( format2 != NULL ) {
 if ( strstrmatch ( map -> enc -> enc_name , "johab" ) != NULL ) {
 ++ enccnt ;
 }
 else {
 enccnt += 2 ;
 hasmac = 3 ;
 }
 }
 if ( format14 != NULL ) ++ enccnt ;
 }
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , enccnt ) ;
 mspos = 2 * sizeof ( uint16 ) + enccnt * ( 2 * sizeof ( uint16 ) + sizeof ( uint32 ) ) ;
 ucs4pos = mspos + ucs2len ;
 cjkpos = ucs4pos + ucs4len ;
 if ( apple2 == NULL ) {
 applecjkpos = cjkpos ;
 applecjklen = cjklen ;
 }
 else applecjkpos = cjkpos + cjklen ;
 vspos = applecjkpos + applecjklen ;
 start_of_macroman = vspos + vslen ;
 if ( hasmac & 1 ) {
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 3 ) ;
 putlong ( at -> cmap , mspos ) ;
 }
 if ( format12 != NULL ) {
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 4 ) ;
 putlong ( at -> cmap , ucs4pos ) ;
 }
 if ( format14 != NULL ) {
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 5 ) ;
 putlong ( at -> cmap , vspos ) ;
 }
 putshort ( at -> cmap , 1 ) ;
 putshort ( at -> cmap , 0 ) ;
 putlong ( at -> cmap , start_of_macroman ) ;
 if ( format2 != NULL && ( hasmac & 2 ) ) {
 putshort ( at -> cmap , 1 ) ;
 putshort ( at -> cmap , map -> enc -> is_japanese || sf -> uni_interp == ui_japanese ? 1 : map -> enc -> is_korean || sf -> uni_interp == ui_korean ? 3 : map -> enc -> is_simplechinese || sf -> uni_interp == ui_simp_chinese ? 25 : ) ;
 putlong ( at -> cmap , applecjkpos ) ;
 }
 putshort ( at -> cmap , 3 ) ;
 putshort ( at -> cmap , modformat == ff_ttfsym ? 0 : ) ;
 putlong ( at -> cmap , mspos ) ;
 if ( format2 != NULL ) {
 putshort ( at -> cmap , 3 ) ;
 putshort ( at -> cmap , strstrmatch ( map -> enc -> enc_name , "johab" ) != NULL ? 6 : map -> enc -> is_korean || sf -> uni_interp == ui_korean ? 5 : map -> enc -> is_japanese || sf -> uni_interp == ui_japanese ? 2 : map -> enc -> is_simplechinese || sf -> uni_interp == ui_simp_chinese ? 3 : 4 ) ;
 putlong ( at -> cmap , cjkpos ) ;
 }
 if ( format12 != NULL ) {
 putshort ( at -> cmap , 3 ) ;
 putshort ( at -> cmap , 10 ) ;
 putlong ( at -> cmap , ucs4pos ) ;
 }
 if ( format4 != NULL ) {
 if ( ! ttfcopyfile ( at -> cmap , format4 , mspos , "cmap-Unicode16" ) ) at -> error = true ;
 }
 if ( format12 != NULL ) {
 if ( ! ttfcopyfile ( at -> cmap , format12 , ucs4pos , "cmap-Unicode32" ) ) at -> error = true ;
 }
 if ( format2 != NULL ) {
 if ( ! ttfcopyfile ( at -> cmap , format2 , cjkpos , "cmap-cjk" ) ) at -> error = true ;
 }
 if ( apple2 != NULL ) {
 if ( ! ttfcopyfile ( at -> cmap , apple2 , applecjkpos , "cmap-applecjk" ) ) at -> error = true ;
 }
 if ( format14 != NULL ) {
 if ( ! ttfcopyfile ( at -> cmap , format14 , vspos , "cmap-uniVariations" ) ) at -> error = true ;
 }
 issmall = true ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) if ( table [ i ] >= 256 ) {
 issmall = false ;
 break ;
 }
 if ( issmall ) {
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 262 ) ;
 putshort ( at -> cmap , 0 ) ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) putc ( table [ i ] , at -> cmap ) ;
 }
 else {
 putshort ( at -> cmap , 6 ) ;
 putshort ( at -> cmap , 522 ) ;
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 0 ) ;
 putshort ( at -> cmap , 256 ) ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) putshort ( at -> cmap , table [ i ] ) ;
 }
 at -> cmaplen = ftell ( at -> cmap ) ;
 if ( ( at -> cmaplen & 2 ) != 0 ) putshort ( at -> cmap , 0 ) ;
 if ( modformat == ff_ttfsym ) {
 if ( ! alreadyprivate ) {
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 sf -> glyphs [ i ] -> unicodeenc = sf -> glyphs [ i ] -> orig_pos ;
 sf -> glyphs [ i ] -> orig_pos = i ;
 }
 }
 }
 }