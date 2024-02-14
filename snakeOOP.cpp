#include <iostream>
#include <conio.h> // Для _kbhit() и _getch()
#include <random>

using namespace std;

class Arena {
public:
	// Длина и ширина арены
	static const int width{ 20 };
	static const int height{ 20 };

	// арена это двумерный массив char = '#'
	char arena[width][height];

	// метод создания арены
	void createArena() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
					arena[i][j] = '#';
				}
				else {
					arena[i][j] = ' ';
				}
			}
		}
	}
	// Вывод арены
	void printArena() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				cout << arena[i][j] << " ";
			}
			cout << endl;
		}
	}
};

class Snake {
public:
	// Змейка это двумерный массив коор-т, пока что сделаю статическим и задам длину с запасом
	static const int max_length{ 100 };
	int snake_cords[max_length][2];

	// Метод для создания змейки и т.к. змейка будет мутировать арену, передадим как аргумент класс арена с ссылкой на экземпляр
	void create_snake(Arena& arena) {
		int positionX = arena.width / 2; // при запуске будет ровно посередине
		int positionY = arena.height / 2;
		snake_cords[0][0] = positionX;
		snake_cords[0][1] = positionY;

		// Обновляем (мутируем) арену
		arena.arena[positionX][positionY] = '0';
	}

	// Метод для движения змейки, в кач-ве аргументов передаем навправление, введенное пользователем и по ссылке экземпляр арены, т.к. опять же будем мутировать
	void move(char direction, Arena& arena) {
		// Получаем "голову" змеи, это будет первый эл-т массива
		int headX = snake_cords[0][0];
		int headY = snake_cords[0][1];

		// Очищаем текущее значение головы
		arena.arena[headX][headY] = ' ';

		switch (direction) {
		case 'w':
			headX--;
			break;
		case 's':
			headX++;
			break;
		case 'd':
			headY++;
			break;
		case 'a':
			headY--;
			break;
		}

		// Обновляем коор-ты змеи (головы)
		snake_cords[0][0] = headX;
		snake_cords[0][1] = headY;

		// Обновляем соответств ячейку арены
		arena.arena[headX][headY] = '0';
	}
};

class Food {
public:

	int foodX;
	int foodY;

	void create_food(Arena& arena) {
		
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(1, 18);

			foodX = dist(gen);
			foodY = dist(gen);

			arena.arena[foodX][foodY] = '8';
	}
};

int main() {

	Arena arena;
	arena.createArena();


	Snake snake;
	snake.create_snake(arena);

	Food food;
	food.create_food(arena);

	arena.printArena(); // Печатаем арену один раз только после создания самой арены и змейки

	char direction;
	while (true) {
		// Проверяем, есть ли ввод с клавиатуры
		if (_kbhit()) {
			// Считываем символ с клавиатуры
			direction = _getch();

			// Ваша логика обработки ввода здесь
			snake.move(direction, arena);

			// Если ввод - q, выходим из цикла
			if (direction == 'q') {
				break;
			}

			// Очистить консоль перед выводом обновленной арены
			system("cls"); // Для Windows

			// Вывести обновленную арену
			arena.printArena();
		}
	}
}