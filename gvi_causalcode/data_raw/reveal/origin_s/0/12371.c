TEST_F ( SoundContentSettingObserverTest , DontUnmuteWhenMutedByExtension ) {
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 SetMuteStateForReason ( true , TabMutedReason : : EXTENSION ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 NavigateAndCommit ( GURL ( kURL2 ) ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 }