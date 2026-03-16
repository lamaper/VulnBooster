static int qemuMonitorJSONExtractCPUInfo ( virJSONValuePtr reply , int * * pids ) {
 virJSONValuePtr data ;
 int ret = - 1 ;
 int i ;
 int * threads = NULL ;
 int ncpus ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cpu reply was missing return data" ) ) ;
 goto cleanup ;
 }
 if ( data -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cpu information was not an array" ) ) ;
 goto cleanup ;
 }
 if ( ( ncpus = virJSONValueArraySize ( data ) ) <= 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cpu information was empty" ) ) ;
 goto cleanup ;
 }
 if ( VIR_REALLOC_N ( threads , ncpus ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 for ( i = 0 ;
 i < ncpus ;
 i ++ ) {
 virJSONValuePtr entry = virJSONValueArrayGet ( data , i ) ;
 int cpu ;
 int thread ;
 if ( ! entry ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "character device information was missing array element" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberInt ( entry , "CPU" , & cpu ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cpu information was missing cpu number" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberInt ( entry , "thread_id" , & thread ) < 0 ) {
 ret = 0 ;
 goto cleanup ;
 }
 if ( cpu != i ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected cpu index %d expecting %d" ) , i , cpu ) ;
 goto cleanup ;
 }
 threads [ i ] = thread ;
 }
 * pids = threads ;
 threads = NULL ;
 ret = ncpus ;
 cleanup : VIR_FREE ( threads ) ;
 return ret ;
 }