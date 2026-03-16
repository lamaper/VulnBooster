static void dumpttf ( FILE * ttf , struct alltabs * at ) {
 int32 checksum ;
 int i , head_index = - 1 ;
 putlong ( ttf , at -> tabdir . version ) ;
 putshort ( ttf , at -> tabdir . numtab ) ;
 putshort ( ttf , at -> tabdir . searchRange ) ;
 putshort ( ttf , at -> tabdir . entrySel ) ;
 putshort ( ttf , at -> tabdir . rangeShift ) ;
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) {
 if ( at -> tabdir . alpha [ i ] -> tag == CHR ( 'h' , 'e' , 'a' , 'd' ) || at -> tabdir . alpha [ i ] -> tag == CHR ( 'b' , 'h' , 'e' , 'd' ) ) head_index = i ;
 putlong ( ttf , at -> tabdir . alpha [ i ] -> tag ) ;
 putlong ( ttf , at -> tabdir . alpha [ i ] -> checksum ) ;
 putlong ( ttf , at -> tabdir . alpha [ i ] -> offset ) ;
 putlong ( ttf , at -> tabdir . alpha [ i ] -> length ) ;
 }
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) if ( at -> tabdir . ordered [ i ] -> data != NULL ) {
 if ( ! ttfcopyfile ( ttf , at -> tabdir . ordered [ i ] -> data , at -> tabdir . ordered [ i ] -> offset , Tag2String ( at -> tabdir . ordered [ i ] -> tag ) ) ) at -> error = true ;
 }
 if ( head_index != - 1 ) {
 checksum = filechecksum ( ttf ) ;
 checksum = 0xb1b0afba - checksum ;
 fseek ( ttf , at -> tabdir . alpha [ head_index ] -> offset + 2 * sizeof ( int32 ) , SEEK_SET ) ;
 putlong ( ttf , checksum ) ;
 }
 }