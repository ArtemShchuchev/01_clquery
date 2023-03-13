#include <chrono>
#include <thread>
#include "SecondaryFunction.h"

/*
Вам необходимо создать приложение, имитирующее очередь в окошко.
Для этого необходимо создать два потока работающие с одной разделяемой переменной.

Первый поток имитирует клиента: раз в секунду он обращается к счетчику клиентов и
увеличивает его на 1. Максимальное количество клиентов должно быть параметризировано.

Второй поток имитирует операциониста: раз в 2 секунды он обращается к счетчику
клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.
*/

void client(int& n)
{
	using namespace std::chrono_literals;
	do
	{
		std::this_thread::sleep_for(1s);
		++n;
		std::wcout << L"Клиент +1: " << n << "\n";
	} while (n < 5);
}
void operat(int& n)
{
	using namespace std::chrono_literals;
	do
	{
		std::this_thread::sleep_for(2s);
		--n;
		std::wcout << L"Клиент -1: " << n << "\n";
	} while (n > 0);
}

int main(int argc, char** argv)
{
	printHeader(L"Очередь клиентов");

	std::wcout << L"Кол-во аппаратных вычислителей: " << std::thread::hardware_concurrency() << "\n";
	std::wcout << L"Номер потока #id: " << std::this_thread::get_id() << "\n";

	int clientCount(0);

	// минус почему то не с каждым запуском работает??!
	// не каждый раз считает до 0?
	std::thread t1(client, std::ref(clientCount));
	std::thread t2(operat, std::ref(clientCount));
	t1.join();
	t2.join();
	
	std::wcout << "\n";

	return 0;
}
