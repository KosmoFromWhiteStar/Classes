#include <iostream>


#define X coordinate[1]
#define Y coordinate[0]
#define YSIZE monitor.size_mon[0]
#define XSIZE monitor.size_mon[1]

class Monitor
{
public:
	const int size_mon[2] = { 100, 100 };
};

bool compare(std::string inP_word, std::string command)
{
	for (int i = 0; i < inP_word.length() && i < command.length(); i++)
	{
		if (inP_word[i] != command[i])
		{
			return false;
		}
	}
	return true;
}


class Window
{
	int coordinate[2] = { 10, 10 };
	int size[2] = { 50, 80 };
	Monitor monitor;

public:
	void move()
	{
		int pos_new[2];
		bool tru_size = false;
		do
		{
			tru_size = false;
			std::cout << "move window: " << std::endl;
			std::cin >> pos_new[0] >> pos_new[1];
			if ((coordinate[0] + pos_new[0] < 0 || coordinate[1] + pos_new[1] < 0)
			 || (coordinate[0] + pos_new[0] + size[0] > YSIZE || coordinate[1] + pos_new[1]+ size[1] > XSIZE))
			{
				std::cout << "Uncorrect window size\n";
				tru_size = true;
			}
		} while (tru_size);

		coordinate[0] += pos_new[0];
		coordinate[1] += pos_new[1];
		std::cout << "x: " << coordinate[0] << " y: " << coordinate[1] << std::endl;
	}
	void resize()
	{
		int nw_size[2];
		bool tru_size = false;
		do
		{
			tru_size = false;
			std::cout << "resize window: " << std::endl;
			std::cin >> nw_size[0] >> nw_size[1];
			if (nw_size[0] < 0 || nw_size[1] < 0)
			{
				std::cout << "Uncorrect window size\n";
				tru_size = true;
			}
			else
			{
				size[0] = nw_size[0];
				size[1] = nw_size[1];
			}

			if (size[0] > monitor.size_mon[0] || size[1] > monitor.size_mon[1])
			{
				std::cerr << "Size bigger than window. Err. try again\n";
				tru_size = true;
			}
		} while (tru_size);
		std::cout << "length: " << size[0] << " width: " << size[1] << std::endl;
	}
	void display()
	{
		system("cls");
		for (int y = YSIZE; y >= -1; y--)
		{
			for (int x = XSIZE; x >= -1; x--)
			{
				if (x == -1 && y == -1) std::cout << "+";
				else if (x == XSIZE && y == YSIZE) std::cout << "+";
				else if (x == -1 && y == YSIZE)std::cout << "+";
				else if (x == XSIZE && y == -1) std::cout << "+";
				else if (x == -1 || x == XSIZE) std::cout << "|";
				else if (y == -1 || y == YSIZE) std::cout << "=";
				else if (((YSIZE - y-1) >= Y && (YSIZE - y - 1) - Y <= size[0]) 
						&& ((XSIZE - x - 1) >= X && (XSIZE - x - 1) - X <= size[1]))
				{
					std::cout << "1";
				}
				else
				{
					std::cout << '0';
				}
			}
			std::cout << y;
			std::cout << std::endl;
		}
	}
	void status()
	{
		std::cout << "coordinate: x " << coordinate[1] << " y: " << coordinate[0] << std::endl;
		std::cout << "Size: x " << size[1] << " y: " << size[0] << std::endl;
	}
};



int main()
{
	Window* window = new Window;
	do {
		std::cout << ">:\n";
		std::string com;
		std::cin >> com;

		if (compare(com, "move")) window->move();
		else if (compare(com, "resize")) window->resize();
		else if (compare(com, "display")) window->display();
		else if (compare(com, "status")) window->status();
		else if (compare(com, "exit")) break;
		else std::cerr << "Unknow command\n";

	} while (true);

	delete window;
	window = nullptr;
}