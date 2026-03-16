TEST_F ( ProfileInfoCacheTest , BackgroundModeStatus ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_2" ) , ASCIIToUTF16 ( "name_2" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 0 ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 1 ) ) ;
 GetCache ( ) -> SetBackgroundStatusOfProfileAtIndex ( 1 , true ) ;
 EXPECT_FALSE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 0 ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 1 ) ) ;
 GetCache ( ) -> SetBackgroundStatusOfProfileAtIndex ( 0 , true ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 0 ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 1 ) ) ;
 GetCache ( ) -> SetBackgroundStatusOfProfileAtIndex ( 1 , false ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 0 ) ) ;
 EXPECT_FALSE ( GetCache ( ) -> GetBackgroundStatusOfProfileAtIndex ( 1 ) ) ;
 }