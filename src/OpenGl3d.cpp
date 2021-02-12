#include <SFML\Audio.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\OpenGL.hpp>
#include <SFML\System\Vector3.hpp>
#include<gl\GLU.h>
#include "Header.h"
#include<thread>
#include<ctime>
#include<cstdlib>
#include <queue>
#include <algorithm>
#include <stack>
#include<iostream>
#define map_width 24
#define map_height 24

int world_map[map_width][map_height] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0/*1x1*/,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1},
	{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1},
	{1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
	{1,1,0,1,1,1,0,1,1,1,1,0/*11x11*/,1,1,1,1,1,1,1,1,1,1,0,1},
	{1,1,0,1,1,1,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1},
	{1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
	{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
	{1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1},
	{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// ################################ RANDOMIZATION BEGIN ################################################

class Solution {
public:
	void maze(int map[][map_width]) {
		for (int i = 0; i < map_width; ++i)
		{
			for (int j = 0; j < map_height; ++j)
			{
				map[i][j] = 1;
			}
		}
		_maze(map, 1, 1);
	}
	void _maze(int map[][map_width], int i, int j) {
		int direct[][2] = { {0,1}, {0,-1}, {-1,0}, {1,0} };
		int visitOrder[] = { 0,1,2,3 };
		if (i <= 0 || j <= 0 || i >= map_height - 1 || j >= map_width - 1) return;
		if (map[i][j] == 0) return;
		if (countVisitedNeighbor(map, i, j) > 1) return;
		map[i][j] = 0;
		shuffle(visitOrder, 4);
		for (int k = 0; k < 4; ++k)
		{
			int ni = i + direct[visitOrder[k]][0];
			int nj = j + direct[visitOrder[k]][1];
			_maze(map, ni, nj);
		}
	}

	int countVisitedNeighbor(int map[][map_width], int i, int j) {
		int direct[][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
		int count = 0;
		for (int k = 0; k < 4; ++k)
		{
			int ni = i + direct[k][0];
			int nj = j + direct[k][1];
	
			if (ni < 0 || nj < 0 || ni >= map_width || nj >= map_height) continue;
			if (map[ni][nj] == 0) count++;
		}
		return count;
	}
	void shuffle(int a[], int n) {
		for (int i = 0; i < n; ++i)
		{
			swap(a[i], a[rand() % n]);
		}
	}
	void swap(int& a, int& b) {
		int c = a;
		a = b;
		b = c;
	}
};

// ################################ RANDOMIZATION END ################################################

int idx[4] = {}; //tablica trzymajaca indeks playera i desta

struct Spherical
{
	float distance, theta, fi;
	Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance), theta(gtheta), fi(gfi) { }
	float getX() { return distance * cos(theta) * cos(fi); }
	float getY() { return distance * sin(theta); }
	float getZ() { return distance * cos(theta) * sin(fi); }
};

Spherical camera(4.0f, 0.75f, 0.0f), light_position(10.0f, 0.5f, 1.6f); 
sf::Vector3f pos(11.5f, 0.5f, 11.5f); //poczatkowa pozycja player
unsigned char projection_type = 'p';
float fov = 60.0f;
float timer = 0.0;
bool write_thread_is_up = false;
GLubyte* data;

sf::Texture TEX_ground;
sf::Texture TEX_wall;

typedef sf::Event sfe;
typedef sf::Keyboard sfk;

void randomise()
{
	srand(time(NULL));

	/*for (int i = 1; i <= map_height - 2; ++i)
	{
		for (int j = 1; j <= map_width - 2; ++j)
		{
			if (world_map[i][j] == 1)
			{
				world_map[i][j] = rand() % 2;
			}
		}
	}*/
	Solution s;
	s.maze(world_map);
	for (int i = 1; i < map_width - 1; ++i) //wybranie indeksow dla destination
		for (int j = 1; j < map_height - 1; ++j)
		{
			if (world_map[i][j] == 0)
			{
				if (world_map[i + 1][j] == 0 || world_map[i - 1][j] == 0 || world_map[i][j + 1] == 0 || world_map[i][j - 1] == 0) //zapobiegniecie zaklinowaniu kulki dest
				{
					idx[0] = j;
					idx[1] = i;
					break;
				}
			}
		}
	for (int i = map_width - 1; i > 1; --i) //wybranie indeksow dla player
		for (int j = map_height - 1; j > 1; --j)
		{
			if (world_map[i][j] == 0)
			{
				if (world_map[i + 1][j] == 0 || world_map[i - 1][j] == 0 || world_map[i][j + 1] == 0 || world_map[i][j - 1] == 0)
				{
					idx[2] = j;		//11
					idx[3] = i;		//11
					pos.x = j + 0.5;
					pos.z = i + 0.5;
					break;
				}

			}
		}
}

void initOpenGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat light_ambient_global[4] = { 0.5,0.5,0.5,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);

	TEX_ground.loadFromFile("ground2.png");
	TEX_wall.loadFromFile("woode2.png");
}

void reshapeScreen(sf::Vector2u size)
{
	glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (projection_type == 'p') gluPerspective(fov, (GLdouble)size.x / (GLdouble)size.y, 1.0, 100.0);
	else glOrtho(-1.245 * ((GLdouble)size.x / (GLdouble)size.y), 1.245 * ((GLdouble)size.x / (GLdouble)size.y), -1.245, 1.245, -3.0, 12.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void drawFloor(GLfloat x1, GLfloat x2, GLfloat z1, GLfloat z2)
{
	sf::Texture::bind(&TEX_ground);
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(x1, 0, z2);
	glTexCoord2f(1, 0);
	glVertex3f(x2, 0, z2);
	glTexCoord2f(1, 1);
	glVertex3f(x2, 0, z1);
	glTexCoord2f(0, 1);
	glVertex3f(x1, 0, z1);
	glEnd();
}

void drawCube(GLint j, GLint i)
{
	GLfloat x1 = (GLfloat)i, x2 = (GLfloat)i + 1, y1 = 0.0f, y2 = 1.0f, z1 = (GLfloat)j, z2 = (GLfloat)j + 1;
	sf::Texture::bind(&TEX_wall);
	if ((j == map_height + 1) || (world_map[j - 1][i] != 1))
	{
		glBegin(GL_POLYGON); // Ty³
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0, 0);
		glVertex3f(x2, y1, z1);
		glTexCoord2f(1, 0);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(1, 1);
		glVertex3f(x1, y2, z1);
		glTexCoord2f(0, 1);
		glVertex3f(x2, y2, z1);
		glEnd();
	}
	if ((j == map_width - 1) || (world_map[j + 1][i] != 1))
	{
		glBegin(GL_POLYGON); // Przód
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0, 0);
		glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 0);
		glVertex3f(x2, y1, z2);
		glTexCoord2f(1, 1);
		glVertex3f(x2, y2, z2);
		glTexCoord2f(0, 1);
		glVertex3f(x1, y2, z2);
		glEnd();
	}
	if ((i > 0) && (world_map[j][i - 1] != 1) || i == 0)
	{
		glBegin(GL_POLYGON); // Lewy
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0, 0);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(1, 0);
		glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 1);
		glVertex3f(x1, y2, z2);
		glTexCoord2f(0, 1);
		glVertex3f(x1, y2, z1);
		glEnd();
	}
	if ((i < map_height) && (world_map[j][i + 1] != 1) || i == map_height - 1)
	{
		glBegin(GL_POLYGON); // Prawy
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0, 0);
		glVertex3f(x2, y1, z2);
		glTexCoord2f(1, 0);
		glVertex3f(x2, y1, z1);
		glTexCoord2f(1, 1);
		glVertex3f(x2, y2, z1);
		glTexCoord2f(0, 1);
		glVertex3f(x2, y2, z2);
		glEnd();
	}
	glBegin(GL_POLYGON); // Góra
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(x1, y2, z2);
	glTexCoord2f(1, 0);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(1, 1);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(0, 1);
	glVertex3f(x1, y2, z1);
	glEnd();
}


