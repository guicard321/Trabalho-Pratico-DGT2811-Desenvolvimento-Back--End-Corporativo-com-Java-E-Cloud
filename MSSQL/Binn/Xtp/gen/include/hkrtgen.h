//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************















#pragma once

#include "hkrtdef.h"

typedef struct HkEsInfoObj HkEsInfoObj;
typedef struct HkIteratorStvf HkIteratorStvf;
typedef struct HkTableMD HkTableMD;
typedef struct HkTopSortContext HkTopSortContext;
typedef struct HkUdeHelper HkUdeHelper;



typedef struct HkCollationInfo
{
	
	
	unsigned int CountCollations;

	
	
	HkCollationType *CollationTypes;

	
	
	
	HkCollationCallback **CollationCallbacks;
} HkCollationInfo;



typedef struct HkTableBindings
{
	
	
	unsigned __int64 MdVersion;

	
	
	HkTableMD *TableMD;

	
	
	HkCollationInfo CollationInfo;
} HkTableBindings;



typedef struct HkProcBindings
{
	
	
	HkTable **Tables;

	
	
	HkTable **DRTables;

	
	
	HkSequenceObj **SeqObjs;

	
	
	HkCollationInfo CollationInfo;

	
	
	long ProcId;

	
	
	HkProcInfo *ProcInfo;

	
	
	unsigned int *TableIdsStabilize;
} HkProcBindings;



typedef struct HkSearchInterval
{
	HkSearchKey const *StartKey;
	HkSearchKey const *EndKey;
#if defined(__cplusplus)
	static const bool isTest = false;
#endif
} HkSearchInterval;



#ifndef GOLDEN_BITS

typedef struct HkSearchIntervalTest
{
	HkSearchKey const *StartKey;
	HkSearchKey const *EndKey;
	unsigned short NullExtendedColumnIdxStart;
	unsigned short NullExtendedColumnIdxEnd;
#if defined(__cplusplus)
	static const bool isTest = true;
#endif
} HkSearchIntervalTest;

#endif

typedef struct HkCompareContext
{
	
	
	HkErrorObject *ErrorObject;

	
	
	unsigned char *DeepDataBuffer;

	
	
	HkTransaction *Transaction;

	
	
	HkTransaction *TableVarTransaction;

	
	
	HkTable **TableVars;

	
	
	HkTable **TableParams;

	
	
	const void *Params;
} HkCompareContext;

typedef struct HkSortContextCommon
{
	
	
	
	
	HkCompareContext *CmpContext;
	int(__cdecl * SortCompare)(void*, const void*, const void*);
	void(__cdecl * LobRelease)(void*);
	void *SortBuffer;
	void *DeepBuffer;
	long *PqLocation;
	size_t SortBufElemSize;
	size_t DeepBufferFreePosition;
	unsigned long MaxRows;
	unsigned long CurrentRowCount;
	unsigned long RowsProcessedSinceLastYield;
} HkSortContextCommon;

typedef struct HkSortContext
{
	
	
	HkSortContextCommon CommonContext;
	unsigned char DirectoryPageAllocated;
	long PagesAllocated;
	long PageIndex;
	HRESULT(__cdecl * BaseCompare)(void*, const void*, const void*, __int64*);
	HRESULT(__cdecl * PqCompare)(void*, long, long, __int64*);
} HkSortContext;

struct HkTopSortContext
{
	
	
	HkSortContextCommon CommonContext;
	void *TiesBuffer;
	void *CurrentPage;
	unsigned long TopNValue;
	unsigned long CurrentRowIndex;
};



HKRAPI _Check_return_ HkILBHandle*
	InitializeHkPalWrappingLockBytesBuffer(
	_In_reads_bytes_(bufferLength) HkPalWrappingLockBytesBuffer * buffer,
	unsigned long bufferLength,
	_In_reads_bytes_(pointerLength) unsigned char *pointer,
	unsigned long pointerLength);



HKRAPI _Check_return_ HRESULT
	AllocateHkPalWrappingLockBytes(
	_In_ HkProcContext * hkcontext,
	_In_reads_bytes_(pointerLength) unsigned char *pointer,
	unsigned long pointerLength,
	_Out_ HkILBHandle * *handle);



HKRAPI _Check_return_ HRESULT
AllocateHkConcatWrappingLockBytes(
	_In_ HkProcContext *hkcontext,
	_In_ HkILBHandle   *left,
	_In_ HkILBHandle   *right,
	_Out_ HkILBHandle  **handle);






HKRAPI _Check_return_ HRESULT
SendNonOptimizedMetadata(
	_In_ HkProcContext	  *hkcontext,
	_In_ HkOutputMetadata *hkoutput);

HKRAPI _Check_return_ HRESULT
SendNonOptimizedOutput(
	_In_ HkProcContext *hkcontext,
	bool			   isEndOfResultSet);

HKRAPI void
EndNonOptimizedResultForError(_In_ HkProcContext *hkcontext);

