static guint8 fach_fdd_tctf ( guint8 hdr , guint16 * bit_offs ) {
 guint8 tctf ;
 tctf = hdr >> 6 ;
 switch ( tctf ) {
 case TCTF_BCCH_FACH_FDD : case TCTF_DCCH_DTCH_FACH_FDD : * bit_offs = 2 ;
 return tctf ;
 }
 tctf = hdr >> 4 ;
 switch ( tctf ) {
 case TCTF_MTCH_FACH_FDD : * bit_offs = 4 ;
 return tctf ;
 }
 * bit_offs = 8 ;
 tctf = hdr ;
 switch ( tctf ) {
 case TCTF_CCCH_FACH_FDD : case TCTF_MCCH_FACH_FDD : case TCTF_MSCH_FACH_FDD : case TCTF_CTCH_FACH_FDD : return tctf ;
 default : return tctf ;
 }
 }