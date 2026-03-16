static void * init_tls ( void ) {
 GL ( dl_tls_static_nelem ) = GL ( dl_tls_max_dtv_idx ) ;
 if ( GL ( dl_initial_dtv ) != NULL ) return NULL ;
 size_t nelem = GL ( dl_tls_max_dtv_idx ) + 1 + TLS_SLOTINFO_SURPLUS ;
 GL ( dl_tls_dtv_slotinfo_list ) = ( struct dtv_slotinfo_list * ) calloc ( sizeof ( struct dtv_slotinfo_list ) + nelem * sizeof ( struct dtv_slotinfo ) , 1 ) ;
 struct dtv_slotinfo * slotinfo = GL ( dl_tls_dtv_slotinfo_list ) -> slotinfo ;
 GL ( dl_tls_dtv_slotinfo_list ) -> len = nelem ;
 GL ( dl_tls_dtv_slotinfo_list ) -> next = NULL ;
 assert ( GL ( dl_ns ) [ LM_ID_BASE + 1 ] . _ns_loaded == NULL ) ;
 int i = 0 ;
 for ( struct link_map * l = GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded ;
 l != NULL ;
 l = l -> l_next ) if ( l -> l_tls_blocksize != 0 ) {
 slotinfo [ i ] . map = l ;
 ++ i ;
 }
 assert ( i == GL ( dl_tls_max_dtv_idx ) ) ;
 _dl_determine_tlsoffset ( ) ;
 void * tcbp = _dl_allocate_tls_storage ( ) ;
 if ( tcbp == NULL ) _dl_fatal_printf ( "\ cannot allocate TLS data structures for initial thread" ) ;
 GL ( dl_initial_dtv ) = GET_DTV ( tcbp ) ;
 const char * lossage = TLS_INIT_TP ( tcbp ) ;
 if ( __glibc_unlikely ( lossage != NULL ) ) _dl_fatal_printf ( "cannot set up thread-local storage: %s\n" , lossage ) ;
 tls_init_tp_called = true ;
 return tcbp ;
 }