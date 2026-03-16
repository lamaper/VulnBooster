static int get_max_filter_level ( const VP9_COMP * cpi ) {
 if ( cpi -> oxcf . pass == 2 ) {
 return cpi -> twopass . section_intra_rating > 8 ? MAX_LOOP_FILTER * 3 / 4 : MAX_LOOP_FILTER ;
 }
 else {
 return MAX_LOOP_FILTER ;
 }
 }