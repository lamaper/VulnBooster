static void ATmaxpInit ( struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 at -> maxp . version = 0x00010000 ;
 if ( format == ff_otf || format == ff_otfcid || ( format == ff_none && at -> applemode ) ) at -> maxp . version = 0x00005000 ;
 at -> maxp . maxnumcomponents = 0 ;
 at -> maxp . maxcomponentdepth = 0 ;
 at -> maxp . maxZones = 2 ;
 at -> maxp . maxFDEFs = 1 ;
 at -> maxp . maxStorage = 1 ;
 at -> maxp . maxStack = 64 ;
 if ( format == ff_otf || format == ff_otfcid || ( format == ff_none && at -> applemode ) ) at -> maxp . version = 0x00005000 ;
 else MaxpFromTable ( at , sf ) ;
 at -> gi . maxp = & at -> maxp ;
 }