HKRAPI _Check_return_ HRESULT
HkRtCreateTempTable(
	_In_ HkProcContext	 *hkcontext,
	_In_ HkTableMD const *tableMd,
	_Outptr_ HkTable	 **table);

HKRAPI _Check_return_ HRESULT
ExecuteNestedModule(
	_In_ HkProcContext	   *hkcontext,
	int					   dbid,
	int					   objid,
	_In_opt_ HkValue	   *valueArray,
	_In_opt_ unsigned char *nullArray,
	_In_opt_ HkTable	   **tvps);

HKRAPI _Check_return_ HRESULT
HostConvert(
	_In_ HkErrorObject *errorObj,
	unsigned char	   fWarnTrunc,
	long			   style,
	unsigned char	   dateFormat,
	unsigned char	   toType,
	unsigned char	   toPrecision,
	unsigned char	   toScale,
	unsigned short	   toMaxLength,
	unsigned long	   toCollation,
	_Out_ HkValue	   *toValue,
	unsigned char	   fromType,
	unsigned char	   fromPrecision,
	unsigned char	   fromScale,
	unsigned short	   fromMaxLength,
	unsigned long	   fromCollation,
	HkValue			   fromValue);

HKRAPI _Check_return_ __int64
GetDateTime(void);

HKRAPI _Check_return_ __int64
GetUTCDateTime(void);

