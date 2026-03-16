TEST_F ( SoundContentSettingObserverTest , DontUnmuteWhenMutedForMediaCapture ) {
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 SetMuteStateForReason ( true , TabMutedReason : : MEDIA_CAPTURE ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 NavigateAndCommit ( GURL ( kURL2 ) ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 }