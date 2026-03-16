IN_PROC_BROWSER_TEST_F ( BookmarkBubbleSignInDelegateTest , OnSignInLinkClickedReusesBlank ) {
 int starting_tab_count = browser ( ) -> tab_strip_model ( ) -> count ( ) ;
 scoped_ptr < BookmarkBubbleDelegate > delegate ;
 delegate . reset ( new BookmarkBubbleSignInDelegate ( browser ( ) ) ) ;
 delegate -> OnSignInLinkClicked ( ) ;
 EXPECT_EQ ( starting_tab_count , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 }