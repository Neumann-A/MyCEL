///-------------------------------------------------------------------------------------------------
// summary:	Implements the processor information class
///-------------------------------------------------------------------------------------------------

#include "ProcessorInformation.h"

#ifdef WIN32
namespace utils
{
    template<typename T>
    T *AdvanceBytes(T *p, SIZE_T cb)
    {
        return reinterpret_cast<T*>(reinterpret_cast<BYTE *>(p) + cb);
    }

    EnumLogicalProcessorInformation::EnumLogicalProcessorInformation(LOGICAL_PROCESSOR_RELATIONSHIP Relationship)
        : m_pinfoBase(nullptr), m_pinfoCurrent(nullptr), m_cbRemaining(0)
    {
        DWORD cb = 0;
        if (GetLogicalProcessorInformationEx(Relationship,
            nullptr, &cb)) return;

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return;
        SetLastError(0);

        m_pinfoBase =
            reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *>
            (LocalAlloc(LMEM_FIXED, cb));
        if (!m_pinfoBase) return;

        if (!GetLogicalProcessorInformationEx(Relationship,
            m_pinfoBase, &cb)) return;

        m_pinfoCurrent = m_pinfoBase;
        m_cbRemaining = cb;
    }

    EnumLogicalProcessorInformation::~EnumLogicalProcessorInformation() { LocalFree(m_pinfoBase); }

    void EnumLogicalProcessorInformation::MoveNext()
    {
        if (m_pinfoCurrent) {
            m_cbRemaining -= m_pinfoCurrent->Size;
            if (m_cbRemaining) {
                m_pinfoCurrent = AdvanceBytes(m_pinfoCurrent,
                    m_pinfoCurrent->Size);
            }
            else {
                m_pinfoCurrent = nullptr;
            }
        }
    }

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* EnumLogicalProcessorInformation::Current()
    {
        return m_pinfoCurrent;
    }

//void PrintMask(KAFFINITY Mask)
//{
//	printf(" [");
//	for (int i = 0; i < sizeof(Mask) * 8; i++) {
//		if (Mask & (static_cast<KAFFINITY>(1) << i)) {
//			printf(" %d", i);
//		}
//	}
//	printf(" ]");
//}
};
#endif
