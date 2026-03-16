static int qemuMonitorJSONExtractPtyPaths ( virJSONValuePtr reply , virHashTablePtr paths ) {
 virJSONValuePtr data ;
 int ret = - 1 ;
 int i ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device reply was missing return data" ) ) ;
 goto cleanup ;
 }
 if ( data -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device information was not an array" ) ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < virJSONValueArraySize ( data ) ;
 i ++ ) {
 virJSONValuePtr entry = virJSONValueArrayGet ( data , i ) ;
 const char * type ;
 const char * id ;
 if ( ! entry ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device information was missing array element" ) ) ;
 goto cleanup ;
 }
 if ( ! ( type = virJSONValueObjectGetString ( entry , "filename" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device information was missing filename" ) ) ;
 goto cleanup ;
 }
 if ( ! ( id = virJSONValueObjectGetString ( entry , "label" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device information was missing filename" ) ) ;
 goto cleanup ;
 }
 if ( STRPREFIX ( type , "pty:" ) ) {
 char * path = strdup ( type + strlen ( "pty:" ) ) ;
 if ( ! path ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virHashAddEntry ( paths , id , path ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to save chardev path '%s'" ) , path ) ;
 VIR_FREE ( path ) ;
 goto cleanup ;
 }
 }
 }
 ret = 0 ;
 cleanup : return ret ;
 }