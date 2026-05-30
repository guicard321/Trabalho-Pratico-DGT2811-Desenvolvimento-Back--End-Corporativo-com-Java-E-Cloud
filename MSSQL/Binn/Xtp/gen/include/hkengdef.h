//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************



















#pragma once

#if HKCODEGEN








#ifndef _Analysis_assume_
#define _Analysis_assume_(...)
#define _Check_return_
#define _Deref_out_range_(...)
#define _In_
#define _In_opt_
#define _In_reads_(x)
#define _In_reads_bytes_(x)
#define _Inout_
#define _Inout_opt_
#define _Inout_updates_(x)
#define _Inout_updates_bytes_(x)
#define _Must_inspect_result_
#define _Null_terminated_
#define _Out_
#define _Out_opt_
#define _Out_writes_(x)
#define _Out_writes_bytes_(x)
#define _Out_writes_bytes_to_(x, y)
#define _Outptr_
#define _Outptr_result_buffer_(x)
#define _Outptr_result_bytebuffer_(x)
#define _Return_type_success_(...)
#define _Success_(x)
#define __callback
#define __checkReturn
#define __deref_inout_bcount_part(x, y)
#define __deref_opt_out
#define __deref_out
#define __deref_out_bcount(x)
#define __deref_out_ecount(x)
#define __deref_out_ecount_opt(x)
#define __deref_out_opt
#define __deref_out_range(x, y)
#define __in
#define __in_bcount(x)
#define __in_ecount(x)
#define __in_opt
#define __inout
#define __inout_bcount(x)
#define __inout_ecount(x)
#define __inout_opt
#define __nullterminated
#define __out
#define __out_bcount(x)
#define __out_bcount_part(x, y)
#define __out_ecount(x)
#define __out_opt
#define __success(x)
#endif



typedef long HRESULT;
typedef unsigned __int64 ULONG_PTR;
#if !__cplusplus
typedef unsigned char bool;
typedef unsigned short wchar_t;
#endif

#endif 

typedef struct HkCallbackContext HkCallbackContext;
typedef struct HkCursorDeltaTracker HkCursorDeltaTracker;
typedef struct HkCursorHash HkCursorHash;
typedef struct HkCursorHashParent HkCursorHashParent;
typedef struct HkCursorHeap HkCursorHeap;
typedef struct HkCursorHeapParent HkCursorHeapParent;
typedef struct HkCursorRange HkCursorRange;
typedef struct HkCursorRangeParent HkCursorRangeParent;
typedef struct HkDatabase HkDatabase;
typedef struct HkErrorObject HkErrorObject;
typedef struct HkLockBytes HkLockBytes;
typedef struct HkParam HkParam;
typedef struct HkRow HkRow;
typedef struct HkTransaction HkTransaction;
typedef struct HkTxDeltaTracker HkTxDeltaTracker;
typedef struct TxStatusStruct TxStatusStruct;







typedef struct HkSearchKey HkSearchKey;
typedef struct HkFlatKey HkFlatKey;




static unsigned int const ScanAllHeaps = (unsigned int) -1 ;








static unsigned long const MaxSampleRate = 10000;











typedef enum
{
	isoReadUncommitted,
	isoSnapshot,
	isoReadRepeatable,
	isoSerializable,
} TxIsoLevel;




typedef enum
{
	internalTableLobTable = 0x1,
	internalTableOffRowDataTable = 0x2, 
} HkInternalTablesForTableVariable;




typedef struct HkInt128
{
	
	__int64	val[2];
} HkInt128;




typedef struct HkInt256
{
	
	__int64	val[4];
} HkInt256;



typedef struct HkInt320
{
	
	__int64 val[5];
} HkInt320;













typedef struct HkInt192
{
	__int64 val[3];
} HkInt192;



typedef unsigned long HkTxSavePointId;



static const HkTxSavePointId HkTxSavePointDefault = 0;






























typedef unsigned int HkTableId;



typedef __int64 HkLobId;



#if !defined(HKEAPI)
	#if defined(HKENGINE_BUILD)
		#define HKEAPI extern "C" __declspec(dllexport)
	#else
		#if defined(__cplusplus)
			#define HKEAPI extern "C" __declspec(dllimport)
		#else
			#define HKEAPI __declspec(dllimport)
		#endif
	#endif
#endif





#define HKAPICC __cdecl

HKEAPI _Check_return_ const TxStatusStruct* HKAPICC
HkTransactionGetStatus(
	_In_ HkTransaction* tx);

HKEAPI void HKAPICC
HkTransactionDeltaTrackerSetEnd(
	_Inout_ HkTxDeltaTracker* tracker);



typedef __callback void
(*TxRundownCallbackFn)(
	_Inout_ TxStatusStruct* status,
	_In_ HkTransaction* tx);



typedef __callback void
(*TxCommitCallbackFn)(
	_In_ const TxStatusStruct* status,
	_In_ void* data);




typedef __callback void
(*TxPostCommitCallbackFn)(
	_In_ void* param,
	_In_ HRESULT reason);

typedef _Check_return_ HRESULT
(*FilterFn)(
	_In_ const HkParam* params,
	_In_ const HkRow* row,
	_In_ HkCallbackContext* context);

HKEAPI _Check_return_ HRESULT HKAPICC
HkDatabaseCreateNewLob(
	_In_ HkDatabase* db,
	_In_opt_ HkErrorObject* errorObject,
	_Out_ HkLockBytes** hkLockBytes);
