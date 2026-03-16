IN_PROC_BROWSER_TEST_F ( MimeHandlerViewTest , DataUrl ) {
 const char * kDataUrlCsv = "data:text/csv;
base64,Y29udGVudCB0byByZWFkCg==" ;
 RunTestWithUrl ( GURL ( kDataUrlCsv ) ) ;
 }