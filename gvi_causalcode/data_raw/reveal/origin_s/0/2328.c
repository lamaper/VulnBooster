TEST_F ( ExtensionWelcomeNotificationTest , NotificationPreviouslyExpired ) {
 StartPreferenceSyncing ( ) ;
 SetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp , true ) ;
 SetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp , 1 ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 EXPECT_EQ ( GetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp ) , 1 ) ;
 EXPECT_TRUE ( task_runner ( ) -> GetPendingTasks ( ) . empty ( ) ) ;
 const base : : TimeDelta requested_show_time = base : : TimeDelta : : FromDays ( ExtensionWelcomeNotification : : kRequestedShowTimeDays ) ;
 SetElapsedTime ( requested_show_time ) ;
 ShowChromeNowNotification ( ) ;
 EXPECT_TRUE ( task_runner ( ) -> GetPendingTasks ( ) . empty ( ) ) ;
 EXPECT_EQ ( message_center ( ) -> add_notification_calls ( ) , 0 ) ;
 EXPECT_EQ ( message_center ( ) -> remove_notification_calls ( ) , 0 ) ;
 EXPECT_EQ ( message_center ( ) -> notifications_with_shown_as_popup ( ) , 0 ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 EXPECT_EQ ( GetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp ) , 1 ) ;
 }