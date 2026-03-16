TEST_F ( ShortcutsBackendTest , AddAndUpdateShortcut ) {
 InitBackend ( ) ;
 EXPECT_FALSE ( changed_notified ( ) ) ;
 ShortcutsDatabase : : Shortcut shortcut ( "BD85DBA2-8C29-49F9-84AE-48E1E90880DF" , base : : ASCIIToUTF16 ( "goog" ) , MatchCoreForTesting ( "http://www.google.com" ) , base : : Time : : Now ( ) , 100 ) ;
 EXPECT_TRUE ( AddShortcut ( shortcut ) ) ;
 EXPECT_TRUE ( changed_notified ( ) ) ;
 ShortcutsBackend : : ShortcutMap : : const_iterator shortcut_iter ( shortcuts_map ( ) . find ( shortcut . text ) ) ;
 ASSERT_TRUE ( shortcut_iter != shortcuts_map ( ) . end ( ) ) ;
 EXPECT_EQ ( shortcut . id , shortcut_iter -> second . id ) ;
 EXPECT_EQ ( shortcut . match_core . contents , shortcut_iter -> second . match_core . contents ) ;
 set_changed_notified ( false ) ;
 shortcut . match_core . contents = base : : ASCIIToUTF16 ( "Google Web Search" ) ;
 EXPECT_TRUE ( UpdateShortcut ( shortcut ) ) ;
 EXPECT_TRUE ( changed_notified ( ) ) ;
 shortcut_iter = shortcuts_map ( ) . find ( shortcut . text ) ;
 ASSERT_TRUE ( shortcut_iter != shortcuts_map ( ) . end ( ) ) ;
 EXPECT_EQ ( shortcut . id , shortcut_iter -> second . id ) ;
 EXPECT_EQ ( shortcut . match_core . contents , shortcut_iter -> second . match_core . contents ) ;
 }