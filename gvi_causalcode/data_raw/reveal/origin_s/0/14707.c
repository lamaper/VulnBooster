static void openpic_init ( Object * obj ) {
 OpenPICState * opp = OPENPIC ( obj ) ;
 memory_region_init ( & opp -> mem , obj , "openpic" , 0x40000 ) ;
 }