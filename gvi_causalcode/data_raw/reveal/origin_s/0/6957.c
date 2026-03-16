static TX_MODE select_tx_mode ( const VP9_COMP * cpi ) {
 if ( cpi -> mb . e_mbd . lossless ) return ONLY_4X4 ;
 if ( cpi -> sf . tx_size_search_method == USE_LARGESTALL ) return ALLOW_32X32 ;
 else if ( cpi -> sf . tx_size_search_method == USE_FULL_RD || cpi -> sf . tx_size_search_method == USE_TX_8X8 ) return TX_MODE_SELECT ;
 else return cpi -> common . tx_mode ;
 }