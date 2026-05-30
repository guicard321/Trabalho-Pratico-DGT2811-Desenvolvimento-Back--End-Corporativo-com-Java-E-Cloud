//*********************************************************************
// Copyright (c) Microsoft Corporation.
//*********************************************************************
















#pragma once




#include "hkengdef.h"

typedef struct HkWait HkWait;

#define ALTER_TABLE_DATASIZE_UNKNOWN	USHRT_MAX	




#define INDEX_CHNG_MAP_NO_CHANGES ((unsigned char*)(-1))

typedef struct HkDatabase HkDatabase;
typedef struct HkHashIndexMD HkHashIndexMD;
typedef struct HkRangeIndexMD HkRangeIndexMD;
typedef struct HkSequenceObj HkSequenceObj;
typedef struct HkTable HkTable;



typedef unsigned long HkHash;














typedef void
(*KeyIncrementFn)(
	_In_ const HkFlatKey* source,
	_Out_ HkSearchKey* target);









typedef _Check_return_ __int64
(*CompareSKeyToFKeyFn)(
	_In_ const HkSearchKey* left,
	_In_ const HkFlatKey* right);









typedef _Check_return_ __int64
(*CompareFKeyToFKeyFn)(
	_In_ const HkFlatKey* left,
	_In_ const HkFlatKey* right);














typedef _Check_return_ __int64
(*CompareSKeyToRowFn)(
	_In_ const HkSearchKey* key,
	_In_ const HkRow* row);














typedef _Check_return_ __int64
(*CompareRowToRowFn)(
	_In_ const HkRow* left,
	_In_ const HkRow* right);








typedef _Check_return_ HkHash
(*ComputeSKeyHashFn)(
	_In_ const HkSearchKey* key);








typedef _Check_return_ HkHash
(*ComputeFKeyHashFn)(
	_In_ const HkFlatKey* key);













typedef _Check_return_ HkHash
(*ComputeRowHashFn)(
	_In_ const HkRow* row);
















typedef _Check_return_ HRESULT
(*ExtractFlatKeyFn)(
	_In_ const HkRow* row,
	_Out_writes_bytes_to_(bufferSize, *keySize) HkFlatKey* key,
	_In_ unsigned short bufferSize,
	_Out_ unsigned short* keySize);



typedef enum
{
	
	
	HkHashIndexType = 0,

	
	
	HkRangeIndexType = 1,

	
	
	HkHeapIndexType = 2,
} HkIndexType;



enum HkIndexFlags
{
	HkIdxFlags_None = 0x0000,

	
	
	HkIdxFlags_IsUnique = 0x0001,

	
	
	
	
	
	HkIdxFlags_FixedSizeKeys = 0x0002,

	
	
	
	HkIdxFlags_NormalizedKeys = 0x0004,
};



struct HkHashIndexMD
{
	
	
	
	unsigned long MdIndexId;

	
	
	unsigned short IndexFlags;

	
	
	unsigned int NumberOfBuckets;

	
	
	
	
	
	
	CompareSKeyToRowFn		CompareSKeyToRow;
	CompareRowToRowFn		CompareRowToRow;
	ComputeSKeyHashFn		ComputeSKeyHash;
	ComputeRowHashFn		ComputeRowHash;
};



struct HkRangeIndexMD
{
	
	
	
	unsigned long MdIndexId;

	
	
	unsigned short IndexFlags;

	
	
	
	unsigned short FlatKeySize;

	
	
	
	
	
	unsigned short SearchKeySize;

	
	
	HkFlatKey const* InfinityKey;

	
	
	unsigned short InfinityKeySize;

	
	
	
	
	
	
	CompareSKeyToFKeyFn		CompareSKeyToFKey;
	CompareFKeyToFKeyFn		CompareFKeyToFKey;
	CompareSKeyToRowFn		CompareSKeyToRow;
	CompareRowToRowFn		CompareRowToRow;
	ComputeFKeyHashFn		ComputeFKeyHash;
	ExtractFlatKeyFn		ExtractFlatKey;
	KeyIncrementFn			KeyIncrement;
};












typedef void
(*FreeRowResourcesFn)(
	_In_ HkDatabase* db,
	_In_ HkRow* row);












typedef _Check_return_ unsigned long
(*GetSerializeSizeFn)(
	_In_ const HkRow* row);












typedef _Check_return_ HRESULT
(*SerializeFn)(
	_In_ const HkRow* row,
	_Out_writes_bytes_to_(bufferSize, *copySize) unsigned char* buffer,
	_In_ unsigned short bufferSize,
	_Out_ unsigned short* copySize);






































