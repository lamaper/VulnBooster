IN_PROC_BROWSER_TEST_F ( BookmarkBubbleSignInDelegateTest , OnSignInLinkClicked ) {
 ReplaceBlank ( browser ( ) ) ;
 int starting_tab_count = browser ( ) -> tab_strip_model ( ) -> count ( ) ;
 scoped_ptr < BookmarkBubbleDelegate > delegate ;
 delegate . reset ( new BookmarkBubbleSignInDelegate ( browser ( ) ) ) ;
 delegate -> OnSignInLinkClicked ( ) ;
 if ( kHasProfileChooser ) {
 EXPECT_TRUE ( ProfileChooserView : : IsShowing ( ) ) ;
 EXPECT_EQ ( starting_tab_count , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 }
 else {
 EXPECT_EQ ( starting_tab_count + 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 }
 }