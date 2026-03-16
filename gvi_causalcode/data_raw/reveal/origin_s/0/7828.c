static guint32 uncompress_subclass ( guint8 csub ) {
 if ( csub & 0x80 ) {
 if ( csub == 0xff ) return ( guint32 ) - 1 ;
 else return 1 << ( csub & 0x1F ) ;
 }
 else return ( guint32 ) csub ;
 }