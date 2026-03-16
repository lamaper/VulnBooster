int virLogParseOutputs ( const char * src , virLogOutputPtr * * outputs ) {
 int ret = - 1 ;
 int at = - 1 ;
 size_t noutputs = 0 ;
 size_t i , count ;
 char * * strings = NULL ;
 virLogOutputPtr output = NULL ;
 virLogOutputPtr * list = NULL ;
 VIR_DEBUG ( "outputs=%s" , src ) ;
 if ( ! ( strings = virStringSplitCount ( src , " " , 0 , & count ) ) ) goto cleanup ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 if ( STREQ ( strings [ i ] , "" ) ) continue ;
 if ( ! ( output = virLogParseOutput ( strings [ i ] ) ) ) goto cleanup ;
 at = virLogFindOutput ( list , noutputs , output -> dest , output -> name ) ;
 if ( VIR_APPEND_ELEMENT ( list , noutputs , output ) < 0 ) {
 virLogOutputFree ( output ) ;
 goto cleanup ;
 }
 if ( at >= 0 ) {
 virLogOutputFree ( list [ at ] ) ;
 VIR_DELETE_ELEMENT ( list , at , noutputs ) ;
 }
 }
 ret = noutputs ;
 * outputs = list ;
 list = NULL ;
 cleanup : virStringListFree ( strings ) ;
 return ret ;
 }