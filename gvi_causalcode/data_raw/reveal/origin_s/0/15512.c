void * TSConfigDataGet ( TSConfig configp ) {
 INKConfigImpl * config = ( INKConfigImpl * ) configp ;
 return config -> mdata ;
 }