void drawScene()
{

	GLUquadricObj* qobj, * qobj2;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Spherical north_of_camera(camera.distance, camera.theta + 0.01f, camera.fi);
	gluLookAt(camera.getX() + pos.x, camera.getY() + pos.y, camera.getZ() + pos.z, pos.x, pos.y, pos.z, north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());
	GLfloat light0_position[4] = { light_position.getX(), light_position.getY(), light_position.getZ(), 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);


	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D); //GENEROWANIE PLASZCZYZNY I KLOCKOW
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < map_width; ++i)
		for (int j = 0; j < map_height; ++j)
			if (world_map[j][i] == 1)
			{
				drawCube(j, i);
			}
			else
			{
				drawFloor(i, i + 1, j, j + 1);
			}

	glDisable(GL_TEXTURE_2D);

	qobj = gluNewQuadric();
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricDrawStyle(qobj2, GLU_FILL);
	gluQuadricNormals(qobj2, GLU_SMOOTH);

	glPushMatrix(); //KULKA - PLAYER
	glTranslatef(pos.x, 0.5, pos.z);
	glColor4f(0.40f, 0.3f, 0.1f, 0.5f);
	gluSphere(qobj, 0.5, 25, 20);
	glPopMatrix();

	glPushMatrix(); //KULKA - DESTINATION
	glColor4f(0.0f, 0.5f, 1.0f, 0.5f);
	glTranslatef(idx[0] + 0.5, 0.5, idx[1] + 0.5);
	gluSphere(qobj2, 0.5, 25, 20);
	glPopMatrix();


}


