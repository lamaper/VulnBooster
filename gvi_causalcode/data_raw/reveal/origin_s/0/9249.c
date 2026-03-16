TEST_F ( ProfileInfoCacheTest , ProfileActiveTime ) {
 GetCache ( ) -> AddProfileToCache ( GetProfilePath ( "path_1" ) , ASCIIToUTF16 ( "name_1" ) , base : : string16 ( ) , 0 , std : : string ( ) ) ;
 EXPECT_EQ ( base : : Time ( ) , GetCache ( ) -> GetProfileActiveTimeAtIndex ( 0 ) ) ;
 base : : Time before = base : : Time : : Now ( ) ;
 before -= base : : TimeDelta : : FromSeconds ( 1 ) ;
 GetCache ( ) -> SetProfileActiveTimeAtIndex ( 0 ) ;
 base : : Time after = base : : Time : : Now ( ) ;
 after += base : : TimeDelta : : FromSeconds ( 1 ) ;
 EXPECT_LE ( before , GetCache ( ) -> GetProfileActiveTimeAtIndex ( 0 ) ) ;
 EXPECT_GE ( after , GetCache ( ) -> GetProfileActiveTimeAtIndex ( 0 ) ) ;
 }