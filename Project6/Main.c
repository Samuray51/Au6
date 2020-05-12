//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<windows.h>
//#include<locale.h>
//int test(char *mas, int k)
//{
//	int i, k1 = 0, k2 = 0, k3 = 0, k4 = 0;
//	for (i = 0; i < k; i++)
//	{
//		if (mas[i] >= '0' && mas[i] <= '9')
//		{
//			k1 = k1 + 1;
//		}
//		if (mas[i] >= 'A' && mas[i] <= 'Z')
//		{
//			k2 = k2 + 1;
//		}
//		if (mas[i] >= 'a' && mas[i] <= 'z')
//		{
//			k3 = k3 + 1;
//		}
//		if ((mas[i] >= 33 && mas[i] <= 47) || (mas[i] >= 58 && mas[i] <= 64) || (mas[i] >= 91 && mas[i] <= 96))
//		{
//			k4 = k4 + 1;
//		}
//	}
//	if (k1 >= 4 && k4 >= 4 && k2 >= 3 && k3 >= 3)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//
//
//int main()
//{
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	setlocale(LC_ALL, "RUS");
//	int n = 21, save = 0, i = 0; 
//	char *mas;
//	mas = (char*)malloc(n * sizeof(char));
//	printf("Enter password max 20 symbol:\n");
//	while (1)
//	{
//		for (i = 0; i < n + 1; i++)
//		{
//			if (i < 0)
//			{
//				i = 0;
//			}
//			mas[i] = _getch();
//			if (mas[i] == '\b')
//			{
//				printf("\b \b");
//				i = i - 2;
//				continue;
//			}
//			if (mas[i] == 0x0D)
//			{
//				break;
//			}
//			else if (mas[i] == 0x0D)
//			{
//				i = i - 1;
//				continue;
//			}
//			if (mas[i] == (char)-32 || mas[i] == (char)83)
//			{
//				i = i - 1;
//				continue;
//			}
//			printf("*");
//		}
//		printf("\n");
//		if (i < 15)
//		{
//			save = 0;
//			printf("Bad password!\n");
//			continue;
//		}
//		save = test(mas, i - 1);
//		if (save == 1)
//		{
//			printf("Good password!\n");
//			break;
//		}
//		else
//		{
//			printf("Bad password!\n");
//		}
//	}
//	system("pause");
//	return 0;
//}




#pragma comment(lib, "netapi32.lib") 

#include <stdio.h> 
#include <assert.h> 
#include <windows.h> 
#include <lm.h> 
#include <locale.h>
int main()
{
	setlocale(LC_ALL, "RUS");
	LPUSER_INFO_1 pBuf = NULL;
	LPUSER_INFO_1 pTmpBuf;
	DWORD dwLevel = 1;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;

	printf("\nUser account on %s: \n", pszServerName);


	do
	{
		nStatus = NetUserEnum(pszServerName,
			dwLevel,
			FILTER_NORMAL_ACCOUNT,
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);


		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL)
					{
						fprintf(stderr, "An access violation has occurred\n");
						break;
					}
					if (pTmpBuf->usri1_priv != USER_PRIV_ADMIN)
					{
						wprintf(L"\t— %s\n", pTmpBuf->usri1_name);
						dwTotalCount++;
					}
					pTmpBuf++;
				}
			}
		}
		else
		{
			printf("A system error has occurred: %d\n", nStatus);
		}
		if (pBuf != NULL)
		{
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);
	if (pBuf != NULL)
	{
		NetApiBufferFree(pBuf);
	}
	printf("\nTotal of %d entries enumerated\n", dwTotalCount);

	system("pause");
	return 0;
}