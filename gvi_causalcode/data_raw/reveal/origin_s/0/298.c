TEST_F ( ProfileInfoCacheTest , CreateSupervisedTestingProfile ) {
 testing_profile_manager_ . CreateTestingProfile ( "default" ) ;
 base : : string16 supervised_user_name = ASCIIToUTF16 ( "Supervised User" ) ;
 testing_profile_manager_ . CreateTestingProfile ( "test1" , scoped_ptr < PrefServiceSyncable > ( ) , supervised_user_name , 0 , "TEST_ID" , TestingProfile : : TestingFactories ( ) ) ;
 for ( size_t i = 0 ;
 i < GetCache ( ) -> GetNumberOfProfiles ( ) ;
 i ++ ) {
 bool is_supervised = GetCache ( ) -> GetNameOfProfileAtIndex ( i ) == supervised_user_name ;
 EXPECT_EQ ( is_supervised , GetCache ( ) -> ProfileIsSupervisedAtIndex ( i ) ) ;
 std : : string supervised_user_id = is_supervised ? "TEST_ID" : "" ;
 EXPECT_EQ ( supervised_user_id , GetCache ( ) -> GetSupervisedUserIdOfProfileAtIndex ( i ) ) ;
 }
 TestingBrowserProcess : : GetGlobal ( ) -> SetProfileManager ( NULL ) ;
 }