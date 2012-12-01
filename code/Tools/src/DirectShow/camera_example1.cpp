/*
* cl  example.cpp Strmiids.lib ole32.lib
* Note: Mingw32 not work
* g++ example.cpp -lStrmiids -lole32 -o example
*/

#include <stdio.h>
#include <dshow.h>

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
    ICreateDevEnum *pDevEnum;
    HRESULT hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

    if (SUCCEEDED(hr)) {
        hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
        if (hr == S_FALSE) {
            hr = VFW_E_NOT_FOUND;
        }
        pDevEnum->Release();
    }
    return hr;
}

HRESULT InitCaptureGraphBuilder(IGraphBuilder **ppGraph, ICaptureGraphBuilder2 **ppBuild)
{
    if (!ppGraph || !ppBuild) {
        return E_POINTER;
    }
    IGraphBuilder *pGraph = NULL;
    ICaptureGraphBuilder2 *pBuild = NULL;

    HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild );
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
        if (SUCCEEDED(hr)) {
            pBuild->SetFiltergraph(pGraph);

            *ppBuild = pBuild;
            *ppGraph = pGraph;
            return S_OK;
        } else {
            pBuild->Release();
        }
    }
    return hr; // Failed
}

HRESULT GetCameraFilter(IBaseFilter** ppCap)
{
    IEnumMoniker * pEnum = NULL;
    IMoniker * pMoniker = NULL;
    IBaseFilter * pCap = NULL;
    HRESULT hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
    if (SUCCEEDED(hr)) {
        if (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
        	LPOLESTR Name;
        	pMoniker->GetDisplayName( 0, NULL, &Name );
        	wprintf( L"* %s\n", Name );
            hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);
            *ppCap = pCap;
            pMoniker->Release();
        }
        pEnum->Release();
    }
    return hr;
}

int main()
{
    CoInitialize(NULL);

    ICaptureGraphBuilder2 * pBuild = NULL;
    IGraphBuilder *pGraph = NULL;
    IMediaControl *pControl = NULL;
    IMediaEvent   *pEvent = NULL;
    IBaseFilter * pCap = NULL;

    if (FAILED(InitCaptureGraphBuilder(&pGraph, &pBuild))) {
        printf("failed inital capture graph builder\n");
        return -2;
    }

    pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

    if (FAILED(GetCameraFilter(&pCap))) {
        printf("failed get camera\n");
        return -3;
    } else {
        pGraph->AddFilter(pCap, L"");
    }

    HRESULT hr = pBuild->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pCap, NULL, NULL);
    if (SUCCEEDED(hr)) {
        printf("ready run...\n");
        hr = pControl->Run();
        if (SUCCEEDED(hr)) {
            long evCode;
            pEvent->WaitForCompletion(60000, &evCode);
        }
    }

    printf("finished\n");
    pBuild->Release();
    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    pCap->Release();
    CoUninitialize();

    return 0;
}
