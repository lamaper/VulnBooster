static int qemuMonitorJSONGetBlockJobInfo ( virJSONValuePtr reply , const char * device , virDomainBlockJobInfoPtr info ) {
 virJSONValuePtr data ;
 int nr_results , i ;
 if ( ! info ) return - 1 ;
 if ( ( data = virJSONValueObjectGet ( reply , "return" ) ) == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "reply was missing return data" ) ) ;
 return - 1 ;
 }
 if ( data -> type != VIR_JSON_TYPE_ARRAY ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "urecognized format of block job information" ) ) ;
 return - 1 ;
 }
 if ( ( nr_results = virJSONValueArraySize ( data ) ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "unable to determine array size" ) ) ;
 return - 1 ;
 }
 for ( i = 0 ;
 i < nr_results ;
 i ++ ) {
 virJSONValuePtr entry = virJSONValueArrayGet ( data , i ) ;
 if ( ! entry ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "missing array element" ) ) ;
 return - 1 ;
 }
 if ( qemuMonitorJSONGetBlockJobInfoOne ( entry , device , info ) == 0 ) return 1 ;
 }
 return 0 ;
 }