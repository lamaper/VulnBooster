static void dumptype42 ( FILE * type42 , struct alltabs * at , enum fontformat format ) {
 FILE * temp = tmpfile ( ) ;
 struct hexout hexout ;
 int i , length ;
 dumpttf ( temp , at ) ;
 rewind ( temp ) ;
 hexout . type42 = type42 ;
 hexout . bytesout = 0 ;
 qsort ( at -> tabdir . ordered , at -> tabdir . numtab , sizeof ( struct taboff * ) , tcomp2 ) ;
 dumphex ( & hexout , temp , at -> tabdir . ordered [ 0 ] -> offset ) ;
 for ( i = 0 ;
 i < at -> tabdir . numtab ;
 ++ i ) {
 if ( at -> tabdir . ordered [ i ] -> length > 65534 && at -> tabdir . ordered [ i ] -> tag == CHR ( 'g' , 'l' , 'y' , 'f' ) ) {
 uint32 last = 0 ;
 int j ;
 fseek ( temp , at -> tabdir . ordered [ i ] -> offset , SEEK_SET ) ;
 for ( j = 0 ;
 j < at -> maxp . numGlyphs ;
 ++ j ) {
 if ( at -> gi . loca [ j + 1 ] - last > 65534 ) {
 dumphex ( & hexout , temp , at -> gi . loca [ j ] - last ) ;
 last = at -> gi . loca [ j ] ;
 }
 }
 dumphex ( & hexout , temp , at -> gi . loca [ j ] - last ) ;
 }
 else {
 if ( i < at -> tabdir . numtab - 1 ) length = at -> tabdir . ordered [ i + 1 ] -> offset - at -> tabdir . ordered [ i ] -> offset ;
 else {
 fseek ( temp , 0 , SEEK_END ) ;
 length = ftell ( temp ) - at -> tabdir . ordered [ i ] -> offset ;
 }
 fseek ( temp , at -> tabdir . ordered [ i ] -> offset , SEEK_SET ) ;
 dumphex ( & hexout , temp , length ) ;
 }
 }
 fclose ( temp ) ;
 }