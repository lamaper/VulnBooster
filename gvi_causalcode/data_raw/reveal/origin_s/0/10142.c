TEST_F ( ExtensionWelcomeNotificationTest , ShowWelcomeNotificationAgain ) {
 StartPreferenceSyncing ( ) ;
 SetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp , true ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 ShowChromeNowNotification ( ) ;
 EXPECT_EQ ( message_center ( ) -> add_notification_calls ( ) , 1 ) ;
 EXPECT_EQ ( message_center ( ) -> remove_notification_calls ( ) , 0 ) ;
 EXPECT_EQ ( message_center ( ) -> notifications_with_shown_as_popup ( ) , 1 ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 }