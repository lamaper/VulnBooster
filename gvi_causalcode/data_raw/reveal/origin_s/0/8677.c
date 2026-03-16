static void redoos2 ( struct alltabs * at ) {
 int i ;
 at -> os2f = tmpfile ( ) ;
 putshort ( at -> os2f , at -> os2 . version ) ;
 putshort ( at -> os2f , at -> os2 . avgCharWid ) ;
 putshort ( at -> os2f , at -> os2 . weightClass ) ;
 putshort ( at -> os2f , at -> os2 . widthClass ) ;
 putshort ( at -> os2f , at -> os2 . fstype ) ;
 putshort ( at -> os2f , at -> os2 . ysubXSize ) ;
 putshort ( at -> os2f , at -> os2 . ysubYSize ) ;
 putshort ( at -> os2f , at -> os2 . ysubXOff ) ;
 putshort ( at -> os2f , at -> os2 . ysubYOff ) ;
 putshort ( at -> os2f , at -> os2 . ysupXSize ) ;
 putshort ( at -> os2f , at -> os2 . ysupYSize ) ;
 putshort ( at -> os2f , at -> os2 . ysupXOff ) ;
 putshort ( at -> os2f , at -> os2 . ysupYOff ) ;
 putshort ( at -> os2f , at -> os2 . yStrikeoutSize ) ;
 putshort ( at -> os2f , at -> os2 . yStrikeoutPos ) ;
 putshort ( at -> os2f , at -> os2 . sFamilyClass ) ;
 for ( i = 0 ;
 i < 10 ;
 ++ i ) putc ( at -> os2 . panose [ i ] , at -> os2f ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) putlong ( at -> os2f , at -> os2 . unicoderange [ i ] ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) putc ( at -> os2 . achVendID [ i ] , at -> os2f ) ;
 putshort ( at -> os2f , at -> os2 . fsSel ) ;
 putshort ( at -> os2f , at -> os2 . firstcharindex ) ;
 putshort ( at -> os2f , at -> os2 . lastcharindex ) ;
 putshort ( at -> os2f , at -> os2 . ascender ) ;
 putshort ( at -> os2f , at -> os2 . descender ) ;
 putshort ( at -> os2f , at -> os2 . linegap ) ;
 putshort ( at -> os2f , at -> os2 . winascent ) ;
 putshort ( at -> os2f , at -> os2 . windescent ) ;
 if ( at -> os2 . version >= 1 ) {
 putlong ( at -> os2f , at -> os2 . ulCodePage [ 0 ] ) ;
 putlong ( at -> os2f , at -> os2 . ulCodePage [ 1 ] ) ;
 }
 if ( at -> os2 . version >= 2 ) {
 putshort ( at -> os2f , at -> os2 . xHeight ) ;
 putshort ( at -> os2f , at -> os2 . capHeight ) ;
 putshort ( at -> os2f , at -> os2 . defChar ) ;
 putshort ( at -> os2f , at -> os2 . breakChar ) ;
 putshort ( at -> os2f , at -> os2 . maxContext ) ;
 }
 at -> os2len = ftell ( at -> os2f ) ;
 if ( ( at -> os2len & 2 ) != 0 ) putshort ( at -> os2f , 0 ) ;
 }