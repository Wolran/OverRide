#include <sys/prctl.h>

int main()
{
	prctl(1, PR_CAPBSET_READ );
}