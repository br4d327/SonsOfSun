#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include "constants.h"


using namespace std;
using namespace sf;

int MATRIX[13][13];

bool dirUp, dirRight, dirDown, dirLeft, start, boss;
int widht = 30, randDir, height = 30, x, y;
int WORLD[130][130];

class Entity {
public:
	float mx, my, x, y, speed, moveTimer;
	int w, h, hp;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; hp = 100; mx = 0; my = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
};

void createWorld() {

	int x, y;
	int randDir, mainRoomX, mainRoomY, countOfRooms;
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			MATRIX[x][y] = 0;
		}
	}
	mainRoomX = 7;
	mainRoomY = 7;
	MATRIX[mainRoomX][mainRoomY] = 3;

	x = mainRoomX;
	y = mainRoomY;

	countOfRooms = RandomNumber(3, 6);

	for (int n = 1; n < countOfRooms; n++) {


		randDir = RandomNumber(1, 4);
		switch (randDir) {
		case 1:
			if (MATRIX[x][y - 1] == 0) {
				MATRIX[x][y - 1] = 1;
				y = y - 1;
				if (n == (countOfRooms - 1)) {
					MATRIX[x][y] = 2;
				}
			}
			else if ((MATRIX[x][y - 1] == 1) || (MATRIX[x][y - 1] == 3)) {
				n--;
			}
			else if ((MATRIX[x + 1][y] == 1) || (MATRIX[x + 1][y] == 3) || (MATRIX[x - 1][y] == 3) || (MATRIX[x - 1][y] == 1) || (MATRIX[x][y + 1] == 1) || (MATRIX[x][y + 1] == 3) || (MATRIX[x][y - 1] == 1) || (MATRIX[x][y - 1] == 3)) { n = countOfRooms; }
			break;
		case 2:
			if (MATRIX[x + 1][y] == 0) {
				MATRIX[x + 1][y] = 1;
				x = x + 1;
				if (n == countOfRooms - 1) {
					MATRIX[x][y] = 2;
				}
			}
			else if ((MATRIX[x + 1][y] == 1) || (MATRIX[x][y - 1] == 3)) {
				n--;
			}
			else if ((MATRIX[x + 1][y] == 1) || (MATRIX[x + 1][y] == 3) || (MATRIX[x - 1][y] == 3) || (MATRIX[x - 1][y] == 1) || (MATRIX[x][y + 1] == 1) || (MATRIX[x][y + 1] == 3) || (MATRIX[x][y - 1] == 1) || (MATRIX[x][y - 1] == 3)) { n = countOfRooms; }
			break;
		case 3:
			if (MATRIX[x][y + 1] == 0) {
				MATRIX[x][y + 1] = 1;
				y = y + 1;
				if (n == countOfRooms - 1) {
					MATRIX[x][y] = 2;
				}
			}
			else if ((MATRIX[x][y + 1] == 1) || (MATRIX[x][y - 1] == 3)) {
				n--;
			}
			else if ((MATRIX[x + 1][y] == 1) || (MATRIX[x + 1][y] == 3) || (MATRIX[x - 1][y] == 3) || (MATRIX[x - 1][y] == 1) || (MATRIX[x][y + 1] == 1) || (MATRIX[x][y + 1] == 3) || (MATRIX[x][y - 1] == 1) || (MATRIX[x][y - 1] == 3)) { n = countOfRooms; }
			break;
		case 4:
			if (MATRIX[x - 1][y] == 0) {
				MATRIX[x - 1][y] = 1;
				x = x - 1;
				if (n == countOfRooms - 1) {
					MATRIX[x][y] = 2;
				}
			}
			else if ((MATRIX[x - 1][y] == 1) || (MATRIX[x][y - 1] == 3)) {
				n--;
			}
			else if ((MATRIX[x + 1][y] == 1) || (MATRIX[x + 1][y] == 3) || (MATRIX[x - 1][y] == 3) || (MATRIX[x - 1][y] == 1) || (MATRIX[x][y + 1] == 1) || (MATRIX[x][y + 1] == 3) || (MATRIX[x][y - 1] == 1) || (MATRIX[x][y - 1] == 3)) { n = countOfRooms; }
			break;
		}
	}
}
void createDoor(int x, int y, bool up, bool right, bool down, bool left, bool boss, bool start) {
	for (int height = 0; height < 10; height++) {
		for (int width = 0; width < 10; width++) {
			if (up) {					//сделали вход сверху
				WORLD[x * 10 + 5][y * 10] = 0;
				WORLD[x * 10 + 4][y * 10] = 0;
				WORLD[x * 10 + 5][y * 10 - 1] = 0;
				WORLD[x * 10 + 4][y * 10 - 1] = 0;
				up = false;
			}
			if (down) {					//снизу
				WORLD[x * 10 + 5][y * 10] = 0;
				WORLD[x * 10 + 5][y * 10 + 1] = 0;
				WORLD[x * 10 + 4][y * 10] = 0;
				WORLD[x * 10 + 4][y * 10 + 1] = 0;
				down = false;
			}
			if (left) {					//слеве
				WORLD[x * 10][y * 10 + 4] = 0;
				WORLD[x * 10][y * 10 + 5] = 0;
				WORLD[x * 10 - 1][y * 10 + 4] = 0;
				WORLD[x * 10 - 1][y * 10 + 5] = 0;
				left = false;
			}
			if (right) {					//справе
				WORLD[x * 10 + 2][y * 10 + 4] = 0;
				WORLD[x * 10 + 2][y * 10 + 5] = 0;
				WORLD[x * 10 + 1][y * 10 + 4] = 0;
				WORLD[x * 10 + 1][y * 10 + 5] = 0;
				right = false;
			}
		}
	}
}
void generateMap() {
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			dirUp = false; dirLeft = false; dirRight = false; dirDown = false;
			if ((MATRIX[x][y] == 1) || (MATRIX[x][y] == 2) || (MATRIX[x][y] == 3)) {
				if (MATRIX[x - 1][y] != 0) {
					dirLeft = true;
				}
				if (MATRIX[x + 1][y] != 0) {
					dirRight = true;
				}
				if (MATRIX[x][y - 1] != 0) {
					dirUp = true;
				}
				if (MATRIX[x][y + 1] != 0) {
					dirDown = true;
				}
				cout << x << y << endl;
				for (int height = 0; height < 10; height++) {
					for (int width = 0; width < 10; width++) {
						if ((width == 0) || (width == 9) || (height == 0) || (height == 9)) {
							WORLD[(width + x * 10) + 1][(height + y * 10) + 1] = 1;     // по краям карты обозначил границы
						}
					}
				}
			}
		}
	}
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 13; x++) {
			if ((MATRIX[x][y] == 1) || (MATRIX[x][y] == 2) || (MATRIX[x][y] == 3)) {
				if (MATRIX[x - 1][y] != 0) {
					dirLeft = true;
				}
				if (MATRIX[x + 1][y] != 0) {
					dirRight = true;
				}
				if (MATRIX[x][y - 1] != 0) {
					dirUp = true;
				}
				if (MATRIX[x][y + 1] != 0) {
					dirDown = true;
				}
				createDoor(x, y, dirUp, dirRight, dirDown, dirLeft, boss, start);
			}
		}
	}
}
class Hero:public Entity
{

public:
	int direction;
	
