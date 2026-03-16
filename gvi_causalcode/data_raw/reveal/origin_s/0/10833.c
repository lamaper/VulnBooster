void SFDefaultOS2Info ( struct pfminfo * pfminfo , SplineFont * sf , char * fontname ) {
 int samewid = - 1 ;
 char * weight = sf -> cidmaster == NULL ? sf -> weight : sf -> cidmaster -> weight ;
 if ( sf -> pfminfo . pfmset ) {
 if ( pfminfo != & sf -> pfminfo ) * pfminfo = sf -> pfminfo ;
 if ( ! pfminfo -> panose_set ) {
 struct pfminfo info ;
 memset ( & info , 0 , sizeof ( info ) ) ;
 sf -> pfminfo . pfmset = false ;
 SFDefaultOS2Info ( & info , sf , fontname ) ;
 sf -> pfminfo . pfmset = true ;
 memcpy ( pfminfo -> panose , info . panose , sizeof ( info . panose ) ) ;
 }
 }
 else {
 struct pfminfo hold ;
 if ( pfminfo -> hheadset || pfminfo -> vheadset ) hold = * pfminfo ;
 else hold . hheadset = hold . vheadset = false ;
 memset ( pfminfo , '\0' , sizeof ( * pfminfo ) ) ;
 SFDefaultOS2Simple ( pfminfo , sf ) ;
 samewid = CIDOneWidth ( sf ) ;
 pfminfo -> pfmfamily = 0x10 ;
 if ( samewid > 0 ) {
 pfminfo -> pfmfamily = 0x30 ;
 }
 else if ( strstrmatch ( fontname , "sans" ) != NULL ) pfminfo -> pfmfamily = 0x20 ;
 else if ( strstrmatch ( fontname , "script" ) != NULL ) {
 pfminfo -> pfmfamily = 0x40 ;
 pfminfo -> panose [ 0 ] = 3 ;
 }
 if ( samewid == - 1 ) pfminfo -> pfmfamily |= 0x1 ;
 if ( weight != NULL ) OS2WeightCheck ( pfminfo , weight ) ;
 OS2WeightCheck ( pfminfo , fontname ) ;
 if ( strstrmatch ( fontname , "ultra" ) != NULL && strstrmatch ( fontname , "condensed" ) != NULL ) {
 pfminfo -> width = 1 ;
 pfminfo -> panose [ 3 ] = 8 ;
 }
 else if ( strstrmatch ( fontname , "extra" ) != NULL && strstrmatch ( fontname , "condensed" ) != NULL ) {
 pfminfo -> width = 2 ;
 pfminfo -> panose [ 3 ] = 8 ;
 }
 else if ( strstrmatch ( fontname , "semi" ) != NULL && strstrmatch ( fontname , "condensed" ) != NULL ) {
 pfminfo -> width = 4 ;
 pfminfo -> panose [ 3 ] = 6 ;
 }
 else if ( strstrmatch ( fontname , "condensed" ) != NULL || strstrmatch ( fontname , "narrow" ) != NULL ) {
 pfminfo -> width = 3 ;
 pfminfo -> panose [ 3 ] = 6 ;
 }
 else if ( strstrmatch ( fontname , "ultra" ) != NULL && strstrmatch ( fontname , "expanded" ) != NULL ) {
 pfminfo -> width = 9 ;
 pfminfo -> panose [ 3 ] = 7 ;
 }
 else if ( strstrmatch ( fontname , "extra" ) != NULL && strstrmatch ( fontname , "expanded" ) != NULL ) {
 pfminfo -> width = 8 ;
 pfminfo -> panose [ 3 ] = 7 ;
 }
 else if ( strstrmatch ( fontname , "semi" ) != NULL && strstrmatch ( fontname , "expanded" ) != NULL ) {
 pfminfo -> width = 6 ;
 pfminfo -> panose [ 3 ] = 5 ;
 }
 else if ( strstrmatch ( fontname , "expanded" ) != NULL ) {
 pfminfo -> width = 7 ;
 pfminfo -> panose [ 3 ] = 5 ;
 }
 if ( samewid > 0 ) pfminfo -> panose [ 3 ] = 9 ;
 if ( hold . hheadset ) {
 pfminfo -> hheadset = true ;
 pfminfo -> hheadascent_add = hold . hheadascent_add ;
 pfminfo -> hheaddescent_add = hold . hheaddescent_add ;
 pfminfo -> hhead_ascent = hold . hhead_ascent ;
 pfminfo -> hhead_descent = hold . hhead_descent ;
 pfminfo -> linegap = hold . linegap ;
 }
 if ( hold . vheadset ) {
 pfminfo -> vheadset = true ;
 pfminfo -> vlinegap = hold . vlinegap ;
 }
 }
 if ( ! pfminfo -> subsuper_set ) SFDefaultOS2SubSuper ( pfminfo , sf -> ascent + sf -> descent , sf -> italicangle ) ;
 }