void write_data_to_disk(unsigned int sw, unsigned int sh) //SCREEN Part1
{
	sf::Image image;
	image.create(sw, sh, data);
	image.flipVertically();
	image.saveToFile("screen.jpg");
	delete[]data;
	write_thread_is_up = false;
}



int main()
{
	randomise();

	//############ MUSIC ####################
	sf:: Music music;
	if (!music.openFromFile("toto.ogg"))
	{
		printf("Blad z otwarciem pliku mp3..\n");
		getchar();
		return -1;

	}
	//############# MUSIC END ######################

	//#################### TEXT #########################

	sf::Font font;
	if (!font.loadFromFile("times.ttf"))
	{
		printf("problem z wczytaniem czcionki...\n");
	}

	sf::Text text, counter, time;
	text.setFont(font);
	text.setString("Ruch: W,S,A,D \nObrot kamery: strzalki \nWysokosc kamery: L/P Shift \nWyjscie: Escape\nZoom: L/P Ctrl");
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	counter.setFont(font);
	counter.setCharacterSize(20);
	counter.setStyle(sf::Text::Bold);
	counter.setFillColor(sf::Color::White);
	counter.setPosition(700, 0);

	time.setFont(font);
	time.setString("Czas: ");
	time.setCharacterSize(20);
	time.setStyle(sf::Text::Bold);
	time.setFillColor(sf::Color::White);
	time.setPosition(640, 0);


	//#################### TEXT END #########################

	int x = idx[3], y = idx[2]; //poczatkowe indeksy playera
	bool ready[4] = { true };
	bool running = true;
	sf::ContextSettings context(24, 0, 0, 4, 5);
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze", 7U, context);
	/*sf::Window App(sf::VideoMode(800, 600, 32), "SFML Window" sf::Style::Fullscreen);
	App.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);*/
	sf::Clock clock;

	window.setVerticalSyncEnabled(true);
	reshapeScreen(window.getSize());
	initOpenGL();
	music.play();

	while (running)
	{
		sfe event;
		
		sf::Time elapsed = clock.restart();
		timer += elapsed.asSeconds();
		counter.setString(std::to_string(timer));
		while (window.pollEvent(event))
		{
			if (event.type == sfe::Closed || (event.type == sfe::KeyPressed && event.key.code == sfk::Escape)) running = false;
			if (event.type == sfe::Resized) reshapeScreen(window.getSize());
			if (event.type == sf::Event::KeyPressed) //ZMIANA WIDOKU NA PERSPEKTYWICZNY BADZ ORTOGONALNY
			{
				if (event.key.code == sf::Keyboard::Num0) { projection_type = 'o'; reshapeScreen(window.getSize()); }
				if (event.key.code == sf::Keyboard::Num9) { projection_type = 'p'; reshapeScreen(window.getSize()); }
			}

			if (event.key.code == sfk::F1 && !write_thread_is_up) //SCREEN part2
			{
				write_thread_is_up = true;
				sf::Vector2u size = window.getSize();
				data = new GLubyte[size.x * size.y * 4];

				glReadPixels(0, 0, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, data);
				std::thread(write_data_to_disk, size.x, size.y).detach();
			}

		}

		if (sfk::isKeyPressed(sfk::Left))  //OBRÓT KAMERY
		{
			if (camera.fi <= -6.4f) camera.fi = -0.14f;
			else camera.fi -= 0.02f;
		}
		if (sfk::isKeyPressed(sfk::Right))
		{
			if (camera.fi >= 6.4f) camera.fi = 0.14f;
			else camera.fi += 0.02f;
		}
		if (sfk::isKeyPressed(sfk::Up) && camera.theta < 1.6f) camera.theta += 0.02f;
		if (sfk::isKeyPressed(sfk::Down) && camera.theta > 0.51f) camera.theta -= 0.02f;

		//		ZMIANA ŒWIAT£A
		 light_position.fi += 0.008f;
		 light_position.theta += 0.008f;
		
		 //			ZOOM
		if (sfk::isKeyPressed(sfk::LControl)) { fov -= 1.0f; reshapeScreen(window.getSize()); } 
		if (sfk::isKeyPressed(sfk::RControl)) { fov += 1.0f; reshapeScreen(window.getSize()); }


		//				DRUGI WARIANT: DÓ£
		if ((camera.fi < -0.8f && camera.fi > -2.4f) || (camera.fi < 5.6f && camera.fi > 4.0f))
		{
			//----------------------OBS£UGA KLAWISZA S---------------------------
			if (sfk::isKeyPressed(sfk::S) && world_map[x - 1][y] == 0 && ready[2])
			{
				pos.z -= 1.0f; x--;
				ready[2] = false;
			}
			if (!sfk::isKeyPressed(sfk::S) && !ready[2])
			{
				ready[2] = true;
			}
			//----------------------OBS£UGA KLAWISZA W---------------------------
			if (sfk::isKeyPressed(sfk::W) && world_map[x + 1][y] == 0 && ready[3])
			{
				pos.z += 1.0f;
				x++;
				ready[3] = false;
			}
			if (!sfk::isKeyPressed(sfk::W) && !ready[3])
			{
				ready[3] = true;
			}
			//----------------------OBS£UGA KLAWISZA D---------------------------
			if (sfk::isKeyPressed(sfk::D) && world_map[x][y - 1] == 0 && ready[1])
			{
				pos.x -= 1.0f; y--;
				ready[1] = false;
			}
			if (!sfk::isKeyPressed(sfk::D) && !ready[1])
			{
				ready[1] = true;
			}
			//----------------------OBS£UGA KLAWISZA A---------------------------
			if (sfk::isKeyPressed(sfk::A) && world_map[x][y + 1] == 0 && ready[0])
			{
				pos.x += 1.0f; y++;
				ready[0] = false;
			}
			if (!sfk::isKeyPressed(sfk::A) && !ready[0])
			{
				ready[0] = true;
			}
		}

		//				PIERWSZY WARIANT: GÓRA
		if ((camera.fi >= 0.8f && camera.fi < 2.4f) || (camera.fi >= -5.6f && camera.fi < -4.0f))
		{
			//----------------------OBS£UGA KLAWISZA W---------------------------
			if (sfk::isKeyPressed(sfk::W) && world_map[x - 1][y] == 0 && ready[2])
			{
				pos.z -= 1.0f; x--;
				ready[2] = false;
			}
			if (!sfk::isKeyPressed(sfk::W) && !ready[2])
			{
				ready[2] = true;
			}
			//----------------------OBS£UGA KLAWISZA S---------------------------
			if (sfk::isKeyPressed(sfk::S) && world_map[x + 1][y] == 0 && ready[3])
			{
				pos.z += 1.0f;
				x++;
				ready[3] = false;
			}
			if (!sfk::isKeyPressed(sfk::S) && !ready[3])
			{
				ready[3] = true;
			}
			//----------------------OBS£UGA KLAWISZA A---------------------------
			if (sfk::isKeyPressed(sfk::A) && world_map[x][y - 1] == 0 && ready[1])
			{
				pos.x -= 1.0f; y--;
				ready[1] = false;
			}
			if (!sfk::isKeyPressed(sfk::A) && !ready[1])
			{
				ready[1] = true;
			}
			//----------------------OBS£UGA KLAWISZA D---------------------------
			if (sfk::isKeyPressed(sfk::D) && world_map[x][y + 1] == 0 && ready[0])
			{
				pos.x += 1.0f; y++;
				ready[0] = false;
			}
			if (!sfk::isKeyPressed(sfk::D) && !ready[0])
			{
				ready[0] = true;
			}
		}

		//				TRZECI WARIANT: LEWO
		if ((abs(camera.fi) < 0.8f) || (camera.fi < 6.4f && camera.fi > 5.6f) || (camera.fi < -5.6f && camera.fi > -6.4f))
		{
			//----------------------OBS£UGA KLAWISZA D---------------------------
			if (sfk::isKeyPressed(sfk::D) && world_map[x - 1][y] == 0 && ready[2])
			{
				pos.z -= 1.0f; x--;
				ready[2] = false;
			}
			if (!sfk::isKeyPressed(sfk::D) && !ready[2])
			{
				ready[2] = true;
			}
			//----------------------OBS£UGA KLAWISZA A---------------------------
			if (sfk::isKeyPressed(sfk::A) && world_map[x + 1][y] == 0 && ready[3])
			{
				pos.z += 1.0f;
				x++;
				ready[3] = false;
			}
			if (!sfk::isKeyPressed(sfk::A) && !ready[3])
			{
				ready[3] = true;
			}
			//----------------------OBS£UGA KLAWISZA W---------------------------
			if (sfk::isKeyPressed(sfk::W) && world_map[x][y - 1] == 0 && ready[1])
			{
				pos.x -= 1.0f; y--;
				ready[1] = false;
			}
			if (!sfk::isKeyPressed(sfk::W) && !ready[1])
			{
				ready[1] = true;
			}
			//----------------------OBS£UGA KLAWISZA S---------------------------
			if (sfk::isKeyPressed(sfk::S) && world_map[x][y + 1] == 0 && ready[0])
			{
				pos.x += 1.0f; y++;
				ready[0] = false;
			}
			if (!sfk::isKeyPressed(sfk::S) && !ready[0])
			{
				ready[0] = true;
			}
		}

		//					CZWARTY WARIANT: PRAWO
		if ((camera.fi <= 4.0f && camera.fi >= 2.4f) || (camera.fi >= -4.0f && camera.fi <= -2.4f))
		{
			//----------------------OBS£UGA KLAWISZA A---------------------------
			if (sfk::isKeyPressed(sfk::A) && world_map[x - 1][y] == 0 && ready[2])
			{
				pos.z -= 1.0f; x--;
				ready[2] = false;
			}
			if (!sfk::isKeyPressed(sfk::A) && !ready[2])
			{
				ready[2] = true;
			}
			//----------------------OBS£UGA KLAWISZA D---------------------------
			if (sfk::isKeyPressed(sfk::D) && world_map[x + 1][y] == 0 && ready[3])
			{
				pos.z += 1.0f;
				x++;
				ready[3] = false;
			}
			if (!sfk::isKeyPressed(sfk::D) && !ready[3])
			{
				ready[3] = true;
			}
			//----------------------OBS£UGA KLAWISZA S---------------------------
			if (sfk::isKeyPressed(sfk::S) && world_map[x][y - 1] == 0 && ready[1])
			{
				pos.x -= 1.0f; y--;
				ready[1] = false;
			}
			if (!sfk::isKeyPressed(sfk::S) && !ready[1])
			{
				ready[1] = true;
			}
			//----------------------OBS£UGA KLAWISZA W---------------------------
			if (sfk::isKeyPressed(sfk::W) && world_map[x][y + 1] == 0 && ready[0])
			{
				pos.x += 1.0f; y++;
				ready[0] = false;
			}
			if (!sfk::isKeyPressed(sfk::W) && !ready[0])
			{
				ready[0] = true;
			}

		}

		if (sfk::isKeyPressed(sfk::LShift)) pos.y += 0.02f; //POZYCJA KAMERY - W GÓRÊ
		if (sfk::isKeyPressed(sfk::RShift) && (pos.y > 0.5f)) pos.y -= 0.02f; //POZYCJA KAMERY - W DÓ£

		//KONIEC GRY - DOJŒCIE DO 2.KULKI
		if ((x == idx[1] && y == idx[0])) {
			running = false; 
			printf("Ukonczyles gre w %f sekund\n", timer);
			window.close();
			getchar();
		}

		drawScene();
		window.pushGLStates();


		if (timer <= 20) window.draw(text);
		window.draw(time);
		window.draw(counter);
		window.popGLStates();


		window.display();

	}
	return 0;
}
