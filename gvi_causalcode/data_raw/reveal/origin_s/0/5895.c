static gint h225ras_call_equal ( gconstpointer k1 , gconstpointer k2 ) {
 const h225ras_call_info_key * key1 = ( const h225ras_call_info_key * ) k1 ;
 const h225ras_call_info_key * key2 = ( const h225ras_call_info_key * ) k2 ;
 return ( key1 -> reqSeqNum == key2 -> reqSeqNum && key1 -> conversation == key2 -> conversation ) ;
 }