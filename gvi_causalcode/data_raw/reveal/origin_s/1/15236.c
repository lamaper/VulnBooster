TEST_F ( ProfileInfoCacheTest , DownloadHighResAvatarTest ) {
 switches : : EnableNewAvatarMenuForTesting ( base : : CommandLine : : ForCurrentProcess ( ) ) ;
 EXPECT_EQ ( 0U , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 base : : FilePath path_1 = GetProfilePath ( "path_1" ) ;
 GetCache ( ) -> AddProfileToCache ( path_1 , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( 1U , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 EXPECT_EQ ( 0U , GetCache ( ) -> cached_avatar_images_ . size ( ) ) ;
 EXPECT_EQ ( 1U , GetCache ( ) -> avatar_images_downloads_in_progress_ . size ( ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> GetHighResAvatarOfProfileAtIndex ( 0 ) ) ;
 const size_t kIconIndex = 0 ;
 ProfileAvatarDownloader avatar_downloader ( kIconIndex , GetCache ( ) -> GetPathOfProfileAtIndex ( 0 ) , GetCache ( ) ) ;
 SkBitmap bitmap ;
 bitmap . allocN32Pixels ( 2 , 2 ) ;
 bitmap . eraseColor ( SK_ColorGREEN ) ;
 avatar_downloader . OnFetchComplete ( GURL ( "http://www.google.com/avatar.png" ) , & bitmap ) ;
 EXPECT_EQ ( 0U , GetCache ( ) -> avatar_images_downloads_in_progress_ . size ( ) ) ;
 std : : string file_name = profiles : : GetDefaultAvatarIconFileNameAtIndex ( kIconIndex ) ;
 EXPECT_EQ ( 1U , GetCache ( ) -> cached_avatar_images_ . size ( ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetHighResAvatarOfProfileAtIndex ( 0 ) ) ;
 EXPECT_EQ ( GetCache ( ) -> cached_avatar_images_ [ file_name ] , GetCache ( ) -> GetHighResAvatarOfProfileAtIndex ( 0 ) ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 base : : FilePath icon_path = profiles : : GetPathOfHighResAvatarAtIndex ( kIconIndex ) ;
 EXPECT_NE ( std : : string : : npos , icon_path . MaybeAsASCII ( ) . find ( file_name ) ) ;
 EXPECT_TRUE ( base : : PathExists ( icon_path ) ) ;
 EXPECT_TRUE ( base : : DeleteFile ( icon_path , true ) ) ;
 EXPECT_FALSE ( base : : PathExists ( icon_path ) ) ;
 }