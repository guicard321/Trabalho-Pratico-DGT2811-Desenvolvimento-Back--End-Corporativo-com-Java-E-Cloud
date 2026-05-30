//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************



















#if !ARMASM

#pragma once

#pragma warning(disable:4201) 
#pragma warning(disable:4668) 

#if !HKCODEGEN
#include "intrin.h"
#endif





typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;



typedef __int64 INT64;
typedef unsigned __int64 UINT64;

#if !__cplusplus
typedef unsigned char bool;
typedef unsigned short wchar_t;
#endif







#if ARM64 || ARM64EC
#define SQL_FLOAT_SUPPORTS_HARDWARE_TRAP 0
#elif AMD64 || i386
#define SQL_FLOAT_SUPPORTS_HARDWARE_TRAP 1
#else
#error unknown architecture
#endif

#if !SQL_FLOAT_SUPPORTS_HARDWARE_TRAP
#define HK_EMU_TRAP 1
#elif !defined(HK_EMU_TRAP)
#define HK_EMU_TRAP 0
#endif

#if HK_EMU_TRAP && SQL_FLOAT_SUPPORTS_HARDWARE_TRAP
#define SetFloatingPointControl         SetFloatingPointControlEmuTrap
#define SetFloatingPointControlCommon   SetFloatingPointControlCommonEmuTrap
#define SetFloatingPointControlExact    SetFloatingPointControlExactEmuTrap
#define SetFloatingPointControlTruncate SetFloatingPointControlTruncateEmuTrap

#define SqlFloatPollTrap                SqlFloatPollTrapEmuTrap
#endif




























#define HK_POLL_LIST_CXX \
    HK_POLL_CXX(bool)    \
    HK_POLL_CXX(float)   \
    HK_POLL_CXX(double)  \
    HK_POLL_CXX(char)    \
    HK_POLL_CXX(wchar_t) \
    HK_POLL_CXX(short)   \
    HK_POLL_CXX(int)     \
    HK_POLL_CXX(long)    \
    HK_POLL_CXX(INT64)   \
    HK_POLL_CXX(UCHAR)   \
    HK_POLL_CXX(USHORT)  \
    HK_POLL_CXX(UINT)    \
    HK_POLL_CXX(ULONG)   \
    HK_POLL_CXX(UINT64)

#define HK_POLL_LIST_C \
    HK_POLL_C(bool)    \
    HK_POLL_C(float)   \
    HK_POLL_C(double)  \
    HK_POLL_C(char)    \
    HK_POLL_C(wchar_t) \
    HK_POLL_C(short)   \
    HK_POLL_C(int)     \
    HK_POLL_C(long)    \
    HK_POLL_C(INT64)   \
    HK_POLL_C(UCHAR)   \
    HK_POLL_C(USHORT)  \
    HK_POLL_C(UINT)    \
    HK_POLL_C(ULONG)   \
    HK_POLL_C(UINT64)  \
    HK_POLL_C(size_t)

#if __cplusplus
#define SQL_IF_CXX(x) x
#else
#define SQL_IF_CXX(x)
#endif

#define SQL_EXTERN_C_BEGIN SQL_IF_CXX(extern "C" {)
#define SQL_EXTERN_C_END   SQL_IF_CXX(})


#define HK_POLL_C(T) \
    SQL_EXTERN_C_BEGIN T hk_poll_##T(T a);       SQL_EXTERN_C_END \
    SQL_EXTERN_C_BEGIN T hk_poll_exact_##T(T a); SQL_EXTERN_C_END \





#if __cplusplus
template <typename T> T hk_poll(T);
template <typename T> T hk_poll_exact(T);
#endif
#define HK_POLL_CXX(T) \
    SQL_IF_CXX(template <> T hk_poll<T>(T a);) \
    SQL_IF_CXX(template <> T hk_poll_exact<T>(T a);)
HK_POLL_LIST_C
HK_POLL_LIST_CXX
#undef HK_POLL_C
#undef HK_POLL_CXX

#if !HK_EMU_TRAP





