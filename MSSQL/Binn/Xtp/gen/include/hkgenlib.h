//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************















#pragma once

#include "SqlFloat.h"

typedef struct HkCompareContext HkCompareContext;
typedef struct HkInt128 HkInt128;
typedef struct HkInt192 HkInt192;
typedef struct HkInt256 HkInt256;
typedef struct HkInt320 HkInt320;
typedef struct HkLockBytes HkLockBytes;
typedef struct HkOutputMetadata HkOutputMetadata;
typedef struct HkPal HkPal;
typedef struct HkProcContext HkProcContext;
typedef struct HkRow HkRow;
typedef struct HkSearchKey HkSearchKey;
typedef struct HkSixteenByteData HkSixteenByteData;
typedef struct HkTable HkTable;
typedef struct HkTransaction HkTransaction;
typedef struct HkTxDeltaTracker HkTxDeltaTracker;
typedef struct IHkStatementExecStats IHkStatementExecStats;
typedef struct IHkStatementPerf IHkStatementPerf;
typedef enum DivRecExactness DivRecExactness;



typedef struct HkILBHandle HkILBHandle;



typedef struct HkStringUtils HkStringUtils;

#define FAILED(hr) (((HRESULT)(hr)) < 0)
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define HRESULT_FACILITY(hr) (((hr) >> 16) & 0x1fff)



#define ROWTAG(id) (((UINT64)(id) << 32) | __LINE__)

#if defined(__cplusplus)
	
	
	#define HKGAPI extern "C" extern
#else
	#define HKGAPI
#endif







#define HKNOALIAS_USEWITHCAUTION __declspec(noalias)





HKGAPI const wchar_t* jsonWstr;
HKGAPI const wchar_t* jsonValueWstr;
HKGAPI const wchar_t* jsonQueryWstr;
HKGAPI const wchar_t* jsonModifyWstr;
HKGAPI const wchar_t* stringEscapeWstr;
HKGAPI const wchar_t* nullWstr;
HKGAPI const wchar_t* jsonPathExistsWstr;

#if HKCODEGEN
	
	
	HKGAPI void
	hkassert_fail(
		unsigned int,
		const char* exp,
		const char* file,
		int line,
		const char* fmt, ...);

	
	
	
	#define utassert_fail hkassert_fail

	
	
	
	#ifndef DBG_ASSERT
		#ifdef DEBUG
			#define DBG_ASSERT(exp) ((exp) ? ((void)0) : hkassert_fail(0 , #exp, __FILE__, __LINE__, 0))
		#else
			#define DBG_ASSERT(exp)
		#endif
	#endif

	#ifndef RTL_ASSERT
		#define RTL_ASSERT(exp) ((exp) ? ((void)0) : hkassert_fail(1 , #exp, __FILE__, __LINE__, 0))
	#endif
#endif



#define IVS_HIGH_SURROGATE          0xDB40
#define IVS_LOW_SURROGATE_START     0xDD00
#define IVS_LOW_SURROGATE_END       0xDDEF





#define IS_SINGLE_UNIT_VS(wch) (((wch) >= 0xFE00 && (wch) <=  0xFE0F) || ((wch) >= 0x180B && (wch) <= 0x180D))



#define IS_IVS_HIGH_SURROGATE(wch) ((wch) == IVS_HIGH_SURROGATE)



#define IS_IVS_LOW_SURROGATE(wch)  (((wch) >= IVS_LOW_SURROGATE_START) && ((wch) <= IVS_LOW_SURROGATE_END))

#define IS_SURROGATE(wch) (wch >= 0xD800 && wch <= 0xDFFF)

HKGAPI __forceinline _Check_return_ __int64
Min(__int64 a, __int64 b)
{
	return (a < b) ? a : b;
}

HKGAPI __forceinline _Check_return_ __int64
Max(__int64 a, __int64 b)
{
	return (a > b) ? a : b;
}

HKGAPI __forceinline _Check_return_ long
ConvertCompareKeysResult(__int64 result64);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeNullHash( _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_int64(
	__int64 key,
	 _Inout_ unsigned long* hashState);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_int128(
	HkInt128 key,
	 _Inout_ unsigned long* hashState);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_int(
	int key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline _Check_return_ __int64
Compare64And64(
	__int64 key1,
	__int64 key2);
HKGAPI __forceinline _Check_return_ __int64
Compare64And64Fast(
	__int64 key1,
	__int64 key2);
HKGAPI __forceinline _Check_return_ __int64
Compare128And128(
	HkInt128 key1,
	HkInt128 key2);
HKGAPI __forceinline _Check_return_ __int64
Compare128And128Fast(
	HkInt128 key1,
	HkInt128 key2);
HKGAPI __forceinline _Check_return_ __int64
Compare256And256(
	HkInt256 key1,
	HkInt256 key2);
HKGAPI __forceinline _Check_return_ __int64
Compare256And256Fast(
	HkInt256 key1,
	HkInt256 key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare16And16(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare32And32(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare64And64(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare128And128(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare256And256(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
SKeyCompare320And320(
	HkSearchKey const* key1,
	HkSearchKey const* key2);

HKGAPI __forceinline _Check_return_ __int64
CompareKeys_int(
	int key1,
	int key2);
HKGAPI __forceinline _Check_return_ __int64
CompareKeys_short(
	short key1,
	short key2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_short(
	short key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline _Check_return_ __int64
CompareKeys_uchar(
	unsigned char key1,
	unsigned char key2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_uchar(
	unsigned char key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline _Check_return_ __int64
CompareKeys_double(
	double key1,
	double key2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_double(
	double key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
IncrementKey_double(
	double source,
	_Out_ double* target);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
DecrementKey_double(
	double source,
	_Out_ double* target);

HKGAPI __forceinline _Check_return_ __int64
CompareKeys_float(
	float key1,
	float key2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_float(
	float key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
IncrementKey_float(
	float source,
	_Out_ float* target);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
DecrementKey_float(
	float source,
	_Out_ float* target);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareKeys_Strings(
	unsigned char const* key1,
	long key1Len,
	unsigned char const* key2,
	long key2Len);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareKeys_Bin(
	_In_reads_bytes_(key1Len) unsigned char const* key1,
	long key1Len,
	_In_reads_bytes_(key2Len) unsigned char const* key2,
	long key2Len);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareKeys_WideStrings(
	_In_reads_bytes_(key1Len) unsigned char const* key1,
	long key1Len,
	_In_reads_bytes_(key2Len) unsigned char const* key2,
	long key2Len);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareLobs_Bin(
	_In_ HkILBHandle* lob1,
	_In_ HkILBHandle* lob2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareLobs_Strings(
	_In_ HkILBHandle* lob1,
	_In_ HkILBHandle* lob2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ __int64
CompareLobs_WideStrings(
	_In_ HkILBHandle* lob1,
	_In_ HkILBHandle* lob2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_Strings(
	unsigned char const* key,
	long keyLen,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_WideStrings(
	_In_reads_bytes_(keyLen) unsigned char const* key,
	long keyLen,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_Bin(
	_In_reads_bytes_(keyLen) unsigned char const* key,
	long keyLen,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline _Check_return_ __int64
CompareKeys_guid(
	HkSixteenByteData key1,
	HkSixteenByteData key2);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_  unsigned long
ComputeHash_guid(
	HkSixteenByteData key,
	 _Inout_ unsigned long* hashState);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
IncrementKey_guid(
	HkSixteenByteData source,
	_Out_ HkSixteenByteData* target);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
DecrementKey_guid(
	HkSixteenByteData source,
	_Out_ HkSixteenByteData* target);

HKGAPI __forceinline _Check_return_ HRESULT
RowSerialize(
	_In_reads_bytes_(serializeSize) HkRow const* row,
	_In_ unsigned long serializeSize,
	_Out_writes_bytes_to_(bufferSize, serializeSize) unsigned char* buffer,
	_In_ unsigned short bufferSize,
	_In_ unsigned short* copySize);

HKGAPI __forceinline _Check_return_ HRESULT
RowDeserialize(
	_In_ HkTransaction* tx,
	_In_ HkTable* table,
	_In_reads_bytes_(datasize) unsigned char const* data,
	_In_ unsigned short datasize,
	_In_ unsigned short minRowSize,
	_In_ unsigned short maxRowSize,
	_In_ unsigned int heapId,
	_Out_ HkRow** row);

HKGAPI _Check_return_ int
ExceptionFilter(unsigned int code, _Out_ HRESULT* hr);
HKGAPI _Check_return_ int
ExceptionFilterExactFloat(unsigned int code, double val, _Out_ float* dest, _Out_ HRESULT* hr);
HKGAPI _Check_return_ int
ExceptionFilterExactFloatToInt(unsigned int code, double val, _Out_ __int64* dest, _Out_ HRESULT* hr);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned char
Fits128Into64(HkInt128 const volatile* value);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned char
Fits256Into64(HkInt256 const* value);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned char
Fits256Into128(HkInt256 const* value);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned char
Fits320Into256(HkInt320 const* value);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128To64(HkInt128 const volatile* value, _Out_ __int64* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert256To64(HkInt256 const* value, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert256To128(HkInt256 const* value, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert64To128(__int64 value, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert320To256(HkInt320 const* value, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert256To320(HkInt256 const* value, _Out_ HkInt320* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128To256(HkInt128 const* value, _Out_ HkInt256* res);

#if __cplusplus
HKNOALIAS_USEWITHCAUTION void
Convert128To256(HkInt128 const& value, _Out_ HkInt256* res);
#endif

__inline HKNOALIAS_USEWITHCAUTION void
Convert128ToDouble(HkInt128 const* value, _Out_ double* res);


HKGAPI __inline HKNOALIAS_USEWITHCAUTION void
hk_Convert128ToDouble(HkInt128 const* value, _Out_ double* res);

#if __cplusplus
HKNOALIAS_USEWITHCAUTION void
Convert128ToDouble(HkInt128 const& value, _Out_ double* res);
#endif

__inline HKNOALIAS_USEWITHCAUTION void
Convert128ToFloat(HkInt128 const* value, _Out_ float* res);

HKGAPI  __inline HKNOALIAS_USEWITHCAUTION void
hk_Convert128ToFloat(HkInt128 const* value, _Out_ float* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert64ToDoubleWithScale64(__int64 value, unsigned __int64 scale, double scaleRecip, _Out_ double* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128ToDoubleWithScale64(HkInt128 const* value, unsigned __int64 scale, double scaleRecip, _Out_ double* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128ToDoubleWithScale128(HkInt128 const* value, HkInt128 const* scale, double scaleRecip, _Out_ double* res);
HKGAPI  __forceinline HKNOALIAS_USEWITHCAUTION void
Convert64ToFloatWithScale64(__int64 value, unsigned __int64 scale, double scaleRecip, _Out_ float* res);
HKGAPI  __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128ToFloatWithScale64(HkInt128 const* value, unsigned __int64 scale, double scaleRecip, _Out_ float* res);
HKGAPI  __forceinline HKNOALIAS_USEWITHCAUTION void
Convert128ToFloatWithScale128(HkInt128 const* value, HkInt128 const* scale, double scaleRecip, _Out_ float* res);

__forceinline HKNOALIAS_USEWITHCAUTION void
ConvertDoubleTo64(double value, _Out_ __int64* res);


HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hk_ConvertDoubleTo64(double value, _Out_ __int64* res);

HKGAPI __inline HKNOALIAS_USEWITHCAUTION void
ConvertDoubleTo128(double value, _Out_ HkInt128* res);


HKGAPI __inline HKNOALIAS_USEWITHCAUTION void
hk_ConvertDoubleTo128(double value, _Out_ HkInt128* res);

HKGAPI __inline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvertDoubleTo64WithScale64(double value, __int64 scale, _Out_ __int64* res);
HKGAPI __inline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvertDoubleTo128WithScale64(double value, __int64 scale, _Out_ HkInt128* res);
HKGAPI __inline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvertDoubleTo128WithScale128(double value, HkInt128 const* scale, _Out_ HkInt128* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftRight128To64Unsafe(HkInt128 const* value, unsigned char shift, _Out_ __int64* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftRight256To64Unsafe(HkInt256 const* value, unsigned char shift, _Out_ __int64* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftRight128To128(HkInt128 const* value, unsigned char shift, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftRight256To128Unsafe(HkInt256 const* value, unsigned char shift, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftRight256To256(HkInt256 const* value, unsigned char shift, _Out_ HkInt256* result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft64To128Unsafe(__int64 value, unsigned char shift, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft64To256Unsafe(__int64 value, unsigned char shift, _Out_ HkInt256* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft64To320Unsafe(__int64 value, unsigned char shift, _Out_ HkInt320* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft128To320Unsafe(HkInt128* input, unsigned char shift, _Out_ HkInt320* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft128To128Unsafe(HkInt128 const* input, unsigned char shift, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft128To256Unsafe(HkInt128 const* input, unsigned char shift, _Out_ HkInt256* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft256To256Unsafe(HkInt256 const* input, unsigned char shift, _Out_ HkInt256* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShiftLeft320To320Unsafe(HkInt320 const* input, unsigned char shift, _Out_ HkInt320* result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal128And64(HkInt128 const volatile* a, __int64 b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal64And128(__int64 a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal128And128(HkInt128 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
Equal128And256(HkInt128 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual128And64(HkInt128 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual64And128(__int64 a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual128And128(HkInt128 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
NotEqual128And256(HkInt128 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan128And64(HkInt128 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan64And128(__int64 a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan128And128(HkInt128 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan128And256(HkInt128 const* a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThan256And256(HkInt256 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan128And64(HkInt128 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan64And128(__int64 a, HkInt128 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan128And128(HkInt128 const volatile* a, HkInt128 const volatile* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan128And256(HkInt128 const* a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThan256And256(HkInt256 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo128And64(HkInt128 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo64And128(__int64 a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo128And128(HkInt128 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
LessThanOrEqualTo128And256(HkInt128 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo128And64(HkInt128 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo64And128(__int64 a, HkInt128 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo128And128(HkInt128 const volatile* a, HkInt128 const volatile* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo256And64(HkInt256 const* a, __int64 b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo64And256(__int64 a, HkInt256 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo256And128(HkInt256 const* a, HkInt128 const* b);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
GreaterThanOrEqualTo128And256(HkInt128 const* a, HkInt256 const* b);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsNeg128(HkInt128 const* a);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsZero128(HkInt128 const* a);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsNeg256(HkInt256 const* a);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Negate64(__int64 input, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Negate128Unsafe(HkInt128 const* input, _Out_ HkInt128* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
BitFlip128(HkInt128 const* input, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
BitFlip256(HkInt256 const* input, _Out_ HkInt256* result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or128And64(_In_ HkInt128 const* input1, _In_ __int64 input2, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or128And128(_In_ HkInt128 const* input1, _In_ HkInt128 const* input2, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or256And128(_In_ HkInt256 const* input1, _In_ HkInt128 const* input2, _Out_ HkInt256* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or256And256(_In_ HkInt256 const* input1, _In_ HkInt256 const* input2, _Out_ HkInt256* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or320And256(_In_ HkInt320 const* input1, _In_ HkInt256 const* input2, _Out_ HkInt320* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Or320And320(_In_ HkInt320 const* input1, _In_ HkInt320 const* input2, _Out_ HkInt320* result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
And128And64(_In_ HkInt128 const* input1, _In_ __int64 input2, _Out_ __int64* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
And128And128(_In_ HkInt128 const* input1, _In_ HkInt128 const* input2, _Out_ HkInt128* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
And256And64(_In_ HkInt256 const* input1, _In_ __int64 input2, _Out_ __int64* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
And256And128(_In_ HkInt256 const* input1, _In_ HkInt128 const* input2, _Out_ HkInt128* result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add64And64(__int64 a, __int64 b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Add128And64(HkInt128 const* a, __int64 b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Add64And128(__int64 a, HkInt128 const* b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Add128And128(HkInt128 const* a, HkInt128 const* b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add128And256Unsafe(HkInt128 const* a, HkInt256 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add256And64Unsafe(HkInt256 const* a, __int64 b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add256And128Unsafe(HkInt256 const* a, HkInt128 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add256And192Unsafe(HkInt256 const* a, HkInt192 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add256And256Unsafe(HkInt256 const* a, HkInt256 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Add256And256(HkInt256 const* a, HkInt256 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add320And64Unsafe(HkInt320 const* a, __int64 b, _Out_ HkInt320* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add320And128Unsafe(HkInt320 const* a, HkInt128 const* b, _Out_ HkInt320* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Add320And320Unsafe(HkInt320 const* a, HkInt320 const* b, _Out_ HkInt320* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Subtract64And64(__int64 a, __int64 b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Subtract128And64(HkInt128 const* a, __int64 b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Subtract64And128(__int64 a, HkInt128 const* b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Subtract128And128(HkInt128 const* a, HkInt128 const* b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Subtract256And64(HkInt256 const* a, __int64 b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Subtract256And128(HkInt256 const* a, HkInt128 const* b, _Out_ HkInt256* res);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Multiply64By64Res64(__int64 a, __int64 b, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Multiply64By64(__int64 a, __int64 b, HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Multiply128By64(HkInt128 const* a, __int64 b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Multiply64By128(__int64 a, HkInt128 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Multiply128By128(HkInt128 const* a, HkInt128 const* b, _Out_ HkInt256* res);


#if __cplusplus
HKNOALIAS_USEWITHCAUTION void
Multiply128By128(HkInt128 const& a, HkInt128 const& b, _Out_ HkInt256* res);
#endif

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Multiply128By192(HkInt128 const* a, HkInt192 const* b, _Out_ HkInt256* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Multiply64By192(__int64 a, HkInt192 const* b, _Out_ HkInt256* res);


HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide64By64(__int64 a, __int64 b, _Out_ __int64* result);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64Unsafe(HkInt128 const* a, __int64 b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By128Unsafe(HkInt128 const* a, HkInt128 const* b, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide256By64(HkInt256 const* a, __int64 b, _Out_ HkInt128* res);
HKGAPI _Check_return_ HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide256By128(HkInt256 const* a, HkInt128 const* b, _Out_ HkInt128* res);


#if __cplusplus
_Check_return_ HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide256By128(HkInt256 const& a, HkInt128 const& b, _Out_ HkInt128* res);
#endif

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Modulo64By64(__int64 a, __int64 b, _Out_ __int64* res, _Out_ __int64* rem);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Modulo64By128Unsafe(__int64 a, HkInt128 const* b, _Out_ __int64* rem);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Modulo128By64Unsafe(HkInt128 const* a, __int64 b, _Out_ __int64* rem);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Modulo128By128Unsafe(HkInt128 const* a, HkInt128 const* b, _Out_ HkInt128* rem);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide64By64Rec(__int64 a, unsigned __int64 b, unsigned __int64 x, _Out_ __int64* res, enum DivRecExactness exact);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide64By64RecTruncDown(__int64 a, unsigned __int64 b, unsigned __int64 x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64RecUnsafeTruncDown(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64RecTruncDown(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By128RecUnsafeTruncDown(HkInt128 const* a, HkInt128 const* b, unsigned __int64 x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide64By64RecTruncUp(__int64 a, unsigned __int64 b, unsigned __int64 x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64RecUnsafeTruncUp(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64RecTruncUp(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ HkInt128* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By128RecUnsafeTruncUp(HkInt128 const* a, HkInt128 const* b, unsigned __int64 x, _Out_ __int64* res);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide64By64RecTruncDownRem(__int64 a, unsigned __int64 b, unsigned __int64 x, _Out_ __int64* res, _Out_ __int64* rem);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
Divide128By64RecUnsafeTruncDownRem(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ __int64* res, _Out_ __int64* rem);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide128By64RecUnsafe(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ __int64* res, enum DivRecExactness exact);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide128By64Rec(HkInt128 const* a, unsigned __int64 b, HkInt128 const* x, _Out_ HkInt128* res, enum DivRecExactness exact);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide128By128RecUnsafe(HkInt128 const* a, HkInt128 const* b, unsigned __int64 x, _Out_ __int64* res, enum DivRecExactness exact);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide256By64Rec(HkInt256 const* a, unsigned __int64 b, HkInt192 const* x, _Out_ HkInt128* res, enum DivRecExactness exact);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
Divide256By128Rec(HkInt256 const* a, HkInt128 const* b, HkInt192 const* x, _Out_ HkInt128* res, enum DivRecExactness exact);



HKGAPI __forceinline _Check_return_ double
hk_Atn2(double x, double y);
HKGAPI __forceinline _Check_return_ double
hk_Degrees(double x);
HKGAPI __forceinline _Check_return_ double
Radians(double x);
HKGAPI __forceinline _Check_return_ double
hk_Square(double x);

HKGAPI __forceinline _Check_return_ HRESULT
YieldCheck(_In_ HkProcContext* hkcontext, unsigned int yc, unsigned long lineNo);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
RTrimBinary(_In_reads_(length) const unsigned char *value, unsigned long length);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
RTrimChar(_In_reads_(length) const unsigned char *value, unsigned long length);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
RTrimWChar(_In_reads_(length) const unsigned char *value, unsigned long length);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
LTrimChar(_In_reads_(length) const unsigned char *value, unsigned long length);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
LTrimWChar(_In_reads_(length) const unsigned char *value, unsigned long length);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
LTrimVarcharLob(_In_ HkProcContext* hkcontext, _In_ HkILBHandle * ilbh, _Out_ HkILBHandle ** handle);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
LTrimNVarcharLob(_In_ HkProcContext* hkcontext, _In_ HkILBHandle * ilbh, _Out_ HkILBHandle ** handle);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
RTrimVarcharLob(_In_ HkProcContext* hkcontext, _In_ HkILBHandle * ilbh, _Out_ HkILBHandle ** handle);
HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
RTrimNVarcharLob(_In_ HkProcContext* hkcontext, _In_ HkILBHandle * ilbh, _Out_ HkILBHandle ** handle);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
TrimOneArgStr(_In_reads_bytes_(length) unsigned char* stringToTrim, unsigned long length, _Inout_ HkPal* result);
HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
TrimOneArgWstr(_In_reads_bytes_(length) unsigned char* stringToTrim, unsigned long length, _Inout_ HkPal* result);
HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
TrimOneArgStrLob(_In_ HkProcContext* hkContext, _In_ HkILBHandle * stringToTrim, _Out_ HkILBHandle ** result);
HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
TrimOneArgWstrLob(_In_ HkProcContext* hkContext, _In_ HkILBHandle * stringToTrim, _Out_ HkILBHandle ** result);

HKGAPI HKNOALIAS_USEWITHCAUTION void
ConcatWsStr(
	_In_reads_(size) unsigned char** stringsToConcat,
	_In_reads_(size) unsigned long* length,
	_In_reads_(size) bool* isNull,
	unsigned long size,
	_Inout_ HkPal* result);

HKGAPI HKNOALIAS_USEWITHCAUTION void
ConcatWsWstr(
	_In_reads_(size) unsigned char** stringsToConcat,
	_In_reads_(size) unsigned long* length,
	_In_reads_(size) bool* isNull,
	unsigned long size,
	_Inout_ HkPal* result);

HKGAPI HKNOALIAS_USEWITHCAUTION HRESULT
ConcatWsLob(
	_In_ HkProcContext* context,
	_In_reads_(size) HkILBHandle** stringsToConcat,
	_In_reads_(size) bool* isNull,
	unsigned long size,
	_Inout_ HkILBHandle ** result);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsDBCSLeadChar_CP932(const unsigned char* character);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsDBCSLeadChar_CPOther(const unsigned char* character);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ bool
IsHighSurrogateWChar(const unsigned char* value);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
LenCharDBCS_CP932(
	_In_reads_(length) const unsigned char* value, long length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
LenCharDBCS_CPOther(
	_In_reads_(length) const unsigned char* value, long length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_String(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_WideString(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_WCharUTF16(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_WCharUTF16VSA(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_CharDBCS_CP932(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned long
GetLobLen_CharDBCS_CPOther(HkILBHandle* lob);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_String(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_WideString(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_WCharUTF16(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_WCharUTF16VSA(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_CharDBCS_CP932(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
GetLobSubstring_CharDBCS_CPOther(_In_ HkProcContext* hkcontext, _In_ HkILBHandle* ilbh, __int64 charOffset, __int64 charLength, _Out_ HkILBHandle** handle);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
LenWChar(_In_reads_(length) const unsigned char* value, long length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
LenWCharUTF16(_In_reads_(length) const unsigned char* value, long length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
LenWCharUTF16VSA(_In_reads_(length) const unsigned char* value, long length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
ShrinkSubstrLenToFit(_Inout_ __int64 *offset, _Inout_ __int64 *length);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
GetSubstringOffsetAndLengthDBCS_CP932(
	_In_reads_(stringLength) const unsigned char* value,
	long stringLength,
	__int64 charOffset,
	__int64 charLength,
	long maxByteLength,
	_Out_ unsigned short* byteOffset,
	_Out_ unsigned short* byteLength);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
GetSubstringOffsetAndLengthDBCS_CPOther(
	_In_reads_(stringLength) const unsigned char* value,
	long stringLength,
	__int64 charOffset,
	__int64 charLength,
	long maxByteLength,
	_Out_ unsigned short* byteOffset,
	_Out_ unsigned short* byteLength);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
GetSubstringOffsetAndLengthUTF16(
	_In_reads_(stringLength) const unsigned char* value,
	long stringLength,
	__int64 charOffset,
	__int64 charLength,
	long maxByteLength,
	_Out_ unsigned short* byteOffset,
	_Out_ unsigned short* byteLength);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
GetSubstringOffsetAndLengthUTF16VSA(
	_In_reads_(stringLength) const unsigned char* value,
	long stringLength,
	__int64 charOffset,
	__int64 charLength,
	long maxByteLength,
	_Out_ unsigned short* byteOffset,
	_Out_ unsigned short* byteLength);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
GetDBCSTruncLen_CP932(unsigned char* value, long srclen);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ unsigned short
GetDBCSTruncLen_CPOther(unsigned char* value, long srclen);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
GetByteLengthOfTrailingHighSurrogate(
	long oldByteLength,
	_In_reads_(oldByteLength) unsigned char* value,
	long newByteLength);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION _Check_return_ long
GetByteLengthOfTrailingBrokenVariationSequence(
	long oldByteLength,
	_In_reads_(oldByteLength) unsigned char* value,
	long newByteLength);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvCharToBit(
	_In_reads_bytes_(strLength) const unsigned char*	str,
	_In_ long									strLength,
	_Out_ __int64*								intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvWCharToBit(
	_In_reads_bytes_(strLength) const unsigned char*	str,
	_In_ long									strLength,
	_Out_ __int64*								intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvCharToInt(
	_In_reads_bytes_(strLength) const unsigned char*	str,
	_In_ long								strLength,
	_Out_ __int64*								intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvWCharToInt(
	_In_reads_bytes_(strLength) const unsigned char*	str,
	_In_ long									strLength,
	_Out_ __int64*								intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvCharToLargeNumeric(
	_In_reads_bytes_(strLength)const unsigned char*  str,
	_In_ long							strLength,
	_In_ unsigned short							prec,
	_In_ unsigned short							scale,
	_Out_ HkInt128*						intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvWCharToLargeNumeric(
	_In_reads_bytes_(strLength)const unsigned char*  str,
	_In_ long									strLength,
	_In_ unsigned short							prec,
	_In_ unsigned short							scale,
	_Out_ HkInt128*						intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvCharToNumeric(
	_In_reads_bytes_(strLength)const unsigned char*  str,
	_In_ long									strLength,
	_In_ unsigned short							prec,
	_In_ unsigned short							scale,
	_Out_ __int64*								intValue);

HKGAPI HKNOALIAS_USEWITHCAUTION _Check_return_ HRESULT
ConvWCharToNumeric(
	_In_reads_bytes_(strLength)const unsigned char*  str,
	_In_ long									strLength,
	_In_ unsigned short							prec,
	_In_ unsigned short							scale,
	_Out_ __int64*								intValue);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hkmemcpy_s(
	_Out_writes_bytes_to_(destSize, srcSize) void* dest,
	size_t destSize,
	_In_reads_bytes_(srcSize) const void* src,
	size_t srcSize);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hkmemcpy_s_ex(
	__deref_inout_bcount_part(*destSize, srcSize) unsigned char** dest,
	_Inout_ size_t* destSize,
	_In_reads_bytes_(srcSize) const void* src,
	size_t srcSize);


#if __cplusplus
template <size_t _Size, typename _DstType>
__forceinline HKNOALIAS_USEWITHCAUTION void
hkmemcpy_s(_DstType (&dest)[_Size], _In_reads_bytes_(srcSize) const void* src, size_t srcSize)
{
	return hkmemcpy_s(dest, _Size * sizeof(_DstType), src, srcSize);
}
#endif

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hkwmemset(_Out_writes_bytes_(_N) void* _S, wchar_t _C, size_t _N);




HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hkwmemset_s_ex(
	__deref_inout_bcount_part(*bufferLength, _N * sizeof(wchar_t)) unsigned char** bufferPtr,
	_Inout_ size_t* bufferLength,
	wchar_t _C,
	size_t _N);

HKGAPI __forceinline HKNOALIAS_USEWITHCAUTION void
hkmemset_s_ex(
	__deref_inout_bcount_part(*bufferLength, _N) unsigned char** bufferPtr,
	_Inout_ size_t* bufferLength,
	char _C,
	size_t _N);

HKGAPI __forceinline void
ReportStmtStarted(_Inout_opt_ IHkStatementPerf* stmtPerf);

HKGAPI __forceinline void
ReportStmtEnded(_Inout_opt_ IHkStatementPerf* stmtPerf, unsigned long qindex, HRESULT execResult);

HKGAPI __forceinline void
SetStmtRowCount(_Inout_opt_ IHkStatementPerf* stmtPerf, unsigned long qindex, __int64 rowCount);

HKGAPI __forceinline void
MeasureAndAggregateElapsedTime(
	_In_opt_ IHkStatementExecStats* stmtExecStats,
	_Inout_updates_(arrayLengths) __int64* actualTicks,
	_Inout_updates_(arrayLengths) __int64* actualCpuTicks,
	unsigned long arrayLengths,
	long qOpNodeId,
	unsigned long qindex);

HKGAPI __forceinline _Check_return_ HRESULT
GenerateStmtStatistics(
	_In_opt_ IHkStatementExecStats* stmtExecStats,
	_In_reads_(arrayLengths) __int64* actualExecs,
	_In_reads_(arrayLengths) __int64* actualRows,
	_In_reads_(arrayLengths) __int64* actualTicks,
	_In_reads_(arrayLengths) __int64* actualCpuTicks,
	unsigned long arrayLengths,
	unsigned long qindex);




HKGAPI __forceinline void*
GetSortBufElem(_In_ void* context, long dirPageIndex);



HKGAPI __forceinline void*
GetTopSortBufElem(_In_ void* context, long index);



HKGAPI __forceinline _Check_return_ HkCompareContext*
FetchCompareContext(_In_ void* context);

HKGAPI _Check_return_ HRESULT
SendOptimizedMetadata(
	_In_ HkProcContext*		hkcontext,
	_In_ HkOutputMetadata*	hkoutput);

HKGAPI void
EndOptimizedResultSet(_In_ HkProcContext* hkcontext);

HKGAPI _Check_return_ HRESULT
StartRow(_In_ HkProcContext* hkcontext);

HKGAPI void
EndRow(_In_ HkProcContext* hkcontext);

HKGAPI _Check_return_ HRESULT
SendReturnStatus(_In_ HkProcContext* hkContext, __int64 status);

HKGAPI _Check_return_ HRESULT
SendReturnValueMetadata(_In_ HkProcContext* hkContext, _In_ const unsigned char* const* metadata, _In_ const unsigned short* metadataLength);

HKGAPI _Check_return_ HRESULT
SendUChar(_In_ HkProcContext* hkcontext, unsigned char value);

HKGAPI _Check_return_ HRESULT
SendNullableUChar(_In_ HkProcContext* hkcontext, unsigned char value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendShort(_In_ HkProcContext* hkcontext, short value);

HKGAPI _Check_return_ HRESULT
SendNullableShort(_In_ HkProcContext* hkcontext, short value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendLong(_In_ HkProcContext* hkcontext, long value);

HKGAPI _Check_return_ HRESULT
SendNullableLong(_In_ HkProcContext* hkcontext, long value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendFloat(_In_ HkProcContext* hkcontext, float value);

HKGAPI _Check_return_ HRESULT
SendNullableFloat(_In_ HkProcContext* hkcontext, float value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendDouble(_In_ HkProcContext* hkcontext, double value);

HKGAPI _Check_return_ HRESULT
SendNullableDouble(_In_ HkProcContext* hkcontext, double value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendBigInt(_In_ HkProcContext* hkcontext, __int64 value);

HKGAPI _Check_return_ HRESULT
SendNullableBigInt(_In_ HkProcContext* hkcontext, __int64 value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendMoney(_In_ HkProcContext* hkcontext, __int64 value);

HKGAPI _Check_return_ HRESULT
SendNullableMoney(_In_ HkProcContext* hkcontext, __int64 value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendDateTime(_In_ HkProcContext* hkcontext, __int64 value);

HKGAPI _Check_return_ HRESULT
SendNullableDateTime(_In_ HkProcContext* hkcontext, __int64 value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendSmallDateTime(_In_ HkProcContext* hkcontext, long value);

HKGAPI _Check_return_ HRESULT
SendNullableSmallDateTime(_In_ HkProcContext* hkcontext, long value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendNumeric(_In_ HkProcContext* hkcontext, __int64 value);

HKGAPI _Check_return_ HRESULT
SendNullableNumeric(_In_ HkProcContext* hkcontext, __int64 value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendLargeNumeric(_In_ HkProcContext* hkcontext, HkInt128 value);

HKGAPI _Check_return_ HRESULT
SendNullableLargeNumeric(_In_ HkProcContext* hkcontext, HkInt128 value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendDate(_In_ HkProcContext* hkcontext, long value);

HKGAPI _Check_return_ HRESULT
SendNullableDate(_In_ HkProcContext* hkcontext, long value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendTime(_In_ HkProcContext* hkcontext, __int64 value, long scale);

HKGAPI _Check_return_ HRESULT
SendNullableTime(_In_ HkProcContext* hkcontext, __int64 value, long scale, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendDateTime2(_In_ HkProcContext* hkcontext, __int64 value, long scale);

HKGAPI _Check_return_ HRESULT
SendNullableDateTime2(_In_ HkProcContext* hkcontext, __int64 value, long scale, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendGuid(_In_ HkProcContext* hkcontext, HkSixteenByteData value);

HKGAPI _Check_return_ HRESULT
SendNullableGuid(_In_ HkProcContext* hkcontext, HkSixteenByteData value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendPal(_In_ HkProcContext* hkcontext, HkPal value);

HKGAPI _Check_return_ HRESULT
SendNullablePal(_In_ HkProcContext* hkcontext, HkPal value, unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SendLockBytes(
	_In_ HkProcContext* hkcontext,
	_In_ HkILBHandle* value,
	long textSize,
	size_t sizeOfChar,
	_In_opt_ bool (*isDBCSLeadChar) (const unsigned char*),
	bool isVariationSelectorAware);

HKGAPI _Check_return_ HRESULT
SendNullableLockBytes(
	_In_ HkProcContext* hkcontext,
	_In_ HkILBHandle* value,
	long textSize,
	size_t sizeOfChar,
	_In_opt_ bool(*isDBCSLeadChar) (const unsigned char*),
	bool isVariationSelectorAware,
	unsigned char isNull);

HKGAPI _Check_return_ HRESULT
SkipBytes(_In_ HkProcContext* hkcontext, unsigned long len);

HKGAPI _Check_return_ HRESULT
EndTdsParse(_In_ HkProcContext* hkContext);

HKGAPI _Check_return_ HRESULT
ReadHkInt(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, long defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkBigInt(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkSmallInt(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, short defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkTinyInt(_In_ HkProcContext* hkContext, _Out_ unsigned __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, unsigned char defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkBit(_In_ HkProcContext* hkContext, _Out_ unsigned __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, unsigned char defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkFloat(_In_ HkProcContext* hkContext, _Out_ float* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, float defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkDouble(_In_ HkProcContext* hkContext, _Out_ double* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, double defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkSmallMoney(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, long defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkMoney(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkNumeric(_In_ HkProcContext* hkContext, _Out_ __int64* value, long prec, long scale, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkLargeNumeric(_In_ HkProcContext* hkContext, _Out_ HkInt128* value, long prec, long scale, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkInt128* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkSmallDateTime(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, long defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkDateTime(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkDate(_In_ HkProcContext* hkContext, _Out_ __int64* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, long defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkTime(_In_ HkProcContext* hkContext, _Out_ __int64* value, long scale, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkDateTime2(_In_ HkProcContext* hkContext, _Out_ __int64* value, long scale, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, __int64 defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkGuid(_In_ HkProcContext* hkContext, _Out_ HkSixteenByteData* value, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkSixteenByteData* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkChar(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkVarChar(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkWChar(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkVarWChar(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkBin(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkVarBin(_In_ HkProcContext* hkContext, _Out_ HkPal* value, unsigned short maxLength, _Out_ unsigned char* isNull, unsigned char isOutputParam, unsigned char isDefaultParam, _In_ HkPal* defaultParam, unsigned char isDefaultNull);

HKGAPI _Check_return_ HRESULT
ReadHkMaxType(
	_In_ HkProcContext* hkContext,
	_Out_ HkILBHandle* value,
	unsigned short maxLength,
	_Out_ unsigned char* isNull,
	unsigned char isOutputParam,
	unsigned char isDefaultParam,
	_In_ HkILBHandle* defaultParam,
	unsigned char isDefaultNull,
	unsigned char tdsToken);

HKGAPI _Check_return_ HRESULT
AllocMemory(_In_ HkProcContext* hkContext, unsigned long bufferSize, __deref_out_opt void** buffer);




HKGAPI _Check_return_ int
IfUpdate(_In_opt_ unsigned char* bitVector, bool defaultForBitVector, int columnId);




HKGAPI _Check_return_ HRESULT
PopulateLob(_In_ HkLockBytes* dest, _In_ HkILBHandle* src);




HKGAPI void
ReleaseLob(_In_ HkILBHandle* lob);




HKGAPI void
AddRefLob(_In_ HkILBHandle* lob);





HKGAPI _Check_return_ HRESULT
CopyHkILBHandleToOutputParam(
	_In_ HkProcContext* hkContext,
	 HkILBHandle** src,
	unsigned long lobOutParamInd,
	bool isNull);




typedef _Check_return_ HRESULT
(*LobAndOffRowDeleteFn)(
	_In_ HkTransaction* tx,
	_In_ HkRow const* hkRow);




HKGAPI _Check_return_ HRESULT
DeleteLobsAndOffRowColumns(
	_In_ HkTransaction* tx,
	_In_ HkTxDeltaTracker* tracker,
	_In_ HkTable* table,
	_In_ LobAndOffRowDeleteFn lobAndOffRowDeleteFn);




HKGAPI _Check_return_ HkStringUtils*
GetUtf16StringUtils(void);





HKGAPI _Check_return_ HkStringUtils*
GetUtf16VsaStringUtils(void);




HKGAPI _Check_return_ HkStringUtils*
GetDbcsCp932StringUtils(void);




HKGAPI _Check_return_ HkStringUtils*
GetDbcsOtherStringUtils(void);