TEST_F ( ProfileInfoCacheTest , MutateProfile ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_2" ) , ASCIIToUTF16 ( "name_2" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 base : : string16 new_name = ASCIIToUTF16 ( "new_name" ) ;
 GetCache ( ) -> SetNameOfProfileAtIndex ( 1 , new_name ) ;
 EXPECT_EQ ( new_name , GetCache ( ) -> GetNameOfProfileAtIndex ( 1 ) ) ;
 EXPECT_NE ( new_name , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 base : : string16 new_user_name = ASCIIToUTF16 ( "user_name" ) ;
 GetCache ( ) -> SetUserNameOfProfileAtIndex ( 1 , new_user_name ) ;
 EXPECT_EQ ( new_user_name , GetCache ( ) -> GetUserNameOfProfileAtIndex ( 1 ) ) ;
 EXPECT_NE ( new_user_name , GetCache ( ) -> GetUserNameOfProfileAtIndex ( 0 ) ) ;
 size_t new_icon_index = 3 ;
 GetCache ( ) -> SetAvatarIconOfProfileAtIndex ( 1 , new_icon_index ) ;
 GetCache ( ) -> GetAvatarIconOfProfileAtIndex ( 1 ) ;
 }