HKRAPI _Check_return_ HRESULT
GetDateTime2(
	_Out_ __int64	   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ __int64
GetUTCDateTime2(void);

HKRAPI _Check_return_ int
CurrentDate(void);

HKRAPI _Check_return_ HRESULT
	GetUserId(
	_In_ HkErrorObject * errorObj,
	_In_reads_bytes_(usernameLength) unsigned char *username,
	int usernameLength,
	_Out_ short *userid);

HKRAPI _Check_return_ HRESULT
	GetUserIdEx(
	_In_ HkErrorObject * errorObj,
	_In_reads_bytes_(usernameLength) unsigned char *username,
	int usernameLength,
	_Out_ int *userid);

HKRAPI void
GetSessionLogin(
	_Out_ HkPal *loginNameBuffer);

HKRAPI void
GetContextInfo(
	_Out_ HkPal *contextInfoBuffer);

HKRAPI _Check_return_ HRESULT
GetUsername(
	_In_ HkErrorObject *errorObject,
	int				   id,
	_Out_ HkPal		   *usernameBuffer);

HKRAPI _Check_return_ HRESULT
GetSusername(
	_In_ HkErrorObject *errorObject,
	int				   id,
	_Out_ HkPal		   *loginNameBuffer);

HKRAPI _Check_return_ HRESULT
	GetSuserSname(
	_In_ HkErrorObject * errorObject,
	_In_reads_bytes_(sidLength) unsigned char *sidValue,
	int sidLength,
	_Out_ HkPal * loginNameBuffer);

HKRAPI _Check_return_ HRESULT
	GetSuserId(
	_In_ HkErrorObject * errorObject,
	_In_reads_bytes_(loginNameLength) unsigned char *loginName,
	int loginNameLength,
	_Out_ int *suserId);

HKRAPI _Check_return_ HRESULT
	GetSuserSid(
	_In_ HkErrorObject * errorObject,
	_In_reads_bytes_(loginNameLength) unsigned char *loginName,
	int loginNameLength,
	bool validateLoginName,
	_Out_ HkPal * sidValue);

HKRAPI _Check_return_ HRESULT
	IsMember(
	_In_ HkErrorObject * errorObj,
	_In_reads_bytes_(roleNameLength) unsigned char *roleName,
	int roleNameLength,
	_Out_ int *isMemberResult);

HKRAPI _Check_return_ HRESULT
	IsRoleMember(
	_In_ HkErrorObject * errorObj,
	_In_reads_bytes_(roleNameLength) unsigned char *roleName,
	int roleNameLength,
	_In_reads_bytes_(usernameLength) unsigned char *username,
	int usernameLength,
	_Out_ int *isRoleMemberResult);

HKRAPI _Check_return_ HRESULT
	IsSrvRoleMember(
	_In_ HkErrorObject * errorObj,
	_In_reads_bytes_(roleNameLength) unsigned char *roleName,
	int roleNameLength,
	_In_reads_bytes_(loginNameLength) unsigned char *loginName,
	int loginNameLength,
	_Out_ int *isRoleMemberResult);

HKRAPI _Check_return_ __int64
SysTranDateTime(_In_ HkTransaction *tx);

HKRAPI _Check_return_ __int64
SysMaxDateTime(_In_ int scale);


HKRAPI __forceinline _Check_return_ HkSixteenByteData
GetNewId(void);

HKRAPI __forceinline _Check_return_ HkSixteenByteData
GetNewSequentialId(void);

HKRAPI _Check_return_ int
DatePart(int datePart, __int64 date, int dateFirst);

HKRAPI _Check_return_ HRESULT
DateAdd(
	int		  datePart,
	__int64	  number,
	int		  date,
	_Out_ int *result);

HKRAPI _Check_return_ int
DateDiff(
	int datePart,
	int firstDate,
	int secondDate);

HKRAPI _Check_return_ int
EOMonth(int date);

HKRAPI _Check_return_ HRESULT
SmallDateTimeFromParts(
	int				   year,
	int				   month,
	int				   day,
	int				   hour,
	int				   minute,
	_Out_ int		   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
DateTimeFromParts(
	int				   year,
	int				   month,
	int				   day,
	int				   hour,
	int				   minute,
	int				   seconds,
	int				   milliseconds,
	_Out_ __int64	   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
DateFromParts(
	int				   year,
	int				   month,
	int				   day,
	_Out_ int		   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
TimeFromParts(
	int				   hour,
	int				   minute,
	int				   seconds,
	int				   fractions,
	int				   precision,
	_Out_ __int64	   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
DateTime2FromParts(
	int				   year,
	int				   month,
	int				   day,
	int				   hour,
	int				   minute,
	int				   seconds,
	int				   fractions,
	int				   precision,
	_Out_ __int64	   *result,
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ double
Rand(void);

HKRAPI _Check_return_ double
SRand(int seed);


HKRAPI _Check_return_ double
hk_Cot(double x);


HKRAPI _Check_return_ double
hk_LogBaseN(double x, double base);

HKRAPI _Check_return_ HRESULT
CreateError(
	_In_ HkErrorObject *errorObj,
	HRESULT			   hr,
	unsigned long	   paramCount,
	...);

HKRAPI void
	CreateErrorForThrow(
	_In_ HkErrorObject * errorObj,
	int errorNum,
	int state,
	unsigned long line,
	long msgLenInBytes,
	_In_reads_(msgLenInBytes) const unsigned char *msg);

HKRAPI void
SetLineNumberForError(
	_Inout_ HkErrorObject *errorObj,
	unsigned long		  line);

HKRAPI _Check_return_ HRESULT
CreateErrorForRethrow(
	_Inout_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
SaveErrorForCatchBlock(
	_Inout_ HkErrorObject *errorObj);

HKRAPI _Check_return_ HRESULT
DismissErrorForCatchBlock(
	_Inout_ HkErrorObject *errorObj);

HKRAPI _Check_return_ long
GetErrorNumber(
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ unsigned char*
GetErrorMessage(
	_In_ HkErrorObject	 *errorObj,
	_Out_ unsigned short *msgLen);

HKRAPI _Check_return_ long
GetErrorSeverity(
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ long
GetErrorState(
	_In_ HkErrorObject *errorObj);

HKRAPI _Check_return_ long
GetErrorLine(
	_In_ HkErrorObject *errorObj);



HKRAPI _Check_return_ short
GetSpid(void);

#ifndef GOLDEN_BITS

HKRAPI void
FireXEventsForCallback(
	int				 callback,
	void const		 *left,
	void const		 *right,
	__int64			 res,
	unsigned long	 dbid,
	unsigned long	 objid,
	unsigned long	 indid,
	unsigned long	 hkIndexId,
	HkColsInfo const *colsInfo,
	bool			 normalized);

HKRAPI void
FireXEventForHkSearchKey(
	HkSearchKey const *key,
	bool			  isEndKey,
	bool			  isPointLookup,
	bool			  isEndTable,
	bool			  isNormalized,
	unsigned long	  dbid,
	unsigned long	  objid,
	unsigned long	  indid,
	unsigned short	  nullExtendedColumnIdx);

HKRAPI void
FireXEventForQuerySearchKey(
	unsigned long startColPos,
	unsigned long colCount,
	bool		  isStrict,
	bool		  isEndKey,
	bool		  isPointLookup,
	unsigned long dbid,
	unsigned long objid,
	unsigned long indid,
	bool		  isDynamicOrRangePointsKey,
	...);

#endif

HKRAPI void
AssertFail(
	unsigned int						  assert_type,
	_In_ _Null_terminated_ const char	  *exp,
	_In_ _Null_terminated_ const char	  *filename,
	int									  line,
	_In_opt_ _Null_terminated_ const char *szDesc,
	_In_ char							  *args);

HKRAPI _Check_return_ HRESULT
YieldThread(_In_ HkProcContext *hkcontext, unsigned long lineNo);

HKRAPI void
ThrowErrorHr(HRESULT hr);

HKRAPI _Check_return_ HRESULT
	SortHkRows(
	_In_ HkProcContext * hkcontext,
	_In_ void *context,
	_Inout_updates_bytes_(countRows * sizeOfSortBufElem) void *sortBuffer,
	int(__cdecl * compare)(void*, const void*, const void*),
	long countRows,
	size_t sizeOfSortBufElem);

HKRAPI _Check_return_ HRESULT
	InitPriorityQueue(
	HRESULT(__cdecl * compare)(void*, long, long, __int64*),
	_In_ void *context,
	_Out_writes_(sizeOfPriorityQueue) long *priorityQueue,
	long sizeOfPriorityQueue,
	_Out_ long *nextEntryPoint);

HKRAPI _Check_return_ HRESULT
	InsertIntoPriorityQueue(
	HRESULT(__cdecl * compare)(void*, long, long, __int64*),
	_In_ void *context,
	_Inout_updates_(sizeOfPriorityQueue) long *priorityQueue,
	long sizeOfPriorityQueue,
	_Inout_ long *nextEntryPoint);

HKRAPI _Check_return_ HRESULT
	InitTopSortContext(
	_Inout_ HkCompareContext * cmpContext,
	_Inout_ HkTopSortContext * topsortContext,
	const void *params,
	void(_cdecl * lobRelease)(void*),
	size_t sortBufElemSize,
	_In_ unsigned char *deepDataBuffer,
	_In_ HkProcContext * hkcontext,
	int(__cdecl * sortCompare)(void*, const void*, const void*));




HKRAPI _Check_return_ HRESULT
	InitSortContext(
	_Inout_ HkCompareContext * cmpContext,
	_Inout_ HkSortContext * sortContext,
	const void *params,
	void(_cdecl * lobRelease)(void*),
	size_t sortBufElemSize,
	_In_ unsigned char *deepDataBuffer,
	_In_ HkProcContext * hkcontext,
	HRESULT(__cdecl * baseCompare)(void*, const void*, const void*, __int64*),
	HRESULT(__cdecl * pqCompare)(void*, long, long, __int64*),
	int(__cdecl * sortCompare)(void*, const void*, const void*));




HKRAPI _Check_return_ HRESULT
GetNextSortedRow(
	_In_ HkProcContext	  *hkcontext,
	_Inout_ HkSortContext *sortContext,
	_Outptr_ void		  **returnRow);



HKRAPI _Check_return_ HRESULT
GetNextSortedRowDistinct(
	_In_ HkProcContext	  *hkcontext,
	_Inout_ HkSortContext *sortContext,
	_Outptr_ void		  **returnRow);




HKRAPI _Check_return_ HRESULT
GetFirstSortedRow(
	_In_ HkProcContext	  *hkcontext,
	_Inout_ HkSortContext *sortContext,
	_Outptr_ void		  **returnRow);








HKRAPI _Check_return_ HRESULT
GetEmptySortRowSlot(
	_In_ HkProcContext	  *hkcontext,
	_Inout_ HkSortContext *sortContext,
	_Outptr_ void		  **returnRow);




HKRAPI _Check_return_ HRESULT
AllocateSortRowDeepData(
	_In_ HkProcContext			*hkcontext,
	_Inout_ HkSortContextCommon *sortCommonContext,
	size_t						size,
	__deref_out_opt void		**buffer);



HKRAPI _Check_return_ HRESULT
AllocateBuffer(
	_In_ HkProcContext *hkcontext,
	_Outptr_ void	   **returnBuffer);




HKRAPI void
DeallocateBufferForSort(
	_In_ HkProcContext	  *hkcontext,
	_Inout_ HkSortContext *sortContext,
	bool				  deallocateDeepData);




HKRAPI void
DeallocateBufferForTopSort(
	_In_ HkProcContext		 *hkcontext,
	_Inout_ HkTopSortContext *topSortContext,
	bool					 deallocateDeepData);





HKRAPI _Check_return_ HRESULT
AllocateSlotForTiesList(
	_In_ HkProcContext		 *hkcontext,
	_Inout_ HkTopSortContext *sortCommonContext,
	__deref_out_opt void	 **returnTiesList);




HKRAPI void
ResetTiesList(
	_In_ HkProcContext		 *hkcontext,
	_Inout_ HkTopSortContext *sortCommonContext);





HKRAPI _Check_return_ HRESULT
GetFirstTopSortElement(
	_In_ HkProcContext		 *hkcontext,
	_Inout_ HkTopSortContext *topSortContext,
	_Outptr_ void			 **elem);





HKRAPI _Check_return_ void*
GetNextTopSortElement(
	_In_ HkProcContext		 *hkcontext,
	_Inout_ HkTopSortContext *topSortContext);





HKRAPI _Check_return_ HRESULT
SortAndMergeHkSearchIntervals(
	_In_ HkProcContext *hkcontext,
	__int64 (*compareHkSearchKeys)(void const*, void const*),
	_Inout_updates_(*intervalCount) HkSearchInterval *hkSearchIntervals,
	_In_ unsigned long *intervalCount);

#ifndef GOLDEN_BITS





HKRAPI _Check_return_ HRESULT
SortAndMergeHkSearchIntervalsTest(
	_In_ HkProcContext *hkcontext,
	__int64 (*compareHkSearchKeys)(void const*, void const*),
	_Inout_updates_(*intervalCount) HkSearchIntervalTest *hkSearchIntervals,
	_In_ unsigned long *intervalCount);

#endif




HKRAPI _Check_return_ int
	CompareStrings(
	HkCollationCallback const *hcco,
	_In_reads_bytes_(leftLength) unsigned char const *leftValue,
	long leftLength,
	_In_reads_bytes_(rightLength) unsigned char const *rightValue,
	long rightLength);




HKRAPI _Check_return_ int
CompareMaxStrings(
	HkCollationCallback const *hcco,
	_In_ HkILBHandle		  *leftValue,
	_In_ HkILBHandle		  *rightValue);




HKRAPI _Check_return_  unsigned long
	HashString(
	HkCollationCallback const *hcco,
	_In_reads_bytes_(length) unsigned char const *value,
	long length,
	_Inout_	 unsigned long *hashState);




HKRAPI _Check_return_ int
TriggerNestLevel(void);




HKRAPI _Check_return_ int
TriggerNestLevelWithId(unsigned long objid);




HKRAPI _Check_return_ HRESULT
	HkCsProcessCustomLogRec(
	_In_ HkDatabase * db,
	_In_ HkTable * table,
	_In_ HkTransaction * tx,
	unsigned int dictTableId,
	unsigned int segTableId,
	unsigned int rgInfoTableId,
	_In_reads_(colCount) unsigned int const *hobtColIds,
	_In_reads_(colCount) unsigned char const *colTypes,
	_In_reads_(colCount) unsigned char const *colPrecs,
	_In_reads_(colCount) unsigned char const *colScales,
	_In_reads_(colCount) bool const *colDesc,
	unsigned short colCount,
	_In_reads_bytes_(dataSize) unsigned char const *data,
	unsigned short dataSize);




HKRAPI _Check_return_ HRESULT
	HkCsPostCheckpointLoad(
	_In_ HkDatabase * db,
	_In_ HkTable * table,
	_In_ HkTransaction * tx,
	unsigned int drTableId,
	unsigned int dictTableId,
	unsigned int segTableId,
	unsigned int rgInfoTableId,
	_In_reads_(colCount) unsigned int const *hobtColIds,
	_In_reads_(colCount) unsigned char const *colTypes,
	_In_reads_(colCount) unsigned char const *colPrecs,
	_In_reads_(colCount) unsigned char const *colScales,
	_In_reads_(colCount) bool const *colDesc,
	unsigned short colCount);




HKRAPI __forceinline _Check_return_ HRESULT
Round64(__int64 val, int length, int trunc, _Out_ __int64 *result);




HKRAPI _Check_return_ HRESULT
RoundDouble(double val, int length, int trunc, double *result);




HKRAPI __forceinline void
Round128(HkInt128 const *val, int length, int trunc, _Out_ HkInt128 *res);




HKRAPI _Check_return_ double
HkCeiling(double number);




HKRAPI _Check_return_ __int64
MaskInt64(
	_In_ HkProcContext		 *hkcontext,
	__int64					 originalValue,
	_In_ HkMaskingParameters *parameters);




HKRAPI void
MaskLargeNumeric(
	_In_ HkProcContext		 *hkcontext,
	_In_ HkInt128			 *originalValue,
	_In_ HkMaskingParameters *parameters,
	_Out_ HkInt128			 *finalValue);




HKRAPI _Check_return_ double
MaskDouble(
	_In_ HkProcContext		 *hkcontext,
	double					 originalValue,
	_In_ HkMaskingParameters *parameters);




HKRAPI _Check_return_ __int64
MaskDateAndTime(
	_In_ HkProcContext		 *hkcontext,
	__int64					 originalValue,
	_In_ HkMaskingParameters *parameters,
	unsigned char			 dateTimeType,
	unsigned char			 scale);




HKRAPI _Check_return_ unsigned long
	MaskAsciiString(
	_In_ HkProcContext * hkcontext,
	_In_reads_bytes_(originalValueLengthInBytes) unsigned char *originalValue,
	int originalValueLengthInBytes,
	_In_ HkMaskingParameters * parameters,
	_In_ HkStringUtils * stringUtils,
	_Out_writes_bytes_(maskedValueLengthInBytes) unsigned char *maskedValue,
	int maskedValueLengthInBytes,
	_Out_ unsigned char **finalValue);




HKRAPI _Check_return_ HRESULT
MaskAsciiStringLob(
	_In_ HkProcContext		 *hkcontext,
	_In_ HkILBHandle		 *originalValue,
	_In_ HkMaskingParameters *parameters,
	_In_ HkStringUtils		 *stringUtils,
	_Out_ HkILBHandle		 **finalResult);




HKRAPI _Check_return_ unsigned long
	MaskUnicodeString(
	_In_ HkProcContext * hkcontext,
	_In_reads_bytes_(originalValueLengthInBytes) unsigned char *originalValue,
	int originalValueLengthInBytes,
	_In_ HkMaskingParameters * parameters,
	_In_ HkStringUtils * stringUtils,
	_Out_writes_bytes_(maskedValueLengthInBytes) unsigned char *maskedValue,
	int maskedValueLengthInBytes,
	_Out_ unsigned char **finalValue);




HKRAPI _Check_return_ HRESULT
MaskUnicodeStringLob(
	_In_ HkProcContext		 *hkcontext,
	_In_ HkILBHandle		 *originalValue,
	_In_ HkMaskingParameters *parameters,
	_In_ HkStringUtils		 *stringUtils,
	_Out_ HkILBHandle		 **finalResult);




HKRAPI _Check_return_ unsigned long
	MaskBinary(
	_In_ HkProcContext * hkcontext,
	_In_reads_bytes_(originalValueLengthInBytes) unsigned char *originalValue,
	int originalValueLengthInBytes,
	_In_ HkMaskingParameters * parameters,
	_Out_writes_bytes_(maskedValueLengthInBytes) unsigned char *maskedValue,
	int maskedValueLengthInBytes,
	_Out_ unsigned char **finalValue);




HKRAPI _Check_return_ HRESULT
MaskBinaryLob(
	_In_ HkProcContext		 *hkcontext,
	_In_ HkILBHandle		 *originalValue,
	_In_ HkMaskingParameters *parameters,
	_Out_ HkILBHandle		 **finalResult);




HKRAPI void
MaskGuid(
	_In_ HkProcContext		 *hkcontext,
	_In_ HkSixteenByteData	 *originalValue,
	_In_ HkMaskingParameters *parameters,
	_Out_ HkSixteenByteData	 *finalValue);




HKRAPI _Check_return_ HRESULT
HostIsJsonLob(
	_In_ HkErrorObject	  *errorObj,
	_In_ HkEsInfoObj	  *esInfoObj,
	_In_ HkILBHandle	  *inputJson,
	int					  isjsonOption,
	_Inout_ unsigned char *isJsonResult);




HKRAPI _Check_return_ HRESULT
	HostJsonPathExistsLob(
	_In_ HkErrorObject   * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_ HkILBHandle * inputJson,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char    *jsonPath,
	int jsonPathLengthInBytes,
	_Inout_ unsigned char   *jsonExistsResult);





HKRAPI _Check_return_ HRESULT
	HostJsonPathExistsWch(
	_In_ HkErrorObject   * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_reads_bytes_(jsonValueLengthInBytes) unsigned char   *jsonValue,
	int jsonValueLengthInBytes,
	unsigned char inputJsonType,
	unsigned long inputJsonCollation,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char    *jsonPath,
	int jsonPathLengthInBytes,
	_Inout_ unsigned char   *jsonExistsResult);

HKRAPI _Check_return_ HRESULT
	HostJsonQueryWch(
	_In_ HkErrorObject * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_reads_bytes_(inputJsonLengthInBytes) unsigned char *inputJson,
	int inputJsonLengthInBytes,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char *jsonPath,
	int jsonPathLengthInBytes,
	bool fArrayWrapper,
	_Inout_ HkPal * finalResult);

HKRAPI _Check_return_ HRESULT
	HostJsonQueryLob(
	_In_ HkErrorObject * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_ HkILBHandle * inputJson,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char *jsonPath,
	int jsonPathLengthInBytes,
	bool fArrayWrapper,
	_Inout_ HkILBHandle * *finalResult);

HKRAPI _Check_return_ HRESULT
	HostJsonValueWch(
	_In_ HkErrorObject * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_reads_bytes_(inputJsonLengthInBytes) unsigned char *inputJson,
	int inputJsonLengthInBytes,
	unsigned char inputJsonType,
	unsigned long inputJsonCollation,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char *jsonPath,
	int jsonPathLengthInBytes,
	_Inout_ HkPal * finalResult);

HKRAPI _Check_return_ HRESULT
	HostJsonValueLob(
	_In_ HkErrorObject * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_ HkILBHandle * inputJson,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char *jsonPath,
	int jsonPathLengthInBytes,
	_Inout_ HkPal * finalResult);




HKRAPI _Check_return_ HRESULT
HostStringEscapeLob(
	_In_ HkErrorObject	*errorObj,
	_In_ HkILBHandle	*inputJson,
	unsigned char		inputType,
	unsigned char		inputPrecision,
	unsigned char		inputScale,
	unsigned short		inputMaxLength,
	unsigned long		inputCollation,
	_Inout_ HkILBHandle **result);




HKRAPI _Check_return_ HRESULT
	HostJsonModifyLob(
	_In_ HkErrorObject * errorObj,
	_In_ HkEsInfoObj * esInfoObj,
	_In_ HkILBHandle * inputJson,
	_In_reads_bytes_(jsonPathLengthInBytes) unsigned char *jsonPath,
	int jsonPathLengthInBytes,
	unsigned char newValueType,
	unsigned char newValuePrecision,
	unsigned char newValueScale,
	unsigned short newValueMaxLength,
	unsigned long newValueCollation,
	const HkValue * newValue,
	bool isNullNewValue,
	bool isNewValueValidJson,
	_Inout_ HkILBHandle * *result);




HKRAPI _Check_return_ HRESULT
	HostTVFStreamAlloc(
	_In_ HkProcContext * context,
	unsigned long indexIntoTvfInfoArray,
	unsigned long paramCount,
	unsigned long columnCount,
	_In_reads_(columnCount) HkValue * columns,
	_In_reads_(columnCount) bool *columnNullFlags,
	_Out_ HkIteratorStvf * *hkSTVFIter);

HKRAPI _Check_return_ HRESULT
	HostTVFStreamGetFirst(
	_In_ HkErrorObject * errorObj,
	_In_ HkIteratorStvf * hkSTVFIter,
	unsigned long paramCount,
	_In_reads_(paramCount) HkValue * parameters,
	_In_reads_(paramCount) bool *paramNullFlags);

HKRAPI _Check_return_ HRESULT
HostTVFStreamGetNext(
	_In_ HkErrorObject	*errorObj,
	_In_ HkIteratorStvf *hkSTVFIter);

HKRAPI void
HostTVFStreamFree(
	_In_ HkErrorObject	*errorObj,
	_In_ HkIteratorStvf *hkSTVFIter);




HKRAPI _Check_return_ HRESULT
HostUdeAlloc(
	_In_ HkProcContext *context,
	unsigned long	   indexIntoUdeArray,
	_Out_ HkUdeHelper  **udeHelper);

HKRAPI _Check_return_ HRESULT
HostUdeInit(
	_In_ HkErrorObject *errorObj,
	_In_ HkUdeHelper   *udeHelper);

HKRAPI _Check_return_ HRESULT
	HostUdeProcessRow(
	_In_ HkErrorObject * errorObj,
	_In_ HkUdeHelper * udeHelper,
	_In_reads_(paramsCount) const HkValue * params,
	unsigned long paramsCount,
	const bool *isNull);

HKRAPI _Check_return_ HRESULT
HostUdeFinalize(
	_In_ HkErrorObject		*errorObj,
	_In_ HkUdeHelper		*udeHelper,
	_Inout_opt_ HkILBHandle **result,
	_Inout_opt_ bool		*isNull);

HKRAPI void
HostUdeFree(_In_ HkUdeHelper *udeHelper);

HKRAPI _Check_return_ HRESULT
	HostTertiaryNorm(
	_In_ HkErrorObject * errorObj,
	unsigned long collationId,
	_In_reads_bytes_(inputStringLengthInBytes) unsigned char *inputString,
	unsigned long inputStringLengthInBytes,
	_Inout_ HkPal * result);

HKRAPI _Check_return_ HRESULT
HostTertiaryNormLob(
	_In_ HkProcContext	*hkContext,
	unsigned long		collationId,
	_In_ HkILBHandle	*inputString,
	_Inout_ HkILBHandle **result);




HKRAPI _Check_return_ HRESULT
	HostTrimStr(
	_In_ HkErrorObject * errorObj,
	int trimLogicIndex,
	unsigned char resultType,
	unsigned short resultMaxLength,
	unsigned long resultCollation,
	unsigned short trimType,
	_In_reads_bytes_(trimCharactersLengthInBytes) unsigned char *trimCharacters,
	unsigned long trimCharactersLengthInBytes,
	_In_reads_bytes_(stringToTrimLengthInBytes) unsigned char *stringToTrim,
	unsigned long stringToTrimLengthInBytes,
	_Inout_ HkPal * result);




HKRAPI _Check_return_ HRESULT
	HostTrimLob(
	_In_ HkProcContext * hkcontext,
	_In_ HkErrorObject * errorObj,
	int trimLogicIndex,
	unsigned char resultType,
	unsigned short resultMaxLength,
	unsigned long resultCollation,
	unsigned short trimType,
	_In_reads_bytes_(trimCharactersLengthInBytes) unsigned char *trimCharacters,
	unsigned long trimCharactersLengthInBytes,
	_In_ HkILBHandle * stringToTrim,
	_Inout_ HkILBHandle * *result);



HKRAPI _Check_return_ HRESULT
HostTranslateStr(
	_In_ HkErrorObject *errorObj,
	int				   translateLogicIndex,
	unsigned char	   type,
	unsigned short	   maxLength,
	unsigned long	   collation,
	_In_ HkPal		   *translateInputString,
	_In_ HkPal		   *charactersString,
	_In_ HkPal		   *translationString,
	_Inout_ HkPal	   *finalResult);



HKRAPI _Check_return_ HRESULT
HostTranslateWstr(
	_In_ HkErrorObject *errorObj,
	int				   translateLogicIndex,
	unsigned char	   type,
	unsigned short	   maxLength,
	unsigned long	   collation,
	_In_ HkPal		   *translateInputString,
	_In_ HkPal		   *charactersString,
	_In_ HkPal		   *translationString,
	_Inout_ HkPal	   *finalResult);



HKRAPI _Check_return_ HRESULT
HostTranslateLob(
	_In_ HkProcContext	*context,
	int					translateLogicIndex,
	unsigned char		type,
	unsigned short		maxLength,
	unsigned long		collation,
	_In_ HkILBHandle	*translateInput,
	_In_ HkPal			*charactersString,
	_In_ HkPal			*translationString,
	_Inout_ HkILBHandle **result);



HKRAPI _Check_return_ HRESULT
	HostUnistrWstr(
	_In_ HkErrorObject                                * errorObj,
	unsigned char type,
	unsigned short maxLength,
	unsigned long collation,
	_In_reads_bytes_(unicodeStringLengthInBytes) unsigned char    *unicodeString,
	unsigned long unicodeStringLengthInBytes,
	_In_reads_bytes_(escapeCharactersLengthInBytes) unsigned char *escapeCharacters,
	unsigned long escapeCharactersLengthInBytes,
	_Inout_ HkPal                                     * result);



HKRAPI _Check_return_ HRESULT
	HostUnistrStr(
	_In_ HkErrorObject                                * errorObj,
	unsigned char type,
	unsigned short maxLength,
	unsigned long collation,
	_In_reads_bytes_(unicodeStringLengthInBytes) unsigned char    *unicodeString,
	unsigned long unicodeStringLengthInBytes,
	_In_reads_bytes_(escapeCharactersLengthInBytes) unsigned char *escapeCharacters,
	unsigned long escapeCharactersLengthInBytes,
	_Inout_ HkPal                                     * result);



HKRAPI _Check_return_ HRESULT
	HostUnistrLob(
	_In_ HkProcContext                                * context,
	unsigned char type,
	unsigned short maxLength,
	unsigned long collation,
	_In_ HkILBHandle                                  * unistrString,
	_In_reads_bytes_(escapeCharactersLengthInBytes) unsigned char *escapeCharacters,
	unsigned long escapeCharactersLengthInBytes,
	_Inout_ HkILBHandle                               * *result);

HKRAPI HRESULT _Check_return_
	HostEditDistanceStr(
	_In_ HkErrorObject                            * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	unsigned long cMaxIter,
	_Inout_ int                                          *result);

HKRAPI HRESULT _Check_return_
	HostEditDistanceWstr(
	_In_ HkErrorObject                            * errorObj,
	_In_reads_(string1Length) unsigned char *wstr1,
	int string1Length,
	_In_reads_bytes_(string2Length) unsigned char *wstr2,
	int string2Length,
	unsigned long cMaxIter,
	_Inout_ int                                          *result);

HKRAPI HRESULT _Check_return_
	HostEditDistanceSimilarityStr(
	_In_ HkErrorObject                            * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	_Inout_ int                                          *result);

HKRAPI HRESULT _Check_return_
	HostEditDistanceSimilarityWstr(
	_In_ HkErrorObject                            * errorObj,
	_In_reads_(string1Length) unsigned char       *wstr1,
	int string1Length,
	_In_reads_bytes_(string2Length) unsigned char *wstr2,
	int string2Length,
	_Inout_ int                                          *result);

HKRAPI HRESULT _Check_return_
	HostJaroWinklerDistanceStr(
	_In_ HkErrorObject               * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	_Out_ double                             *result);

HKRAPI HRESULT _Check_return_
	HostJaroWinklerDistanceWstr(
	_In_ HkErrorObject               * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	_Out_ double                             *result);

HKRAPI HRESULT _Check_return_
	HostJaroWinklerSimilarityStr(
	_In_ HkErrorObject               * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	_Out_ int                             *result);

HKRAPI HRESULT _Check_return_
	HostJaroWinklerSimilarityWstr(
	_In_ HkErrorObject               * errorObj,
	_In_reads_(string1Length) unsigned char *str1,
	int string1Length,
	_In_reads_(string2Length) unsigned char *str2,
	int string2Length,
	_Out_ int                             *result);

HKRAPI _Check_return_ HRESULT
AllocateEsInfoObj(
	_In_ HkErrorObject	*errorObj,
	bool				isInputLob,
	int					builtinFunction,
	_Inout_ HkEsInfoObj **esInfoObj);

HKRAPI void
DeallocateEsInfoObj(_In_ HkEsInfoObj **esInfoObj);

#if !defined(HKRUNTIME_BUILD)
#if __cplusplus
extern "C"
{
#endif
double hk_acos(double x);
double hk_asin(double x);
double hk_atan(double x);
double hk_atan2(double x, double y);
double hk_cos(double x);
double hk_exp(double x);
double hk_floor(double x);
double hk_log(double x);
double hk_log10(double x);
double hk_pow(double x, double y);
double hk_sin(double x);
double hk_sqrt(double x);
double hk_tan(double x);
#if __cplusplus
}
#endif
#endif
