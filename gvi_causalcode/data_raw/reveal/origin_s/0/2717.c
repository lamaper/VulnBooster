int virLogSetFilters ( const char * src ) {
 int ret = - 1 ;
 int nfilters = 0 ;
 virLogFilterPtr * filters = NULL ;
 if ( virLogInitialize ( ) < 0 ) return - 1 ;
 if ( src && ( nfilters = virLogParseFilters ( src , & filters ) ) < 0 ) goto cleanup ;
 if ( virLogDefineFilters ( filters , nfilters ) < 0 ) goto cleanup ;
 filters = NULL ;
 ret = 0 ;
 cleanup : virLogFilterListFree ( filters , nfilters ) ;
 return ret ;
 }