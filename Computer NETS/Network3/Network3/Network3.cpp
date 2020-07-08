#include <cstdlib>
#include <iostream>
#include <winsock.h>
#include <iphlpapi.h>
#define BUFFER_SIZE 256
#pragma comment (lib, "iphlpapi.lib")
#pragma comment (lib, "wsock32.lib")

using namespace std;
unsigned long showARPTable() {
	char type[BUFFER_SIZE], address[BUFFER_SIZE];
	unsigned long realSize = 0;
	PMIB_IPADDRTABLE IPAddrTable = NULL;
	PMIB_IPNETTABLE  IPARPTable = NULL;

	GetIpNetTable(IPARPTable, &realSize, true);
	IPARPTable = (PMIB_IPNETTABLE)malloc(realSize);

	if (GetIpNetTable(IPARPTable, &realSize, true) != NO_ERROR) {
		cout << "Ошибка при получении таблицы!\n" << endl;
		if (IPARPTable)	free(IPARPTable);
		return 1;
	}

	realSize = 0;

	GetIpAddrTable(IPAddrTable, &realSize, true);
	IPAddrTable = (PMIB_IPADDRTABLE)malloc(realSize);
	GetIpAddrTable(IPAddrTable, &realSize, true);
	unsigned long index = -100;
	for (unsigned long i = 0; i < IPARPTable->dwNumEntries; i++) {
		if (IPARPTable->table[i].dwIndex != index) {

			index = IPARPTable->table[i].dwIndex;
			IN_ADDR inaddr;

			for (unsigned long j = 0; j < IPAddrTable->dwNumEntries; j++) {
				if (index != IPAddrTable->table[j].dwIndex)	continue;

				inaddr.S_un.S_addr = IPAddrTable->table[j].dwAddr;
				strcpy_s(address, inet_ntoa(inaddr));
			}

			printf("\nИнтерфейс: %s -- 0x%X\nСетевой адрес      | Физический адрес  | Тип\n", address, index);
		}

		if(IPARPTable->table[i].dwType == 1)		strcpy_s(type, "Другой");
		else if (IPARPTable->table[i].dwType == 2)		strcpy_s(type, "Неверный");
		else if (IPARPTable->table[i].dwType == 3) 		strcpy_s(type, "Динамический");
		else if (IPARPTable->table[i].dwType == 4)		strcpy_s(type, "Статический");
		else						strcpy_s(type, "");

		IN_ADDR inaddr;
		inaddr.S_un.S_addr = IPARPTable->table[i].dwAddr;

		printf("%-18s | %02X:%02X:%02X:%02X:%02X:%02X | %-11s\n",
			inet_ntoa(inaddr),
			IPARPTable->table[i].bPhysAddr[0],
			IPARPTable->table[i].bPhysAddr[1],
			IPARPTable->table[i].bPhysAddr[2],
			IPARPTable->table[i].bPhysAddr[3],
			IPARPTable->table[i].bPhysAddr[4],
			IPARPTable->table[i].bPhysAddr[5],
			type);
	}

	free(IPARPTable);
	puts("");
	return 0;
}

unsigned long addARPRecord() {
	char address[255], macaddr[255], interfaceindex[255];
	MIB_IPNETROW ARPRow;

	cout << "Введите интерфейс	   : ";	cin >> interfaceindex;
	cout << "Введите сетевой адрес : ";	cin >> address;
	cout << "Введите mac	   : ";	cin >> macaddr;

	unsigned long inetaddr = inet_addr(address);

	if (inetaddr == INADDR_NONE) {
		cout << "Неверный сетевой адрес!\n";
		return 1;
	}

	sscanf_s(interfaceindex, "%x", &(ARPRow.dwIndex));
	ARPRow.dwPhysAddrLen = 6;

	sscanf_s(macaddr, "%hx:%hx:%hx:%hx:%hx:%hx",
		&ARPRow.bPhysAddr[0],
		&ARPRow.bPhysAddr[1],
		&ARPRow.bPhysAddr[2],
		&ARPRow.bPhysAddr[3],
		&ARPRow.bPhysAddr[4],
		&ARPRow.bPhysAddr[5]);

	ARPRow.dwAddr = inetaddr;
	ARPRow.dwType = MIB_IPNET_TYPE_STATIC;

	int err = CreateIpNetEntry(&ARPRow);
	if (err == ERROR_ACCESS_DENIED) {
		cout << "Доступ запрещен, запись не добавлена\n";
		return 1;
	}
	else if (err == NO_ERROR) cout << "Ок!\n";
	else {
		cout << "Что-то идет не так, запись не была добавлена\n";
		return 1;
	}

	return 0;
}

unsigned long deleteARPRecord() {
	MIB_IPNETROW ARPRow;
	char address[255], interfaceindex[255];

	cout << "Введите интерфейс	   : ";	cin >> interfaceindex;
	cout << "Введите сетевой адрес : ";	cin >> address;

	unsigned long inetaddr = inet_addr(address);

	if (inetaddr == INADDR_NONE) {
		cout << "Wrong network address!" << endl;
		return 1;
	}

	sscanf_s(interfaceindex, "%x", &(ARPRow.dwIndex));

	ARPRow.dwAddr = inetaddr;

	if (DeleteIpNetEntry(&ARPRow) == ERROR_ACCESS_DENIED) {
		cout << "Доступ запрещен, запись не добавлена\n";
		return 1;
	}
	else if (CreateIpNetEntry(&ARPRow) == NO_ERROR) cout << "Ок!\n";
	else {
		cout << "Что-то идет не так, запись не была добавлена\n";
		return 1;
	}

	return 0;
}

void getIpFromMac() {
	char address[255];
	unsigned long realSize = 0, inetaddr;
	PMIB_IPNETTABLE IPAddrTable = NULL;
	bool found = false;

	GetIpNetTable(IPAddrTable, &realSize, true);
	IPAddrTable = (PMIB_IPNETTABLE)malloc(realSize);
	GetIpNetTable(IPAddrTable, &realSize, true);

	cout << "Введите сетевой адрес: ";	cin >> address;
	inetaddr = inet_addr(address);

	if (inetaddr == INADDR_NONE) {
		cout << "Неверный сетевой адрес!\n";
		return;
	}

	for (unsigned long i = 0; i < IPAddrTable->dwNumEntries; i++)
		if (inetaddr == IPAddrTable->table[i].dwAddr) {
			printf("Mac: %02X-%02X-%02X-%02X-%02X-%02X на интерфейсе с индексом %x\n",
				IPAddrTable->table[i].bPhysAddr[0],
				IPAddrTable->table[i].bPhysAddr[1],
				IPAddrTable->table[i].bPhysAddr[2],
				IPAddrTable->table[i].bPhysAddr[3],
				IPAddrTable->table[i].bPhysAddr[4],
				IPAddrTable->table[i].bPhysAddr[5],
				IPAddrTable->table[i].dwIndex);
			found = true;
		}

	if (!found) cout << "Не найден!\n";
}

int main() {
	int choice = 0;
	setlocale(LC_ALL, "Russian");

	cout << "Выберите:\n 0) Вывод ARP-Таблицы\n 1) Добавить ARP Запись\n 2) Удалить ARP Запись\n 3) MAC из IP\n> "; cin >> choice;

	if (choice == 0)	showARPTable();
	else if (choice == 1)	addARPRecord();
	else if (choice == 2)	deleteARPRecord();
	else if (choice == 3)	getIpFromMac();

	system("pause");
	return 0;
}