	Hero(Image &image, float X, float Y, float W, float H,String Name):Entity(image,X,Y,W,H,Name) {
		direction = 0;
		speed = 0;
		mx = 0;
		my = 0;
		w = W;
		h = H;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}

	void update(float time) {
		switch (direction) {
		case 0:
			mx = speed;
			my = 0;
			break;
		case 1:
			mx = -speed;
			my = 0;
			break;
		case 2:
			mx = 0;
			my = speed;
			break;
		case 3:
			mx = 0;
			my = -speed;
			break;
		}
		x += mx * time;
		y += my * time;
		speed = 0;
		sprite.setPosition(x, y);
		collisionwMap();
	}
	void collisionwMap() {
	
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (WORLD[i][j] == 1)
				{
					if (my>0)
					{
						y = i * 32 - h;
					}
					if (my<0)
					{
						y = i * 32 + 32;
					}
					if (mx>0)
					{
						x = j * 32 - w;
					}
					if (mx < 0)
					{
						x = j * 32 + 32;
					}
				}

			}
	}
	float getPlayerPositionX() {
		return x;
	}
	float getPlayerPositionY() {
		return y;
	}
};

class Enemy :public Entity {
public:
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "rat") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			mx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if (WORLD[i][j] == 0)
				{
					//if?? тут надо как то сказать, что крыс врезался ((
				}
			}
	}

	void update(float time)
	{
		if (name == "rat") {

								
			checkCollisionWithMap(mx, 0);
			x += mx * time;
			sprite.setPosition(x + w / 2, y + h / 2); 
		}
	}
};

View view;

void getPlayerCoord(float x, float y) {
	view.setCenter(x, y);
}


