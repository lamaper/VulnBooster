TEST_F ( ProfileInfoCacheTest , Sort ) {
 base : : string16 name_a = ASCIIToUTF16 ( "apple" ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_a" ) , name_a , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 base : : string16 name_c = ASCIIToUTF16 ( "cat" ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_c" ) , name_c , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( name_a , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 EXPECT_EQ ( name_c , GetCache ( ) -> GetNameOfProfileAtIndex ( 1 ) ) ;
 base : : string16 name_b = ASCIIToUTF16 ( "Banana" ) ;
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_b" ) , name_b , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( name_a , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 EXPECT_EQ ( name_b , GetCache ( ) -> GetNameOfProfileAtIndex ( 1 ) ) ;
 EXPECT_EQ ( name_c , GetCache ( ) -> GetNameOfProfileAtIndex ( 2 ) ) ;
 name_a = UTF8ToUTF16 ( "dog" ) ;
 GetCache ( ) -> SetNameOfProfileAtIndex ( 0 , name_a ) ;
 EXPECT_EQ ( name_b , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 EXPECT_EQ ( name_c , GetCache ( ) -> GetNameOfProfileAtIndex ( 1 ) ) ;
 EXPECT_EQ ( name_a , GetCache ( ) -> GetNameOfProfileAtIndex ( 2 ) ) ;
 GetCache ( ) -> DeleteProfileFromCache ( GetProfilePath ( "path_c" ) ) ;
 EXPECT_EQ ( name_b , GetCache ( ) -> GetNameOfProfileAtIndex ( 0 ) ) ;
 EXPECT_EQ ( name_a , GetCache ( ) -> GetNameOfProfileAtIndex ( 1 ) ) ;
 }