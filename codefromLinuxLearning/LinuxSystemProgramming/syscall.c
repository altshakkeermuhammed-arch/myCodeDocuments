#include <sys/syscall.h>
#include <sys/types.h>

int main()
{
	pid_t tid;
	tid = syscall(SYS_gettid);
}

