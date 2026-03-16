static inline int get_bs ( cavs_vector * mvP , cavs_vector * mvQ , int b ) {
 if ( ( mvP -> ref == REF_INTRA ) || ( mvQ -> ref == REF_INTRA ) ) return 2 ;
 if ( ( abs ( mvP -> x - mvQ -> x ) >= 4 ) || ( abs ( mvP -> y - mvQ -> y ) >= 4 ) ) return 1 ;
 if ( b ) {
 mvP += MV_BWD_OFFS ;
 mvQ += MV_BWD_OFFS ;
 if ( ( abs ( mvP -> x - mvQ -> x ) >= 4 ) || ( abs ( mvP -> y - mvQ -> y ) >= 4 ) ) return 1 ;
 }
 else {
 if ( mvP -> ref != mvQ -> ref ) return 1 ;
 }
 return 0 ;
 }