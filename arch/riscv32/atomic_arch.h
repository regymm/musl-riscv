#define a_barrier a_barrier
static inline void a_barrier()
{
	//__asm__ __volatile__ ("fence rw,rw" : : : "memory");
}

//#define a_ll a_ll
//static inline int a_ll(volatile int *p)
//{
	//int v;
	//__asm__ __volatile__ ("lr.w %0, (%1)" : "=&r"(v) : "r"(p));
	//return v;
//}

//#define a_sc a_sc
//static inline int a_sc(volatile int *p, int v)
//{
	//int r;
	//__asm__ __volatile__ ("sc.w %0, %2, (%1)" : "=&r"(r) : "r"(p), "r"(v) : "memory");
	//return !r;
//}

static inline void _pseudos_sti()
{
	__asm("li t0, 0x00000088; csrw mstatus, t0" ::: "t0");
}
static inline void _pseudos_cli()
{
	__asm("li t0, 0x00000000; csrw mstatus, t0" ::: "t0");
}

#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
	_pseudos_cli();
	int old;
	old = *p;
	if (old == t) *p = s; // always success
	_pseudos_sti();
	return old;
	// TODO:
	// forbidding process switching during a_cas seems enough
	// current is very lamed -- at least should reverse 
	// mstatus to original value instead of just 0x00/0x88
	//int old, tmp;
	//__asm__("1:  lr.w    %0, %2      \n"
		//"    bne     %0, %3, 1f  \n"
		//"    sc.w    %1, %4, %2  \n"
		//"    bnez    %1, 1b      \n"
		//"1:                      \n"
		//: "=&r"(old), "+r"(tmp), "+A"(*p)
		//: "r"(t), "r"(s));
	//return old;
}
