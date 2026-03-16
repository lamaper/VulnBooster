static FILE * NeedsVariationSequenceTable ( SplineFont * sf , int * vslen ) {
 int gid , vs_cnt = 0 , vs_max = 512 , i , j , k , cnt , mingid , maxgid ;
 struct altuni * altuni , * au ;
 int32 vsbuf [ 512 ] , * vses = vsbuf ;
 FILE * format14 ;
 uint32 * avail = NULL ;
 enum vs_type {
 vs_default = ( 1 << 24 ) , vs_nondefault = ( 2 << 24 ) }
 ;
 SplineChar * sc ;
 uint32 here ;
 int any ;
 mingid = maxgid = - 1 ;
 for ( gid = 0 ;
 gid < sf -> glyphcnt ;
 ++ gid ) if ( ( sc = sf -> glyphs [ gid ] ) != NULL ) {
 for ( altuni = sc -> altuni ;
 altuni != NULL ;
 altuni = altuni -> next ) {
 if ( altuni -> unienc != - 1 && ( uint32 ) altuni -> unienc < unicode4_size && altuni -> vs != - 1 && altuni -> fid == 0 ) {
 for ( i = 0 ;
 i < vs_cnt ;
 ++ i ) if ( vses [ i ] == altuni -> vs ) break ;
 if ( i >= vs_cnt ) {
 if ( i >= vs_max ) {
 if ( vses == vsbuf ) {
 vses = malloc ( ( vs_max *= 2 ) * sizeof ( uint32 ) ) ;
 memcpy ( vses , vsbuf , sizeof ( vsbuf ) ) ;
 }
 else vses = realloc ( vses , ( vs_max += 512 ) * sizeof ( uint32 ) ) ;
 }
 vses [ vs_cnt ++ ] = altuni -> vs ;
 }
 if ( mingid == - 1 ) mingid = maxgid = gid ;
 else maxgid = gid ;
 }
 }
 }
 if ( vs_cnt == 0 ) {
 * vslen = 0 ;
 return ( NULL ) ;
 }
 for ( i = 0 ;
 i < vs_cnt ;
 ++ i ) for ( j = i + 1 ;
 j < vs_cnt ;
 ++ j ) {
 if ( vses [ i ] > vses [ j ] ) {
 int temp = vses [ i ] ;
 vses [ i ] = vses [ j ] ;
 vses [ j ] = temp ;
 }
 }
 avail = malloc ( unicode4_size * sizeof ( uint32 ) ) ;
 format14 = tmpfile ( ) ;
 putshort ( format14 , 14 ) ;
 putlong ( format14 , 0 ) ;
 putlong ( format14 , vs_cnt ) ;
 for ( i = 0 ;
 i < vs_cnt ;
 ++ i ) {
 putu24 ( format14 , vses [ i ] ) ;
 putlong ( format14 , 0 ) ;
 putlong ( format14 , 0 ) ;
 }
 for ( i = 0 ;
 i < vs_cnt ;
 ++ i ) {
 memset ( avail , 0 , unicode4_size * sizeof ( uint32 ) ) ;
 any = 0 ;
 for ( gid = mingid ;
 gid <= maxgid ;
 ++ gid ) if ( ( sc = sf -> glyphs [ gid ] ) != NULL ) {
 for ( altuni = sc -> altuni ;
 altuni != NULL ;
 altuni = altuni -> next ) {
 if ( altuni -> unienc != - 1 && altuni -> unienc < ( int ) unicode4_size && altuni -> vs == vses [ i ] && altuni -> fid == 0 ) {
 for ( au = sc -> altuni ;
 au != NULL ;
 au = au -> next ) if ( au -> unienc == altuni -> unienc && au -> vs == - 1 && au -> fid == 0 ) break ;
 if ( altuni -> unienc == sc -> unicodeenc || au != NULL ) {
 avail [ altuni -> unienc ] = gid | vs_default ;
 any |= vs_default ;
 }
 else {
 avail [ altuni -> unienc ] = gid | vs_nondefault ;
 any |= vs_nondefault ;
 }
 }
 }
 }
 if ( any & vs_default ) {
 here = ftell ( format14 ) ;
 fseek ( format14 , 10 + i * 11 + 3 , SEEK_SET ) ;
 putlong ( format14 , here ) ;
 fseek ( format14 , 0 , SEEK_END ) ;
 cnt = 0 ;
 for ( j = 0 ;
 ( unsigned ) j < unicode4_size ;
 ++ j ) if ( avail [ j ] & vs_default ) {
 for ( k = j + 1 ;
 ( unsigned ) k < unicode4_size && ( avail [ k ] & vs_default ) ;
 ++ k ) ;
 if ( k - j > 256 ) k = j + 256 ;
 ++ cnt ;
 j = k - 1 ;
 }
 putlong ( format14 , cnt ) ;
 for ( j = 0 ;
 ( unsigned ) j < unicode4_size ;
 ++ j ) if ( avail [ j ] & vs_default ) {
 for ( k = j + 1 ;
 ( unsigned ) k < unicode4_size && ( avail [ k ] & vs_default ) ;
 ++ k ) ;
 if ( k - j > 256 ) k = j + 256 ;
 putu24 ( format14 , j ) ;
 putc ( k - j - 1 , format14 ) ;
 j = k - 1 ;
 }
 }
 if ( any & vs_nondefault ) {
 here = ftell ( format14 ) ;
 fseek ( format14 , 10 + i * 11 + 7 , SEEK_SET ) ;
 putlong ( format14 , here ) ;
 fseek ( format14 , 0 , SEEK_END ) ;
 cnt = 0 ;
 for ( j = 0 ;
 ( unsigned ) j < unicode4_size ;
 ++ j ) if ( avail [ j ] & vs_nondefault ) ++ cnt ;
 putlong ( format14 , cnt ) ;
 for ( j = 0 ;
 ( unsigned ) j < unicode4_size ;
 ++ j ) if ( avail [ j ] & vs_nondefault ) {
 putu24 ( format14 , j ) ;
 putshort ( format14 , sf -> glyphs [ avail [ j ] & 0xffff ] -> ttf_glyph ) ;
 }
 }
 }
 here = ftell ( format14 ) ;
 fseek ( format14 , 2 , SEEK_SET ) ;
 putlong ( format14 , here ) ;
 fseek ( format14 , 0 , SEEK_END ) ;
 if ( here & 1 ) {
 putc ( '\0' , format14 ) ;
 ++ here ;
 }
 if ( here & 2 ) {
 putshort ( format14 , 0 ) ;
 here += 2 ;
 }
 * vslen = here ;
 free ( avail ) ;
 if ( vses != vsbuf ) free ( vses ) ;
 return ( format14 ) ;
 }