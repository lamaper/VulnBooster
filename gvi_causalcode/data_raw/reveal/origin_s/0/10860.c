IN_PROC_BROWSER_TEST_F ( BookmarkBubbleSignInDelegateTest , OnSignInLinkClickedIncognito ) {
 ReplaceBlank ( browser ( ) ) ;
 Browser * incognito_browser = CreateIncognitoBrowser ( ) ;
 int starting_tab_count_normal = browser ( ) -> tab_strip_model ( ) -> count ( ) ;
 int starting_tab_count_incognito = incognito_browser -> tab_strip_model ( ) -> count ( ) ;
 scoped_ptr < BookmarkBubbleDelegate > delegate ;
 delegate . reset ( new BookmarkBubbleSignInDelegate ( incognito_browser ) ) ;
 delegate -> OnSignInLinkClicked ( ) ;
 if ( kHasProfileChooser ) {
 EXPECT_FALSE ( ProfileChooserView : : IsShowing ( ) ) ;
 }
 else {
 int tab_count_normal = browser ( ) -> tab_strip_model ( ) -> count ( ) ;
 EXPECT_EQ ( starting_tab_count_normal + 1 , tab_count_normal ) ;
 }
 int tab_count_incognito = incognito_browser -> tab_strip_model ( ) -> count ( ) ;
 EXPECT_EQ ( starting_tab_count_incognito , tab_count_incognito ) ;
 }