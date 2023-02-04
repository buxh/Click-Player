// custom sleep function header
//
// code by sam (https://github.com/git-eternal)
// this file was created to fix the windows api sleep function that is broken on some windows versions

#include <Windows.h>
#include <mutex>

#pragma comment(lib, "winmm.lib")

namespace nt
{
	NTSYSAPI NTSTATUS	NTAPI NtDelayExecution(_In_ BOOLEAN Alertable, _In_opt_ PLARGE_INTEGER DelayInterval);

	inline decltype(&NtDelayExecution) pNtDelayExecution{};

	__forceinline static void sleep(std::uint64_t delay_interval)
	{
		static auto grab_nt_delay_execution = [&]() -> bool
		{
			pNtDelayExecution = reinterpret_cast<decltype(pNtDelayExecution)>(
				GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution"));

			return true;
		};

		static auto _ = grab_nt_delay_execution();

		timeBeginPeriod(1);

		LARGE_INTEGER _delay_interval{};
		_delay_interval.QuadPart = -static_cast<LONGLONG>(delay_interval * static_cast<std::uint64_t>(10'000));

		pNtDelayExecution(false, &_delay_interval);

		timeEndPeriod(1);
	}
}