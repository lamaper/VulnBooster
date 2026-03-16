void virLogFilterFree ( virLogFilterPtr filter ) {
 if ( ! filter ) return ;
 VIR_FREE ( filter -> match ) ;
 VIR_FREE ( filter ) ;
 }