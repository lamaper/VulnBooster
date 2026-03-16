static int initTables ( struct alltabs * at , SplineFont * sf , enum fontformat format , int32 * bsizes , enum bitmapformat bf ) {
 int i , j , aborted , offset ;
 BDFFont * bdf ;
 struct ttf_table * tab ;
 if ( strmatch ( at -> map -> enc -> enc_name , "symbol" ) == 0 && format == ff_ttf ) format = ff_ttfsym ;
 tab = SFFindTable ( sf , CHR ( 'c' , 'v' , 't' , ' ' ) ) ;
 if ( tab != NULL ) {
 at -> oldcvt = tab ;
 at -> oldcvtlen = tab -> len ;
 }
 SFDefaultOS2Info ( & sf -> pfminfo , sf , sf -> fontname ) ;
 at -> gi . xmin = at -> gi . ymin = 15000 ;
 at -> gi . sf = sf ;
 if ( bf != bf_ttf && bf != bf_sfnt_dfont && bf != bf_otb && bf != bf_sfnt_ms ) bsizes = NULL ;
 if ( bsizes != NULL ) {
 for ( i = j = 0 ;
 bsizes [ i ] != 0 ;
 ++ i ) {
 for ( bdf = sf -> bitmaps ;
 bdf != NULL && ( bdf -> pixelsize != ( bsizes [ i ] & 0xffff ) || BDFDepth ( bdf ) != ( bsizes [ i ] >> 16 ) ) ;
 bdf = bdf -> next ) ;
 if ( bdf != NULL ) bsizes [ j ++ ] = bsizes [ i ] ;
 else ff_post_error ( _ ( "Missing bitmap strike" ) , _ ( "The font database does not contain a bitmap of size %d and depth %d" ) , bsizes [ i ] & 0xffff , bsizes [ i ] >> 16 ) ;
 }
 bsizes [ j ] = 0 ;
 for ( i = 0 ;
 bsizes [ i ] != 0 ;
 ++ i ) ;
 at -> gi . strikecnt = i ;
 if ( i == 0 ) bsizes = NULL ;
 }
 if ( sf -> subfonts != NULL ) {
 SFDummyUpCIDs ( & at -> gi , sf ) ;
 }
 else if ( format != ff_none ) AssignTTFGlyph ( & at -> gi , sf , at -> map , format == ff_otf ) ;
 else {
 if ( bsizes == NULL ) {
 ff_post_error ( _ ( "No bitmap strikes" ) , _ ( "No bitmap strikes" ) ) ;
 AbortTTF ( at , sf ) ;
 return ( false ) ;
 }
 AssignTTFBitGlyph ( & at -> gi , sf , at -> map , bsizes ) ;
 }
 if ( at -> gi . gcnt > 65535 ) {
 ff_post_error ( _ ( "Too many glyphs" ) , _ ( "The 'sfnt' format is currently limited to 65535 glyphs, and your font has %d of them." ) , at -> gi . gcnt ) ;
 AbortTTF ( at , sf ) ;
 return ( false ) ;
 }
 else if ( at -> gi . gcnt == 65535 ) {
 LogError ( _ ( "Your font has exactly 65535 glyphs. Encoding 65535 is the limit and is often used as a magic \ value, so it may cause quirks.\n" ) ) ;
 }
 ATmaxpInit ( at , sf , format ) ;
 if ( format == ff_otf ) aborted = ! dumptype2glyphs ( sf , at ) ;
 else if ( format == ff_otfcid ) aborted = ! dumpcidglyphs ( sf , at ) ;
 else if ( format == ff_none && at -> applebitmaps ) {
 aborted = ! dumpcffhmtx ( at , sf , true ) ;
 }
 else if ( format == ff_none && at -> otbbitmaps ) {
 aborted = ! dumpcffhmtx ( at , sf , true ) ;
 dumpnoglyphs ( & at -> gi ) ;
 }
 else if ( format == ff_none && at -> msbitmaps ) {
 aborted = ! dumpglyphs ( sf , & at -> gi ) ;
 }
 else {
 aborted = ! dumpglyphs ( sf , & at -> gi ) ;
 }
 if ( format != ff_type42 && format != ff_type42cid ) {
 if ( bsizes != NULL && ! aborted ) ttfdumpbitmap ( sf , at , bsizes ) ;
 if ( bsizes != NULL && format == ff_none && at -> msbitmaps ) ttfdumpbitmapscaling ( sf , at , bsizes ) ;
 }
 if ( aborted ) {
 AbortTTF ( at , sf ) ;
 return ( false ) ;
 }
 sethead ( & at -> head , sf , at , format , bsizes ) ;
 sethhead ( & at -> hhead , & at -> vhead , at , sf ) ;
 if ( format == ff_none && at -> otbbitmaps ) dummyloca ( at ) ;
 else if ( format != ff_otf && format != ff_otfcid && bf != bf_sfnt_dfont && ( format != ff_none || ( bsizes != NULL && ! at -> applemode && at -> opentypemode ) ) ) redoloca ( at ) ;
 redohead ( at ) ;
 if ( format != ff_none || ! at -> applemode ) redohhead ( at , false ) ;
 if ( sf -> hasvmetrics ) {
 redohhead ( at , true ) ;
 }
 ttf_fftm_dump ( sf , at ) ;
 if ( format != ff_type42 && format != ff_type42cid && ! sf -> internal_temp ) {
 initATTables ( at , sf , format ) ;
 }
 redomaxp ( at , format ) ;
 if ( format != ff_otf && format != ff_otfcid && format != ff_none ) {
 if ( ( sf -> gasp_cnt != 0 || ! SFHasInstructions ( sf ) ) && format != ff_type42 && format != ff_type42cid ) dumpgasp ( at , sf ) ;
 at -> fpgmf = dumpstoredtable ( sf , CHR ( 'f' , 'p' , 'g' , 'm' ) , & at -> fpgmlen ) ;
 at -> prepf = dumpstoredtable ( sf , CHR ( 'p' , 'r' , 'e' , 'p' ) , & at -> preplen ) ;
 at -> cvtf = dumpstoredtable ( sf , CHR ( 'c' , 'v' , 't' , ' ' ) , & at -> cvtlen ) ;
 }
 for ( tab = sf -> ttf_tab_saved ;
 tab != NULL ;
 tab = tab -> next ) tab -> temp = dumpsavedtable ( tab ) ;
 if ( format != ff_type42 && format != ff_type42cid ) {
 dumppost ( at , sf , format ) ;
 dumpcmap ( at , sf , format ) ;
 pfed_dump ( at , sf ) ;
 tex_dump ( at , sf ) ;
 }
 if ( sf -> subfonts != NULL ) {
 free ( sf -> glyphs ) ;
 sf -> glyphs = NULL ;
 sf -> glyphcnt = sf -> glyphmax = 0 ;
 }
 free ( at -> gi . bygid ) ;
 at -> gi . gcnt = 0 ;
 buildtablestructures ( at , sf , format ) ;
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) {
 struct taboff * tab = & at -> tabdir . tabs [ i ] ;
 at -> tabdir . ordered [ i ] = tab ;
 at -> tabdir . alpha [ i ] = tab ;
 if ( format == ff_otf || format == ff_otfcid ) {
 tab -> orderingval = tab -> tag == CHR ( 'h' , 'e' , 'a' , 'd' ) ? 1 : tab -> tag == CHR ( 'h' , 'h' , 'e' , 'a' ) ? 2 : tab -> tag == CHR ( 'm' , 'a' , 'x' , 'p' ) ? 3 : tab -> tag == CHR ( 'O' , 'S' , '/' , '2' ) ? 4 : tab -> tag == CHR ( 'n' , 'a' , 'm' , 'e' ) ? 5 : tab -> tag == CHR ( 'c' , 'm' , 'a' , 'p' ) ? 6 : tab -> tag == CHR ( 'p' , 'o' , 's' , 't' ) ? 7 : tab -> tag == CHR ( 'C' , 'F' , 'F' , ' ' ) ? 8 : tab -> tag == CHR ( 'G' , 'D' , 'E' , 'F' ) ? 17 : tab -> tag == CHR ( 'G' , 'S' , 'U' , 'B' ) ? 18 : tab -> tag == CHR ( 'G' , 'P' , 'O' , 'S' ) ? 19 : 20 ;
 }
 else {
 tab -> orderingval = tab -> tag == CHR ( 'h' , 'e' , 'a' , 'd' ) ? 1 : tab -> tag == CHR ( 'h' , 'h' , 'e' , 'a' ) ? 2 : tab -> tag == CHR ( 'm' , 'a' , 'x' , 'p' ) ? 3 : tab -> tag == CHR ( 'O' , 'S' , '/' , '2' ) ? 4 : tab -> tag == CHR ( 'h' , 'm' , 't' , 'x' ) ? 5 : tab -> tag == CHR ( 'L' , 'T' , 'S' , 'H' ) ? 6 : tab -> tag == CHR ( 'V' , 'D' , 'M' , 'X' ) ? 7 : tab -> tag == CHR ( 'h' , 'd' , 'm' , 'x' ) ? 8 : tab -> tag == CHR ( 'c' , 'm' , 'a' , 'p' ) ? 9 : tab -> tag == CHR ( 'f' , 'p' , 'g' , 'm' ) ? 10 : tab -> tag == CHR ( 'p' , 'r' , 'e' , 'p' ) ? 11 : tab -> tag == CHR ( 'c' , 'v' , 't' , ' ' ) ? 12 : tab -> tag == CHR ( 'l' , 'o' , 'c' , 'a' ) ? 13 : tab -> tag == CHR ( 'g' , 'l' , 'y' , 'f' ) ? 14 : tab -> tag == CHR ( 'k' , 'e' , 'r' , 'n' ) ? 15 : tab -> tag == CHR ( 'n' , 'a' , 'm' , 'e' ) ? 16 : tab -> tag == CHR ( 'p' , 'o' , 's' , 't' ) ? 17 : tab -> tag == CHR ( 'g' , 'a' , 's' , 'p' ) ? 18 : tab -> tag == CHR ( 'P' , 'C' , 'L' , 'T' ) ? 19 : tab -> tag == CHR ( 'D' , 'S' , 'I' , 'G' ) ? 20 : tab -> tag == CHR ( 'G' , 'D' , 'E' , 'F' ) ? 21 : tab -> tag == CHR ( 'G' , 'S' , 'U' , 'B' ) ? 22 : tab -> tag == CHR ( 'G' , 'P' , 'O' , 'S' ) ? 23 : 24 ;
 }
 }
 qsort ( at -> tabdir . ordered , at -> tabdir . numtab , sizeof ( struct taboff * ) , tcomp ) ;
 qsort ( at -> tabdir . alpha , i , sizeof ( struct taboff * ) , tagcomp ) ;
 offset = sizeof ( int32 ) + 4 * sizeof ( int16 ) + at -> tabdir . numtab * 4 * sizeof ( int32 ) ;
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) if ( at -> tabdir . ordered [ i ] -> data != NULL ) {
 at -> tabdir . ordered [ i ] -> offset = offset ;
 offset += ( ( at -> tabdir . ordered [ i ] -> length + 3 ) >> 2 ) << 2 ;
 at -> tabdir . ordered [ i ] -> checksum = filechecksum ( at -> tabdir . ordered [ i ] -> data ) ;
 }
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) if ( at -> tabdir . ordered [ i ] -> data == NULL ) {
 struct taboff * tab = & at -> tabdir . tabs [ at -> tabdir . ordered [ i ] -> dup_of ] ;
 at -> tabdir . ordered [ i ] -> offset = tab -> offset ;
 at -> tabdir . ordered [ i ] -> checksum = tab -> checksum ;
 }
 tab = SFFindTable ( sf , CHR ( 'c' , 'v' , 't' , ' ' ) ) ;
 if ( tab != NULL ) {
 if ( at -> oldcvt != NULL && at -> oldcvtlen < tab -> len ) tab -> len = at -> oldcvtlen ;
 else if ( at -> oldcvt == NULL ) {
 struct ttf_table * prev = NULL ;
 for ( tab = sf -> ttf_tables ;
 tab != NULL ;
 prev = tab , tab = tab -> next ) if ( tab -> tag == CHR ( 'c' , 'v' , 't' , ' ' ) ) break ;
 if ( tab != NULL ) {
 if ( prev == NULL ) sf -> ttf_tables = tab -> next ;
 else prev -> next = tab -> next ;
 tab -> next = NULL ;
 TtfTablesFree ( tab ) ;
 }
 }
 }
 return ( true ) ;
 }