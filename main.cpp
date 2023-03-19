#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include "SecondaryFunction.h"

/*
Вам необходимо создать приложение, имитирующее очередь в окошко.
Для этого необходимо создать два потока работающие с одной разделяемой переменной.

Первый поток имитирует клиента: раз в секунду он обращается к счетчику клиентов и
увеличивает его на 1. Максимальное количество клиентов должно быть параметризировано.

Второй поток имитирует операциониста: раз в 2 секунды он обращается к счетчику
клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.
*/

//std::mutex m;
std::atomic<int> clientCount(0);

void client()
{
	std::wcout << L"Номер потока cl++: " << std::this_thread::get_id() << "\n";

	do
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::lock_guard<std::mutex> grd(m);
		clientCount.fetch_add(1);
		consoleCol(col::br_green);
		std::wcout << L"Клиент +1: " << clientCount.load() << "\n";
		consoleCol(col::cancel);
	} while (clientCount.load() < 5);
}
void operat()
{
	std::wcout << L"Номер потока op--: " << std::this_thread::get_id() << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // теперь "клиент" успеет 2жды плюсануть
	do
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		//std::lock_guard<std::mutex> grd(m);
		clientCount.fetch_sub(1);
		consoleCol(col::br_cyan);
		std::wcout << L"Клиент -1: " << clientCount.load() << "\n";
		consoleCol(col::cancel);
	} while (clientCount.load() > 0);
}

int main(int argc, char** argv)
{
	printHeader(L"Очередь клиентов");

	std::wcout << L"Кол-во аппаратных вычислителей: " << std::thread::hardware_concurrency() << "\n";
	std::wcout << L"Номер потока main: " << std::this_thread::get_id() << "\n";

	std::thread t1(client);
	std::thread t2(operat);
	t1.join();
	t2.join();
	
	std::wcout << "\n";

	return 0;
}
