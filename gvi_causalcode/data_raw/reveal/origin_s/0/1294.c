static int sid_gain_to_lsp_index ( int gain ) {
 if ( gain < 0x10 ) return gain << 6 ;
 else if ( gain < 0x20 ) return gain - 8 << 7 ;
 else return gain - 20 << 8 ;
 }