#define hk_poll(x)               (x)
#define hk_poll_bool(x)          (x)
#define hk_poll_float(x)         (x)
#define hk_poll_double(x)        (x)
#define hk_poll_char(x)          (x)
#define hk_poll_wchar_t(x)       (x)
#define hk_poll_short(x)         (x)
#define hk_poll_int(x)           (x)
#define hk_poll_long(x)          (x)
#define hk_poll_INT64(x)         (x)
#define hk_poll_UCHAR(x)         (x)
#define hk_poll_USHORT(x)        (x)
#define hk_poll_UINT(x)          (x)
#define hk_poll_ULONG(x)         (x)
#define hk_poll_UINT64(x)        (x)
#define hk_poll_size_t(x)        (x)

#define hk_poll_exact(x)         (x)
#define hk_poll_exact_bool(x)    (x)
#define hk_poll_exact_float(x)   (x)
#define hk_poll_exact_double(x)  (x)
#define hk_poll_exact_char(x)    (x)
#define hk_poll_exact_wchar_t(x) (x)
#define hk_poll_exact_short(x)   (x)
#define hk_poll_exact_int(x)     (x)
#define hk_poll_exact_long(x)    (x)
#define hk_poll_exact_INT64(x)   (x)
#define hk_poll_exact_UCHAR(x)   (x)
#define hk_poll_exact_USHORT(x)  (x)
#define hk_poll_exact_UINT(x)    (x)
#define hk_poll_exact_ULONG(x)   (x)
#define hk_poll_exact_UINT64(x)  (x)
#define hk_poll_exact_size_t(x)  (x)

#endif

#if __cplusplus
extern "C" {
#endif

void _mm_setcsr(UINT);
UINT _mm_getcsr(void);


#define _MM_EXCEPT_MASK       0x003f
#define _MM_MASK_MASK         0x1f80
#define _MM_MASK_INVALID      0x0080
#define _MM_MASK_DENORM       0x0100
#define _MM_MASK_DIV_ZERO     0x0200
#define _MM_MASK_OVERFLOW     0x0400
#define _MM_MASK_UNDERFLOW    0x0800
#define _MM_MASK_INEXACT      0x1000
#define _MM_ROUND_MASK        0x6000
#define _MM_ROUND_NEAREST     0x0000
#define _MM_ROUND_DOWN        0x2000
#define _MM_ROUND_UP          0x4000
#define _MM_ROUND_TOWARD_ZERO 0x6000

#define SQL_AMD64_FLOAT_ROUND_SHIFT 13

#endif 




























#define SQL_ARM64_FLOAT_ROUND_NEAREST 0
#define SQL_ARM64_FLOAT_ROUND_UP   1
#define SQL_ARM64_FLOAT_ROUND_DOWN 2

#define SQL_ARM64_FLOAT_ROUND_TOWARD_ZERO 3

#define SQL_ARM64_FLOAT_STATUS_INVALID   0x01
#define SQL_ARM64_FLOAT_STATUS_DIV_ZERO  0x02
#define SQL_ARM64_FLOAT_STATUS_OVERFLOW  0x04
#define SQL_ARM64_FLOAT_STATUS_UNDERFLOW 0x08
#define SQL_ARM64_FLOAT_STATUS_INEXACT   0x10


#define SQL_ARM64_FLOAT_HK_STATUS (SQL_ARM64_FLOAT_STATUS_INVALID  + \
                                   SQL_ARM64_FLOAT_STATUS_DIV_ZERO + \
                                   SQL_ARM64_FLOAT_STATUS_OVERFLOW)


#define SQL_ARM64_FLOAT_HK_STATUS_EXACT (SQL_ARM64_FLOAT_HK_STATUS        + \
                                         SQL_ARM64_FLOAT_STATUS_UNDERFLOW + \
                                         SQL_ARM64_FLOAT_STATUS_INEXACT)

#define SQL_ARM64_FLOAT_STATUS_ALL SQL_ARM64_FLOAT_HK_STATUS_EXACT

#define SQL_ARM64_FLOAT_CONTROL_ERROR_OFFSET 8
#define SQL_ARM64_FLOAT_CONTROL_ERROR_SIZE 5
#define SQL_ARM64_FLOAT_ERROR_MASK 0x1F

#define SQL_ARM64_FLOAT_CONTROL_ALL SQL_ARM64_FLOAT_HK_STATUS_EXACT

