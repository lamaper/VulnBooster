static void redomaxp ( struct alltabs * at , enum fontformat format ) {
 at -> maxpf = tmpfile ( ) ;
 putlong ( at -> maxpf , at -> maxp . version ) ;
 putshort ( at -> maxpf , at -> maxp . numGlyphs ) ;
 if ( format != ff_otf && format != ff_otfcid ) {
 putshort ( at -> maxpf , at -> maxp . maxPoints ) ;
 putshort ( at -> maxpf , at -> maxp . maxContours ) ;
 putshort ( at -> maxpf , at -> maxp . maxCompositPts ) ;
 putshort ( at -> maxpf , at -> maxp . maxCompositCtrs ) ;
 putshort ( at -> maxpf , at -> maxp . maxZones ) ;
 putshort ( at -> maxpf , at -> maxp . maxTwilightPts ) ;
 putshort ( at -> maxpf , at -> maxp . maxStorage ) ;
 putshort ( at -> maxpf , at -> maxp . maxFDEFs ) ;
 putshort ( at -> maxpf , at -> maxp . maxIDEFs ) ;
 putshort ( at -> maxpf , at -> maxp . maxStack ) ;
 putshort ( at -> maxpf , at -> maxp . maxglyphInstr ) ;
 putshort ( at -> maxpf , at -> maxp . maxnumcomponents ) ;
 putshort ( at -> maxpf , at -> maxp . maxcomponentdepth ) ;
 }
 at -> maxplen = ftell ( at -> maxpf ) ;
 if ( ( at -> maxplen & 2 ) != 0 ) putshort ( at -> maxpf , 0 ) ;
 }