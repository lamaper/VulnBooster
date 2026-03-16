static void cirrus_bitblt_start ( CirrusVGAState * s ) {
 uint8_t blt_rop ;
 if ( ! s -> enable_blitter ) {
 goto bitblt_ignore ;
 }
 s -> vga . gr [ 0x31 ] |= CIRRUS_BLT_BUSY ;
 s -> cirrus_blt_width = ( s -> vga . gr [ 0x20 ] | ( s -> vga . gr [ 0x21 ] << 8 ) ) + 1 ;
 s -> cirrus_blt_height = ( s -> vga . gr [ 0x22 ] | ( s -> vga . gr [ 0x23 ] << 8 ) ) + 1 ;
 s -> cirrus_blt_dstpitch = ( s -> vga . gr [ 0x24 ] | ( s -> vga . gr [ 0x25 ] << 8 ) ) ;
 s -> cirrus_blt_srcpitch = ( s -> vga . gr [ 0x26 ] | ( s -> vga . gr [ 0x27 ] << 8 ) ) ;
 s -> cirrus_blt_dstaddr = ( s -> vga . gr [ 0x28 ] | ( s -> vga . gr [ 0x29 ] << 8 ) | ( s -> vga . gr [ 0x2a ] << 16 ) ) ;
 s -> cirrus_blt_srcaddr = ( s -> vga . gr [ 0x2c ] | ( s -> vga . gr [ 0x2d ] << 8 ) | ( s -> vga . gr [ 0x2e ] << 16 ) ) ;
 s -> cirrus_blt_mode = s -> vga . gr [ 0x30 ] ;
 s -> cirrus_blt_modeext = s -> vga . gr [ 0x33 ] ;
 blt_rop = s -> vga . gr [ 0x32 ] ;
 s -> cirrus_blt_dstaddr &= s -> cirrus_addr_mask ;
 s -> cirrus_blt_srcaddr &= s -> cirrus_addr_mask ;


 case CIRRUS_BLTMODE_PIXELWIDTH8 : s -> cirrus_blt_pixelwidth = 1 ;
 break ;
 case CIRRUS_BLTMODE_PIXELWIDTH16 : s -> cirrus_blt_pixelwidth = 2 ;
 break ;
 case CIRRUS_BLTMODE_PIXELWIDTH24 : s -> cirrus_blt_pixelwidth = 3 ;
 break ;
 case CIRRUS_BLTMODE_PIXELWIDTH32 : s -> cirrus_blt_pixelwidth = 4 ;
 break ;
 default : # ifdef DEBUG_BITBLT printf ( "cirrus: bitblt - pixel width is unknown\n" ) ;

 }
 s -> cirrus_blt_mode &= ~ CIRRUS_BLTMODE_PIXELWIDTHMASK ;
 if ( ( s -> cirrus_blt_mode & ( CIRRUS_BLTMODE_MEMSYSSRC | CIRRUS_BLTMODE_MEMSYSDEST ) ) == ( CIRRUS_BLTMODE_MEMSYSSRC | CIRRUS_BLTMODE_MEMSYSDEST ) ) {


 }
 if ( ( s -> cirrus_blt_modeext & CIRRUS_BLTMODEEXT_SOLIDFILL ) && ( s -> cirrus_blt_mode & ( CIRRUS_BLTMODE_MEMSYSDEST | CIRRUS_BLTMODE_TRANSPARENTCOMP | CIRRUS_BLTMODE_PATTERNCOPY | CIRRUS_BLTMODE_COLOREXPAND ) ) == ( CIRRUS_BLTMODE_PATTERNCOPY | CIRRUS_BLTMODE_COLOREXPAND ) ) {
 cirrus_bitblt_fgcol ( s ) ;
 cirrus_bitblt_solidfill ( s , blt_rop ) ;
 }
 else {
 if ( ( s -> cirrus_blt_mode & ( CIRRUS_BLTMODE_COLOREXPAND | CIRRUS_BLTMODE_PATTERNCOPY ) ) == CIRRUS_BLTMODE_COLOREXPAND ) {
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP ) {
 if ( s -> cirrus_blt_modeext & CIRRUS_BLTMODEEXT_COLOREXPINV ) cirrus_bitblt_bgcol ( s ) ;
 else cirrus_bitblt_fgcol ( s ) ;
 s -> cirrus_rop = cirrus_colorexpand_transp [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 else {
 cirrus_bitblt_fgcol ( s ) ;
 cirrus_bitblt_bgcol ( s ) ;
 s -> cirrus_rop = cirrus_colorexpand [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 }
 else if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_PATTERNCOPY ) {
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_COLOREXPAND ) {
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP ) {
 if ( s -> cirrus_blt_modeext & CIRRUS_BLTMODEEXT_COLOREXPINV ) cirrus_bitblt_bgcol ( s ) ;
 else cirrus_bitblt_fgcol ( s ) ;
 s -> cirrus_rop = cirrus_colorexpand_pattern_transp [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 else {
 cirrus_bitblt_fgcol ( s ) ;
 cirrus_bitblt_bgcol ( s ) ;
 s -> cirrus_rop = cirrus_colorexpand_pattern [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 }
 else {
 s -> cirrus_rop = cirrus_patternfill [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 }
 else {
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_TRANSPARENTCOMP ) {
 if ( s -> cirrus_blt_pixelwidth > 2 ) {
 printf ( "src transparent without colorexpand must be 8bpp or 16bpp\n" ) ;
 goto bitblt_ignore ;
 }
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_BACKWARDS ) {
 s -> cirrus_blt_dstpitch = - s -> cirrus_blt_dstpitch ;
 s -> cirrus_blt_srcpitch = - s -> cirrus_blt_srcpitch ;
 s -> cirrus_rop = cirrus_bkwd_transp_rop [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 else {
 s -> cirrus_rop = cirrus_fwd_transp_rop [ rop_to_index [ blt_rop ] ] [ s -> cirrus_blt_pixelwidth - 1 ] ;
 }
 }
 else {
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_BACKWARDS ) {
 s -> cirrus_blt_dstpitch = - s -> cirrus_blt_dstpitch ;
 s -> cirrus_blt_srcpitch = - s -> cirrus_blt_srcpitch ;
 s -> cirrus_rop = cirrus_bkwd_rop [ rop_to_index [ blt_rop ] ] ;
 }
 else {
 s -> cirrus_rop = cirrus_fwd_rop [ rop_to_index [ blt_rop ] ] ;
 }
 }
 }
 if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_MEMSYSSRC ) {
 if ( ! cirrus_bitblt_cputovideo ( s ) ) goto bitblt_ignore ;
 }
 else if ( s -> cirrus_blt_mode & CIRRUS_BLTMODE_MEMSYSDEST ) {
 if ( ! cirrus_bitblt_videotocpu ( s ) ) goto bitblt_ignore ;
 }
 else {
 if ( ! cirrus_bitblt_videotovideo ( s ) ) goto bitblt_ignore ;
 }
 }
 return ;
 bitblt_ignore : ;
 cirrus_bitblt_reset ( s ) ;
 }