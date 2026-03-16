static void find_ns ( struct ieee80211_radiotap_iterator * iterator , guint32 oui , guint8 subns ) {
 int i ;
 iterator -> current_namespace = NULL ;
 if ( ! iterator -> _vns ) return ;
 for ( i = 0 ;
 i < iterator -> _vns -> n_ns ;
 i ++ ) {
 if ( iterator -> _vns -> ns [ i ] . oui != oui ) continue ;
 if ( iterator -> _vns -> ns [ i ] . subns != subns ) continue ;
 iterator -> current_namespace = & iterator -> _vns -> ns [ i ] ;
 break ;
 }
 }