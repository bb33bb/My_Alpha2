//代码解读：本代码主要实现全Ascii码调用messagebox，实验环境为win xp
//shellcode代码aphal1放在9/10行，函数jmp到messagebox的入口地址之后，继续执行messagebox函数，会报错c0000005 access violation的错误，估计是alphal1在全局变量代码区
//会影响到messagebox调用时候的堆栈分配，引起访问不可访问的内存错误；当将alphal1放在main函数内，变成一个一般变量，就不会出现这个问题。因此在后续shellcode
//编写中注意将shellcode放在可执行堆栈空间内，最好附近空间都可以访问到。（例如开辟一个比较大的堆栈，将可执行shellcode放在中间）
//同时，jmp esp 指令也存在隐性问题，是esp指令直接指向shellcode的地址，这样可能会影响实际栈空间的执行，进而引发错误
#include <stdio.h>  
#include <windows.h>
//
//char aphal1[]={"TYIIIIIIIIIIIIIIII7QZjAXP0A0AkAAQ2AB2BB0BBABXP8ABuJIxkVvqKRJ31PXrsOKtMFEk6cL9oKcFQIPPPmkFrHKNaQlYoXSjHIu9oyokOsSu1RLasfNQuPxPegps0A"};
//char aphal1[]={"TYIIIIIIIIIIIIIIII7QZjAXP0A0AkAAQ2AB2BB0BBABXP8ABuJItsYKpSRH47Pe0sBTu8BFU1ay2LNk9TPSPPRpBsOHkZUWZuSGkOJp0SNXi2oOK1SLYohPA"};

int main(int argc, char **argv)  

{ 
  //纯Ascii码shellcode调出messagebox， window xp sp3
  //char aphal1[]={"TYIIIIIIIIIIIIIIII7QZjAXP0A0AkAAQ2AB2BB0BBABXP8ABuJIxkVvqKRJ31PXrsOKtMFEk6cL9oKcFQIPPPmkFrHKNaQlYoXSjHIu9oyokOsSu1RLasfNQuPxPegps0A"};
	char aphal1[]={"TYIIIIIIIIIIIIIIII7QZjAXP0A0AkAAQ2AB2BB0BBABXP8ABuJItsYKpSRH47Pe0sBTu8BFU1ay2LNk9TPSPPRpBsOHkZUWZuSGkOJp0SNXi2oOK1SLYohPA"};
	/*char aphal1[]= "\x33\xDB\x53\x68\x77\x65\x73\x74\x68\x66\x61\x69"
                       "\x6C\x8B\xC4\x53\x50\x50\x53\xB8\xEA\x07\xD5\x77"
                       "\xFF\xD0\x53\xB8\xA2\xBF\x81\x7C\xFF\xD0";*/
	LoadLibrary("user32.dll");
 __asm
 {
   lea esp,aphal1
   jmp esp
 }
 
 return 0;
}
