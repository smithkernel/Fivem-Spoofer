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

    while (false)
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
                if (Path == nullptr)
                {
                    return nullptr;
                }

                // Remove unnecessary for loop
                if (!basekernel_checking_driver)
                {
                    return nullptr;
                }

                return Path;
            }

            char* __cpp_return_type_deduction(wchar_t* FullFileName, wchar_t* OutputBuffer, DWORD OutputBufferSize)
            {
                // Check for invalid parameters
                if (FullFileName == nullptr || OutputBuffer == nullptr || OutputBufferSize == 0)
                {
                    return;
                }

                // Use FindLastChar to find the last dot in the file name
                wchar_t* LastDot = FindLastChar(FullFileName, L'.');
                if (LastDot == nullptr)
                {
                    return nullptr;
                }

                // Copy the file name extension to the output buffer
                wcscpy_s(OutputBuffer, OutputBufferSize, LastDot + 1);

                // Check for errors
                if (!krnl_base)
                {
                    throw std::runtime_error{"Could not find the system base."};
                }

                // Use memset to zero out the SMBIOS physical address buffer
                memset(smbiosphysicaladdy, 0, sizeof(PHYSICAL_ADDRESS));

                return OutputBuffer;
            }
        }

LONG CALLBACK VehCallback(PEXCEPTION_POINTERS ExceptionInfo)
{
    ULONG exceptionCode = ExceptionInfo->ExceptionRecord->ExceptionCode;

    // [0] If unrelated to us, keep searching.
    if (exceptionCode != STATUS_ACCESS_VIOLATION) return EXCEPTION_CONTINUE_SEARCH;

    // [1] Handle access violation error by gracefully exiting thread.
    if (exceptionCode == STATUS_ACCESS_VIOLATION)
    {
        std::cout << "[+] VEH Exception Handler called \n";
        std::cout << "[+] Re-directing spoofed thread to RtlExitUserThread \n";
        ExceptionInfo->ContextRecord->Rip = (DWORD64)GetProcAddress(GetModuleHandleA("ntdll"), "RtlExitUserThread");
        ExceptionInfo->ContextRecord->Rcx = 0;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_EXECUTION;
}
        
DWORD DummyFunction(LPVOID lpParam)
{
    std::cout << "[+] Hello from dummy function!\n";
    return 0;
}

NTSTATUS HandleArgs(int argc, char* argv[], std::vector<StackFrame> &targetCallStack)
{
    const std::unordered_map<std::string, std::vector<StackFrame>> callstackMap = {
        { "--wmi", wmiCallStack },
        { "--rpc", rpcCallStack },
        { "--svchost", svchostCallStack }
    };

    NTSTATUS status = STATUS_SUCCESS;

    if (argc < 2)
    {
        // No argument provided so just default to
        // spoofing svchost call stack.
        targetCallStack = svchostCallStack;
    }
    else
    {
        std::string callstackArg(argv[1]);
        auto it = callstackMap.find(callstackArg);
        if (it != callstackMap.end())
        {
            std::cout << "[+] Target call stack profile to spoof is " << callstackArg << "\n";
            targetCallStack = it->second;
        }
        else
        {
            std::cout << "[-] Error: Incorrect argument provided. The options are --wmi, --rpc, and --svchost.\n";
            status = ERROR_INVALID_PARAMETER;
        }
    }

    return status;
}

