static void int_ossl_decode_sanity_check ( long len , long read , long offset ) {
 if ( len != 0 && ( read != len || offset != len ) ) {
 ossl_raise ( eASN1Error , "Type mismatch. Total bytes read: %ld Bytes available: %ld Offset: %ld" , read , len , offset ) ;
 }
 }