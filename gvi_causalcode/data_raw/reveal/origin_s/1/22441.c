static void _SCSUClose ( UConverter * cnv ) {
 if ( cnv -> extraInfo != NULL ) {
 if ( ! cnv -> isExtraLocal ) {
 uprv_free ( cnv -> extraInfo ) ;
 }
 cnv -> extraInfo = NULL ;
 }
 }