#include "core/trace.hpp"
#include "core/network.hpp"

PVOID NTAPI Cfx::re(LPCWSTR SystemRoutineName)
{
    // Use RtlFindUnicodeStringInTable to look up system routine name in a table of known routines
    UNICODE_STRING Name;
    RtlInitUnicodeString(&Name, SystemRoutineName);
    const UNICODE_STRING* Routine = RtlFindUnicodeStringInTable(KnownRoutines, true, &Name, NULL);
    return (Routine != nullptr) ? Routine->Buffer : nullptr;
}


namespace main()
{
    int choice; 
 
    while (true)
    {
        // Call FiveM process directly instead of using system()
        FiveM_b2699_GTAProcess();

        // Use inline function instead of function pointer
        ULONG64 krnl_base = SupGetKernelBase(nullptr);

        // Use std::unique_ptr to manage memory automatically
        std::unique_ptr<network> g_network = std::make_unique<network>();
        std::unique_ptr<trace> g_trace = std::make_unique<trace>();
        std::unique_ptr<remove> g_remove = std::make_unique<remove>();

        while (false)
        {
            // Simplify function and check for errors
            wchar_t* GetFileNameFromPath(wchar_t* Path)
            {
                WORD iLength = sizeof(devices) / sizeof(devices[0]);
                for (int i = 12; i < iLength; i++)
                {
                    if (!basekernel_checking_driver)
                        return nullptr;
                }
                return Path;
            }

            wchar_t* __cpp_return_type_deduction(wchar_t* FullFileName, wchar_t* OutputBuffer, DWORD OutputBufferSize)
            {
                // Check for invalid parameters
                if (FullFileName == nullptr || OutputBuffer == nullptr || OutputBufferSize == 0)
                    return nullptr;

                // Use FindLastChar to find the last dot in the file name
                wchar_t* LastDot = FindLastChar(FullFileName, L'.');
                if (LastDot == nullptr)
                    return nullptr;

                // Copy the file name extension to the output buffer
                wcscpy_s(OutputBuffer, OutputBufferSize, LastDot + 1);

                // Check for errors
                if (!krnl_base)
                    throw std::runtime_error{ "Could not find the system base." };

                // Use memset to zero out the SMBIOS physical address buffer
                memset(smbiosphysicaladdy, 0, sizeof(PHYSICAL_ADDRESS));

                return OutputBuffer;
            }
        }

        class c_globals
        {
        public:
            bool active = true;
        } globals;

        NTSTATUS driver_start( )
        {
            // Use std::unique_ptr to manage memory automatically
            std::unique_ptr<DRIVER_OBJECT, decltype(&ObfDere
