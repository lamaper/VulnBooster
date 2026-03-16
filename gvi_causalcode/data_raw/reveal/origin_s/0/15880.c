static void ATinit ( struct alltabs * at , SplineFont * sf , EncMap * map , int flags , int layer , enum fontformat format , enum bitmapformat bf , int * bsizes ) {
 at -> gi . flags = flags ;
 at -> gi . layer = layer ;
 at -> gi . is_ttf = format == ff_ttf || format == ff_ttfsym || format == ff_ttfmacbin || format == ff_ttfdfont ;
 at -> gi . sf = sf ;
 at -> applemode = ( flags & ttf_flag_applemode ) ? 1 : 0 ;
 at -> opentypemode = ( flags & ttf_flag_otmode ) ? 1 : 0 ;
 at -> msbitmaps = bsizes != NULL && at -> opentypemode ;
 at -> applebitmaps = bsizes != NULL && at -> applemode ;
 at -> gi . onlybitmaps = format == ff_none ;
 if ( bf == bf_sfnt_dfont ) {
 at -> msbitmaps = false ;
 at -> applebitmaps = true ;
 at -> opentypemode = false ;
 at -> gi . onlybitmaps = true ;
 }
 if ( bf == bf_sfnt_ms ) {
 at -> msbitmaps = true ;
 at -> applebitmaps = false ;
 at -> applemode = false ;
 at -> gi . onlybitmaps = true ;
 }
 if ( bf == bf_otb ) {
 at -> otbbitmaps = true ;
 at -> applebitmaps = at -> msbitmaps = false ;
 at -> applemode = false ;
 at -> gi . onlybitmaps = true ;
 }
 if ( bsizes != NULL && ! at -> applebitmaps && ! at -> otbbitmaps && ! at -> msbitmaps ) at -> msbitmaps = true ;
 at -> gi . bsizes = bsizes ;
 at -> gi . fixed_width = CIDOneWidth ( sf ) ;
 at -> isotf = format == ff_otf || format == ff_otfcid ;
 at -> format = format ;
 at -> next_strid = 256 ;
 if ( at -> applemode && sf -> mm != NULL && sf -> mm -> apple && ( format == ff_ttf || format == ff_ttfsym || format == ff_ttfmacbin || format == ff_ttfdfont ) && MMValid ( sf -> mm , false ) ) {
 at -> dovariations = true ;
 at -> gi . dovariations = true ;
 sf = sf -> mm -> normal ;
 }
 at -> sf = sf ;
 at -> map = map ;
 }