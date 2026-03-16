int qemuDomainDeviceAliasIndex ( const virDomainDeviceInfo * info , const char * prefix ) {
 int idx ;
 if ( ! info -> alias ) return - 1 ;
 if ( ! STRPREFIX ( info -> alias , prefix ) ) return - 1 ;
 if ( virStrToLong_i ( info -> alias + strlen ( prefix ) , NULL , 10 , & idx ) < 0 ) return - 1 ;
 return idx ;
 }