void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("img/newgame.png");// загружаем картинки меню ( красоту наведем потом )
	menuTexture2.loadFromFile("img/exit.png");
	menuBackground.loadFromFile("img/bg.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1; // делаем меню точкой старта
	int menuNum = 0;
	menu1.setPosition(100, 500); // добавляем на экран расположение кнопок
	menu2.setPosition(100, 600);
	menuBg.setPosition(0, 0);
	/**********************Меню**********************/
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 500, 350, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::White); menuNum = 1; }// когда наведена мышь
		if (IntRect(100, 600, 350, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::White); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	/************************************************/
}
////////////////////// INGAME MENU ////////////////////////
void pauseMenu(RenderWindow & window, float x,float y) {
	Texture pauseContinue, pauseExit, pauseMainmenu;
	pauseContinue.loadFromFile("img/continue.png");
	pauseMainmenu.loadFromFile("img/menu.png");
	pauseExit.loadFromFile("img/exit.png");
	Sprite continueButton(pauseContinue), exitButton(pauseExit), menuButton(pauseMainmenu);
	int menuNum = 0;
	bool isPause = 1;
	continueButton.setPosition(x - 125, y - 160);
	menuButton.setPosition(x - 125, y - 50);
	exitButton.setPosition(x - 125, y + 60);
	while (isPause)
	{
		continueButton.setColor(Color::White);
		exitButton.setColor(Color::White);
		menuButton.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(387, 224, 250, 100).contains(Mouse::getPosition(window))) { continueButton.setColor(Color::Blue); menuNum = 1; }// когда наведена мышь
		if (IntRect(387, 334, 250, 100).contains(Mouse::getPosition(window))) { menuButton.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(387, 445, 250, 100).contains(Mouse::getPosition(window))) { exitButton.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isPause = false;
			if (menuNum == 2) {
				isPause = false;
				view.reset(FloatRect(0, 0, 1024, 768));
				menu(window);
			}
			if (menuNum == 3) window.close();
		}

		window.draw(continueButton);
		window.draw(exitButton);
		window.draw(menuButton);

		window.display();
	}
}

int main() 
{
	/////////////////// ТУТ СДЕЛАЛ НЕБОЛЬШУЮ КАРТУ ДЛЯ ТЕСТОВ //////////////??/////////////////////////
	Image mapImg;
	mapImg.loadFromFile("img/map.png");
	Texture mapText;
	mapText.loadFromImage(mapImg);
	Sprite map;
	map.setTexture(mapText);
	// переменные, что бы персонаж смотрел в сторону курсора 
	float vectorX;
	float vectorY;


	srand(time(0));
	
	RenderWindow window(VideoMode(1024, 768), "Poprobuyem");  //Style::Fullscreen
	menu(window);
	view.reset(FloatRect(1888, 2016, 1024, 768));

	float CurrentFrame = 0;
	Clock clock;
	
	createWorld();
	generateMap();

	
	Image ratImage;
	ratImage.loadFromFile("img/rat.png");

	Enemy rat(ratImage, 2400, 2400, 100, 28, "rat");

	Image heroImage;
	heroImage.loadFromFile("img/hero_animation.png");

	Hero MainHero(heroImage, 2400, 2400,10, 30,"Player");

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			MainHero.direction = 1; MainHero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			MainHero.sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 0, 21, 40));
			getPlayerCoord(MainHero.getPlayerPositionX(), MainHero.getPlayerPositionY());
}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			MainHero.direction = 0; MainHero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			MainHero.sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 40, 21, 40));
			getPlayerCoord(MainHero.getPlayerPositionX(), MainHero.getPlayerPositionY());
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			MainHero.direction = 3; MainHero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			MainHero.sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 120, 21, 40));
			getPlayerCoord(MainHero.getPlayerPositionX(), MainHero.getPlayerPositionY());
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			MainHero.direction = 2; MainHero.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 4) CurrentFrame -= 4; 
			MainHero.sprite.setTextureRect(IntRect(21 * int(CurrentFrame), 80, 21, 40));
			getPlayerCoord(MainHero.getPlayerPositionX(), MainHero.getPlayerPositionY());
		}

		float vectorX = pos.x - MainHero.x;
		float vectorY = pos.y - MainHero.y;
		float rotation = (atan2(vectorY, vectorX)) * 180 / 3.14159265;
		//MainHero.sprite.setRotation(rotation);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pauseMenu(window,MainHero.x,MainHero.y);
		}
		rat.update(time);
		MainHero.update(time);

		window.setView(view);
		window.clear();

		int HEIGHT_MAP = 130, WIDTH_MAP = 130;

		for (int i = 0; i < HEIGHT_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (WORLD[i][j] == 0)  map.setTextureRect(IntRect(0, 0, 32, 32));// пусто
				if (WORLD[i][j] == 2)  map.setTextureRect(IntRect(32, 0, 32, 32));//камень
				if (WORLD[i][j] == 1)  map.setTextureRect(IntRect(64, 0, 32, 32));//стена
				map.setPosition(j * 32, i * 32);
				window.draw(map);
			}
		}
		window.draw(MainHero.sprite);
		window.draw(rat.sprite);
		window.display();
	}
	
	
	system("pause");
	return 0;
}
