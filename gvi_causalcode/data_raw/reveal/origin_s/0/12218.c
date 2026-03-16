IN_PROC_BROWSER_TEST_F ( DownloadExtensionTest , DownloadExtensionTest_OnDeterminingFilename_IncognitoSplit ) {
 LoadExtension ( "downloads_split" ) ;
 ASSERT_TRUE ( StartEmbeddedTestServer ( ) ) ;
 std : : string download_url = embedded_test_server ( ) -> GetURL ( "/slow?0" ) . spec ( ) ;
 GoOnTheRecord ( ) ;
 AddFilenameDeterminer ( ) ;
 GoOffTheRecord ( ) ;
 AddFilenameDeterminer ( ) ;
 GoOnTheRecord ( ) ;
 std : : unique_ptr < base : : Value > result ( RunFunctionAndReturnResult ( new DownloadsDownloadFunction ( ) , base : : StringPrintf ( "[{
\"url\": \"%s\"}
]" , download_url . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( result . get ( ) ) ;
 int result_id = - 1 ;
 ASSERT_TRUE ( result -> GetAsInteger ( & result_id ) ) ;
 DownloadItem * item = GetCurrentManager ( ) -> GetDownload ( result_id ) ;
 ASSERT_TRUE ( item ) ;
 ScopedCancellingItem canceller ( item ) ;
 ASSERT_EQ ( download_url , item -> GetOriginalUrl ( ) . spec ( ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnCreated : : kEventName , base : : StringPrintf ( "[{
\"danger\": \"safe\"," " \"incognito\": false," " \"id\": %d," " \"mime\": \"text/plain\"," " \"paused\": false," " \"url\": \"%s\"}
]" , result_id , download_url . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnDeterminingFilename : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"incognito\": false," " \"filename\":\"slow.txt\"}
]" , result_id ) ) ) ;
 ASSERT_TRUE ( item -> GetTargetFilePath ( ) . empty ( ) ) ;
 ASSERT_EQ ( DownloadItem : : IN_PROGRESS , item -> GetState ( ) ) ;
 std : : string error ;
 ASSERT_TRUE ( ExtensionDownloadsEventRouter : : DetermineFilename ( current_browser ( ) -> profile ( ) , false , GetExtensionId ( ) , result_id , base : : FilePath ( FILE_PATH_LITERAL ( "42.txt" ) ) , downloads : : FILENAME_CONFLICT_ACTION_UNIQUIFY , & error ) ) ;
 EXPECT_EQ ( "" , error ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"filename\": {
" " \"previous\": \"\"," " \"current\": \"%s\"}
}
]" , result_id , GetFilename ( "42.txt" ) . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"state\": {
" " \"previous\": \"in_progress\"," " \"current\": \"complete\"}
}
]" , result_id ) ) ) ;
 GoOffTheRecord ( ) ;
 result . reset ( RunFunctionAndReturnResult ( new DownloadsDownloadFunction ( ) , base : : StringPrintf ( "[{
\"url\": \"%s\"}
]" , download_url . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( result . get ( ) ) ;
 result_id = - 1 ;
 ASSERT_TRUE ( result -> GetAsInteger ( & result_id ) ) ;
 item = GetCurrentManager ( ) -> GetDownload ( result_id ) ;
 ASSERT_TRUE ( item ) ;
 ScopedCancellingItem canceller2 ( item ) ;
 ASSERT_EQ ( download_url , item -> GetOriginalUrl ( ) . spec ( ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnCreated : : kEventName , base : : StringPrintf ( "[{
\"danger\": \"safe\"," " \"incognito\": true," " \"id\": %d," " \"mime\": \"text/plain\"," " \"paused\": false," " \"url\": \"%s\"}
]" , result_id , download_url . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnDeterminingFilename : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"incognito\": true," " \"filename\":\"slow.txt\"}
]" , result_id ) ) ) ;
 ASSERT_TRUE ( item -> GetTargetFilePath ( ) . empty ( ) ) ;
 ASSERT_EQ ( DownloadItem : : IN_PROGRESS , item -> GetState ( ) ) ;
 error = "" ;
 ASSERT_TRUE ( ExtensionDownloadsEventRouter : : DetermineFilename ( current_browser ( ) -> profile ( ) , false , GetExtensionId ( ) , result_id , base : : FilePath ( FILE_PATH_LITERAL ( "5.txt" ) ) , downloads : : FILENAME_CONFLICT_ACTION_UNIQUIFY , & error ) ) ;
 EXPECT_EQ ( "" , error ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"filename\": {
" " \"previous\": \"\"," " \"current\": \"%s\"}
}
]" , result_id , GetFilename ( "5.txt" ) . c_str ( ) ) ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"state\": {
" " \"previous\": \"in_progress\"," " \"current\": \"complete\"}
}
]" , result_id ) ) ) ;
 }