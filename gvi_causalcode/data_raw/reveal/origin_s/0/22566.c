TEST_F ( ProfileInfoCacheTest , GAIAName ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , ASCIIToUTF16 ( "Person 1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 base : : string16 profile_name ( ASCIIToUTF16 ( "Person 2" ) ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_2" ) , profile_name , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 int index1 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_1" ) ) ;
 int index2 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_2" ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetGAIANameOfProfileAtIndex ( index1 ) . empty ( ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetGAIANameOfProfileAtIndex ( index2 ) . empty ( ) ) ;
 base : : string16 gaia_name ( ASCIIToUTF16 ( "Pat Smith" ) ) ;
 GetCache ( ) -> SetGAIANameOfProfileAtIndex ( index2 , gaia_name ) ;
 index1 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_1" ) ) ;
 index2 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_2" ) ) ;
 EXPECT_TRUE ( GetCache ( ) -> GetGAIANameOfProfileAtIndex ( index1 ) . empty ( ) ) ;
 EXPECT_EQ ( gaia_name , GetCache ( ) -> GetGAIANameOfProfileAtIndex ( index2 ) ) ;
 EXPECT_EQ ( gaia_name , GetCache ( ) -> GetNameOfProfileAtIndex ( index2 ) ) ;
 base : : string16 custom_name ( ASCIIToUTF16 ( "Custom name" ) ) ;
 GetCache ( ) -> SetNameOfProfileAtIndex ( index2 , custom_name ) ;
 GetCache ( ) -> SetProfileIsUsingDefaultNameAtIndex ( index2 , false ) ;
 index1 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_1" ) ) ;
 index2 = GetCache ( ) -> GetIndexOfProfileWithPath ( GetProfilePath ( "path_2" ) ) ;
 EXPECT_EQ ( custom_name , GetCache ( ) -> GetNameOfProfileAtIndex ( index2 ) ) ;
 EXPECT_EQ ( gaia_name , GetCache ( ) -> GetGAIANameOfProfileAtIndex ( index2 ) ) ;
 }