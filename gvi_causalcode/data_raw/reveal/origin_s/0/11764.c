IN_PROC_BROWSER_TEST_F ( DownloadExtensionTest , MAYBE_DownloadExtensionTest_AcceptDanger ) {
 LoadExtension ( "downloads_split" ) ;
 std : : unique_ptr < base : : Value > result ( RunFunctionAndReturnResult ( new DownloadsDownloadFunction ( ) , "[{
\"url\": \"data:,\", \"filename\": \"dangerous.swf\"}
]" ) ) ;
 ASSERT_TRUE ( result . get ( ) ) ;
 int result_id = - 1 ;
 ASSERT_TRUE ( result -> GetAsInteger ( & result_id ) ) ;
 DownloadItem * item = GetCurrentManager ( ) -> GetDownload ( result_id ) ;
 ASSERT_TRUE ( item ) ;
 ASSERT_TRUE ( WaitFor ( downloads : : OnChanged : : kEventName , base : : StringPrintf ( "[{
\"id\": %d, " " \"danger\": {
" " \"previous\": \"safe\"," " \"current\": \"file\"}
}
]" , result_id ) ) ) ;
 ASSERT_TRUE ( item -> IsDangerous ( ) ) ;
 ScopedCancellingItem canceller ( item ) ;
 std : : unique_ptr < content : : DownloadTestObserver > observer ( new content : : DownloadTestObserverTerminal ( GetCurrentManager ( ) , 1 , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_IGNORE ) ) ;
 DownloadsAcceptDangerFunction : : OnPromptCreatedCallback callback = base : : Bind ( & OnDangerPromptCreated ) ;
 DownloadsAcceptDangerFunction : : OnPromptCreatedForTesting ( & callback ) ;
 BrowserActionTestUtil : : Create ( browser ( ) ) -> Press ( 0 ) ;
 observer -> WaitForFinished ( ) ;
 }