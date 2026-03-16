TSReturnCode TSHttpAltInfoCachedRespGet ( TSHttpAltInfo infop , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_alt_info ( infop ) == TS_SUCCESS ) ;
 HttpAltInfo * info = ( HttpAltInfo * ) infop ;
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = & info -> m_cached_resp ;
 * obj = reinterpret_cast < TSMLoc > ( info -> m_cached_resp . m_http ) ;
 return sdk_sanity_check_mbuffer ( * bufp ) ;
 }