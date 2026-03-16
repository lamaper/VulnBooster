int xml_complete ( modsec_rec * msr , char * * error_msg ) {
 if ( error_msg == NULL ) return - 1 ;
 * error_msg = NULL ;
 if ( msr -> xml -> parsing_ctx != NULL ) {
 xmlParseChunk ( msr -> xml -> parsing_ctx , NULL , 0 , 1 ) ;
 msr -> xml -> well_formed = msr -> xml -> parsing_ctx -> wellFormed ;
 msr -> xml -> doc = msr -> xml -> parsing_ctx -> myDoc ;
 xmlFreeParserCtxt ( msr -> xml -> parsing_ctx ) ;
 msr -> xml -> parsing_ctx = NULL ;
 msr_log ( msr , 4 , "XML: Parsing complete (well_formed %u)." , msr -> xml -> well_formed ) ;
 if ( msr -> xml -> well_formed != 1 ) {
 * error_msg = apr_psprintf ( msr -> mp , "XML: Failed parsing document." ) ;
 return - 1 ;
 }
 }
 return 1 ;
 }