TSReturnCode sdk_sanity_check_continuation ( TSCont cont ) {
 if ( ( cont == nullptr ) || ( ( ( INKContInternal * ) cont ) -> m_free_magic == INKCONT_INTERN_MAGIC_DEAD ) ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }