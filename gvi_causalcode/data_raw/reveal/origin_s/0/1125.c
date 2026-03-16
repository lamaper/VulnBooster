static guint h225ras_call_hash ( gconstpointer k ) {
 const h225ras_call_info_key * key = ( const h225ras_call_info_key * ) k ;
 return key -> reqSeqNum + GPOINTER_TO_UINT ( key -> conversation ) ;
 }