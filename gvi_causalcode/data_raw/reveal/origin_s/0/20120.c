static INTERP_FILTER get_interp_filter ( const int64_t threshes [ SWITCHABLE_FILTER_CONTEXTS ] , int is_alt_ref ) {
 if ( ! is_alt_ref && threshes [ EIGHTTAP_SMOOTH ] > threshes [ EIGHTTAP ] && threshes [ EIGHTTAP_SMOOTH ] > threshes [ EIGHTTAP_SHARP ] && threshes [ EIGHTTAP_SMOOTH ] > threshes [ SWITCHABLE - 1 ] ) {
 return EIGHTTAP_SMOOTH ;
 }
 else if ( threshes [ EIGHTTAP_SHARP ] > threshes [ EIGHTTAP ] && threshes [ EIGHTTAP_SHARP ] > threshes [ SWITCHABLE - 1 ] ) {
 return EIGHTTAP_SHARP ;
 }
 else if ( threshes [ EIGHTTAP ] > threshes [ SWITCHABLE - 1 ] ) {
 return EIGHTTAP ;
 }
 else {
 return SWITCHABLE ;
 }
 }