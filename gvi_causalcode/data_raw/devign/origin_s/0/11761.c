static int sysctl_oldcvt(void *holdp, size_t holdlen, uint32_t kind)

{

    switch (kind & CTLTYPE) {

    case CTLTYPE_INT:

    case CTLTYPE_UINT:

        *(uint32_t *)holdp = tswap32(*(uint32_t *)holdp);

        break;


    case CTLTYPE_LONG:

    case CTLTYPE_ULONG:

        *(uint32_t *)holdp = tswap32(*(long *)holdp);

        break;


    case CTLTYPE_LONG:

        *(uint64_t *)holdp = tswap64(*(long *)holdp);

    case CTLTYPE_ULONG:

        *(uint64_t *)holdp = tswap64(*(unsigned long *)holdp);

        break;



    case CTLTYPE_QUAD:


    case CTLTYPE_U64:


        *(uint64_t *)holdp = tswap64(*(uint64_t *)holdp);

        break;

    case CTLTYPE_STRING:

        break;

    default:

         

        return -1;

    }

    return 0;

}
