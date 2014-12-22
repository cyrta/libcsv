
#if ___STDC_VERSION__ >= 199901L
#  include <stdint.h>
#else
#  define SIZE_MAX ((size_t)-1) /* C89 doesn't have stdint.h or SIZE_MAX */
#endif


#include "csv.h"



// ===========================================
// A 'quick and (really) dirty' wget (don't use this code in production!)
// ----------------------------------------------------------------------------
// read a CRLF-terminated line of text from the socket
// return the number of bytes read, -1 if error
// ----------------------------------------------------------------------------
static int read_line(int fd, char *buffer, int max)
{
   char *p = buffer;
   while(max--)
   {
      if(read(fd, p, 1) <= 0) break;
      if(*p == '\r') continue;
      if(*p == '\n') break;
      p++;
   }
   *p = 0;
   return p - buffer;
}
// ----------------------------------------------------------------------------
// read 'len' bytes from the socket
// return the number of bytes read, -1 if error
// ----------------------------------------------------------------------------
static int read_len(int fd, char *buffer, int len)
{
   int ret;
   char *p = buffer;
   while(len > 0)
   {
      ret = read(fd, p, len);
      if(ret <= 0) return -1;
      p += ret;
      len -= ret;
   }
   return p - buffer;
}


   // -------------------------------------------------------------------------
   // test header
   // -------------------------------------------------------------------------
   {
      const char head1[] =
      " Number        Requests per second            CPU               RAM\n"
      "   of     ----------------------------  ----------------  --------------\n"
      "Clients      min       ave       max      user    kernel  SRV MB  SYS MB    Time\n"
      "--------  --------  --------  --------  -------  -------  ------  ------  --------\n";
      const char head2[] =
      " Number        Requests per second\n"
      "   of     ----------------------------\n"
      "Clients      min       ave       max         Time\n"
      "--------  --------  --------  --------  --------------\n";
      const char *head = SERVER_NAME && nbr_pids ? head1 : head2;
      printf("%s", head); // avoid (a) CRLF, (b) GCC warning
      fputs(head, fo);
      fflush(stdout);
   }


int csv_init() 
{
	return 0;
}

int csv_term()
{
	return 0;
}

int csv_parse(char *name)
{
	return 0;
}


