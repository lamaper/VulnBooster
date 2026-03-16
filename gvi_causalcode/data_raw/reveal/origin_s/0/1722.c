void TSHttpAltInfoQualitySet ( TSHttpAltInfo infop , float quality ) {
 sdk_assert ( sdk_sanity_check_alt_info ( infop ) == TS_SUCCESS ) ;
 HttpAltInfo * info = ( HttpAltInfo * ) infop ;
 info -> m_qvalue = quality ;
 }