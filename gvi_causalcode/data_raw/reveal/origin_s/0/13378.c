static void ttc_dump ( FILE * ttc , struct alltabs * all , enum fontformat format , int flags , enum ttc_flags ttc_flags ) {
 int i , j , cnt , tot , ch , dup ;
 int offset , startoffset ;
 struct taboff * tab ;
 for ( cnt = 0 ;
 all [ cnt ] . sf != NULL ;
 ++ cnt ) ;
 -- cnt ;
 putlong ( ttc , CHR ( 't' , 't' , 'c' , 'f' ) ) ;
 if ( flags & ttf_flag_dummyDSIG ) {
 putlong ( ttc , 0x00020000 ) ;
 startoffset = 4 * ( 3 + cnt + 4 ) ;
 }
 else {
 putlong ( ttc , 0x00010000 ) ;
 startoffset = 4 * ( 3 + cnt ) ;
 }
 putlong ( ttc , cnt ) ;
 offset = startoffset ;
 for ( i = 0 ;
 i < cnt ;
 ++ i ) {
 putlong ( ttc , offset ) ;
 offset += ( 8 + 16 * MAX_TAB ) ;
 }
 if ( flags & ttf_flag_dummyDSIG ) {
 putlong ( ttc , CHR ( 'D' , 'S' , 'I' , 'G' ) ) ;
 putlong ( ttc , 8 ) ;
 putlong ( ttc , 0x00000001 ) ;
 putlong ( ttc , 0 ) ;
 }
 tot = cnt * ( 8 + 16 * MAX_TAB ) ;
 for ( i = 0 ;
 i < tot ;
 ++ i ) putc ( '\0' , ttc ) ;
 buildtablestructures ( & all [ cnt ] , all [ cnt ] . sf , format ) ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'h' , 'h' , 'e' , 'a' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'v' , 'h' , 'e' , 'a' ) ) ;
 if ( tab != NULL ) {
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 }
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'm' , 'a' , 'x' , 'p' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 for ( i = 0 ;
 i < 64 ;
 ++ i ) putc ( '\0' , ttc ) ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'F' , 'F' , 'T' , 'M' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 for ( i = 0 ;
 i < cnt ;
 ++ i ) {
 ttc_perfonttables ( all , i , cnt , format ) ;
 buildtablestructures ( & all [ i ] , all [ i ] . sf , format ) ;
 for ( j = 0 ;
 j < all [ i ] . tabdir . numtab ;
 ++ j ) {
 if ( all [ i ] . tabdir . tabs [ j ] . data != ( void * ) ( intpt ) - 1 && ( dup = tablefilematch ( & all [ i ] . tabdir . tabs [ j ] , ttc , all , i ) ) != - 1 ) {
 fclose ( all [ i ] . tabdir . tabs [ j ] . data ) ;
 all [ i ] . tabdir . tabs [ j ] . data = ( void * ) ( intpt ) - 1 ;
 all [ i ] . tabdir . tabs [ j ] . length = dup ;
 }
 }
 for ( j = 0 ;
 j < all [ i ] . tabdir . numtab ;
 ++ j ) {
 if ( all [ i ] . tabdir . tabs [ j ] . data != ( void * ) ( intpt ) - 1 ) {
 all [ i ] . tabdir . tabs [ j ] . offset = ftell ( ttc ) ;
 all [ i ] . tabdir . tabs [ j ] . checksum = filechecksum ( all [ i ] . tabdir . tabs [ j ] . data ) ;
 if ( ! ttfcopyfile ( ttc , all [ i ] . tabdir . tabs [ j ] . data , all [ i ] . tabdir . tabs [ j ] . offset , Tag2String ( all [ i ] . tabdir . tabs [ j ] . tag ) ) ) all [ cnt ] . error = true ;
 }
 }
 }
 free ( all [ cnt ] . sf -> glyphs ) ;
 free ( all [ cnt ] . gi . bygid ) ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'h' , 'm' , 't' , 'x' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'v' , 'm' , 't' , 'x' ) ) ;
 if ( tab != NULL ) {
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 }
 if ( format == ff_ttf ) {
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'l' , 'o' , 'c' , 'a' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'g' , 'l' , 'y' , 'f' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 }
 else {
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'C' , 'F' , 'F' , ' ' ) ) ;
 tab -> offset = ftell ( ttc ) ;
 tab -> checksum = filechecksum ( tab -> data ) ;
 if ( ! ttfcopyfile ( ttc , tab -> data , tab -> offset , Tag2String ( tab -> tag ) ) ) all [ cnt ] . error = true ;
 }
 redomaxp ( & all [ cnt ] , format ) ;
 tab = findtabindir ( & all [ cnt ] . tabdir , CHR ( 'm' , 'a' , 'x' , 'p' ) ) ;
 fseek ( ttc , tab -> offset , SEEK_SET ) ;
 tab -> checksum = filechecksum ( all [ cnt ] . maxpf ) ;
 tab -> length = all [ cnt ] . maxplen ;
 rewind ( all [ cnt ] . maxpf ) ;
 while ( ( ch = getc ( all [ cnt ] . maxpf ) ) != EOF ) putc ( ch , ttc ) ;
 for ( offset = startoffset , i = 0 ;
 i < cnt ;
 ++ i , offset += ( 8 + 16 * MAX_TAB ) ) {
 struct alltabs * at = & all [ i ] ;
 for ( j = 0 ;
 j < at -> tabdir . numtab ;
 ++ j ) {
 struct taboff * curtab = & at -> tabdir . tabs [ j ] ;
 if ( curtab -> data == ( void * ) ( intpt ) - 1 ) {
 tab = findtabindir ( & all [ curtab -> length ] . tabdir , curtab -> tag ) ;
 if ( tab == NULL ) {
 IError ( "Failed to find tab" ) ;
 curtab -> length = 0 ;
 curtab -> offset = 0 ;
 curtab -> checksum = 0 ;
 }
 else {
 curtab -> offset = tab -> offset ;
 curtab -> length = tab -> length ;
 curtab -> checksum = tab -> checksum ;
 }
 }
 }
 fseek ( ttc , offset , SEEK_SET ) ;
 for ( j = 0 ;
 j < at -> tabdir . numtab ;
 ++ j ) at -> tabdir . alpha [ j ] = & at -> tabdir . tabs [ j ] ;
 qsort ( at -> tabdir . alpha , at -> tabdir . numtab , sizeof ( struct taboff * ) , tagcomp ) ;
 putlong ( ttc , at -> tabdir . version ) ;
 putshort ( ttc , at -> tabdir . numtab ) ;
 putshort ( ttc , at -> tabdir . searchRange ) ;
 putshort ( ttc , at -> tabdir . entrySel ) ;
 putshort ( ttc , at -> tabdir . rangeShift ) ;
 for ( j = 0 ;
 j < at -> tabdir . numtab ;
 ++ j ) {
 putlong ( ttc , at -> tabdir . alpha [ j ] -> tag ) ;
 putlong ( ttc , at -> tabdir . alpha [ j ] -> checksum ) ;
 putlong ( ttc , at -> tabdir . alpha [ j ] -> offset ) ;
 putlong ( ttc , at -> tabdir . alpha [ j ] -> length ) ;
 }
 }
 tab = findtabindir ( & all [ 0 ] . tabdir , CHR ( 'h' , 'e' , 'a' , 'd' ) ) ;
 if ( tab != NULL ) {
 int checksum ;
 checksum = filechecksum ( ttc ) ;
 checksum = 0xb1b0afba - checksum ;
 fseek ( ttc , tab -> offset + 2 * sizeof ( int32 ) , SEEK_SET ) ;
 putlong ( ttc , checksum ) ;
 }
 }