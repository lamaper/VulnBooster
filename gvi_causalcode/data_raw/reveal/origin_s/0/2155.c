static void AddMacName ( NamTab * nt , struct macname * mn , int strid ) {
 NameEntry * ne ;
 if ( nt -> cur + 1 >= nt -> max ) {
 if ( nt -> cur == 0 ) nt -> entries = malloc ( ( nt -> max = 100 ) * sizeof ( NameEntry ) ) ;
 else nt -> entries = realloc ( nt -> entries , ( nt -> max += 100 ) * sizeof ( NameEntry ) ) ;
 }
 ne = nt -> entries + nt -> cur ;
 ne -> platform = 1 ;
 ne -> specific = mn -> enc ;
 ne -> lang = mn -> lang ;
 ne -> strid = strid ;
 ne -> offset = ftell ( nt -> strings ) ;
 ne -> len = strlen ( mn -> name ) ;
 dumpstr ( nt -> strings , mn -> name ) ;
 ++ nt -> cur ;
 }