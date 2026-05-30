//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************















#pragma once

typedef struct HkErrorObject HkErrorObject;
typedef struct HkFlatKeyColsInfo HkFlatKeyColsInfo;
typedef struct HkILBHandle HkILBHandle;
typedef struct HkInt128 HkInt128;
typedef struct HkOffsetInfo HkOffsetInfo;
typedef struct HkPal HkPal;
typedef struct HkRootTableRowBase HkRootTableRowBase;
typedef struct HkSixteenByteData HkSixteenByteData;
typedef struct HkTable HkTable;
typedef struct HkTableMD HkTableMD;
typedef struct HkTransaction HkTransaction;
typedef struct HkTxDeltaTracker HkTxDeltaTracker;

typedef struct IHkStatementExecStats IHkStatementExecStats;
typedef struct IHkStatementPerf IHkStatementPerf;



#pragma warning(push)
#pragma warning(disable: 4512)  

typedef struct HkOffsetInfo
{
	unsigned short const DataOffset;			
	unsigned short const NullOffset;			
	unsigned char const NullBitMask;			
	unsigned long const OffRowTableId;			
} HkOffsetInfo;

#pragma warning(pop)




typedef struct HkSearchKeyColsInfo
{
	
	
	
	
	
	unsigned short FixedSize;

	
	
	HkOffsetInfo const* Offsets;

	
	
	
	
	unsigned short ColCountOffset;

	
	
	
	
	unsigned short EpsilonOffset;
} HkSearchKeyColsInfo;




typedef struct HkFlatKeyColsInfo
{
	unsigned short FixedSize;					
	HkOffsetInfo const* Offsets;			
} HkFlatKeyColsInfo;



typedef struct HkColsInfo
{
	
	
	unsigned short FixedSize;								
	HkOffsetInfo const* Offsets;						
	unsigned short CSRIDOffset;								
	unsigned short SizeLocationOffset;						
	HkSearchKeyColsInfo const* SearchKeyColsInfo;	
	HkFlatKeyColsInfo const* FlatKeyColsInfo;		
} HkColsInfo;



#define MAX_TDS_DATA_CLASSIFICATION_VERSION 2



typedef struct HkOutputMetadata
{
	int							rsId;
	unsigned long				currentLineNumber;
	unsigned short				columnCount;
	const unsigned char*		columnNameLens;
	const wchar_t* const*		columnNames;
	const unsigned char*		columnTypes;
	const unsigned char*		columnNullables;
	const unsigned char*		columnPrecisions;
	const unsigned char*		columnScales;
	const unsigned short*		columnMaxLengths;
	const unsigned long*		columnCollations;
	const unsigned char*		columnStatusBits;
	unsigned short				orderByCount;
	const unsigned short*		orderByColumns;
	const unsigned char* const*	tdsBufs;
	const unsigned short*		tdsBufLengths;
	unsigned short				clientCount;
	const unsigned char*		tdsKeyBuf;
	unsigned short				tdsKeyBufLength;
	const unsigned char* const*	tdsDataClassificationBufs;
	const unsigned short*       tdsDataClassificationBufLengths;
} HkOutputMetadata;



enum
{
	eHkCl42 = 0,
	eHkCl6x = 1,
	eHkCl70 = 2,
	eHkCl71 = 3,
	eHkCl71_SP1 = 4,
	eHkCl72 = 5,
	eHkCl73 = 6,
	eHkCl74 = 7,
	eHkClBase = eHkCl70
};

#define CLIENTLEVEL_AND_TCEENABLED_TO_OFFSET(e, isTceSupported) (e - eHkClBase + (isTceSupported ? 1 : 0))
#define OFFSET_TO_CLIENTLEVEL(e) (e == CLIENTLEVEL_AND_TCEENABLED_TO_OFFSET(eHkCl74, true) ? eHkCl74 : (e + eHkClBase))
#define OFFSET_TO_TCEENABLED(e) (e == CLIENTLEVEL_AND_TCEENABLED_TO_OFFSET(eHkCl74, true))

struct TDSCOLLATION;

#pragma pack(push, 1)


typedef struct HkDonePkt
{
	unsigned char donetoken;
	unsigned short donestat;
	unsigned short donecurcmd;
	unsigned long long donecount;
} HkDonePkt;
#pragma pack(pop)



