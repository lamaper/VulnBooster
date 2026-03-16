static void WinBB ( SplineFont * sf , uint16 * winascent , uint16 * windescent , struct alltabs * at ) {
 * winascent = at -> head . ymax ;
 * windescent = - at -> head . ymin ;
 if ( sf -> cidmaster != NULL ) sf = sf -> cidmaster ;
 if ( sf -> pfminfo . winascent_add ) * winascent += sf -> pfminfo . os2_winascent ;
 else * winascent = sf -> pfminfo . os2_winascent ;
 if ( sf -> pfminfo . windescent_add ) * windescent += sf -> pfminfo . os2_windescent ;
 else * windescent = sf -> pfminfo . os2_windescent ;
 }