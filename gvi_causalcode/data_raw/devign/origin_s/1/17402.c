static bool get_phys_addr_lpae(CPUARMState *env, target_ulong address,

                               MMUAccessType access_type, ARMMMUIdx mmu_idx,

                               hwaddr *phys_ptr, MemTxAttrs *txattrs, int *prot,

                               target_ulong *page_size_ptr,

                               ARMMMUFaultInfo *fi, ARMCacheAttrs *cacheattrs)

{

    ARMCPU *cpu = arm_env_get_cpu(env);

    CPUState *cs = CPU(cpu);

     

    ARMFaultType fault_type = ARMFault_Translation;

    uint32_t level;

    uint32_t epd = 0;

    int32_t t0sz, t1sz;

    uint32_t tg;

    uint64_t ttbr;

    int ttbr_select;

    hwaddr descaddr, indexmask, indexmask_grainsize;

    uint32_t tableattrs;

    target_ulong page_size;

    uint32_t attrs;

    int32_t stride = 9;

    int32_t addrsize;

    int inputsize;

    int32_t tbi = 0;

    TCR *tcr = regime_tcr(env, mmu_idx);

    int ap, ns, xn, pxn;

    uint32_t el = regime_el(env, mmu_idx);

    bool ttbr1_valid = true;

    uint64_t descaddrmask;

    bool aarch64 = arm_el_is_aa64(env, el);



     

    if (aarch64) {

        level = 0;

        addrsize = 64;

        if (el > 1) {

            if (mmu_idx != ARMMMUIdx_S2NS) {

                tbi = extract64(tcr->raw_tcr, 20, 1);

            }

        } else {

            if (extract64(address, 55, 1)) {

                tbi = extract64(tcr->raw_tcr, 38, 1);

            } else {

                tbi = extract64(tcr->raw_tcr, 37, 1);

            }

        }

        tbi *= 8;



         

        if (el > 1) {

            ttbr1_valid = false;

        }

    } else {

        level = 1;

        addrsize = 32;

         

        if (el == 2) {

            ttbr1_valid = false;

        }

    }



     

    if (aarch64) {

         

        t0sz = extract32(tcr->raw_tcr, 0, 6);

        t0sz = MIN(t0sz, 39);

        t0sz = MAX(t0sz, 16);

    } else if (mmu_idx != ARMMMUIdx_S2NS) {

         

        t0sz = extract32(tcr->raw_tcr, 0, 3);

    } else {

         

        bool sext = extract32(tcr->raw_tcr, 4, 1);

        bool sign = extract32(tcr->raw_tcr, 3, 1);

         

        addrsize = 40;

        t0sz = sextract32(tcr->raw_tcr, 0, 4) + 8;



         

        if (sign != sext) {

            qemu_log_mask(LOG_GUEST_ERROR,

                          "AArch32: VTCR.S / VTCR.T0SZ[3] mismatch\n");

        }

    }

    t1sz = extract32(tcr->raw_tcr, 16, 6);

    if (aarch64) {

        t1sz = MIN(t1sz, 39);

        t1sz = MAX(t1sz, 16);

    }

    if (t0sz && !extract64(address, addrsize - t0sz, t0sz - tbi)) {

         

        ttbr_select = 0;

    } else if (ttbr1_valid && t1sz &&

               !extract64(~address, addrsize - t1sz, t1sz - tbi)) {

         

        ttbr_select = 1;

    } else if (!t0sz) {

         

        ttbr_select = 0;

    } else if (!t1sz && ttbr1_valid) {

         

        ttbr_select = 1;

    } else {

         

        fault_type = ARMFault_Translation;

        goto do_fault;

    }



     

    if (ttbr_select == 0) {

        ttbr = regime_ttbr(env, mmu_idx, 0);

        if (el < 2) {

            epd = extract32(tcr->raw_tcr, 7, 1);

        }

        inputsize = addrsize - t0sz;



        tg = extract32(tcr->raw_tcr, 14, 2);

        if (tg == 1) {  

            stride = 13;

        }

        if (tg == 2) {  

            stride = 11;

        }

    } else {

         

        assert(ttbr1_valid);



        ttbr = regime_ttbr(env, mmu_idx, 1);

        epd = extract32(tcr->raw_tcr, 23, 1);

        inputsize = addrsize - t1sz;



        tg = extract32(tcr->raw_tcr, 30, 2);

        if (tg == 3)  {  

            stride = 13;

        }

        if (tg == 1) {  

            stride = 11;

        }

    }



     



    if (epd) {

         

        goto do_fault;

    }



    if (mmu_idx != ARMMMUIdx_S2NS) {

         

        level = 4 - (inputsize - 4) / stride;

    } else {

         

        uint32_t sl0 = extract32(tcr->raw_tcr, 6, 2);

        uint32_t startlevel;

        bool ok;



        if (!aarch64 || stride == 9) {

             

            startlevel = 2 - sl0;

        } else {

             

            startlevel = 3 - sl0;

        }



         

        ok = check_s2_mmu_setup(cpu, aarch64, startlevel,

                                inputsize, stride);

        if (!ok) {

            fault_type = ARMFault_Translation;

            goto do_fault;

        }

        level = startlevel;

    }



    indexmask_grainsize = (1ULL << (stride + 3)) - 1;

    indexmask = (1ULL << (inputsize - (stride * (4 - level)))) - 1;



     

    descaddr = extract64(ttbr, 0, 48);

    descaddr &= ~indexmask;



     

    descaddrmask = ((1ull << (aarch64 ? 48 : 40)) - 1) &

                   ~indexmask_grainsize;



     

    tableattrs = regime_is_secure(env, mmu_idx) ? 0 : (1 << 4);

    for (;;) {

        uint64_t descriptor;

        bool nstable;



        descaddr |= (address >> (stride * (4 - level))) & indexmask;

        descaddr &= ~7ULL;

        nstable = extract32(tableattrs, 4, 1);

        descriptor = arm_ldq_ptw(cs, descaddr, !nstable, mmu_idx, fi);

        if (fi->s1ptw) {

            goto do_fault;

        }



        if (!(descriptor & 1) ||

            (!(descriptor & 2) && (level == 3))) {

             

            goto do_fault;

        }

        descaddr = descriptor & descaddrmask;



        if ((descriptor & 2) && (level < 3)) {

             

            tableattrs |= extract64(descriptor, 59, 5);

            level++;

            indexmask = indexmask_grainsize;

            continue;

        }

         

        page_size = (1ULL << ((stride * (4 - level)) + 3));

        descaddr |= (address & (page_size - 1));

         

        attrs = extract64(descriptor, 2, 10)

            | (extract64(descriptor, 52, 12) << 10);



        if (mmu_idx == ARMMMUIdx_S2NS) {

             

            break;

        }

         

        attrs |= extract32(tableattrs, 0, 2) << 11;  

        attrs |= extract32(tableattrs, 3, 1) << 5;  

         

        if (extract32(tableattrs, 2, 1)) {

            attrs &= ~(1 << 4);

        }

        attrs |= nstable << 3;  

        break;

    }

     

    fault_type = ARMFault_AccessFlag;

    if ((attrs & (1 << 8)) == 0) {

         

        goto do_fault;

    }



    ap = extract32(attrs, 4, 2);

    xn = extract32(attrs, 12, 1);



    if (mmu_idx == ARMMMUIdx_S2NS) {

        ns = true;

        *prot = get_S2prot(env, ap, xn);

    } else {

        ns = extract32(attrs, 3, 1);

        pxn = extract32(attrs, 11, 1);

        *prot = get_S1prot(env, mmu_idx, aarch64, ap, ns, xn, pxn);

    }



    fault_type = ARMFault_Permission;

    if (!(*prot & (1 << access_type))) {

        goto do_fault;

    }



    if (ns) {

         

        txattrs->secure = false;

    }



    if (cacheattrs != NULL) {

        if (mmu_idx == ARMMMUIdx_S2NS) {

            cacheattrs->attrs = convert_stage2_attrs(env,

                                                     extract32(attrs, 0, 4));

        } else {

             

            uint8_t attrindx = extract32(attrs, 0, 3);

            uint64_t mair = env->cp15.mair_el[regime_el(env, mmu_idx)];

            assert(attrindx <= 7);

            cacheattrs->attrs = extract64(mair, attrindx * 8, 8);

        }

        cacheattrs->shareability = extract32(attrs, 6, 2);

    }



    *phys_ptr = descaddr;

    *page_size_ptr = page_size;

    return false;



do_fault:

    fi->type = fault_type;

    fi->level = level;

     

    fi->stage2 = fi->s1ptw || (mmu_idx == ARMMMUIdx_S2NS);

    return true;

}
