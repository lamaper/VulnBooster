static void sethead ( struct head * head , SplineFont * sf , struct alltabs * at , enum fontformat format , int32 * bsizes ) {
 int i , lr , rl , indic_rearrange , arabic ;
 ASM * sm ;
 struct ttflangname * useng ;
 float vn ;
 if ( at -> gi . xmin == 15000 ) at -> gi . xmin = 0 ;
 if ( at -> gi . ymin == 15000 ) at -> gi . ymin = 0 ;
 if ( bsizes != NULL && format == ff_none ) {
 if ( sf -> ascent > at -> gi . ymax ) at -> gi . ymax = sf -> ascent ;
 if ( - sf -> descent < at -> gi . ymin ) at -> gi . ymin = - sf -> descent ;
 }
 head -> xmin = at -> gi . xmin ;
 head -> ymin = at -> gi . ymin ;
 head -> xmax = at -> gi . xmax ;
 head -> ymax = at -> gi . ymax ;
 lr = rl = arabic = 0 ;
 for ( i = 0 ;
 i < at -> gi . gcnt ;
 ++ i ) if ( at -> gi . bygid [ i ] != - 1 ) {
 SplineChar * sc = sf -> glyphs [ at -> gi . bygid [ i ] ] ;
 int uni = sc -> unicodeenc ;
 if ( SCRightToLeft ( sc ) ) rl = 1 ;
 else if ( ( uni != - 1 && uni < 0x10000 && islefttoright ( uni ) ) || ( uni >= 0x10300 && uni < 0x107ff ) ) lr = 1 ;
 if ( SCScriptFromUnicode ( sc ) == CHR ( 'a' , 'r' , 'a' , 'b' ) ) arabic = 1 ;
 }
 head -> version = 0x00010000 ;
 head -> revision = sf -> sfntRevision ;
 if ( sf -> sfntRevision == sfntRevisionUnset ) {
 head -> revision = 0x00010000 ;
 for ( useng = sf -> names ;
 useng != NULL ;
 useng = useng -> next ) if ( useng -> lang == 0x409 ) break ;
 if ( useng != NULL && useng -> names [ ttf_version ] != NULL && sscanf ( useng -> names [ ttf_version ] , "Version %f" , & vn ) == 1 ) {
 head -> revision = vn * 65536 ;
 }
 else if ( sf -> subfontcnt != 0 ) {
 int val , mant ;
 val = floor ( sf -> cidversion ) ;
 mant = floor ( 65536. * ( ( double ) sf -> cidversion - val ) ) ;
 head -> revision = ( val << 16 ) | mant ;
 }
 else if ( sf -> version != NULL ) {
 char * pt = sf -> version ;
 double dval ;
 int val , mant ;
 while ( * pt && ! isdigit ( * pt ) && * pt != '.' ) ++ pt ;
 if ( * pt ) {
 dval = strtod ( pt , NULL ) ;
 val = floor ( dval ) ;
 mant = floor ( 65536. * ( dval - val ) ) ;
 head -> revision = ( val << 16 ) | mant ;
 }
 }
 }
 head -> checksumAdj = 0 ;
 head -> magicNum = 0x5f0f3cf5 ;
 head -> flags = 8 | 2 | 1 ;
 if ( format >= ff_ttf && format <= ff_ttfdfont ) {
 if ( AnyInstructions ( sf ) ) head -> flags = 0x10 | 8 | 4 | 2 | 1 ;
 else if ( AnyMisleadingBitmapAdvances ( sf , bsizes ) ) head -> flags = 0x10 | 8 | 2 | 1 ;
 }
 if ( sf -> hasvmetrics ) head -> flags |= ( 1 << 5 ) ;
 if ( arabic ) head -> flags |= ( 1 << 7 ) ;
 if ( sf -> sm ) head -> flags |= ( 1 << 8 ) ;
 if ( rl ) head -> flags |= ( 1 << 9 ) ;
 indic_rearrange = 0 ;
 for ( sm = sf -> sm ;
 sm != NULL ;
 sm = sm -> next ) if ( sm -> type == asm_indic ) indic_rearrange = true ;
 if ( indic_rearrange ) head -> flags |= ( 1 << 10 ) ;
 if ( sf -> head_optimized_for_cleartype ) head -> flags |= ( 1 << 13 ) ;
 head -> emunits = sf -> ascent + sf -> descent ;
 head -> macstyle = MacStyleCode ( sf , NULL ) ;
 head -> lowestreadable = 8 ;
 head -> locais32 = 1 ;
 if ( at -> gi . glyph_len < 0x20000 ) head -> locais32 = 0 ;
 if ( lr && rl ) head -> dirhint = 0 ;
 else if ( rl ) head -> dirhint = - 2 ;
 else head -> dirhint = 2 ;
 if ( rl ) head -> flags |= ( 1 << 9 ) ;
 cvt_unix_to_1904 ( sf -> creationtime , head -> createtime ) ;
 cvt_unix_to_1904 ( sf -> modificationtime , head -> modtime ) ;
 }