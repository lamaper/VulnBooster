static void pvfc_fmt_release_num ( gchar * result , guint32 release_nr ) {
 g_snprintf ( result , ITEM_LABEL_LENGTH , "%d (%d.%d.%d)" , release_nr , release_nr / 10000 , ( release_nr % 10000 ) / 100 , ( release_nr % 10000 ) % 100 ) ;
 }