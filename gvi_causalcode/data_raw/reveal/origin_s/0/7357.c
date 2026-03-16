int qemuMonitorJSONGetBlockExtent ( qemuMonitorPtr mon , const char * dev_name , unsigned long long * extent ) {
 int ret = - 1 ;
 int i ;
 int found = 0 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-blockstats" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr devices ;
 * extent = 0 ;
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
 virJSONValuePtr parent ;
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
 if ( ( parent = virJSONValueObjectGet ( dev , "parent" ) ) == NULL || parent -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats parent entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( ( stats = virJSONValueObjectGet ( parent , "stats" ) ) == NULL || stats -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "blockstats stats entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( stats , "wr_highest_offset" , extent ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s statistic" ) , "wr_highest_offset" ) ;
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