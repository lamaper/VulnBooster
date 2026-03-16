void macio_ide_init_drives ( MACIOIDEState * s , DriveInfo * * hd_table ) {
 int i ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 if ( hd_table [ i ] ) {
 ide_create_drive ( & s -> bus , i , hd_table [ i ] ) ;
 }
 }
 }