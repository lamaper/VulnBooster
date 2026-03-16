static void MaxpFromTable ( struct alltabs * at , SplineFont * sf ) {
 struct ttf_table * maxp ;
 maxp = SFFindTable ( sf , CHR ( 'm' , 'a' , 'x' , 'p' ) ) ;
 if ( maxp == NULL && sf -> mm != NULL && sf -> mm -> apple ) maxp = SFFindTable ( sf -> mm -> normal , CHR ( 'm' , 'a' , 'x' , 'p' ) ) ;
 if ( maxp == NULL || maxp -> len < 13 * sizeof ( uint16 ) ) return ;
 at -> maxp . maxZones = memushort ( maxp -> data , maxp -> len , 7 * sizeof ( uint16 ) ) ;
 at -> maxp . maxTwilightPts = memushort ( maxp -> data , maxp -> len , 8 * sizeof ( uint16 ) ) ;
 at -> maxp . maxStorage = memushort ( maxp -> data , maxp -> len , 9 * sizeof ( uint16 ) ) ;
 at -> maxp . maxFDEFs = memushort ( maxp -> data , maxp -> len , 10 * sizeof ( uint16 ) ) ;
 at -> maxp . maxIDEFs = memushort ( maxp -> data , maxp -> len , 11 * sizeof ( uint16 ) ) ;
 at -> maxp . maxStack = memushort ( maxp -> data , maxp -> len , 12 * sizeof ( uint16 ) ) ;
 }