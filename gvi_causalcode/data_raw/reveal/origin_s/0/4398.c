int SFFigureDefWidth ( SplineFont * sf , int * _nomwid ) {
 uint16 * widths ;
 uint32 * cumwid ;
 int nomwid , defwid , i , j , sameval = ( int ) 0x80000000 , maxw = 0 , allsame = true ;
 unsigned cnt ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( SCWorthOutputting ( sf -> glyphs [ i ] ) ) {
 if ( maxw < sf -> glyphs [ i ] -> width ) maxw = sf -> glyphs [ i ] -> width ;
 if ( sameval == 0x8000000 ) sameval = sf -> glyphs [ i ] -> width ;
 else if ( sameval != sf -> glyphs [ i ] -> width ) allsame = false ;
 }
 if ( allsame ) {
 nomwid = defwid = sameval ;
 }
 else {
 ++ maxw ;
 if ( maxw > 65535 ) maxw = 3 * ( sf -> ascent + sf -> descent ) ;
 widths = calloc ( maxw , sizeof ( uint16 ) ) ;
 cumwid = calloc ( maxw , sizeof ( uint32 ) ) ;
 defwid = 0 ;
 cnt = 0 ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( SCWorthOutputting ( sf -> glyphs [ i ] ) && sf -> glyphs [ i ] -> width >= 0 && sf -> glyphs [ i ] -> width < maxw ) if ( ++ widths [ sf -> glyphs [ i ] -> width ] > cnt ) {
 defwid = sf -> glyphs [ i ] -> width ;
 cnt = widths [ defwid ] ;
 }
 widths [ defwid ] = 0 ;
 for ( i = 0 ;
 i < maxw ;
 ++ i ) for ( j = - 107 ;
 j <= 107 ;
 ++ j ) if ( i + j >= 0 && i + j < maxw ) cumwid [ i ] += widths [ i + j ] ;
 cnt = 0 ;
 nomwid = 0 ;
 for ( i = 0 ;
 i < maxw ;
 ++ i ) if ( cnt < cumwid [ i ] ) {
 cnt = cumwid [ i ] ;
 nomwid = i ;
 }
 free ( widths ) ;
 free ( cumwid ) ;
 }
 if ( _nomwid != NULL ) * _nomwid = nomwid ;
 return ( defwid ) ;
 }