void ber_free ( BerElement * ber , int freebuf ) {
 if ( ber == NULL ) {
 LDAP_MEMORY_DEBUG_ASSERT ( ber != NULL ) ;
 return ;
 }
 if ( freebuf ) ber_free_buf ( ber ) ;
 ber_memfree_x ( ( char * ) ber , ber -> ber_memctx ) ;
 }