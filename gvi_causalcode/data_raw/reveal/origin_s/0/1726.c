int ff_h263_get_gob_height ( MpegEncContext * s ) {
 if ( s -> height <= 400 ) return 1 ;
 else if ( s -> height <= 800 ) return 2 ;
 else return 4 ;
 }