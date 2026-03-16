static void dumpinstrs ( struct glyphinfo * gi , uint8 * instrs , int cnt ) {
 int i ;
 if ( ( gi -> flags & ttf_flag_nohints ) ) {
 putshort ( gi -> glyphs , 0 ) ;
 return ;
 }
 if ( gi -> maxp -> maxglyphInstr < cnt ) gi -> maxp -> maxglyphInstr = cnt ;
 putshort ( gi -> glyphs , cnt ) ;
 for ( i = 0 ;
 i < cnt ;
 ++ i ) putc ( instrs [ i ] , gi -> glyphs ) ;
 }