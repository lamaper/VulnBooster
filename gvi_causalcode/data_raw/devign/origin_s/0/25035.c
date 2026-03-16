static int get_phys_addr_lpae(CPUARMState *env, target_ulong address,

                              int access_type, ARMMMUIdx mmu_idx,

                              hwaddr *phys_ptr, MemTxAttrs *txattrs, int *prot,

                              target_ulong *page_size_ptr)

{

    CPUState *cs = CPU(arm_env_get_cpu(env));

     

    MMUFaultType fault_type = translation_fault;

    uint32_t level = 1;

    uint32_t epd;

    int32_t tsz;

    uint32_t tg;

    uint64_t ttbr;

    int ttbr_select;

    hwaddr descaddr, descmask;

    uint32_t tableattrs;

    target_ulong page_size;

    uint32_t attrs;

    int32_t granule_sz = 9;

    int32_t va_size = 32;

    int32_t tbi = 0;

    TCR *tcr = regime_tcr(env, mmu_idx);

    int ap, ns, xn, pxn;



     

    if (arm_el_is_aa64(env, regime_el(env, mmu_idx))) {

        va_size = 64;

        if (extract64(address, 55, 1))

            tbi = extract64(tcr->raw_tcr, 38, 1);

        else

            tbi = extract64(tcr->raw_tcr, 37, 1);

        tbi *= 8;

    }



     

    uint32_t t0sz = extract32(tcr->raw_tcr, 0, 6);

    if (va_size == 64) {

        t0sz = MIN(t0sz, 39);

        t0sz = MAX(t0sz, 16);

    }

    uint32_t t1sz = extract32(tcr->raw_tcr, 16, 6);

    if (va_size == 64) {

        t1sz = MIN(t1sz, 39);

        t1sz = MAX(t1sz, 16);

    }

    if (t0sz && !extract64(address, va_size - t0sz, t0sz - tbi)) {

         

        ttbr_select = 0;

    } else if (t1sz && !extract64(~address, va_size - t1sz, t1sz - tbi)) {

         

        ttbr_select = 1;

    } else if (!t0sz) {

         

        ttbr_select = 0;

    } else if (!t1sz) {

         

        ttbr_select = 1;

    } else {

         

        fault_type = translation_fault;

        goto do_fault;

    }



     

    if (ttbr_select == 0) {

        ttbr = regime_ttbr(env, mmu_idx, 0);

        epd = extract32(tcr->raw_tcr, 7, 1);

        tsz = t0sz;



        tg = extract32(tcr->raw_tcr, 14, 2);

        if (tg == 1) {  

            granule_sz = 13;

        }

        if (tg == 2) {  

            granule_sz = 11;

        }

    } else {

        ttbr = regime_ttbr(env, mmu_idx, 1);

        epd = extract32(tcr->raw_tcr, 23, 1);

        tsz = t1sz;



        tg = extract32(tcr->raw_tcr, 30, 2);

        if (tg == 3)  {  

            granule_sz = 13;

        }

        if (tg == 1) {  

            granule_sz = 11;

        }

    }



     



    if (epd) {

         

        goto do_fault;

    }



     

    level = 4 - (va_size - tsz - 4) / granule_sz;



     

    if (tsz) {

        address &= (1ULL << (va_size - tsz)) - 1;

    }



    descmask = (1ULL << (granule_sz + 3)) - 1;



     

    descaddr = extract64(ttbr, 0, 48);

    descaddr &= ~((1ULL << (va_size - tsz - (granule_sz * (4 - level)))) - 1);



     

    tableattrs = regime_is_secure(env, mmu_idx) ? 0 : (1 << 4);

    for (;;) {

        uint64_t descriptor;

        bool nstable;



        descaddr |= (address >> (granule_sz * (4 - level))) & descmask;

        descaddr &= ~7ULL;

        nstable = extract32(tableattrs, 4, 1);

        descriptor = arm_ldq_ptw(cs, descaddr, !nstable);

        if (!(descriptor & 1) ||

            (!(descriptor & 2) && (level == 3))) {

             

            goto do_fault;

        }

        descaddr = descriptor & 0xfffffff000ULL;



        if ((descriptor & 2) && (level < 3)) {

             

            tableattrs |= extract64(descriptor, 59, 5);

            level++;

            continue;

        }

         

        page_size = (1ULL << ((granule_sz * (4 - level)) + 3));

        descaddr |= (address & (page_size - 1));

         

        attrs = extract64(descriptor, 2, 10)

            | (extract64(descriptor, 52, 12) << 10);

        attrs |= extract32(tableattrs, 0, 2) << 11;  

        attrs |= extract32(tableattrs, 3, 1) << 5;  

         

        if (extract32(tableattrs, 2, 1)) {

            attrs &= ~(1 << 4);

        }

        attrs |= nstable << 3;  

        break;

    }

     

    fault_type = access_fault;

    if ((attrs & (1 << 8)) == 0) {

         

        goto do_fault;

    }



    ap = extract32(attrs, 4, 2);

    ns = extract32(attrs, 3, 1);

    xn = extract32(attrs, 12, 1);

    pxn = extract32(attrs, 11, 1);



    *prot = get_S1prot(env, mmu_idx, va_size == 64, ap, ns, xn, pxn);



    fault_type = permission_fault;

    if (!(*prot & (1 << access_type))) {

        goto do_fault;

    }



    if (ns) {

         

        txattrs->secure = false;

    }

    *phys_ptr = descaddr;

    *page_size_ptr = page_size;

    return 0;



do_fault:

     

    return (1 << 9) | (fault_type << 2) | level;

}
