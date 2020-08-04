#pragma once
#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "TaskInfo.h"
#include "FileDownType.h"

DECLARE_DELEGATE_TwoParams(FOnTaskEvent, const EDownloadTaskEvent, const FTaskInfo&);

class FDownloadTask final
{
public:
    FDownloadTask(const FString& URL, const FString& SaveRoot, const FString& FileName,
                  const int32 FileSize);

    void Start();

    void Stop();

    bool IsDownloading() const
    {
        return bIsDownLoading;
    }

    FString GetFilePath() const;

    FGuid GetGuid() const;

    FTaskInfo GetTaskInfo() const;

    FOnTaskEvent OnTaskEvent;

    static FString TempFileExtension;

protected:
    void ReqGetHead();

    void RetGetHead(FHttpRequestPtr, const FHttpResponsePtr Response, const bool bConnectedSuccessfully);

    void ReqGetChunk();

    void GetChunkProgress(FHttpRequestPtr, int32 BytesSent, int32 BytesReceived);

    void RetGetChunk(FHttpRequestPtr, const FHttpResponsePtr Response, const bool bConnectedSuccessfully);

    void OnWriteChunkEnd(int32 BufferSize);

    void OnTaskCompleted();

    FString GetEncodedURL() const;

    bool IsFileExist() const;

private:
    FTaskInfo TaskInfo;

    FString Root;

    bool bIsDownLoading;

    const int32 ChunkSize = 4 * 1024 * 1024;

    FString TempFileName;

    IFileHandle* TempFileHandle;

    TSharedPtr<class IHttpRequest> Request;
};
