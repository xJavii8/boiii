#include <std_include.hpp>
#include "macho_loader.hpp"
#include "utils/hook.hpp"

#include <pthread.h>

#pragma region runtime

int NSGetExecutablePath(char* buf, uint32_t* bufsize)
{
	*bufsize = GetModuleFileNameA(GetModuleHandleA(nullptr), buf, *bufsize);
	return *bufsize == 0;
}

int onesub()
{
	return 1;
}

int nullsub()
{
	return 0;
}

void* resolve_symbol(const std::string& module, const std::string& function);

void* dlsym(void* handle, const char* name)
{
	return resolve_symbol({}, name);
}

char* realpath(const char* path, char* resolved_path)
{
	return _fullpath(resolved_path, path, 0x7FFFFFFF);
}

std::vector<std::function<void()>> exit_handlers;

int cxa_atexit(void (*func)(void*), void* arg, void* dso_handle)
{
	exit_handlers.emplace_back([arg, func]()
	{
		func(arg);
	});

	return 0;
}

#pragma endregion

void* create_calling_convention_wrapper(void* func)
{
	return utils::hook::assemble([func](utils::hook::assembler& a)
	{
		a.push(rax);
		a.pushad64();

		a.push(rdi);
		a.push(rsi);
		a.push(rdx);
		a.push(rcx);

		// More than 4 arguments not supported yet

		a.pop(r9);
		a.pop(r8);
		a.pop(rdx);
		a.pop(rcx);

		a.call(func);

		a.mov(ptr(rsp, 0x80, 8), rax);

		a.popad64();
		a.pop(rax);
		a.ret();
	});
}

void wrap_calling_convention(std::unordered_map<std::string, void*>& symbols)
{
	auto copy = symbols;
	symbols.clear();

	std::unordered_map<void*, void*> function_mapping;

	for (auto i = copy.begin(); i != copy.end(); ++i)
	{
		if (function_mapping.find(i->second) == function_mapping.end())
		{
			function_mapping[i->second] = create_calling_convention_wrapper(i->second);
		}
	}

	for (auto i = copy.begin(); i != copy.end(); ++i)
	{
		symbols[i->first] = function_mapping[i->second];
	}
}

bool isPrime(int n)
{
	// Corner cases
	if (n <= 1) return false;
	if (n <= 3) return true;

	// This is checked so that we can skip 
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0) return false;

	for (int i = 5; i * i <= n; i = i + 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	return true;
}

size_t
__next_prime(size_t prime)
{
	if (prime <= 1)
		return 2;

	bool found = false;

	// Loop continuously until isPrime returns
	// true for a number greater than n
	while (!found)
	{
		prime++;

		if (isPrime(static_cast<int>(prime)))
			found = true;
	}

	return prime;
}

