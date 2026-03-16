static struct alltabs * ttc_prep ( struct sflist * sfs , enum fontformat format , enum bitmapformat bf , int flags , int layer , SplineFont * dummysf ) {
 struct alltabs * ret ;
 int fcnt , cnt , gcnt = 3 ;
 struct sflist * sfitem ;
 int emsize = - 1 ;
 UHash * uhash ;
 NHash * nhash ;
 int anyvmetrics = false ;
 int * bygid ;
 SplineFont * sf ;
 SplineChar * sc , * test ;
 int i , aborted ;
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) {
 sf = sfitem -> sf ;
 if ( emsize == - 1 ) emsize = sf -> ascent + sf -> descent ;
 else if ( emsize != sf -> ascent + sf -> descent ) return ( NULL ) ;
 if ( format == ff_otf && ! PSDictSame ( sf -> private , sfs -> sf -> private ) ) return ( NULL ) ;
 if ( sf -> hasvmetrics ) anyvmetrics = true ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( ( sc = sf -> glyphs [ i ] ) != NULL ) sc -> ttf_glyph = - 1 ;
 gcnt += sf -> glyphcnt ;
 }
 if ( cnt == 0 ) return ( NULL ) ;
 fcnt = cnt ;
 uhash = calloc ( 1 , sizeof ( UHash ) ) ;
 nhash = calloc ( 1 , sizeof ( NHash ) ) ;
 * dummysf = * sfs -> sf ;
 dummysf -> glyphmax = gcnt ;
 dummysf -> glyphs = calloc ( gcnt , sizeof ( SplineChar * ) ) ;
 dummysf -> glyphcnt = 0 ;
 dummysf -> hasvmetrics = anyvmetrics ;
 bygid = malloc ( ( gcnt + 3 ) * sizeof ( int ) ) ;
 memset ( bygid , 0xff , ( gcnt + 3 ) * sizeof ( int ) ) ;
 for ( sfitem = sfs ;
 sfitem != NULL ;
 sfitem = sfitem -> next ) {
 AssignNotdefNull ( sfitem -> sf , bygid , false ) ;
 if ( bygid [ 0 ] != - 1 && dummysf -> glyphs [ 0 ] == NULL ) {
 dummysf -> glyphs [ 0 ] = sfitem -> sf -> glyphs [ bygid [ 0 ] ] ;
 bygid [ 0 ] = 0 ;
 }
 if ( format == ff_ttf ) {
 if ( bygid [ 1 ] != - 1 && dummysf -> glyphs [ 1 ] == NULL ) {
 dummysf -> glyphs [ 1 ] = sfitem -> sf -> glyphs [ bygid [ 1 ] ] ;
 bygid [ 1 ] = 1 ;
 }
 if ( bygid [ 2 ] != - 1 && dummysf -> glyphs [ 2 ] == NULL ) {
 dummysf -> glyphs [ 2 ] = sfitem -> sf -> glyphs [ bygid [ 2 ] ] ;
 bygid [ 2 ] = 2 ;
 }
 if ( bygid [ 0 ] != - 1 && bygid [ 1 ] != - 1 && bygid [ 2 ] != - 1 ) break ;
 }
 else {
 if ( bygid [ 0 ] != - 1 ) break ;
 }
 }
 dummysf -> glyphcnt = format == ff_ttf ? 3 : 1 ;
 ret = calloc ( fcnt + 2 , sizeof ( struct alltabs ) ) ;
 ATinit ( & ret [ fcnt ] , dummysf , sfs -> map , flags & ~ ttf_flag_dummyDSIG , layer , format , bf , NULL ) ;
 ret [ fcnt ] . gi . ttc_composite_font = true ;
 ATmaxpInit ( & ret [ fcnt ] , dummysf , format ) ;
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) {
 sf = sfitem -> sf ;
 ATinit ( & ret [ cnt ] , sf , sfitem -> map , flags & ~ ttf_flag_dummyDSIG , layer , format , bf , sfitem -> sizes ) ;
 ret [ cnt ] . gi . bygid = malloc ( ( gcnt + 3 ) * sizeof ( int ) ) ;
 memset ( ret [ cnt ] . gi . bygid , - 1 , ( gcnt + 3 ) * sizeof ( int ) ) ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) {
 if ( SCWorthOutputting ( sc = sf -> glyphs [ i ] ) ) {
 if ( sc -> ttf_glyph == - 1 ) {
 if ( strcmp ( sc -> name , ".notdef" ) == 0 ) sc -> ttf_glyph = bygid [ 0 ] ;
 else if ( format == ff_ttf && ( strcmp ( sf -> glyphs [ i ] -> name , ".null" ) == 0 || strcmp ( sf -> glyphs [ i ] -> name , "uni0000" ) == 0 || ( i == 1 && strcmp ( sf -> glyphs [ 1 ] -> name , "glyph1" ) == 0 ) ) ) sc -> ttf_glyph = bygid [ 1 ] ;
 else if ( format == ff_ttf && ( strcmp ( sf -> glyphs [ i ] -> name , "nonmarkingreturn" ) == 0 || strcmp ( sf -> glyphs [ i ] -> name , "uni000D" ) == 0 || ( i == 2 && strcmp ( sf -> glyphs [ 2 ] -> name , "glyph2" ) == 0 ) ) ) sc -> ttf_glyph = bygid [ 2 ] ;
 else {
 test = hashglyphfound ( sc , uhash , nhash , layer ) ;
 if ( test != NULL ) sc -> ttf_glyph = test -> ttf_glyph ;
 else {
 sc -> ttf_glyph = dummysf -> glyphcnt ++ ;
 bygid [ sc -> ttf_glyph ] = sc -> ttf_glyph ;
 dummysf -> glyphs [ sc -> ttf_glyph ] = sc ;
 hashglyphadd ( sc , uhash , nhash ) ;
 }
 }
 }
 if ( sc -> ttf_glyph != - 1 ) {
 ret [ cnt ] . gi . bygid [ sc -> ttf_glyph ] = i ;
 if ( sc -> ttf_glyph >= ret [ cnt ] . gi . gcnt ) ret [ cnt ] . gi . gcnt = sc -> ttf_glyph + 1 ;
 }
 }
 if ( sc != NULL ) sc -> lsidebearing = 0x7fff ;
 }
 MaxpFromTable ( & ret [ cnt ] , sf ) ;
 if ( ret [ cnt ] . maxp . maxZones > ret [ fcnt ] . maxp . maxZones ) ret [ fcnt ] . maxp . maxZones = ret [ cnt ] . maxp . maxZones ;
 if ( ret [ cnt ] . maxp . maxTwilightPts > ret [ fcnt ] . maxp . maxTwilightPts ) ret [ fcnt ] . maxp . maxTwilightPts = ret [ cnt ] . maxp . maxTwilightPts ;
 if ( ret [ cnt ] . maxp . maxStorage > ret [ fcnt ] . maxp . maxStorage ) ret [ fcnt ] . maxp . maxStorage = ret [ cnt ] . maxp . maxStorage ;
 if ( ret [ cnt ] . maxp . maxFDEFs > ret [ fcnt ] . maxp . maxFDEFs ) ret [ fcnt ] . maxp . maxFDEFs = ret [ cnt ] . maxp . maxFDEFs ;
 if ( ret [ cnt ] . maxp . maxIDEFs > ret [ fcnt ] . maxp . maxIDEFs ) ret [ fcnt ] . maxp . maxIDEFs = ret [ cnt ] . maxp . maxIDEFs ;
 if ( ret [ cnt ] . maxp . maxStack > ret [ fcnt ] . maxp . maxStack ) ret [ fcnt ] . maxp . maxStack = ret [ cnt ] . maxp . maxStack ;
 }
 free ( uhash ) ;
 free ( nhash ) ;
 if ( dummysf -> glyphcnt > 0xffff ) {
 free ( dummysf -> glyphs ) ;
 free ( bygid ) ;
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) free ( ret [ cnt ] . gi . bygid ) ;
 free ( ret ) ;
 return ( NULL ) ;
 }
 ret [ fcnt ] . gi . fixed_width = CIDOneWidth ( sf ) ;
 ret [ fcnt ] . gi . bygid = bygid ;
 ret [ fcnt ] . gi . gcnt = ret [ fcnt ] . maxp . numGlyphs = dummysf -> glyphcnt ;
 if ( format == ff_ttf ) aborted = ! dumpglyphs ( dummysf , & ret [ cnt ] . gi ) ;
 else aborted = ! dumptype2glyphs ( dummysf , & ret [ cnt ] ) ;
 if ( aborted ) {
 free ( dummysf -> glyphs ) ;
 free ( bygid ) ;
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) free ( ret [ cnt ] . gi . bygid ) ;
 free ( ret ) ;
 return ( NULL ) ;
 }
 sethhead ( & ret [ fcnt ] . hhead , & ret [ fcnt ] . vhead , & ret [ fcnt ] , dummysf ) ;
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) ret [ cnt ] . maxp = ret [ fcnt ] . maxp ;
 sethead ( & ret [ fcnt ] . head , dummysf , & ret [ fcnt ] , format , NULL ) ;
 if ( format == ff_ttf ) redoloca ( & ret [ fcnt ] ) ;
 redohhead ( & ret [ fcnt ] , false ) ;
 if ( dummysf -> hasvmetrics ) redohhead ( & ret [ fcnt ] , true ) ;
 ttf_fftm_dump ( dummysf , & ret [ fcnt ] ) ;
 return ( ret ) ;
 }