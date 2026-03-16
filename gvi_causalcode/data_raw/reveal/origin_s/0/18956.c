static void mcc_mnc_aux ( guint8 * octs , gchar * mcc , gchar * mnc ) {
 if ( ( octs [ 0 ] & 0x0f ) <= 9 ) {
 mcc [ 0 ] = Dgt_tbcd . out [ octs [ 0 ] & 0x0f ] ;
 }
 else {
 mcc [ 0 ] = ( octs [ 0 ] & 0x0f ) + 55 ;
 }
 if ( ( ( octs [ 0 ] & 0xf0 ) >> 4 ) <= 9 ) {
 mcc [ 1 ] = Dgt_tbcd . out [ ( octs [ 0 ] & 0xf0 ) >> 4 ] ;
 }
 else {
 mcc [ 1 ] = ( ( octs [ 0 ] & 0xf0 ) >> 4 ) + 55 ;
 }
 if ( ( octs [ 1 ] & 0x0f ) <= 9 ) {
 mcc [ 2 ] = Dgt_tbcd . out [ octs [ 1 ] & 0x0f ] ;
 }
 else {
 mcc [ 2 ] = ( octs [ 1 ] & 0x0f ) + 55 ;
 }
 mcc [ 3 ] = '\0' ;
 if ( ( ( octs [ 1 ] & 0xf0 ) >> 4 ) <= 9 ) {
 mnc [ 2 ] = Dgt_tbcd . out [ ( octs [ 1 ] & 0xf0 ) >> 4 ] ;
 }
 else {
 mnc [ 2 ] = ( ( octs [ 1 ] & 0xf0 ) >> 4 ) + 55 ;
 }
 if ( ( octs [ 2 ] & 0x0f ) <= 9 ) {
 mnc [ 0 ] = Dgt_tbcd . out [ octs [ 2 ] & 0x0f ] ;
 }
 else {
 mnc [ 0 ] = ( octs [ 2 ] & 0x0f ) + 55 ;
 }
 if ( ( ( octs [ 2 ] & 0xf0 ) >> 4 ) <= 9 ) {
 mnc [ 1 ] = Dgt_tbcd . out [ ( octs [ 2 ] & 0xf0 ) >> 4 ] ;
 }
 else {
 mnc [ 1 ] = ( ( octs [ 2 ] & 0xf0 ) >> 4 ) + 55 ;
 }
 if ( mnc [ 1 ] == 'F' ) {
 mnc [ 1 ] = '\0' ;
 }
 else if ( mnc [ 2 ] == 'F' ) {
 mnc [ 2 ] = '\0' ;
 }
 else {
 mnc [ 3 ] = '\0' ;
 }
 }