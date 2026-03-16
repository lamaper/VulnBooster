TEST_F ( ProfileInfoCacheTest , MigrateLegacyProfileNamesWithNewAvatarMenu ) {
 switches : : EnableNewAvatarMenuForTesting ( base : : CommandLine : : ForCurrentProcess ( ) ) ;
 EXPECT_EQ ( 0U , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 base : : FilePath path_1 = GetProfilePath ( "path_1" ) ;
 GetCache ( ) -> AddProfileToCache ( path_1 , ASCIIToUTF16 ( "Default Profile" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 base : : FilePath path_2 = GetProfilePath ( "path_2" ) ;
 GetCache ( ) -> AddProfileToCache ( path_2 , ASCIIToUTF16 ( "First user" ) , base : : string16 ( ) , 1 , std : : string ( ) ) ;
 base : : string16 name_3 = ASCIIToUTF16 ( "Lemonade" ) ;
 base : : FilePath path_3 = GetProfilePath ( "path_3" ) ;
 GetCache ( ) -> AddProfileToCache ( path_3 , name_3 , base : : string16 ( ) , 2 , std : : string ( ) ) ;
 base : : string16 name_4 = ASCIIToUTF16 ( "Batman" ) ;
 base : : FilePath path_4 = GetProfilePath ( "path_4" ) ;
 GetCache ( ) -> AddProfileToCache ( path_4 , name_4 , base : : string16 ( ) , 3 , std : : string ( ) ) ;
 base : : string16 name_5 = ASCIIToUTF16 ( "Person 2" ) ;
 base : : FilePath path_5 = GetProfilePath ( "path_5" ) ;
 GetCache ( ) -> AddProfileToCache ( path_5 , name_5 , base : : string16 ( ) , 2 , std : : string ( ) ) ;
 EXPECT_EQ ( 5U , GetCache ( ) -> GetNumberOfProfiles ( ) ) ;
 ResetCache ( ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Person 1" ) , GetCache ( ) -> GetNameOfProfileAtIndex ( GetCache ( ) -> GetIndexOfProfileWithPath ( path_1 ) ) ) ;
 EXPECT_EQ ( ASCIIToUTF16 ( "Person 3" ) , GetCache ( ) -> GetNameOfProfileAtIndex ( GetCache ( ) -> GetIndexOfProfileWithPath ( path_2 ) ) ) ;
 EXPECT_EQ ( name_3 , GetCache ( ) -> GetNameOfProfileAtIndex ( GetCache ( ) -> GetIndexOfProfileWithPath ( path_3 ) ) ) ;
 EXPECT_EQ ( name_4 , GetCache ( ) -> GetNameOfProfileAtIndex ( GetCache ( ) -> GetIndexOfProfileWithPath ( path_4 ) ) ) ;
 EXPECT_EQ ( name_5 , GetCache ( ) -> GetNameOfProfileAtIndex ( GetCache ( ) -> GetIndexOfProfileWithPath ( path_5 ) ) ) ;
 }