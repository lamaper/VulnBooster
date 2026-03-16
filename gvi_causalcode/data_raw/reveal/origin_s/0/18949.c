static guint iax_circuit_lookup ( const address * address_p , port_type ptype , guint32 port , guint32 callno ) {
 iax_circuit_key key ;
 guint32 * circuit_id_p ;
 key . addr = * address_p ;
 key . ptype = ptype ;
 key . port = port ;
 key . callno = callno ;
 circuit_id_p = ( guint32 * ) g_hash_table_lookup ( iax_circuit_hashtab , & key ) ;
 if ( ! circuit_id_p ) {
 iax_circuit_key * new_key ;
 new_key = wmem_new ( wmem_file_scope ( ) , iax_circuit_key ) ;
 new_key -> addr . type = address_p -> type ;
 new_key -> addr . len = MIN ( address_p -> len , MAX_ADDRESS ) ;
 new_key -> addr . data = new_key -> address_data ;
 memcpy ( new_key -> address_data , address_p -> data , new_key -> addr . len ) ;
 new_key -> ptype = ptype ;
 new_key -> port = port ;
 new_key -> callno = callno ;
 circuit_id_p = ( guint32 * ) wmem_new ( wmem_file_scope ( ) , iax_circuit_key ) ;
 * circuit_id_p = ++ circuitcount ;
 g_hash_table_insert ( iax_circuit_hashtab , new_key , circuit_id_p ) ;


 return * circuit_id_p ;
 }