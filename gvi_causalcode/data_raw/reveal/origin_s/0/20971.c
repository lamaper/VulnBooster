TEST_F ( ProfileInfoCacheTest , PersistGAIAPicture ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 gfx : : Image gaia_image ( gfx : : test : : CreateImage ( ) ) ;
 GetCache ( ) -> SetGAIAPictureOfProfileAtIndex ( 0 , & gaia_image ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 EXPECT_TRUE ( gfx : : test : : IsEqual ( gaia_image , * GetCache ( ) -> GetGAIAPictureOfProfileAtIndex ( 0 ) ) ) ;
 ResetCache ( ) ;
 EXPECT_EQ ( NULL , GetCache ( ) -> GetGAIAPictureOfProfileAtIndex ( 0 ) ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 EXPECT_TRUE ( gfx : : test : : IsEqual ( gaia_image , * GetCache ( ) -> GetGAIAPictureOfProfileAtIndex ( 0 ) ) ) ;
 }