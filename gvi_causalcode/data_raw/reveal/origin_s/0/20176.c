int qemuMonitorJSONGetVirtType ( qemuMonitorPtr mon , int * virtType ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-kvm" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 * virtType = VIR_DOMAIN_VIRT_QEMU ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) {
 virJSONValuePtr data ;
 bool val = false ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info kvm reply was missing return data" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetBoolean ( data , "enabled" , & val ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info kvm reply missing 'running' field" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( val ) * virtType = VIR_DOMAIN_VIRT_KVM ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }