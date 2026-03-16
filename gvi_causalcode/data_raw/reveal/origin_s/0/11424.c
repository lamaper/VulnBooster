TEST_F ( ProfileInfoCacheTest , AddProfiles ) {
 EXPECT_EQ ( 0u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 SkBitmap bitmap ;
 bitmap . allocN32Pixels ( 38 , 31 ) ;
 bitmap . eraseColor ( SK_ColorGREEN ) ;
 ui : : ResourceBundle & rb = ui : : ResourceBundle : : GetSharedInstance ( ) ;
 for ( uint32 i = 0 ;
 i < 4 ;
 ++ i ) {
 base : : FilePath profile_path = GetProfilePath ( base : : StringPrintf ( "path_%ud" , i ) ) ;
 base : : string16 profile_name = ASCIIToUTF16 ( base : : StringPrintf ( "name_%ud" , i ) ) ;
 const SkBitmap * icon = rb . GetImageNamed ( profiles : : GetDefaultAvatarIconResourceIDAtIndex ( i ) ) . ToSkBitmap ( ) ;
 std : : string supervised_user_id = i == 3 ? "TEST_ID" : "" ;
 GetCache ( ) -> AddProfileToCache ( profile_path , profile_name , base : : string16 ( ) , i , supervised_user_id ) ;
 GetCache ( ) -> SetBackgroundStatusOfProfileAtIndex ( i , true ) ;
 base : : string16 gaia_name = ASCIIToUTF16 ( base : : StringPrintf ( "gaia_%ud" , i ) ) ;
 GetCache ( ) -> SetGAIANameOfProfileAtIndex ( i , gaia_name ) ;
 EXPECT_EQ ( i + 1 , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 EXPECT_EQ ( profile_name , GetCache ( ) -> GetNameOfProfileAtIndex ( i ) ) ;
 EXPECT_EQ ( profile_path , GetCache ( ) -> GetPathOfProfileAtIndex ( i ) ) ;
 ProfileAvatarDownloader avatar_downloader ( GetCache ( ) -> GetAvatarIconIndexOfProfileAtIndex ( i ) , profile_path , GetCache ( ) ) ;
 avatar_downloader . OnFetchComplete ( GURL ( "http://www.google.com/avatar.png" ) , & bitmap ) ;
 const SkBitmap * actual_icon = GetCache ( ) -> GetAvatarIconOfProfileAtIndex ( i ) . ToSkBitmap ( ) ;
 EXPECT_EQ ( icon -> width ( ) , actual_icon -> width ( ) ) ;
 EXPECT_EQ ( icon -> height ( ) , actual_icon -> height ( ) ) ;
 EXPECT_EQ ( i == 3 , GetCache ( ) -> ProfileIsSupervisedAtIndex ( i ) ) ;
 EXPECT_EQ ( i == 3 , GetCache ( ) -> IsOmittedProfileAtIndex ( i ) ) ;
 EXPECT_EQ ( supervised_user_id , GetCache ( ) -> GetSupervisedUserIdOfProfileAtIndex ( i ) ) ;
 }
 ResetCache ( ) ;
 EXPECT_EQ ( 4u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 for ( uint32 i = 0 ;
 i < 4 ;
 ++ i ) {
 base : : FilePath profile_path = GetProfilePath ( base : : StringPrintf ( "path_%ud" , i ) ) ;
 EXPECT_EQ ( i , GetCache ( ) -> GetIndexOfProfileWithPath ( profile_path ) ) ;
 base : : string16 profile_name = ASCIIToUTF16 ( base : : StringPrintf ( "name_%ud" , i ) ) ;
 EXPECT_EQ ( profile_name , GetCache ( ) -> GetNameOfProfileAtIndex ( i ) ) ;
 EXPECT_EQ ( i , GetCache ( ) -> GetAvatarIconIndexOfProfileAtIndex ( i ) ) ;
 EXPECT_EQ ( true , GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( i ) ) ;
 base : : string16 gaia_name = ASCIIToUTF16 ( base : : StringPrintf ( "gaia_%ud" , i ) ) ;
 EXPECT_EQ ( gaia_name , GetCache ( ) -> GetGAIANameOfProfileAtIndex ( i ) ) ;
 }
 }