std::unordered_map<std::string, void*> build_symbol_map()
{
	std::unordered_map<std::string, void*> symbols;

	// Symbols that need calling convention wrapping

	symbols["__Znwm"] = malloc;
	symbols["__Znam"] = malloc;
	symbols["__ZdlPv"] = free;
	symbols["__ZdaPv"] = free;

	symbols["__NSGetExecutablePath"] = NSGetExecutablePath;

	symbols["_strlen"] = strlen;
	symbols["_memcpy"] = memcpy;

	symbols["___cxa_guard_acquire"] = onesub;
	symbols["___cxa_guard_release"] = onesub;

	symbols["_dlsym"] = dlsym;
	symbols["realpath"] = realpath;
	symbols["___cxa_atexit"] = cxa_atexit;

	symbols["_pthread_attr_destroy"] = pthread_attr_destroy;
	symbols["_pthread_attr_init"] = pthread_attr_init;
	symbols["_pthread_attr_setdetachstate"] = pthread_attr_setdetachstate;
	symbols["_pthread_attr_setstacksize"] = pthread_attr_setstacksize;
	symbols["_pthread_cancel"] = pthread_cancel;
	symbols["_pthread_cond_broadcast"] = pthread_cond_broadcast;
	symbols["_pthread_cond_destroy"] = pthread_cond_destroy;
	symbols["_pthread_cond_init"] = pthread_cond_init;
	symbols["_pthread_cond_signal"] = pthread_cond_signal;
	symbols["_pthread_cond_timedwait"] = pthread_cond_timedwait;
	symbols["_pthread_cond_wait"] = pthread_cond_wait;
	symbols["_pthread_create"] = pthread_create;
	symbols["_pthread_detach"] = pthread_detach;
	symbols["_pthread_equal"] = pthread_equal;
	symbols["_pthread_exit"] = pthread_exit;
	symbols["_pthread_getname_np"] = pthread_getname_np;
	symbols["_pthread_getschedparam"] = pthread_getschedparam;
	symbols["_pthread_getspecific"] = pthread_getspecific;
	symbols["_pthread_join"] = pthread_join;
	symbols["_pthread_key_create"] = pthread_key_create;
	symbols["_pthread_key_delete"] = pthread_key_delete;
	//symbols["_pthread_mach_thread_np"] = pthread_mach_thread_np;
	//symbols["_pthread_main_np"] = pthread_main_np;
	symbols["_pthread_mutex_destroy"] = pthread_mutex_destroy;
	symbols["_pthread_mutex_init"] = pthread_mutex_init;
	symbols["_pthread_mutex_lock"] = pthread_mutex_lock;
	symbols["_pthread_mutex_trylock"] = pthread_mutex_trylock;
	symbols["_pthread_mutex_unlock"] = pthread_mutex_unlock;
	symbols["_pthread_mutexattr_destroy"] = pthread_mutexattr_destroy;
	symbols["_pthread_mutexattr_init"] = pthread_mutexattr_init;
	symbols["_pthread_mutexattr_settype"] = pthread_mutexattr_settype;
	symbols["_pthread_once"] = pthread_once;
	symbols["_pthread_rwlock_destroy"] = pthread_rwlock_destroy;
	symbols["_pthread_rwlock_init"] = pthread_rwlock_init;
	symbols["_pthread_rwlock_rdlock"] = pthread_rwlock_rdlock;
	symbols["_pthread_rwlock_tryrdlock"] = pthread_rwlock_tryrdlock;
	symbols["_pthread_rwlock_trywrlock"] = pthread_rwlock_trywrlock;
	symbols["_pthread_rwlock_unlock"] = pthread_rwlock_unlock;
	symbols["_pthread_rwlock_wrlock"] = pthread_rwlock_wrlock;
	symbols["_pthread_self"] = pthread_self;
	symbols["_pthread_setcanceltype"] = pthread_setcanceltype;
	symbols["_pthread_setname_np"] = pthread_setname_np;
	symbols["_pthread_setschedparam"] = pthread_setschedparam;
	symbols["_pthread_setspecific"] = pthread_setspecific;
	//symbols["_pthread_sigmask"] = pthread_sigmask;

	symbols["__ZNSt3__112__next_primeEm"] = __next_prime;

	wrap_calling_convention(symbols);

	// Symbols without calling convention wrapping

	static uint64_t guard = 0x1337;
	symbols["___stack_chk_guard"] = &guard;

	static uint64_t point[2] = {0, 0};
	symbols["_NSZeroPoint"] = &point;

	return symbols;
}

void* resolve_symbol(const std::string& module, const std::string& function)
{
	static const auto symbol_map = build_symbol_map();

	const auto symbol = symbol_map.find(function);
	if (symbol != symbol_map.end())
	{
		return symbol->second;
	}

	printf("Needed symbol %s (%s)\n", function.data(), module.data());

	return nullptr;
}

int __stdcall WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
#if _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	macho_loader loader("./CoDBlkOps3_Exe", resolve_symbol);

	for (const auto& constructor : loader.get_mapped_binary().get_constructors())
	{
		constructor();
	}

	const auto entry_point = utils::hook::assemble([&loader](utils::hook::assembler& a)
	{
		a.sub(rsp, 8);
		a.pushad64();

		a.xor_(rdi, rdi);
		a.xor_(rsi, rsi);

		a.call(loader.get_mapped_binary().get_entry_point());

		a.popad64();
		a.add(rsp, 8);
		a.ret();
	});

	static_cast<void(*)()>(entry_point)();

	for (const auto& exit_handler : exit_handlers)
	{
		exit_handler();
	}

	for (const auto& destructor : loader.get_mapped_binary().get_destructors())
	{
		destructor();
	}

	return 0;
}
