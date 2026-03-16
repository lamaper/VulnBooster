int qemuMonitorJSONGetBlockInfo ( qemuMonitorPtr mon , const char * devname , struct qemuDomainDiskInfo * info ) {
 int ret = 0 ;
 bool found = false ;
 int i ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-block" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr devices ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret < 0 ) goto cleanup ;
 ret = - 1 ;
 devices = virJSONValueObjectGet ( reply , "return" ) ;
 if ( ! devices || devices -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block info reply was missing device list" ) ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < virJSONValueArraySize ( devices ) ;
 i ++ ) {
 virJSONValuePtr dev = virJSONValueArrayGet ( devices , i ) ;
 const char * thisdev ;
 if ( ! dev || dev -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block info device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( ( thisdev = virJSONValueObjectGetString ( dev , "device" ) ) == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "block info device entry was not in expected format" ) ) ;
 goto cleanup ;
 }
 if ( STRPREFIX ( thisdev , QEMU_DRIVE_HOST_PREFIX ) ) thisdev += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STRNEQ ( thisdev , devname ) ) continue ;
 found = true ;
 if ( virJSONValueObjectGetBoolean ( dev , "removable" , & info -> removable ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s value" ) , "removable" ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetBoolean ( dev , "locked" , & info -> locked ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot read %s value" ) , "locked" ) ;
 goto cleanup ;
 }
 ignore_value ( virJSONValueObjectGetBoolean ( dev , "tray-open" , & info -> tray_open ) ) ;
 break ;
 }
 if ( ! found ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "cannot find info for device '%s'" ) , devname ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }