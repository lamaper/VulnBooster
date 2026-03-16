int xml_process_chunk ( modsec_rec * msr , const char * buf , unsigned int size , char * * error_msg ) {
 if ( error_msg == NULL ) return - 1 ;
 * error_msg = NULL ;
 if ( msr -> xml -> parsing_ctx == NULL ) {
 msr_log ( msr , 4 , "XML: Initialising parser." ) ;
 msr -> xml -> parsing_ctx = xmlCreatePushParserCtxt ( NULL , NULL , buf , size , "body.xml" ) ;
 if ( msr -> xml -> parsing_ctx == NULL ) {
 * error_msg = apr_psprintf ( msr -> mp , "XML: Failed to create parsing context." ) ;
 return - 1 ;
 }
 }
 else {
 xmlParseChunk ( msr -> xml -> parsing_ctx , buf , size , 0 ) ;
 if ( msr -> xml -> parsing_ctx -> wellFormed != 1 ) {
 * error_msg = apr_psprintf ( msr -> mp , "XML: Failed parsing document." ) ;
 return - 1 ;
 }
 }
 return 1 ;
 }