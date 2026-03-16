static void U_CALLCONV _ISCIIClose ( UConverter * cnv ) {
 if ( cnv -> extraInfo != NULL ) {
 if ( ! cnv -> isExtraLocal ) {
 uprv_free ( cnv -> extraInfo ) ;
 }
 cnv -> extraInfo = NULL ;
 }
 }