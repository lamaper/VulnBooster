static void setos2 ( struct os2 * os2 , struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 int i , cnt1 , cnt2 , first , last , avg1 , avg2 , gid ;
 char * pt ;
 static int const weightFactors [ 26 ] = {
 64 , 14 , 27 , 35 , 100 , 20 , 14 , 42 , 63 , 3 , 6 , 35 , 20 , 56 , 56 , 17 , 4 , 49 , 56 , 71 , 31 , 10 , 18 , 3 , 18 , 2 }
 ;
 EncMap * map ;
 SplineChar * sc ;
 int modformat = format ;
 os2 -> version = 1 ;
 if ( format == ff_otf || format == ff_otfcid ) os2 -> version = 3 ;
 if ( sf -> use_typo_metrics || sf -> weight_width_slope_only ) os2 -> version = 4 ;
 if ( sf -> os2_version > os2 -> version ) os2 -> version = sf -> os2_version ;
 if ( ( format >= ff_ttf && format <= ff_otfdfont ) && ( at -> gi . flags & ttf_flag_symbol ) ) modformat = ff_ttfsym ;
 os2 -> weightClass = sf -> pfminfo . weight ;
 os2 -> widthClass = sf -> pfminfo . width ;
 os2 -> fstype = 0x8 ;
 if ( sf -> pfminfo . fstype != - 1 ) os2 -> fstype = sf -> pfminfo . fstype ;
 if ( ! sf -> pfminfo . subsuper_set ) SFDefaultOS2SubSuper ( & sf -> pfminfo , sf -> ascent + sf -> descent , sf -> italicangle ) ;
 os2 -> ysupYSize = sf -> pfminfo . os2_supysize ;
 os2 -> ysubXSize = sf -> pfminfo . os2_subxsize ;
 os2 -> ysubYSize = sf -> pfminfo . os2_subysize ;
 os2 -> ysupXSize = sf -> pfminfo . os2_supxsize ;
 os2 -> ysubYOff = sf -> pfminfo . os2_subyoff ;
 os2 -> ysubXOff = sf -> pfminfo . os2_subxoff ;
 os2 -> ysupXOff = sf -> pfminfo . os2_supxoff ;
 os2 -> ysupYOff = sf -> pfminfo . os2_supyoff ;
 os2 -> yStrikeoutSize = sf -> pfminfo . os2_strikeysize ;
 os2 -> yStrikeoutPos = sf -> pfminfo . os2_strikeypos ;
 if ( sf -> pfminfo . stylemap != - 1 ) {
 int changed = 0 ;
 os2 -> fsSel = sf -> pfminfo . stylemap ;
 if ( at -> head . macstyle & 1 && ! ( os2 -> fsSel & 32 ) ) {
 at -> head . macstyle &= 0x7E ;
 changed = 1 ;
 }
 if ( at -> head . macstyle & 2 && ! ( os2 -> fsSel & 1 ) ) {
 at -> head . macstyle &= 0x7D ;
 changed = 1 ;
 }
 if ( changed ) redohead ( at ) ;
 }
 else {
 os2 -> fsSel = ( at -> head . macstyle & 1 ? 32 : 0 ) | ( at -> head . macstyle & 2 ? 1 : 0 ) ;
 if ( os2 -> fsSel == 0 && sf -> pfminfo . weight == 400 ) os2 -> fsSel = 64 ;
 }
 if ( sf -> fullname != NULL && strstrmatch ( sf -> fullname , "outline" ) != NULL ) os2 -> fsSel |= 8 ;
 if ( os2 -> version >= 4 ) {
 if ( strstrmatch ( sf -> fontname , "Obli" ) != NULL ) {
 os2 -> fsSel |= 512 ;
 }
 if ( sf -> use_typo_metrics ) os2 -> fsSel |= 128 ;
 if ( sf -> weight_width_slope_only ) os2 -> fsSel |= 256 ;
 }
 if ( sf -> pfminfo . typoascent_add ) os2 -> ascender = sf -> ascent + sf -> pfminfo . os2_typoascent ;
 else os2 -> ascender = sf -> pfminfo . os2_typoascent ;
 if ( sf -> pfminfo . typodescent_add ) os2 -> descender = - sf -> descent + sf -> pfminfo . os2_typodescent ;
 else os2 -> descender = sf -> pfminfo . os2_typodescent ;
 WinBB ( sf , & os2 -> winascent , & os2 -> windescent , at ) ;
 os2 -> linegap = sf -> pfminfo . os2_typolinegap ;
 os2 -> sFamilyClass = sf -> pfminfo . os2_family_class ;
 avg1 = avg2 = last = 0 ;
 first = 0xffff ;
 cnt1 = cnt2 = 0 ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( ( sc = sf -> glyphs [ i ] ) != NULL ) {
 if ( SCWorthOutputting ( sc ) && sc -> unicodeenc != - 1 ) {
 if ( ( format >= ff_ttf && format <= ff_otfdfont && sc -> ttf_glyph > 2 ) || ( format >= ff_ttf && format <= ff_otfdfont && sc -> ttf_glyph > 0 ) ) {
 if ( sc -> unicodeenc <= 0xffff ) {
 if ( sc -> unicodeenc < first ) first = sc -> unicodeenc ;
 if ( sc -> unicodeenc > last ) last = sc -> unicodeenc ;
 }
 else {
 last = 0xffff ;
 }
 }
 if ( sc -> width != 0 ) {
 avg2 += sc -> width ;
 ++ cnt2 ;
 }
 if ( sc -> unicodeenc == ' ' ) {
 avg1 += sc -> width * 166 ;
 ++ cnt1 ;
 }
 else if ( sc -> unicodeenc >= 'a' && sc -> unicodeenc <= 'z' ) {
 avg1 += sc -> width * weightFactors [ sc -> unicodeenc - 'a' ] ;
 ++ cnt1 ;
 }
 }
 }
 if ( sf -> pfminfo . hasunicoderanges ) memcpy ( os2 -> unicoderange , sf -> pfminfo . unicoderanges , sizeof ( os2 -> unicoderange ) ) ;
 else OS2FigureUnicodeRanges ( sf , os2 -> unicoderange ) ;
 if ( modformat == ff_ttfsym ) memset ( os2 -> unicoderange , 0 , sizeof ( os2 -> unicoderange ) ) ;
 if ( sf -> pfminfo . pfmset ) strncpy ( os2 -> achVendID , sf -> pfminfo . os2_vendor , 4 ) ;
 else if ( TTFFoundry != NULL ) strncpy ( os2 -> achVendID , TTFFoundry , 4 ) ;
 else memcpy ( os2 -> achVendID , "PfEd" , 4 ) ;
 for ( pt = os2 -> achVendID ;
 pt < os2 -> achVendID && * pt != '\0' ;
 ++ pt ) ;
 while ( pt < os2 -> achVendID ) * pt ++ = ' ' ;
 os2 -> avgCharWid = 500 ;
 os2 -> v1_avgCharWid = os2 -> v3_avgCharWid = 0 ;
 if ( cnt1 == 27 ) os2 -> v1_avgCharWid = avg1 / 1000 ;
 if ( cnt2 != 0 ) os2 -> v3_avgCharWid = avg2 / cnt2 ;
 memcpy ( os2 -> panose , sf -> pfminfo . panose , sizeof ( os2 -> panose ) ) ;
 map = at -> map ;
 if ( modformat == ff_ttfsym ) {
 if ( sf -> pfminfo . hascodepages ) memcpy ( os2 -> ulCodePage , sf -> pfminfo . codepages , sizeof ( os2 -> ulCodePage ) ) ;
 else {
 os2 -> ulCodePage [ 0 ] = 0x80000000 ;
 os2 -> ulCodePage [ 1 ] = 0 ;
 }
 if ( AlreadyMSSymbolArea ( sf , map ) ) {
 first = 0xf0ff ;
 last = 0 ;
 for ( i = 0xf020 ;
 i < map -> enccount && i <= 0xf0ff ;
 ++ i ) if ( ( gid = map -> map [ i ] ) != - 1 && sf -> glyphs [ gid ] != NULL && sf -> glyphs [ gid ] -> ttf_glyph != - 1 ) {
 if ( i < first ) first = i ;
 if ( i > last ) last = i ;
 }
 for ( i = 0 ;
 i < map -> enccount && i <= 255 ;
 ++ i ) if ( ( gid = map -> map [ i ] ) != - 1 && sf -> glyphs [ gid ] != NULL && sf -> glyphs [ gid ] -> ttf_glyph != - 1 ) {
 if ( i + 0xf000 < first ) first = i + 0xf000 ;
 if ( i + 0xf000 > last ) last = i + 0xf000 ;
 }
 os2 -> firstcharindex = first ;
 os2 -> lastcharindex = last ;
 }
 else {
 first = 255 ;
 last = 0 ;
 for ( i = 0 ;
 i < map -> enccount && i <= 255 ;
 ++ i ) if ( ( gid = map -> map [ i ] ) != - 1 && sf -> glyphs [ gid ] != NULL && sf -> glyphs [ gid ] -> ttf_glyph != - 1 ) {
 if ( i < first ) first = i ;
 if ( i > last ) last = i ;
 }
 for ( i = 0xf020 ;
 i < map -> enccount && i <= 0xf0ff ;
 ++ i ) if ( ( gid = map -> map [ i ] ) != - 1 && sf -> glyphs [ gid ] != NULL && sf -> glyphs [ gid ] -> ttf_glyph != - 1 ) {
 if ( i - 0xf000 < first ) first = i - 0xf000 ;
 if ( i - 0xf000 > last ) last = i - 0xf000 ;
 }
 if ( first < ' ' ) first = ' ' ;
 os2 -> firstcharindex = 0xf000 + first ;
 os2 -> lastcharindex = 0xf000 + last ;
 }
 }
 else {
 os2 -> firstcharindex = first ;
 os2 -> lastcharindex = last ;
 if ( sf -> pfminfo . hascodepages ) memcpy ( os2 -> ulCodePage , sf -> pfminfo . codepages , sizeof ( os2 -> ulCodePage ) ) ;
 else OS2FigureCodePages ( sf , os2 -> ulCodePage ) ;
 if ( ! sf -> pfminfo . hascodepages ) if ( ( os2 -> ulCodePage [ 0 ] & ~ ( 1U << 31 ) ) == 0 && os2 -> ulCodePage [ 1 ] == 0 ) os2 -> ulCodePage [ 0 ] |= 1 ;
 }
 if ( os2 -> version >= 2 ) {
 if ( sf -> pfminfo . os2_xheight != 0 ) os2 -> xHeight = sf -> pfminfo . os2_xheight ;
 else {
 double xh = SFXHeight ( sf , at -> gi . layer , true ) ;
 os2 -> xHeight = ( xh >= 0.0 ? xh : 0 ) ;
 }
 if ( sf -> pfminfo . os2_capheight != 0 ) os2 -> capHeight = sf -> pfminfo . os2_capheight ;
 else {
 double caph = SFCapHeight ( sf , at -> gi . layer , true ) ;
 os2 -> capHeight = ( caph >= 0.0 ? caph : 0 ) ;
 }
 os2 -> defChar = 0 ;
 if ( format == ff_otf || format == ff_otfcid ) os2 -> defChar = ' ' ;
 os2 -> breakChar = ' ' ;
 os2 -> maxContext = 1 ;
 }
 if ( os2 -> version >= 3 && os2 -> v3_avgCharWid != 0 ) os2 -> avgCharWid = os2 -> v3_avgCharWid ;
 else if ( os2 -> v1_avgCharWid != 0 ) os2 -> avgCharWid = os2 -> v1_avgCharWid ;
 else if ( os2 -> v3_avgCharWid != 0 ) os2 -> avgCharWid = os2 -> v3_avgCharWid ;
 }