IN_PROC_BROWSER_TEST_F ( BookmarkBubbleSignInDelegateTest , BrowserRemoved ) {
 Browser * extra_browser = CreateBrowser ( profile ( ) ) ;
 ReplaceBlank ( extra_browser ) ;
 int starting_tab_count = extra_browser -> tab_strip_model ( ) -> count ( ) ;
 scoped_ptr < BookmarkBubbleDelegate > delegate ;
 delegate . reset ( new BookmarkBubbleSignInDelegate ( browser ( ) ) ) ;
 BrowserList : : SetLastActive ( extra_browser ) ;
 browser ( ) -> tab_strip_model ( ) -> CloseAllTabs ( ) ;
 content : : RunAllPendingInMessageLoop ( ) ;
 delegate -> OnSignInLinkClicked ( ) ;
 int tab_count = extra_browser -> tab_strip_model ( ) -> count ( ) ;
 EXPECT_EQ ( starting_tab_count + 1 , tab_count ) ;
 }