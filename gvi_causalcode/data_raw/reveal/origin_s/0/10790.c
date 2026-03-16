TEST_F ( ProfileInfoCacheTest , AddStubProfile ) {
 EXPECT_EQ ( 0u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 const struct {
 const char * profile_path ;
 const char * profile_name ;
 }
 kTestCases [ ] = {
 {
 "path.test0" , "name_0" }
 , {
 "path_test1" , "name_1" }
 , {
 "path.test2" , "name_2" }
 , {
 "path_test3" , "name_3" }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( kTestCases ) ;
 ++ i ) {
 base : : FilePath profile_path = GetProfilePath ( kTestCases [ i ] . profile_path ) ;
 base : : string16 profile_name = ASCIIToUTF16 ( kTestCases [ i ] . profile_name ) ;
 GetCache ( ) -> AddProfileToCache ( profile_path , profile_name , base : : string16 ( ) , i , "" ) ;
 EXPECT_EQ ( profile_path , GetCache ( ) -> GetPathOfProfileAtIndex ( i ) ) ;
 EXPECT_EQ ( profile_name , GetCache ( ) -> GetNameOfProfileAtIndex ( i ) ) ;
 }
 ASSERT_EQ ( 4U , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 std : : vector < base : : string16 > names ;
 PrefService * local_state = g_browser_process -> local_state ( ) ;
 const base : : DictionaryValue * cache = local_state -> GetDictionary ( prefs : : kProfileInfoCache ) ;
 base : : string16 name ;
 for ( base : : DictionaryValue : : Iterator it ( * cache ) ;
 ! it . IsAtEnd ( ) ;
 it . Advance ( ) ) {
 const base : : DictionaryValue * info = NULL ;
 it . value ( ) . GetAsDictionary ( & info ) ;
 info -> GetString ( "name" , & name ) ;
 names . push_back ( name ) ;
 }
 for ( size_t i = 0 ;
 i < 4 ;
 i ++ ) ASSERT_FALSE ( names [ i ] . empty ( ) ) ;
 }