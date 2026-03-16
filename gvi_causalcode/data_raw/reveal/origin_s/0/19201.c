TEST_F ( UsbBlocklistTest , StaticEntries ) {
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0010 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0018 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0030 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0110 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0111 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0112 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0113 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0114 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0115 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0116 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0120 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0200 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0211 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0401 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0402 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0403 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0404 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0405 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0406 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0407 , 0x0100 }
 ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x1050 , 0x0410 , 0x0100 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x104F , 0x0200 , 0x0100 }
 ) ) ;
 EXPECT_FALSE ( list ( ) . IsExcluded ( {
 0x1051 , 0x0200 , 0x0100 }
 ) ) ;
 }