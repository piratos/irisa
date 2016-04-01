#include <stdio.h>
#include <time.h>
#include <iwlib.h>

int main(void) 
{
	wireless_scan_head head;
	wireless_scan *result;
	iwrange range;
	int sock;

	/* Open socket to kernel */
	sock = iw_sockets_open();

	/* Get metadata to use for scanning */
	if (iw_get_range_info(sock, "wlan0", &range) < 0)
	{
		printf("Error during iw_get_range. Aborting\n");
		exit(2);
	}

	/* Perform the scan */
	if (iw_scan(sock, "wlan0", range.we_version_compiled, &head) < 0 )
	{
		printf("Error during scan. Aborting\n");
		exit(2);
	}

	/* Traverse results */
	result = head.result;
	while (NULL != result)
	{
		printf("ESSID : %s\n", result->b.essid);
		printf("FREQ : %f\n", result->b.freq);
		result = result->next;
	}

	exit(0);
}