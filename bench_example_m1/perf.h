#ifndef vct_AARCH64_H
#define vct_AARCH64_H

/* ==================== GNU C and possibly other UNIX compilers ===================== */
#if defined(__GNUC__) || defined(__linux__)
    #define VOLATILE __volatile__
    #define ASM __asm__
#else
    /* if we're neither compiling with gcc or under linux, we can hope
        * the following lines work, they probably won't */
    #define ASM asm
    #define VOLATILE
#endif

#define TIMESTAMP unsigned long long
#define FREQ unsigned long long
#define INT32 unsigned int
#define myInt64 unsigned long long
#define INT32 unsigned int


/* This is the virtual counter-timer 
* It is a 64-bit register that counts at the frequency of the system's
* physical counter. It is available from ARMv8 onwards.
*
* The frequency of the counter is accessible through the CNTFRQ_EL0 register.
*
* The counter is read by reading the CNTVCT_EL0 register.
*/

#define COUNTER_LO(a) ((a).int32.lo)
#define COUNTER_HI(a) ((a).int32.hi)
#define COUNTER_VAL(a) ((a).int64)

#define COUNTER(a) \
    ((unsigned long long)COUNTER_VAL(a))

#define COUNTER_DIFF(a,b) \
    (COUNTER(a)-COUNTER(b))

#ifdef __aarch64__

    typedef union
    {       TIMESTAMP int64;
            struct {INT32 lo, hi;} int32;
    } vct_counter;

    typedef union
    {       FREQ int64;
            struct {INT32 lo, hi;} int32;
    } vct_freq;

    // virtual counter-timer
    #define CNTVCT(cpu_c) \
        ASM VOLATILE ("mrs %0, cntvct_el0" : "=r" (cpu_c))
    
    // physical counter-timer
    #define CNTPCT(cpu_c) \
        ASM VOLATILE ("mrs %0, cntpct_el0" : "=r" (cpu_c))

    // offset of virtual to physical counter-timer
    #define CNTVOFF(cpu_c) \
        ASM VOLATILE ("mrs %0, cntvoff_el2" : "=r" (cpu_c))

    // frequency of the counter
    #define CNTFRQ(cpu_c) \
        ASM VOLATILE ("mrs %0, cntfrq_el0" : "=r" (cpu_c))
#else // __aarch64__
    #error "Only ARM64 is supported"
#endif // __aarch64__

TIMESTAMP start_tsc(void);
TIMESTAMP start_tsc(void) {
    vct_counter start;
    CNTPCT(start);
    return COUNTER_VAL(start);
}

TIMESTAMP stop_tsc(TIMESTAMP start);
TIMESTAMP stop_tsc(TIMESTAMP start) {
    vct_counter end;
    CNTPCT(end);
    return COUNTER_VAL(end) - start;
}

TIMESTAMP get_vct_offset(void);
TIMESTAMP get_vct_offset(void) {
    vct_counter offset;
    CNTVOFF(offset);
    return COUNTER_VAL(offset);
}

TIMESTAMP get_vct_freq(void);
TIMESTAMP get_vct_freq(void) {
    vct_freq freq;
    CNTFRQ(freq);
    return COUNTER_VAL(freq);
}

#endif // vct_AARCH64_H


#ifdef __x86_64__

/* ==================== GNU C and possibly other UNIX compilers ===================== */
#ifndef _WIN32

#if defined(__GNUC__) || defined(__linux__)
    #define VOLATILE __volatile__
    #define ASM __asm__
#else
    /* if we're neither compiling with gcc or under linux, we can hope
     * the following lines work, they probably won't */
    #define ASM asm
    #define VOLATILE 
#endif

#define myInt64 unsigned long long
#define INT32 unsigned int

/* ======================== WIN32 ======================= */
#else

#define myInt64 signed __int64
#define INT32 unsigned __int32

#endif

/* This is the RDTSC timer.
* RDTSC is an instruction on several Intel and compatible CPUs that Reads the
* Time Stamp Counter. The Intel manuals contain more information.
*/


#define COUNTER_LO(a) ((a).int32.lo)
#define COUNTER_HI(a) ((a).int32.hi)
#define COUNTER_VAL(a) ((a).int64)

#define COUNTER(a) \
((unsigned long long)COUNTER_VAL(a))

#define COUNTER_DIFF(a,b) \
(COUNTER(a)-COUNTER(b))

/* ==================== GNU C and possibly other UNIX compilers ===================== */
#ifndef _WIN32

typedef union
{       myInt64 int64;
        struct {INT32 lo, hi;} int32;
} tsc_counter;

#define RDTSC(cpu_c) \
  ASM VOLATILE ("rdtsc" : "=a" ((cpu_c).int32.lo), "=d"((cpu_c).int32.hi))
#define CPUID() \
    ASM VOLATILE ("cpuid" : : "a" (0) : "bx", "cx", "dx" )

/* ======================== WIN32 ======================= */
#else

typedef union
{       myInt64 int64;
        struct {INT32 lo, hi;} int32;
} tsc_counter;

#define RDTSC(cpu_c)   \
{       __asm rdtsc    \
        __asm mov (cpu_c).int32.lo,eax  \
        __asm mov (cpu_c).int32.hi,edx  \
}

#define CPUID() \
{ \
    __asm mov eax, 0 \
    __asm cpuid \
}

#endif


static void init_tsc() {
; // no need to initialize anything for x86
}

static myInt64 start_tsc(void) {
tsc_counter start;
CPUID();
RDTSC(start);
return COUNTER_VAL(start);
}

static myInt64 stop_tsc(myInt64 start) {
tsc_counter end;
RDTSC(end);
CPUID();
return COUNTER_VAL(end) - start;
}



#endif