typedef struct HkTdsContext
{
	unsigned char* currentMark;				
	unsigned char* safeMark;				
	unsigned long bytesLeft;				
	unsigned long currentLineNumber;		
	bool isNetworkOptimized;				
	bool updateSafeMark;					
	bool haveUpdatedToSafeMark;				
	bool rsStarted;							
	bool isTceSupported;					
	bool isDataClassificationSupported;		
	int  dataClassificationVersion;         

	unsigned char rsEnd;					
	unsigned char stmtEnd;					
	HkDonePkt donepkt;						

	unsigned short clientLevelOffset;		

	bool isRef;								
	bool isEndOfStream;						
	unsigned long inputBytesLeft;			
	unsigned char* inputCurrentBuf;			

	
	
	unsigned char* paramStart;				
	unsigned short paramReadCount;			

	unsigned short outParamReadCount;		
	unsigned char* outParam;				

	unsigned short collatedParamReadCount;	
	struct TDSCOLLATION* collations;		
} HkTdsContext;

#define HKVALUEBASE_MEMBERS \
	__int64				SignedIntData;	\
	unsigned __int64	UnsignedIntData;	\
	float				FloatData;			\
	double				DoubleData;



typedef struct HkSixteenByteData
{
	unsigned char data[16];
} HkSixteenByteData;

typedef struct HkPal
{
	unsigned char* Pointer;
	long Length;
} HkPal;




typedef struct HkPalWrappingLockBytesBuffer
{
	unsigned char data[32];
} HkPalWrappingLockBytesBuffer;

typedef union HkValue
{
	
	
	HKVALUEBASE_MEMBERS

	
	
	HkSixteenByteData SixteenByteData;

	
	
	HkInt128 Int128Data;

	
	
	HkPal PalData;

	
	
	HkILBHandle* LockBytesData;
} HkValue;

typedef struct HkProcContext
{
	HkDatabase* Database;
	HkTransaction* Transaction;
	HkTransaction* TableVarTransaction;
	HkErrorObject* ErrorObject;
	unsigned char* DeepDataBuffer;
	HkTdsContext* TdsContext;
	HkValue* HkValuesBuffer;
	unsigned char* NullsBuffer;
	unsigned char* IsOutputParamBuffer;
	unsigned long HkValuesBufferSize;
	HkTable** TableVars;
	HkTable** TableParams;
	IHkStatementPerf* StmtPerf;
	IHkStatementExecStats* StmtExecStats;
	HkTxDeltaTracker* DeltaTracker;
	__int64 Rowcount;
	unsigned char* UpdateBitVector;
	bool DefaultForUpdateBitVector;
	bool IsInTrigger;
	bool IsInvokedFromExecStmt;
	bool IsDllRequiredAtCommit;
} HkProcContext;



typedef _Check_return_ HRESULT
( __stdcall *ProcEntryPoint)(
	_In_ HkProcContext* context,
	_In_ HkValue* valueArray,
	_In_ unsigned char* nullArray);

typedef struct HkQueryStmtInfo
{
	int					Offset;
	int					OffsetEnd;
	unsigned long		LineNum;
	unsigned long		QdsDataIndex;

	
	
	
	
	
	long*				ParentQueryNodeIds;
	long*				ExecutionsInheritance;
	bool*				DidGenerateGetFirstLabel;
	bool*				WasPassedReturnRowLabel;

	
	
	unsigned long		ArrayLengths;
} HkQueryStmtInfo;





typedef struct HkCollationType
{
	
	
	unsigned long CollationId;

	
	
	bool Unicode;

	
	
	bool Lob;
} HkCollationType;



typedef struct HkCollationCallback
{
	
	
	void* CompareString;

	
	
	void* HashString;
} HkCollationCallback;

