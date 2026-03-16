TEST_F ( PromoResourceServiceTest , NotificationPromoTest ) {
 NotificationPromoTest promo_test ;
 promo_test . Init ( "{
" " \"ntp_notification_promo\": [" " {
" " \"date\":" " [" " {
" " \"start\":\"3 Aug 1999 9:26:06 GMT\"," " \"end\":\"$1\"" " }
" " ]," " \"strings\":" " {
" " \"NTP4_HOW_DO_YOU_FEEL_ABOUT_CHROME\":" " \"What do you think of Chrome?\"" " }
," " \"grouping\":" " {
" " \"buckets\":1000," " \"segment\":200," " \"increment\":100," " \"increment_frequency\":3600," " \"increment_max\":400" " }
," " \"payload\":" " {
" " \"days_active\":7," " \"install_age_days\":21" " }
," " \"max_views\":30" " }
" " ]" "}
" , "What do you think of Chrome?" , 933672366 , 1000 , 200 , 100 , 3600 , 400 , 30 ) ;
 promo_test . InitPromoFromJson ( true ) ;
 promo_test . InitPromoFromJson ( false ) ;
 promo_test . TestInitFromPrefs ( ) ;
 promo_test . TestGroup ( ) ;
 promo_test . TestViews ( ) ;
 promo_test . TestClosed ( ) ;
 promo_test . TestPromoText ( ) ;
 promo_test . TestTime ( ) ;
 promo_test . TestIncrement ( ) ;
 }