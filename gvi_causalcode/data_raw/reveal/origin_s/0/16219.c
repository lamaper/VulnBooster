TEST_F ( ProfileInfoCacheTest , SetSupervisedUserId ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "test" ) , ASCIIToUTF16 ( "Test" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> ProfileIsSupervisedAtIndex ( 0 ) ) ;
 GetCache ( ) -> SetSupervisedUserIdOfProfileAtIndex ( 0 , "TEST_ID" ) ;
 EXPECT_TRUE ( GetCache ( ) -> ProfileIsSupervisedAtIndex ( 0 ) ) ;
 EXPECT_EQ ( "TEST_ID" , GetCache ( ) -> GetSupervisedUserIdOfProfileAtIndex ( 0 ) ) ;
 ResetCache ( ) ;
 EXPECT_TRUE ( GetCache ( ) -> ProfileIsSupervisedAtIndex ( 0 ) ) ;
 GetCache ( ) -> SetSupervisedUserIdOfProfileAtIndex ( 0 , std : : string ( ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> ProfileIsSupervisedAtIndex ( 0 ) ) ;
 EXPECT_EQ ( "" , GetCache ( ) -> GetSupervisedUserIdOfProfileAtIndex ( 0 ) ) ;
 }