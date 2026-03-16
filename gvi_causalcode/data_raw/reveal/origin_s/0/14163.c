int response_cacheable_indicated_by_cc ( HTTPHdr * response ) {
 uint32_t cc_mask ;
 cc_mask = ( MIME_COOKED_MASK_CC_NO_STORE | MIME_COOKED_MASK_CC_PRIVATE ) ;
 if ( response -> get_cooked_cc_mask ( ) & cc_mask ) {
 return - 1 ;
 }
 cc_mask = ( MIME_COOKED_MASK_CC_PUBLIC | MIME_COOKED_MASK_CC_MAX_AGE | MIME_COOKED_MASK_CC_S_MAXAGE | MIME_COOKED_MASK_CC_MUST_REVALIDATE | MIME_COOKED_MASK_CC_PROXY_REVALIDATE ) ;
 if ( response -> get_cooked_cc_mask ( ) & cc_mask ) {
 return 1 ;
 }
 return 0 ;
 }