typedef _Check_return_ HRESULT
(*DeserializeFn)(
	_In_ HkCallbackContext* hkContext,
	_In_ HkTable* table,
	_In_reads_bytes_(dataSize) const unsigned char* data,
	_In_ unsigned short dataSize,
	_In_ unsigned long hkTableId,
	_In_ bool calledFromCkptLoad,
	_Out_ HkRow** row);






















typedef void
(*LargeDataSerializeFn)(
	_In_ const HkRow* row,
	_In_ unsigned long largeDataOffset,
	_Out_writes_bytes_to_(bufferSize, *copySize) unsigned char* buffer,
	_In_ unsigned short bufferSize,
	_Out_ unsigned short* copySize);




























typedef _Check_return_ HRESULT
(*LargeDataDeserializeFn)(
	_In_ HkDatabase* db,
	_In_ const HkTable* table,
	_Inout_ HkRow* row,
	_In_ unsigned long largeDataOffset,
	_In_reads_bytes_(dataSize) const unsigned char* data,
	_In_ unsigned short dataSize);














typedef _Check_return_ unsigned short
(*GetSerializeRecKeySizeFn)(
	_In_ const HkRow* row);















typedef _Check_return_ HRESULT
(*SerializeRecKeyFn)(
	_In_ const HkRow* row,
	_Out_writes_bytes_to_(bufferSize, *copySize) unsigned char* buffer,
	_In_ unsigned short bufferSize,
	_Out_ unsigned short* copySize);













typedef _Check_return_ HRESULT
(*DeserializeRecKeyFn)(
	_In_reads_bytes_(dataSize) const unsigned char* data,
	_In_ unsigned short dataSize,
	_Out_writes_bytes_(bufferSize) HkSearchKey* key,
	_In_ unsigned short bufferSize);




































typedef _Check_return_ HRESULT
(*DeserializeRecKeyToRowFn)(
	_In_reads_bytes_(keyBufferSize) const unsigned char* keyBuffer,
	_In_ unsigned short keyBufferSize,
	_Out_writes_bytes_(rowBufferSize) HkRow* rowBuffer,
	_In_ unsigned short rowBufferSize,
	_Out_ unsigned short* rowSize);

























typedef _Check_return_ HRESULT
(*ProcessCustomLogRecFn)(
	_In_ HkDatabase* db,
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_reads_bytes_(dataSize) unsigned char const* data,
	_In_ unsigned short dataSize);
























typedef _Check_return_ HRESULT
(*PostCheckpointLoadFn)(
	_In_ HkDatabase* db,
	_In_ HkTable* table,
	_In_ HkTransaction* tx);

















typedef void
(*PostCommitProcessingFn)(
	_In_ HkTable* table,
	_In_opt_ HkRow const* oldRow,
	_In_opt_ HkRow const* newRow);








typedef enum HkTableFlags
{
	
	
	HkTableFlags_None = 0x0000,

	
	
	HkTableFlags_IsNonDurable = 0x0001,

	
	
	
	HkTableFlags_AllowsBackgroundInsertsAndDeletes = 0x0002,

	
	
	
	HkTableFlags_StoresLobData = 0x0004,

	
	
	
	
	HkTableFlags_CkptLoadIntoPKIndexOnly = 0x0008,

	
	
	HkTableFlags_Default = HkTableFlags_None
} HkTableFlags;



struct HkTableMD
{
	
	
	
	size_t MinRowSize;

	
	
	
	size_t MaxRowSize;

	
	
	unsigned int CountHeaps;

	
	
	unsigned int CountHashIndices;

	
	
	HkHashIndexMD* HashIndexMD;

	
	
	unsigned int CountRangeIndices;

	
	
	HkRangeIndexMD* RangeIndexMD;

	
	
	
	
	
	
	
	
	
	unsigned int RecoveryIndex;

	
	
	void const* OpaqueData;

	
	
	
	
	
	
	
	unsigned int HostTableId;

	
	
	HkTableFlags TableFlags;

	
	
	
	unsigned int MaxBufferNeededForAlter;

	
	
	FreeRowResourcesFn			FreeRowResources;
	GetSerializeSizeFn			GetSerializeSize;
	SerializeFn					Serialize;
	DeserializeFn				Deserialize;
	LargeDataSerializeFn		LargeDataSerialize;
	LargeDataDeserializeFn		LargeDataDeserialize;
	GetSerializeRecKeySizeFn	GetSerializeRecKeySize;
	SerializeRecKeyFn			SerializeRecKey;
	DeserializeRecKeyFn			DeserializeRecKey;
	DeserializeRecKeyToRowFn	DeserializeRecKeyToRow;
	ProcessCustomLogRecFn		ProcessCustomLogRec;
	PostCheckpointLoadFn		PostCheckpointLoad;
	PostCommitProcessingFn		PostCommitProcessing;
};




