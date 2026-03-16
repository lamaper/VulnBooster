IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestSessionRestoreShowBookmarkBar ) {
 EXPECT_FALSE ( browser ( ) -> profile ( ) -> GetPrefs ( ) -> GetBoolean ( bookmarks : : prefs : : kShowBookmarkBar ) ) ;
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetBoolean ( bookmarks : : prefs : : kShowBookmarkBar , true ) ;
 EXPECT_TRUE ( browser ( ) -> profile ( ) -> GetPrefs ( ) -> GetBoolean ( bookmarks : : prefs : : kShowBookmarkBar ) ) ;
 EXPECT_TRUE ( browser ( ) -> profile ( ) -> GetPrefs ( ) -> GetBoolean ( bookmarks : : prefs : : kShowBookmarkBar ) ) ;
 EXPECT_EQ ( BookmarkBar : : SHOW , browser ( ) -> bookmark_bar_state ( ) ) ;
 }