typedef struct HkProcInfo
{
	ProcEntryPoint			ProcFn;
	ProcEntryPoint			TdsParseProcFn;
	ProcEntryPoint			TdsReturnProcFn;
	unsigned long			BufferSpaceNeeded;
	unsigned short			MaxNestedExecScalarParams;
	unsigned short			MaxNestedExecTableParams;
	unsigned short			MaxOutputColumns;
	unsigned short			MaxOrderByColumns;
	unsigned short			MaxStvfOutputColumns;
	unsigned long			TableVarsCount;
	unsigned long			TableParamsCount;
	unsigned long const*	TableVarsMDOffsets;
	unsigned long			TableTypeCount;
	unsigned int*			TableTypeIds;
	unsigned char*			InternalTablesNeededForType;
	HkTableMD const**	TableTypeMDs;
	bool					SortBufferNeeded;
	bool					TopSortBufferNeeded;
	bool					BlobHandleFactoryNeeded;
	unsigned char			ProcIsolationLevel;
	bool					DelayedDurability;
	unsigned short			MinClientForOutputTDSOptimization;
	unsigned int			CountTablesStabilize;
	HkRootTableRowBase** TableRowsStabilize;
	unsigned long			ProcQueryStmtCount;
	HkQueryStmtInfo*	ProcQueryStmtInfo;
	unsigned int			CountTables;
	HkTableId*				TableIds;
	HkTableId*				DRTableIds;
	unsigned int*			HostTableIds;

	
	
	
	
	
	
	
	
	
	
	
	
	__int64					MaxRefTablesCreationTs;
	unsigned long			MaxRefTablesCreationTsHostTableId;
} HkProcInfo;










static unsigned __int64 const InvalidCSRID = (unsigned __int64) -1;








#define MAKE_CSRID(rgid, rid) ((unsigned __int64) (rgid) << 32) + (unsigned __int64) (rid)
#define RGID_FROM_CSRID(csrid) (unsigned int) ((unsigned __int64) (csrid) >> 32)
#define RID_FROM_CSRID(csrid) (unsigned int) ((unsigned __int64) (csrid) & ULONG_MAX)














typedef struct DeletedRowsTableRow
{
	unsigned int			RowGroupId;
	unsigned int 			BeginRID;
	unsigned int			EndRID;
} DeletedRowsTableRow;






typedef struct DeletedRowsTableKey
{
	unsigned int			RowGroupId;
	unsigned int 			BeginRID;
} DeletedRowsTableKey;





typedef struct HkMaskFunctionArgument
{
	int XvtType;	
	union
	{
		__int64 IntegerValue;
		double DoubleValue;
		HkInt128 Int128Value;
		HkPal PalValue;
	} Value;
} HkMaskFunctionArgument;





typedef struct HkMaskingParameters
{
	int MaskingFunction;						
	HkMaskFunctionArgument Arguments[3];	
	unsigned long MaskingStateIndex;
} HkMaskingParameters;



typedef struct HkStmtExecStatsData
{
	
	
	__int64* ActualRows;
	__int64* ActualEndOfScans;
	__int64* ActualExecutions;
	__int64* ActualTicks;
	__int64* ActualCpuTicks;
} HkStmtExecStatsData;

typedef void
(*CountCharactersFn)(
	_In_reads_bytes_(bufferSize) const unsigned char* buffer,
	_In_ unsigned long bufferSize,
	_In_ unsigned long numberOfCharactersToRead,
	_Out_ unsigned long* bytesRead,
	_Out_ unsigned long* charactersRead);

typedef unsigned short
(*TruncLenFn)(
	_In_reads_bytes_(bufferSize) unsigned char* buffer,
	_In_ long bufferSize);

typedef struct HkStringUtils
{
	unsigned char BaseCharacterSize;
	CountCharactersFn CountCharacters;
	TruncLenFn TruncBufferLength;
} HkStringUtils;

#if !defined(HKRAPI)
	#if defined(HKRUNTIME_BUILD)
		#define HKRAPI extern "C" __declspec(dllexport)
	#else
		#if defined(__cplusplus)
			#define HKRAPI extern "C" __declspec(dllimport)
		#else
			#define HKRAPI __declspec(dllimport)
		#endif
	#endif
#endif





#define HKAPICC __cdecl

HKRAPI _Check_return_ HRESULT HKAPICC
HkRtWaitForDependencies(_In_ HkProcContext *hkcontext, unsigned long currentLineNo, HRESULT hrCurrent);

HKRAPI _Check_return_ HRESULT HKAPICC
HkRtWaitForDependenciesEx(_In_ HkProcContext *hkcontext, unsigned long currentLineNo, HRESULT hrCurrent);