#define SQL_ARM64_FLOAT_CONTROL_ROUND_OFFSET 22
#define SQL_FLOAT_CONTROL_ROUND_SIZE 2 

#if !ARMASM




typedef union SqlArmFloatStatus_t {
    UINT all;
    struct {
        
        UINT invalid     : 1; 
        UINT zero_divide : 1; 
        UINT overflow    : 1; 
        UINT underflow   : 1; 
        UINT inexact     : 1; 
    };
    struct {
        UINT errors : 5;
    };
} SqlArmFloatStatus_t;




typedef union SqlArmFloatControl_t {
    UINT all;
    struct {
        UINT             : 8;
        
        
        
        
        
        
        
        
        UINT invalid     : 1; 
        UINT zero_divide : 1; 
        UINT overflow    : 1; 
        UINT underflow   : 1; 
        UINT inexact     : 1; 
    };
    struct {
        UINT       : 8;
        UINT traps : 5;
    };
    struct {
        UINT       : SQL_ARM64_FLOAT_CONTROL_ROUND_OFFSET;
        UINT round : SQL_FLOAT_CONTROL_ROUND_SIZE;
    };
    struct {
        UINT      : 8;
        UINT mask : 5; 
    };
} SqlArmFloatControl_t;




























typedef union SqlAmd64FloatStatus_t {
    UINT all;
    struct {
        
        
        UINT invalid     : 1; 
        UINT denorm      : 1; 
        UINT zero_divide : 1; 
        UINT overflow    : 1; 
        UINT underflow   : 1; 
        UINT inexact     : 1; 
    };
    struct {
        UINT errors : 6;
        UINT        : 1;
        UINT mask   : 6;
    };
} SqlAmd64FloatStatus_t;

typedef union SqlAmd64FloatControl_t {
    UINT all;
    struct {
        
        UINT             : 7;
        
        
        UINT invalid     : 1; 
        UINT denorm      : 1; 
        UINT zero_divide : 1; 
        UINT overflow    : 1; 
        UINT underflow   : 1; 
        UINT inexact     : 1; 
    };
    struct {
        UINT errors : 6;
        UINT        : 1;
        UINT mask   : 6;
        UINT round  : SQL_FLOAT_CONTROL_ROUND_SIZE;
    };
    struct {
        UINT       : 7;
        UINT traps : 6; 
#if AMD64 && !ARM64EC
#define SQL_FLOAT_CONTROL_TRAPS_TO_MASK(traps) (~(traps))
#else
#define SQL_FLOAT_CONTROL_TRAPS_TO_MASK(traps) (traps)
#endif
    };
} SqlAmd64FloatControl_t;

#if ARM64 || ARM64EC
typedef SqlArmFloatControl_t SqlFloatControl_t;
typedef SqlArmFloatStatus_t  SqlFloatStatus_t;
#elif AMD64 || i386
typedef SqlAmd64FloatControl_t SqlFloatControl_t;
typedef SqlAmd64FloatStatus_t  SqlFloatStatus_t;
#else
#error unknown architecture
#endif


void ClearFloatErrors(void);
void SqlSetFloatControl(SqlFloatControl_t control);
void SqlSetFloatStatus(SqlFloatStatus_t status);



#if __cplusplus
#define SQL_FLOAT_EXTRA_PARAMETERS ...
#else
#define SQL_FLOAT_EXTRA_PARAMETERS
#endif






SqlFloatControl_t SqlGetFloatControl(SQL_FLOAT_EXTRA_PARAMETERS);
SqlFloatStatus_t SqlGetFloatStatus(SQL_FLOAT_EXTRA_PARAMETERS);











void RaiseFloatControl(SqlFloatControl_t control SQL_FLOAT_EXTRA_PARAMETERS);


void RaiseFloatControlAndStatus(SqlFloatControl_t control, SqlFloatStatus_t status);

void SetFloatingPointControlDefault(void);





UINT SqlGetCurrentAmd64RoundingModeRightShifted(void);



#if (AMD64 && !ARM64EC) || i386
__forceinline void
SetFloatingPointControlCommon(UINT set)
{
	
	
	
	UINT csr = _mm_getcsr();
#if HK_EMU_TRAP
	csr &= ~(_MM_ROUND_MASK | _MM_EXCEPT_MASK);
	csr |= _MM_MASK_MASK; 
#else
	csr &= ~(_MM_MASK_MASK | _MM_ROUND_MASK | _MM_EXCEPT_MASK);
#endif
	csr |= set;
	_mm_setcsr(csr);
}






__forceinline void
SetFloatingPointControl(void)
{
	
	
	
	
	SetFloatingPointControlCommon(_MM_MASK_DENORM | _MM_MASK_UNDERFLOW | _MM_MASK_INEXACT | _MM_ROUND_NEAREST);
}



__forceinline void
SetFloatingPointControlTruncate(void)
{
	
	
	
	
	
	
	SetFloatingPointControlCommon(_MM_MASK_DENORM | _MM_MASK_UNDERFLOW | _MM_MASK_INEXACT | _MM_ROUND_TOWARD_ZERO);
}




__forceinline void
SetFloatingPointControlExact(void)
{
	
	
	
	
	SetFloatingPointControlCommon(_MM_MASK_DENORM | _MM_ROUND_NEAREST);
}

#else




void SetFloatingPointControl(void);
void SetFloatingPointControlExact(void);
void SetFloatingPointControlTruncate(void);

#endif

#define SQL_FLOAT_EXCEPTIONS                            \
    SQL_FLOAT_EXCEPTION(STATUS_FLOAT_OVERFLOW)          \
    SQL_FLOAT_EXCEPTION(STATUS_FLOAT_UNDERFLOW)         \
    SQL_FLOAT_EXCEPTION(STATUS_FLOAT_DIVIDE_BY_ZERO)    \
    SQL_FLOAT_EXCEPTION(STATUS_FLOAT_INVALID_OPERATION) \
    SQL_FLOAT_EXCEPTION(STATUS_FLOAT_INEXACT_RESULT)    \

typedef struct SqlFloatException
{
    UINT status;
    const char* string;
} SqlFloatException;

#define SQL_FLOAT_EXCEPTION(status) extern const SqlFloatException SqlFloat_##status;

SQL_FLOAT_EXCEPTIONS

#undef SQL_FLOAT_EXCEPTION




void SqlFloatRaiseException(const SqlFloatException* exception);

#if __cplusplus
}



template <typename T, bool trap>
struct SqlFloatPollTrap
{
private:

    template <typename T3> static T3 Poll(T3 a);

#define HK_POLL_CXX(T4) template <> T4 Poll(T4 a) { return trap ? hk_poll(a) : a; }
HK_POLL_LIST_CXX
#undef HK_POLL_CXX

    T m_rep { };

public:
    SqlFloatPollTrap() = default;

    constexpr SqlFloatPollTrap(T rep) : m_rep(rep)
    {
        
        
        
        if (!__builtin_is_constant_evaluated())
            Poll(rep);
    }

    
    SqlFloatPollTrap (const SqlFloatPollTrap& a) : m_rep(a.m_rep) { }

    SqlFloatPollTrap& operator=(SqlFloatPollTrap a) { m_rep = a.m_rep; return *this; }
    SqlFloatPollTrap& operator=(T a) { Poll(m_rep = a); return *this; }

    
    
    T get() const { return m_rep; }

    template <typename T2> struct is_same_helper { enum { value = 0 };};
    template <> struct is_same_helper<T> { enum { value = 1 };};
    template <typename T2> const static bool is_same = is_same_helper<T2>::value;

    
    template <typename T2>
    operator T2 () const
    {
#pragma warning(suppress:4244) 
        T2 const t2 = static_cast<T2>(m_rep);
        if (!is_same<T2>)
        {
            Poll(t2);
        }
        return t2;
    }

    SqlFloatPollTrap& operator+=(SqlFloatPollTrap a) { Poll(m_rep += a.m_rep); return *this; }
    SqlFloatPollTrap& operator-=(SqlFloatPollTrap a) { Poll(m_rep -= a.m_rep); return *this; }
    SqlFloatPollTrap& operator*=(SqlFloatPollTrap a) { Poll(m_rep *= a.m_rep); return *this; }
    SqlFloatPollTrap& operator/=(SqlFloatPollTrap a) { Poll(m_rep /= a.m_rep); return *this; }
    friend SqlFloatPollTrap operator+(SqlFloatPollTrap a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a.m_rep + b.m_rep); }
    friend SqlFloatPollTrap operator-(SqlFloatPollTrap a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a.m_rep - b.m_rep); }
    friend SqlFloatPollTrap operator*(SqlFloatPollTrap a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a.m_rep * b.m_rep); }
    friend SqlFloatPollTrap operator/(SqlFloatPollTrap a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a.m_rep / b.m_rep); }
    template <typename T2> friend SqlFloatPollTrap operator+(T2 a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a + b.m_rep); }
    template <typename T2> friend SqlFloatPollTrap operator-(T2 a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a - b.m_rep); }
    template <typename T2> friend SqlFloatPollTrap operator*(T2 a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a * b.m_rep); }
    template <typename T2> friend SqlFloatPollTrap operator/(T2 a, SqlFloatPollTrap b) { return SqlFloatPollTrap(a / b.m_rep); }
    template <typename T2> friend SqlFloatPollTrap operator+(SqlFloatPollTrap a, T2 b) { return SqlFloatPollTrap(a.m_rep + b); }
    template <typename T2> friend SqlFloatPollTrap operator-(SqlFloatPollTrap a, T2 b) { return SqlFloatPollTrap(a.m_rep - b); }
    template <typename T2> friend SqlFloatPollTrap operator*(SqlFloatPollTrap a, T2 b) { return SqlFloatPollTrap(a.m_rep * b); }
    template <typename T2> friend SqlFloatPollTrap operator/(SqlFloatPollTrap a, T2 b) { return SqlFloatPollTrap(a.m_rep / b); }
    SqlFloatPollTrap operator-() const { return SqlFloatPollTrap(-m_rep); }
    
    friend bool operator==(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep == b.m_rep); }
    friend bool operator!=(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep != b.m_rep); }
    friend bool operator<(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep < b.m_rep); }
    friend bool operator<=(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep <= b.m_rep); }
    friend bool operator>(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep > b.m_rep); }
    friend bool operator>=(SqlFloatPollTrap a, SqlFloatPollTrap b) { return Poll(a.m_rep >= b.m_rep); }
    template <typename T2> friend bool operator==(T2 a, SqlFloatPollTrap b) { return Poll(a == b.m_rep); }
    template <typename T2> friend bool operator!=(T2 a, SqlFloatPollTrap b) { return Poll(a != b.m_rep); }
    template <typename T2> friend bool operator<(T2 a, SqlFloatPollTrap b) { return Poll(a < b.m_rep); }
    template <typename T2> friend bool operator<=(T2 a, SqlFloatPollTrap b) { return Poll(a <= b.m_rep); }
    template <typename T2> friend bool operator>(T2 a, SqlFloatPollTrap b) { return Poll(a > b.m_rep); }
    template <typename T2> friend bool operator>=(T2 a, SqlFloatPollTrap b) { return Poll(a >= b.m_rep); }
    template <typename T2> friend bool operator==(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep == b); }
    template <typename T2> friend bool operator!=(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep != b); }
    template <typename T2> friend bool operator<(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep < b); }
    template <typename T2> friend bool operator<=(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep <= b); }
    template <typename T2> friend bool operator>(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep > b); }
    template <typename T2> friend bool operator>=(SqlFloatPollTrap a, T2 b) { return Poll(a.m_rep >= b); }
};

template <typename T, bool trap> struct SqlFloatPollTrapSpecialized;

template <typename T> struct SqlFloatPollTrapSpecialized<T, true>
{
#if HK_EMU_TRAP
    using type = SqlFloatPollTrap<T, true>;
#else
    
    using type = T;
#endif
};

template <typename T> struct SqlFloatPollTrapSpecialized<T, false>
{
    using type = T;
};








template <typename T, bool trap> using SqlFloatTemplate = typename SqlFloatPollTrapSpecialized<T, trap>::type;


using HkFloat_t = SqlFloatTemplate<float, true>;
using HkDouble_t = SqlFloatTemplate<double, true>;

#else 

#if HK_EMU_TRAP

#else

typedef float HkFloat_t;
typedef double HkDouble_t;
#endif

#endif 
#endif 
