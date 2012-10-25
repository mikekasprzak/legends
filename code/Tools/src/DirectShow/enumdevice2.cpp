/*
 * cl enumdevices.cpp Strmiids.lib ole32.lib oleaut32.lib
 * g++ enumdevices.cpp -lStrmiids -lole32 -loleaut32 -o enumdevices
 * 测试: windows xp + mingw32 4.4 + w32api 3.13
 */

// http://h-win-exercise.googlecode.com/svn-history/r78/trunk/dshow/

#include <stdio.h>
#include <windows.h>
#include <dshow.h>

#ifdef __MINGW32__
#include <Ocidl.h>
DEFINE_GUID( CLSID_VideoInputDeviceCategory, 0x860BB310, 0x5D01,
        0x11d0, 0xBD, 0x3B, 0x00, 0xA0, 0xC9, 0x11, 0xCE, 0x86);
const GUID IID_IPropertyBag = {0x55272A00, 0x42CB, 0x11CE, {0x81, 0x35, 0x00, 0xAA, 0x00, 0x4B, 0xB8, 0x51}};
DEFINE_GUID( CLSID_AudioInputDeviceCategory,0x33d9a762,0x90c8,0x11d0,0xbd,0x43,0x00,0xa0,0xc9,0x11,0xce,0x86);

#endif

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
    ICreateDevEnum *pDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
        CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pDevEnum);

    if (SUCCEEDED(hr)) {
        hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
        if (hr == S_FALSE) {
            hr = VFW_E_NOT_FOUND;
        }
        pDevEnum->Release();
    }
    return hr;
}

void DisplayDeviceInformation(IEnumMoniker *pEnum)
{
    IMoniker *pMoniker = NULL;

    while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);
        if (FAILED(hr)) {
            pMoniker->Release();
            continue;  
        } 

        VARIANT var;
        VariantInit(&var);

        hr = pPropBag->Read(L"Description", &var, 0);
        if (FAILED(hr)) {
            hr = pPropBag->Read(L"FriendlyName", &var, 0);
        }
        if (SUCCEEDED(hr)) {
            printf("%S\n", var.bstrVal);
            VariantClear(&var); 
        }

        hr = pPropBag->Read(L"DevicePath", &var, 0);
        if (SUCCEEDED(hr)) {
            printf("Device path: %S\n", var.bstrVal);
            VariantClear(&var); 
        }
        printf("\n");

        pPropBag->Release();
        pMoniker->Release();
    }
}

int main()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        IEnumMoniker *pEnum;

//        hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
        hr = EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
        if (SUCCEEDED(hr)) {
            DisplayDeviceInformation(pEnum);
            pEnum->Release();
        }
        CoUninitialize();
    }
    return 0;
}

/*
来自 ObjBase.h 文件，MSDN 上介绍至少是 windows7，在xp也可用。(Mingw 下不可用) 
//  IID_PPV_ARGS(ppType)
//      ppType is the variable of type IType that will be filled
//
//      RESULTS in:  IID_IType, ppvType
//      will create a compiler error if wrong level of indirection is used.
//
extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp) 
    {
        // make sure everyone derives from IUnknown
        static_cast<IUnknown*>(*pp);
        
        return reinterpret_cast<void**>(pp);
    }
}

#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)
*/
