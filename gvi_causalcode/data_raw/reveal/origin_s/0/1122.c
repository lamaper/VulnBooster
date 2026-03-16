TEST_F ( ProfileInfoCacheTest , EmptyGAIAInfo ) {
 base : : string16 profile_name = ASCIIToUTF16 ( "name_1" ) ;
 int id = profiles : : GetDefaultAvatarIconResourceIDAtIndex ( 0 ) ;
 const gfx : : Image & profile_image ( ResourceBundle : : GetSharedInstance ( ) . GetImageNamed ( id ) ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , profile_name , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 GetCache ( ) -> SetGAIANameOfProfileAtIndex ( 0 , base : : string16 ( ) ) ;
 GetCache ( ) -> SetGAIAPictureOfProfileAtIndex ( 0 , NULL ) ;
 GetCache ( ) -> SetIsUsingGAIAPictureOfProfileAtIndex ( 0 , true ) ;
 EXPECT_EQ ( profile_name , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 EXPECT_TRUE ( gfx : : test : : IsEqual ( profile_image , GetCache ( ) -> GetAvatarIconOfProfileAtIndex ( 0 ) ) ) ;
 }