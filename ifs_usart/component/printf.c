/*************************************************************************
	> File Name: printf.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月28日 星期六 22时03分35秒
 ************************************************************************/
#include <stdarg.h>
#include "ifs_lib.h"

#define CONSOLE     IFS_USART1

#ifndef NULL
#define NULL (void *)0
#endif


char* ifs_itoa(int val, char* buf, int radix)
{
    char   *p;             
    char   *firstdig;      
    char   temp;           
    unsigned   digval;     
    p = buf;
    if(val <0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    firstdig = p; 
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
       
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a'); 
        else
            *p++ = (char)(digval + '0');      
    }while(val > 0);
   
    *p-- = '\0';         
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;        
    }while(firstdig < p);  
    return buf;
}

static void ifs_put(char c)
{
    while (IFS_READY != ifs.usart.tx_ready(CONSOLE)) ;
    ifs.usart.put(CONSOLE, c);

}

static void ifs_put_str(char *pc)
{
    while (*pc) {  
        ifs_put(*pc);  
        pc++;  
    }  
}

int print(const char *format, ...)  
{  
    char *pstr = (char *)format;
    va_list arg;  
    va_start(arg, format);  

    while (*pstr) {  
        char buf[15] = {0};
        char ch;
        int in;
        char *pc;
        if (*pstr == '%') {  
            pstr ++;
            switch (*pstr) {  
                case 'D':
                case 'd':
                {
                    in = va_arg(arg, int);
                    pc = ifs_itoa(in, buf, 10);
                    ifs_put_str(pc);
                }
                break;
                case 'X':
                case 'x':
                {
                    in = va_arg(arg, int);
                    pc = ifs_itoa(in, buf, 16);
                    ifs_put_str(pc);
                }
                break;
                case 'C':
                case 'c':  
                {
                    ch = (char)va_arg(arg, int);  
                    ifs_put(ch);  
                }
                break;  
                case 'S':
                case 's':  
                {
                    pc = va_arg(arg, char *);  
                    ifs_put_str(pc);
                }
                break;  
                default:  
                break;  
            }  
        } else {  
            ifs_put(*pstr);  
        }  
        pstr++;  
    }  
    va_end(arg);  
    return 0;
}

