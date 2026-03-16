void sun4m_irq_info ( Monitor * mon , const QDict * qdict ) {
 if ( slavio_intctl ) slavio_irq_info ( mon , slavio_intctl ) ;
 }