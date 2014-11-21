#include "ClassFactory.h"
#include "AvidContextMenu.h"

extern long g_cDllRef;

ClassFactory::ClassFactory() : m_cRef(1)
{
	InterlockedIncrement(&g_cDllRef);
}

ClassFactory::~ClassFactory()
{
	InterlockedDecrement(&g_cDllRef);
}

IFACEMETHODIMP ClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	static const QITAB qit[] = { QITABENT(ClassFactory, IClassFactory), { 0 } };
	return QISearch(this, qit, riid, ppv);
}

IFACEMETHODIMP_(ULONG) ClassFactory::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

IFACEMETHODIMP_(ULONG) ClassFactory::Release()
{
	ULONG cRef = InterlockedDecrement(&m_cRef);
	if (cRef == 0)
	{
		delete this;
	}
	return cRef;
}

IFACEMETHODIMP ClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	HRESULT hr = CLASS_E_NOAGGREGATION;

	if (pUnkOuter == NULL)
	{
		hr = E_OUTOFMEMORY;
		AvidContextMenu *pExt;

		try
		{
			pExt = new AvidContextMenu();
		}
		catch(std::bad_alloc &e)
		{
			OutputDebugString(reinterpret_cast<LPCWSTR> (e.what()));
			return hr;
		}

		hr = pExt->QueryInterface(riid, ppv); // query interface of extention of context menu
		pExt->Release();
	}
	return hr;
}

IFACEMETHODIMP ClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		InterlockedIncrement(&g_cDllRef);
	}
	else
	{
		InterlockedDecrement(&g_cDllRef);
	}
	return S_OK;
}