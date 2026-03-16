IN_PROC_BROWSER_TEST_F ( DownloadExtensionTest , DISABLED_DownloadExtensionTest_OnDeterminingFilename_InterruptedResume ) {
 LoadExtension ( "downloads_split" ) ;
 ASSERT_TRUE ( StartEmbeddedTestServer ( ) ) ;
 GoOnTheRecord ( ) ;
 content : : RenderProcessHost * host = AddFilenameDeterminer ( ) ;
 DownloadItem * item = NULL ;
 {
 DownloadManager * manager = GetCurrentManager ( ) ;
 std : : unique_ptr < content : : DownloadTestObserver > observer ( new JustInProgressDownloadObserver ( manager , 1 ) ) ;
 ASSERT_EQ ( 0 , manager -> InProgressCount ( ) ) ;
 ASSERT_EQ ( 0 , manager -> NonMaliciousInProgressCount ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( current_browser ( ) , GURL ( net : : URLRequestSlowDownloadJob : : kUnknownSizeUrl ) , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 observer -> WaitForFinished ( ) ;
 EXPECT_EQ ( 1u , observer -> NumDownloadsSeenInState ( DownloadItem : : IN_PROGRESS ) ) ;
 DownloadManager : : DownloadVector items ;
 manager -> GetAllDownloads ( & items ) ;
 for ( DownloadManager : : DownloadVector : : iterator iter = items . begin ( ) ;
 iter != items . end ( ) ;
 ++ iter ) {
 if ( ( * iter ) -> GetState ( ) == DownloadItem : : IN_PROGRESS ) {
 EXPECT_EQ ( NULL , item ) ;
 item = * iter ;
 }
 }
 ASSERT_TRUE ( item ) ;
 }
 ScopedCancellingItem canceller ( item ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnCreated : : kEventName , base : : StringPrintf ( "[{
\"danger\": \"safe\"," " \"incognito\": false," " \"id\": %d," " \"mime\": \"application/octet-stream\"," " \"paused\": false}
]" , item -> GetId ( ) ) ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnDeterminingFilename : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"incognito\": false," " \"filename\":\"download-unknown-size\"}
]" , item -> GetId ( ) ) ) ) ;
 ASSERT_TRUE ( item -> GetTargetFilePath ( ) . empty ( ) ) ;
 ASSERT_EQ ( DownloadItem : : IN_PROGRESS , item -> GetState ( ) ) ;
 ClearEvents ( ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( current_browser ( ) , GURL ( net : : URLRequestSlowDownloadJob : : kErrorDownloadUrl ) , WindowOpenDisposition : : NEW_BACKGROUND_TAB , ui_test_utils : : BROWSER_TEST_WAIT_FOR_NAVIGATION ) ;
 std : : string error ;
 ASSERT_TRUE ( ExtensionDownloadsEventRouter : : DetermineFilename ( current_browser ( ) -> profile ( ) , false , GetExtensionId ( ) , item -> GetId ( ) , base : : FilePath ( FILE_PATH_LITERAL ( "42.txt" ) ) , downloads : : FILENAME_CONFLICT_ACTION_UNIQUIFY , & error ) ) << error ;
 EXPECT_EQ ( "" , error ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"filename\": {
" " \"previous\": \"\"," " \"current\": \"%s\"}
}
]" , item -> GetId ( ) , GetFilename ( "42.txt" ) . c_str ( ) ) ) ) ;
 content : : DownloadUpdatedObserver interrupted ( item , base : : Bind ( ItemIsInterrupted ) ) ;
 ASSERT_TRUE ( interrupted . WaitForEvent ( ) ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"error\":{
\"current\":\"NETWORK_FAILED\"}
," " \"state\":{
" " \"previous\":\"in_progress\"," " \"current\":\"interrupted\"}
}
]" , item -> GetId ( ) ) ) ) ;
 ClearEvents ( ) ;
 RemoveFilenameDeterminer ( host ) ;
 item -> Resume ( ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"error\":{
\"previous\":\"NETWORK_FAILED\"}
," " \"state\":{
" " \"previous\":\"interrupted\"," " \"current\":\"in_progress\"}
}
]" , item -> GetId ( ) ) ) ) ;
 ClearEvents ( ) ;
 FinishFirstSlowDownloads ( ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d," " \"state\": {
" " \"previous\": \"in_progress\"," " \"current\": \"complete\"}
}
]" , item -> GetId ( ) ) ) ) ;
 }