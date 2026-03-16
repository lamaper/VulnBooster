static void init_ppc_proc (CPUPPCState *env, ppc_def_t *def)

{

    env->reserve = -1;

     

    env->nb_BATs = -1;

    env->nb_tlb = 0;

    env->nb_ways = 0;

     

    spr_register(env, SPR_PVR, "PVR",

                 SPR_NOACCESS, SPR_NOACCESS,

                 &spr_read_generic, SPR_NOACCESS,

                 def->pvr);

    printf("%s: PVR %08x mask %08x => %08x\n", __func__,

           def->pvr, def->pvr_mask, def->pvr & def->pvr_mask);

    switch (def->pvr) {

     

    case CPU_PPC_401A1:    

    case CPU_PPC_401B2:    

    case CPU_PPC_401C2:    

    case CPU_PPC_401D2:    

    case CPU_PPC_401E2:    

    case CPU_PPC_401F2:    

    case CPU_PPC_401G2:    

    case CPU_PPC_IOP480:   

    case CPU_PPC_COBRA:    

        gen_spr_generic(env);

        gen_spr_40x(env);

        gen_spr_401_403(env);


         

        gen_spr_compress(env);


        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        break;



    case CPU_PPC_403GA:    

    case CPU_PPC_403GB:    

    case CPU_PPC_403GC:    

    case CPU_PPC_403GCX:   

        gen_spr_generic(env);

        gen_spr_40x(env);

        gen_spr_401_403(env);

        gen_spr_403(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        break;



    case CPU_PPC_405CR:    

    case CPU_PPC_405EP:    

    case CPU_PPC_405GPR:   

    case CPU_PPC_405D2:    

    case CPU_PPC_405D4:    

        gen_spr_generic(env);

         

        gen_tbl(env);

        gen_spr_40x(env);

        gen_spr_405(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        ppc405_irq_init(env);

        break;



    case CPU_PPC_NPE405H:  

    case CPU_PPC_NPE405H2:

    case CPU_PPC_NPE405L:  

        gen_spr_generic(env);

         

        gen_tbl(env);

        gen_spr_40x(env);

        gen_spr_405(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        ppc405_irq_init(env);

        break;


    case CPU_PPC_STB01000:



    case CPU_PPC_STB01010:



    case CPU_PPC_STB0210:


    case CPU_PPC_STB03:    


    case CPU_PPC_STB043:   



    case CPU_PPC_STB045:   


    case CPU_PPC_STB25:    


    case CPU_PPC_STB130:   


        gen_spr_generic(env);

         

        gen_tbl(env);

        gen_spr_40x(env);

        gen_spr_405(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        ppc405_irq_init(env);

        break;



    case CPU_PPC_440EP:    

    case CPU_PPC_440GP:    

    case CPU_PPC_440GX:    

    case CPU_PPC_440GXc:   

    case CPU_PPC_440GXf:   

    case CPU_PPC_440SP:    

    case CPU_PPC_440SP2:

    case CPU_PPC_440SPE:   

        gen_spr_generic(env);

         

        gen_tbl(env);

        gen_spr_BookE(env);

        gen_spr_440(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        break;


    case CPU_PPC_5xx:

        break;



    case CPU_PPC_8xx:      

        break;



    case CPU_PPC_82xx_HIP3:     

    case CPU_PPC_82xx_HIP4:     

        break;



    case CPU_PPC_827x:     

        break;




     

    case CPU_PPC_e500v110:

    case CPU_PPC_e500v120:

    case CPU_PPC_e500v210:

    case CPU_PPC_e500v220:

        gen_spr_generic(env);

         

        gen_tbl(env);

        gen_spr_BookE(env);

        gen_spr_BookE_FSL(env);

        env->nb_BATs = 0;

        env->nb_tlb = 64;

        env->nb_ways = 1;

        env->id_tlbs = 0;

         

        break;


    case CPU_PPC_e600:

        break;




     

    case CPU_PPC_601:      

        gen_spr_generic(env);

        gen_spr_ne_601(env);

        gen_spr_601(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_601_HID2, "HID2",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_601_HID5, "HID5",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);


        spr_register(env, SPR_601_HID15, "HID15",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);


        env->nb_tlb = 64;

        env->nb_ways = 2;

        env->id_tlbs = 0;

        env->id_tlbs = 0;

         

        break;



    case CPU_PPC_602:      

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

        gen_6xx_7xx_soft_tlb(env, 64, 2);

        gen_spr_602(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_603:      

    case CPU_PPC_603E:     

    case CPU_PPC_603E7v:

    case CPU_PPC_603E7v2:

    case CPU_PPC_603P:     

    case CPU_PPC_603R:     

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

        gen_6xx_7xx_soft_tlb(env, 64, 2);

        gen_spr_603(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_G2:       

    case CPU_PPC_G2H4:

    case CPU_PPC_G2gp:

    case CPU_PPC_G2ls:

    case CPU_PPC_G2LE:     

    case CPU_PPC_G2LEgp:

    case CPU_PPC_G2LEls:

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

         

        gen_high_BATs(env);

        gen_6xx_7xx_soft_tlb(env, 64, 2);

        gen_spr_G2_755(env);

        gen_spr_G2(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID2, "HID2",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_604:      

    case CPU_PPC_604E:     

    case CPU_PPC_604R:     

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

        gen_spr_604(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_74x:      

    case CPU_PPC_740E:

    case CPU_PPC_750E:

    case CPU_PPC_74xP:     

    case CPU_PPC_750CXE21:  

    case CPU_PPC_750CXE22:

    case CPU_PPC_750CXE23:

    case CPU_PPC_750CXE24:

    case CPU_PPC_750CXE24b:

    case CPU_PPC_750CXE31:

    case CPU_PPC_750CXE31b:

    case CPU_PPC_750CXR:

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

        gen_spr_7xx(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_750FX10:  

    case CPU_PPC_750FX20:

    case CPU_PPC_750FX21:

    case CPU_PPC_750FX22:

    case CPU_PPC_750FX23:

    case CPU_PPC_750GX10:  

    case CPU_PPC_750GX11:

    case CPU_PPC_750GX12:

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_high_BATs(env);

         

        gen_tbl(env);

        gen_spr_7xx(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_750_HID2, "HID2",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;



    case CPU_PPC_755_10:   

    case CPU_PPC_755_11:

    case CPU_PPC_755_20:

    case CPU_PPC_755D:

    case CPU_PPC_755E:

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

         

        gen_high_BATs(env);

        gen_6xx_7xx_soft_tlb(env, 64, 2);

        gen_spr_G2_755(env);

         

         

        spr_register(env, SPR_ICTC, "ICTC",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_L2PM, "L2PM",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID2, "HID2",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc6xx_irq_init(env);

        break;


     

    case CPU_PPC_7400:     

    case CPU_PPC_7410C:    

    case CPU_PPC_7410D:

    case CPU_PPC_7410E:

    case CPU_PPC_7441:     

    case CPU_PPC_7445:     

    case CPU_PPC_7447:     

    case CPU_PPC_7447A:    

    case CPU_PPC_7448:     

    case CPU_PPC_7450:     

    case CPU_PPC_7450b:

    case CPU_PPC_7451:     

    case CPU_PPC_7451G:

    case CPU_PPC_7455:     

    case CPU_PPC_7455F:

    case CPU_PPC_7455G:

    case CPU_PPC_7457:     

    case CPU_PPC_7457C:

    case CPU_PPC_7457A:    

        break;




    case CPU_PPC_620:      

    case CPU_PPC_630:      

    case CPU_PPC_631:      

    case CPU_PPC_POWER4:   

    case CPU_PPC_POWER4P:  

    case CPU_PPC_POWER5:   

    case CPU_PPC_POWER5P:  


        break;



    case CPU_PPC_970:      

    case CPU_PPC_970FX10:  

    case CPU_PPC_970FX20:

    case CPU_PPC_970FX21:

    case CPU_PPC_970FX30:

    case CPU_PPC_970FX31:

    case CPU_PPC_970MP10:  

    case CPU_PPC_970MP11:

        gen_spr_generic(env);

        gen_spr_ne_601(env);

         

        gen_low_BATs(env);

         

        gen_tbl(env);

        gen_spr_7xx(env);

         

         

        spr_register(env, SPR_HID0, "HID0",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_HID1, "HID1",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        spr_register(env, SPR_750_HID2, "HID2",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     0x00000000);

         

        ppc970_irq_init(env);

        break;


    case CPU_PPC_CELL10:   

    case CPU_PPC_CELL20:

    case CPU_PPC_CELL30:

    case CPU_PPC_CELL31:


        break;


    case CPU_PPC_RS64:     

    case CPU_PPC_RS64II:   

    case CPU_PPC_RS64III:  

    case CPU_PPC_RS64IV:   


        break;



         

    case CPU_POWER:        

    case CPU_POWER2:       

        break;




    default:

        gen_spr_generic(env);

         

        break;

    }

    if (env->nb_BATs == -1)

        env->nb_BATs = 4;

     

    if (env->nb_tlb != 0) {

        int nb_tlb = env->nb_tlb;

        if (env->id_tlbs != 0)

            nb_tlb *= 2;

        env->tlb = qemu_mallocz(nb_tlb * sizeof(ppc_tlb_t));

         

        env->tlb_per_way = env->nb_tlb / env->nb_ways;

    }

}
