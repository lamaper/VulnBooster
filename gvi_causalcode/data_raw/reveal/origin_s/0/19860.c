TEST_F ( MdDownloadsDOMHandlerTest , HandleGetDownloads ) {
 TestMdDownloadsDOMHandler handler ( manager ( ) , web_ui ( ) ) ;
 handler . set_web_ui ( web_ui ( ) ) ;
 base : : ListValue empty_search_terms ;
 handler . HandleGetDownloads ( & empty_search_terms ) ;
 EXPECT_EQ ( 1U , web_ui ( ) -> call_data ( ) . size ( ) ) ;
 EXPECT_EQ ( "downloads.Manager.insertItems" , web_ui ( ) -> call_data ( ) [ 0 ] -> function_name ( ) ) ;
 }