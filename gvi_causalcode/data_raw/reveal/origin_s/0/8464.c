TEST_F ( ShortcutsProviderTest , DeleteMatch ) {
 TestShortcutData shortcuts_to_test_delete [ ] = {
 {
 "BD85DBA2-8C29-49F9-84AE-48E1E90881F1" , "delete" , "www.deletetest.com/1" , "http://www.deletetest.com/1" , "http://www.deletetest.com/1" , "0,2" , "Erase this shortcut!" , "0,0" , ui : : PAGE_TRANSITION_TYPED , AutocompleteMatchType : : HISTORY_URL , "" , 1 , 1 }
 , {
 "BD85DBA2-8C29-49F9-84AE-48E1E90881F2" , "erase" , "www.deletetest.com/1" , "http://www.deletetest.com/1" , "http://www.deletetest.com/1" , "0,2" , "Erase this shortcut!" , "0,0" , ui : : PAGE_TRANSITION_TYPED , AutocompleteMatchType : : HISTORY_TITLE , "" , 1 , 1 }
 , {
 "BD85DBA2-8C29-49F9-84AE-48E1E90881F3" , "keep" , "www.deletetest.com/1/2" , "http://www.deletetest.com/1/2" , "http://www.deletetest.com/1/2" , "0,2" , "Keep this shortcut!" , "0,0" , ui : : PAGE_TRANSITION_TYPED , AutocompleteMatchType : : HISTORY_TITLE , "" , 1 , 1 }
 , {
 "BD85DBA2-8C29-49F9-84AE-48E1E90881F4" , "delete" , "www.deletetest.com/2" , "http://www.deletetest.com/2" , "http://www.deletetest.com/2" , "0,2" , "Erase this shortcut!" , "0,0" , ui : : PAGE_TRANSITION_TYPED , AutocompleteMatchType : : HISTORY_URL , "" , 1 , 1 }
 , }
 ;
 scoped_refptr < ShortcutsBackend > backend = client_ -> GetShortcutsBackend ( ) ;
 size_t original_shortcuts_count = backend -> shortcuts_map ( ) . size ( ) ;
 PopulateShortcutsBackendWithTestData ( backend , shortcuts_to_test_delete , arraysize ( shortcuts_to_test_delete ) ) ;
 EXPECT_EQ ( original_shortcuts_count + 4 , backend -> shortcuts_map ( ) . size ( ) ) ;
 EXPECT_FALSE ( backend -> shortcuts_map ( ) . end ( ) == backend -> shortcuts_map ( ) . find ( ASCIIToUTF16 ( "delete" ) ) ) ;
 EXPECT_FALSE ( backend -> shortcuts_map ( ) . end ( ) == backend -> shortcuts_map ( ) . find ( ASCIIToUTF16 ( "erase" ) ) ) ;
 AutocompleteMatch match ( provider_ . get ( ) , 1200 , true , AutocompleteMatchType : : HISTORY_TITLE ) ;
 match . destination_url = GURL ( shortcuts_to_test_delete [ 0 ] . destination_url ) ;
 match . contents = ASCIIToUTF16 ( shortcuts_to_test_delete [ 0 ] . contents ) ;
 match . description = ASCIIToUTF16 ( shortcuts_to_test_delete [ 0 ] . description ) ;
 provider_ -> DeleteMatch ( match ) ;
 EXPECT_EQ ( original_shortcuts_count + 2 , backend -> shortcuts_map ( ) . size ( ) ) ;
 EXPECT_FALSE ( backend -> shortcuts_map ( ) . end ( ) == backend -> shortcuts_map ( ) . find ( ASCIIToUTF16 ( "delete" ) ) ) ;
 EXPECT_TRUE ( backend -> shortcuts_map ( ) . end ( ) == backend -> shortcuts_map ( ) . find ( ASCIIToUTF16 ( "erase" ) ) ) ;
 match . destination_url = GURL ( shortcuts_to_test_delete [ 3 ] . destination_url ) ;
 match . contents = ASCIIToUTF16 ( shortcuts_to_test_delete [ 3 ] . contents ) ;
 match . description = ASCIIToUTF16 ( shortcuts_to_test_delete [ 3 ] . description ) ;
 provider_ -> DeleteMatch ( match ) ;
 EXPECT_EQ ( original_shortcuts_count + 1 , backend -> shortcuts_map ( ) . size ( ) ) ;
 EXPECT_TRUE ( backend -> shortcuts_map ( ) . end ( ) == backend -> shortcuts_map ( ) . find ( ASCIIToUTF16 ( "delete" ) ) ) ;
 }