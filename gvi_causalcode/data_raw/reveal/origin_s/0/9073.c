char * qemuAliasTLSObjFromChardevAlias ( const char * chardev_alias ) {
 char * ret ;
 ignore_value ( virAsprintf ( & ret , "obj%s_tls0" , chardev_alias ) ) ;
 return ret ;
 }