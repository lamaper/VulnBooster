static int qemuMonitorJSONBlockIoThrottleInfo ( virJSONValuePtr result , const char * device , virDomainBlockIoTuneInfoPtr reply ) {
 virJSONValuePtr io_throttle ;
 int ret = - 1 ;
 int i ;
 int found = 0 ;
 io_throttle = virJSONValueObjectGet ( result , "return" ) ;
 if ( ! io_throttle || io_throttle -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( " block_io_throttle reply was missing device list" ) ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < virJSONValueArraySize ( io_throttle ) ;
 i ++ ) {
 virJSONValuePtr temp_dev = virJSONValueArrayGet ( io_throttle , i ) ;
 virJSONValuePtr inserted ;
 const char * current_dev ;
 if ( ! temp_dev || temp_dev -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block io throttle device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( ( current_dev = virJSONValueObjectGetString ( temp_dev , "device" ) ) == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block io throttle device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( STRPREFIX ( current_dev , QEMU_DRIVE_HOST_PREFIX ) ) current_dev += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STREQ ( current_dev , device ) ) continue ;
 found = 1 ;
 if ( ( inserted = virJSONValueObjectGet ( temp_dev , "inserted" ) ) == NULL || inserted -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block io throttle inserted entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "bps" , & reply -> total_bytes_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read total_bytes_sec" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "bps_rd" , & reply -> read_bytes_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read read_bytes_sec" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "bps_wr" , & reply -> write_bytes_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read write_bytes_sec" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "iops" , & reply -> total_iops_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read total_iops_sec" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "iops_rd" , & reply -> read_iops_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read read_iops_sec" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( inserted , "iops_wr" , & reply -> write_iops_sec ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot read write_iops_sec" ) ) ;
 goto cleanup ;
 }
 break ;
 }
 if ( ! found ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot find throttling info for device '%s'" ) , device ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : return ret ;
 }