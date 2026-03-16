void SFDefaultOS2Simple ( struct pfminfo * pfminfo , SplineFont * sf ) {
 pfminfo -> pfmfamily = 0x11 ;
 pfminfo -> panose [ 0 ] = 2 ;
 pfminfo -> weight = 400 ;
 pfminfo -> panose [ 2 ] = 5 ;
 pfminfo -> width = 5 ;
 pfminfo -> panose [ 3 ] = 3 ;
 pfminfo -> winascent_add = pfminfo -> windescent_add = true ;
 pfminfo -> hheadascent_add = pfminfo -> hheaddescent_add = true ;
 pfminfo -> typoascent_add = pfminfo -> typodescent_add = true ;
 pfminfo -> os2_winascent = pfminfo -> os2_windescent = 0 ;
 if ( sf -> subfonts != NULL ) sf = sf -> subfonts [ 0 ] ;
 pfminfo -> linegap = pfminfo -> vlinegap = pfminfo -> os2_typolinegap = rint ( .09 * ( sf -> ascent + sf -> descent ) ) ;
 }