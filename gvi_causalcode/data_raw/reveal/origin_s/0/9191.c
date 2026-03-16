int qemuMonitorJSONGetBlockStatsParamsNumber ( qemuMonitorPtr mon , int * nparams ) {
 int ret , i , num = 0 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-blockstats" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr devices = NULL ;
 virJSONValuePtr dev = NULL ;
 virJSONValuePtr stats = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret < 0 ) goto cleanup ;
 ret = - 1 ;
 devices = virJSONValueObjectGet ( reply , "return" ) ;
 if ( ! devices || devices -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats reply was missing device list" ) ) ;
 goto cleanup ;
 }
 dev = virJSONValueArrayGet ( devices , 0 ) ;
 if ( ! dev || dev -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( ( stats = virJSONValueObjectGet ( dev , "stats" ) ) == NULL || stats -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats stats entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < stats -> data . object . npairs ;
 i ++ ) {
 const char * key = stats -> data . object . pairs [ i ] . key ;
 if ( STREQ ( key , "rd_bytes" ) || STREQ ( key , "rd_operations" ) || STREQ ( key , "rd_total_times_ns" ) || STREQ ( key , "wr_bytes" ) || STREQ ( key , "wr_operations" ) || STREQ ( key , "wr_total_times_ns" ) || STREQ ( key , "flush_operations" ) || STREQ ( key , "flush_total_times_ns" ) ) {
 num ++ ;
 }
 else {
 if ( STRNEQ ( key , "wr_highest_offset" ) ) VIR_DEBUG ( "Missed block stat: %s" , key ) ;
 }
 }
 * nparams = num ;
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }