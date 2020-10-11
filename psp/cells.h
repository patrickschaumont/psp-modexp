#ifndef CELLS_H_
#define CELLS_H_


#define MDTYPE unsigned

#define X86_HL

#ifdef X86_HL
#define AND2(a,b,r) { r = a & b;}
#define OR2(a,b,r) { r = a | b; }
#define BIC2(a,b,r) { r = a & ~b; }
#define XOR2(a,b,r) { r = a ^ b; }
#define ORN2(a,b,r) { r = a | ~b; }
#define NOT1(a,r) { r = ~a; }
#define DFF(clk,d,q) { q = d; }
#define DFFSR(clk,d, q, rst, set) {q = rst ? 0 : (set ? 1 : d);}
#endif

#ifdef X86_DEBUG_STATE
#define AND2(a,b,r) { r = a & b; } //printf("%8s AND %8x %8x -> %8x\n", #r, a, b, r);}
#define OR2(a,b,r) { r = a | b; } // printf("%8s OR  %8x %8x -> %8x\n", #r, a, b, r);}
#define BIC2(a,b,r) { r = a & ~b; } // printf("%8s BIC %8x %8x -> %8x\n", #r, a, b, r);}
#define XOR2(a,b,r) { r = a ^ b; } // printf("%8s XOR %8x %8x -> %8x\n", #r, a, b, r);}
#define ORN2(a,b,r) { r = a | ~b; } // printf("%8s ORN %8x %8x -> %8x\n", #r, a, b, r);}
#define NOT1(a,r) { r = ~a; } // printf("%8s NOT          %8x -> %8x\n", #r, a, r);}
#define DFF(clk,d,q) { printf("%8s DFF %8x  / %8x\n", #q, q, d); q = d; }
#define DFFSR(clk,d, q, rst, set) {printf("%8s DFFSR %8x  / %8x\n", #q, q, d); q = rst ? 0 : (set ? 1 : d);}
#endif

#ifdef X86_DEBUG_FULL
#define AND2(a,b,r) { r = a & b; printf("%8s AND %8x %8x -> %8x\n", #r, a, b, r);}
#define OR2(a,b,r) { r = a | b; printf("%8s OR  %8x %8x -> %8x\n", #r, a, b, r);}
#define BIC2(a,b,r) { r = a & ~b; printf("%8s BIC %8x %8x -> %8x\n", #r, a, b, r);}
#define XOR2(a,b,r) { r = a ^ b; printf("%8s XOR %8x %8x -> %8x\n", #r, a, b, r);}
#define ORN2(a,b,r) { r = a | ~b; printf("%8s ORN %8x %8x -> %8x\n", #r, a, b, r);}
#define NOT1(a,r) { r = ~a; printf("%8s NOT          %8x -> %8x\n", #r, a, r);}
#define DFF(clk,d,q) { printf("%8s DFF %8x  / %8x\n", #q, q, d); q = d; }
#define DFFSR(clk,d, q, rst, set) {printf("%8s DFFSR %8x  / %8x\n", #q, q, d); q = rst ? 0 : (set ? 1 : d);}
#endif


#endif /* CELLS_H_ */
