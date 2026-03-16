TEST ( BuildTime , InThePast ) {
 EXPECT_TRUE ( base : : GetBuildTime ( ) < base : : Time : : Now ( ) ) ;
 EXPECT_TRUE ( base : : GetBuildTime ( ) < base : : Time : : NowFromSystemTime ( ) ) ;
 }