TEST_F ( ProfileInfoCacheTest , DeleteProfile ) {
 EXPECT_EQ ( 0u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 base : : FilePath path_1 = GetProfilePath ( "path_1" ) ;
 GetCache ( ) -> AddProfileToCache ( path_1 , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( 1u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 base : : FilePath path_2 = GetProfilePath ( "path_2" ) ;
 base : : string16 name_2 = ASCIIToUTF16 ( "name_2" ) ;
 GetCache ( ) -> AddProfileToCache ( path_2 , name_2 , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( 2u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 GetCache ( ) -> DeleteProfileFromCache ( path_1 ) ;
 EXPECT_EQ ( 1u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 EXPECT_EQ ( name_2 , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 GetCache ( ) -> DeleteProfileFromCache ( path_2 ) ;
 EXPECT_EQ ( 0u , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 }