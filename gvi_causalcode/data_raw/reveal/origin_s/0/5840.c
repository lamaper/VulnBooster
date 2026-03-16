int qemuMonitorJSONGetBlockStatsInfo ( qemuMonitorPtr mon , const char * dev_name , long long * rd_req , long long * rd_bytes , long long * rd_total_times , long long * wr_req , long long * wr_bytes , long long * wr_total_times , long long * flush_req , long long * flush_total_times , long long * errs ) {
 int ret ;
 int i ;
 int found = 0 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-blockstats" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr devices ;
 * rd_req = * rd_bytes = - 1 ;
 * wr_req = * wr_bytes = * errs = - 1 ;
 if ( rd_total_times ) * rd_total_times = - 1 ;
 if ( wr_total_times ) * wr_total_times = - 1 ;
 if ( flush_req ) * flush_req = - 1 ;
 if ( flush_total_times ) * flush_total_times = - 1 ;
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
 for ( i = 0 ;
 i < virJSONValueArraySize ( devices ) ;
 i ++ ) {
 virJSONValuePtr dev = virJSONValueArrayGet ( devices , i ) ;
 virJSONValuePtr stats ;
 const char * thisdev ;
 if ( ! dev || dev -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( ( thisdev = virJSONValueObjectGetString ( dev , "device" ) ) == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( STRPREFIX ( thisdev , QEMU_DRIVE_HOST_PREFIX ) ) thisdev += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STRNEQ ( thisdev , dev_name ) ) continue ;
 found = 1 ;
 if ( ( stats = virJSONValueObjectGet ( dev , "stats" ) ) == NULL || stats -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats stats entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberLong ( stats , "rd_bytes" , rd_bytes ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "rd_bytes" ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberLong ( stats , "rd_operations" , rd_req ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "rd_operations" ) ;
 goto cleanup ;
 }
 if ( rd_total_times && virJSONValueObjectHasKey ( stats , "rd_total_times_ns" ) && ( virJSONValueObjectGetNumberLong ( stats , "rd_total_times_ns" , rd_total_times ) < 0 ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "rd_total_times_ns" ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberLong ( stats , "wr_bytes" , wr_bytes ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "wr_bytes" ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberLong ( stats , "wr_operations" , wr_req ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "wr_operations" ) ;
 goto cleanup ;
 }
 if ( wr_total_times && virJSONValueObjectHasKey ( stats , "wr_total_times_ns" ) && ( virJSONValueObjectGetNumberLong ( stats , "wr_total_times_ns" , wr_total_times ) < 0 ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "wr_total_times_ns" ) ;
 goto cleanup ;
 }
 if ( flush_req && virJSONValueObjectHasKey ( stats , "flush_operations" ) && ( virJSONValueObjectGetNumberLong ( stats , "flush_operations" , flush_req ) < 0 ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "flush_operations" ) ;
 goto cleanup ;
 }
 if ( flush_total_times && virJSONValueObjectHasKey ( stats , "flush_total_times_ns" ) && ( virJSONValueObjectGetNumberLong ( stats , "flush_total_times_ns" , flush_total_times ) < 0 ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "flush_total_times_ns" ) ;
 goto cleanup ;
 }
 }
 if ( ! found ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot find statistics for device '%s'" ) , dev_name ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }