static void _ISCIIClose ( UConverter * cnv ) {
 if ( cnv -> extraInfo != NULL ) {
 if ( ! cnv -> isExtraLocal ) {
 uprv_free ( cnv -> extraInfo ) ;
 }
 cnv -> extraInfo = NULL ;
 }
 }