TEST_F ( ScoredHistoryMatchTest , GetFinalRelevancyScore ) {
 std : : vector < ScoredHistoryMatch : : ScoreMaxRelevance > hqp_buckets ;
 hqp_buckets . push_back ( std : : make_pair ( 0.0 , 100 ) ) ;
 hqp_buckets . push_back ( std : : make_pair ( 1.0 , 200 ) ) ;
 hqp_buckets . push_back ( std : : make_pair ( 4.0 , 500 ) ) ;
 hqp_buckets . push_back ( std : : make_pair ( 8.0 , 900 ) ) ;
 hqp_buckets . push_back ( std : : make_pair ( 10.0 , 1000 ) ) ;
 float topicality_score = 0.0 ;
 float frequency_score = 10.0 ;
 EXPECT_EQ ( 0 , ScoredHistoryMatch : : GetFinalRelevancyScore ( topicality_score , frequency_score , hqp_buckets ) ) ;
 topicality_score = 0.4f ;
 frequency_score = 10.0f ;
 EXPECT_EQ ( 500 , ScoredHistoryMatch : : GetFinalRelevancyScore ( topicality_score , frequency_score , hqp_buckets ) ) ;
 topicality_score = 0.5f ;
 frequency_score = 10.0f ;
 EXPECT_EQ ( 600 , ScoredHistoryMatch : : GetFinalRelevancyScore ( topicality_score , frequency_score , hqp_buckets ) ) ;
 topicality_score = 0.5f ;
 frequency_score = 22.0f ;
 EXPECT_EQ ( 1000 , ScoredHistoryMatch : : GetFinalRelevancyScore ( topicality_score , frequency_score , hqp_buckets ) ) ;
 }