struct HkCallbackContext
{
	
	
	HkErrorObject* ErrorObject;

	
	
	unsigned char* DeepDataBuffer;

	
	
	HkTransaction* Transaction;
};

HKEAPI void HKAPICC
HkTableReleaseRow(
	_In_ HkTable* table,
	_In_ HkRow* row);

HKEAPI void HKAPICC
HkTableAddRefRow(
	_In_ HkTable* table,
	_Inout_ HkRow* row);

HKEAPI void HKAPICC
HkTableReleaseRows(
	_In_ HkTable* table,
	_In_reads_(rowCount) HkRow** rows,
	_In_ unsigned long rowCount);

HKEAPI void HKAPICC
HkTableReleaseLinkedRows(
	_In_ HkTable* table,
	_In_ HkRow* rows);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableInsert(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ HkRow* row,
	_In_ bool isInvisibleToSelf);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableInsertLinkedRows(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ HkRow* row);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableUpdate(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ HkRow* rowToUpdate,
	_In_ HkRow* newRow,
	_In_opt_ const unsigned char* indexChangeMap,
	_In_ bool allowInvisibleRow,
	_Out_opt_ HkRow** updatedRow);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableDelete(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ HkRow* row,
	_Out_opt_ HkRow** updatedRow);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableRefreshInternalTableMapping(
	_In_ HkTable* table,
	_In_ HkTransaction* tx);

HKEAPI void HKAPICC
HkTableDropTempTable(
	_In_ HkTable* table);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableGetNextLobId(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_Out_ HkLobId* lobId);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableCreateNewLob(
	_In_ HkTable* table,
	_In_ unsigned long columnId,
	_In_opt_ HkErrorObject* errorObject,
	_Out_ HkLockBytes** hkLockBytes);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableCreateNewOffRowDeepData(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ unsigned __int64 dataLength,
	_Out_ unsigned char** data);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableInsertLob(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ HkLobId lobId,
	_In_ HkLockBytes* hkLockBytes);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableInsertOffRowDeepData(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ HkLobId lobId,
	_In_ unsigned __int64 length,
	_In_ unsigned char* data);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableDeleteLob(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ HkLobId lobId);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableGetLobFromId(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ HkLobId lobId,
	_Out_ HkLockBytes** hkLockBytes);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTableGetOffRowDeepFromId(
	_In_ HkTable* table,
	_In_ HkTransaction* tx,
	_In_ unsigned long columnId,
	_In_ HkLobId lobId,
	_Out_ unsigned char** data,
	_Out_ unsigned long* length);

HKEAPI void HKAPICC
HkOffRowDataFree(
	_In_ HkTable* table,
	_In_ unsigned long columnId,
	_In_ unsigned char* data);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionAllocMemory(
	_In_ HkTransaction* tx,
	_In_ unsigned long size,
	_Outptr_result_bytebuffer_(size) unsigned char** txMemory);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionCreateSavePoint(
	_In_ HkTransaction* tx,
	_Out_ HkTxSavePointId* id);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionCreateHkTempDbSavePoint(
	_In_ HkTransaction* tx,
	_Out_ HkTxSavePointId* id);

HKEAPI void HKAPICC
HkTransactionRefreshSavePoint(
	_In_ HkTransaction* tx,
	_In_ HkTxSavePointId id);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionRollbackToSavePoint(
	_In_ HkTransaction* tx,
	_In_ HkTxSavePointId id);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionRollbackToLastHkTempDbSavePoint(
	_In_ HkTransaction* tx);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionWaitForDependencies(
	_In_ HkTransaction* tx,
	_In_ HkWait* wait);

HKEAPI _Check_return_ HRESULT HKAPICC
HkRefreshStatementId(
	_In_ HkTransaction* tx);

HKEAPI _Check_return_ HRESULT HKAPICC
HkTransactionDeltaTrackerAlloc(
	_In_ HkTransaction* tx,
	_Outptr_ HkTxDeltaTracker** tracker);

HKEAPI void HKAPICC
HkTransactionDeltaTrackerFree(
	_In_ HkTxDeltaTracker* tracker);

