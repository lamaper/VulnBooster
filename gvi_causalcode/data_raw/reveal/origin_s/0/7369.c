TEST_F ( ScoredHistoryMatchTest , GetHQPBucketsFromString ) {
 std : : string buckets_str = "0.0:400,1.5:600,12.0:1300,20.0:1399" ;
 std : : vector < ScoredHistoryMatch : : ScoreMaxRelevance > hqp_buckets ;
 EXPECT_TRUE ( ScoredHistoryMatch : : GetHQPBucketsFromString ( buckets_str , & hqp_buckets ) ) ;
 EXPECT_THAT ( hqp_buckets , ElementsAre ( Pair ( 0.0 , 400 ) , Pair ( 1.5 , 600 ) , Pair ( 12.0 , 1300 ) , Pair ( 20.0 , 1399 ) ) ) ;
 buckets_str = "0.0,400,1.5,600" ;
 EXPECT_FALSE ( ScoredHistoryMatch : : GetHQPBucketsFromString ( buckets_str , & hqp_buckets ) ) ;
 }