HKEAPI _Check_return_ HRESULT HKAPICC
HkRowAlloc(
	_In_ HkTransaction* transaction,
	_In_ HkTable* table,
	_In_ unsigned int heapId,
	_In_ unsigned long rowSize,
	_In_ bool storageBeginField,
	_In_ unsigned long long tag,
	_Out_ HkRow** row,
	_In_opt_ const HkRow* prevRow);

HKEAPI _Check_return_ HRESULT HKAPICC
HkCursorHashAlloc(
	_In_ HkTable* table,
	_In_ unsigned int indexId,
	_In_ FilterFn filterFunction,
	_In_ unsigned int bufferRequiredForFilter,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkCursorHash** cursorHash,
	_In_opt_ char const* tag);

HKEAPI void HKAPICC
HkCursorHashFree(
	_In_ HkCursorHash* cursor);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorHashGetFirst(
	_In_ HkCursorHash* cursor,
	_In_ HkTransaction* tx,
	_In_ HkSearchKey const* key,
	_In_opt_ HkParam const* params,
	_In_ TxIsoLevel isoLevel,
	_In_ bool isScanForFKValidation,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorHashGetNext(
	_In_ HkCursorHash*  cursor,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ HRESULT HKAPICC
HkCursorRangeAlloc(
	_In_ HkTable* table,
	_In_ unsigned int indexId,
	_In_opt_ FilterFn filterFunction,
	_In_ unsigned int bufferRequiredForFilter,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkCursorRange** cursorRange,
	_In_opt_ char const* tag);

HKEAPI void HKAPICC
HkCursorRangeFree(
	_In_ HkCursorRange* cursor);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorRangeGetFirst(
	_In_ HkCursorRange* cursor,
	_In_ HkTransaction* tx,
	_In_ HkSearchKey const* startKey,
	_In_ HkSearchKey const* endKey,
	_In_opt_ HkParam const* params,
	_In_ TxIsoLevel isoLevel,
	_In_ bool isScanForFKValidation,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorRangeGetNext(
	_In_ HkCursorRange* cursor,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ HRESULT HKAPICC
HkCursorHeapAlloc(
	_In_ HkTable* table,
	_In_ unsigned int heapId,
	_In_ FilterFn filterFunction,
	_In_ unsigned int bufferRequiredForFilter,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkCursorHeap** cursorHeap,
	_In_opt_ char const* tag);

HKEAPI void HKAPICC
HkCursorHeapFree(
	_In_ HkCursorHeap* cursor);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorHeapGetFirst(
	_In_ HkCursorHeap* cursor,
	_In_ HkTransaction* tx,
	_In_opt_ HkParam const* params,
	_In_ TxIsoLevel isoLevel,
	_In_ unsigned long sampleRate,
	_In_ bool isScanForFKValidation,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorHeapGetNext(
	_In_ HkCursorHeap* cursor,
	_Out_opt_ HkErrorObject* error,
	_Out_ HkRow const** row);

HKEAPI _Check_return_ HRESULT HKAPICC
HkCursorDeltaTrackerAlloc(
	_Out_opt_ HkErrorObject* error,
	_Outptr_ HkCursorDeltaTracker** cursor);

HKEAPI void HKAPICC
HkCursorDeltaTrackerFree(
	_In_ HkCursorDeltaTracker* cursor);

HKEAPI _Check_return_ HRESULT HKAPICC
HkCursorDeltaTrackerGetFirst(
	_In_ HkCursorDeltaTracker* cursor,
	_In_ HkTxDeltaTracker const* tracker,
	_In_ HkTable const* table,
	_In_ bool inserted,
	_Outptr_ HkRow const** row);

HKEAPI _Check_return_ _Success_(return == S_OK) HRESULT HKAPICC
HkCursorDeltaTrackerGetNext(
	_In_ HkCursorDeltaTracker* cursor,
	_Out_opt_ HkErrorObject* error,
	_Outptr_ HkRow const** row);

HKEAPI _Check_return_ HRESULT HKAPICC
HkSequenceObjGetNext64(
	_In_ HkTransaction* tx,
	_In_ HkSequenceObj* seqObj,
	_Out_ __int64* value64);

HKEAPI _Check_return_ HRESULT HKAPICC
HkSequenceObjGetNext128(
	_In_ HkTransaction* tx,
	_In_ HkSequenceObj* seqObj,
	_Out_ HkInt128* value128);

HKEAPI void HKAPICC
HkTransactionUpdateTemporalTs(
	_In_ HkTransaction* tx,
	_In_ __int64 newTs);
