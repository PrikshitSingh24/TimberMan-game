#include<sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include<SFML/Audio.hpp>

using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
Sprite treesBackground[4];
enum class side{LEFT,RIGHT,NONE};
side branchPosition[NUM_BRANCHES];

int main() {
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!", Style::Fullscreen);

	/*
	the loop is used so that we can display the window until the player wish to exit
	the game.........
	*/
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	bool cloudActive = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloudSpeed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	Clock clock;
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	bool paused = true;
	int score = 0;
	Text messageText;
	Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width/2.0f,
		textRect.top+
		textRect.height/2.0f
	);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setPosition(220, 20);
	}
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;

	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sounds/Chapter01_sound_chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sounds/Chapter01_sound_death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sounds/Chapter01_sound_out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	Texture textureBackgroundTree;
	textureBackgroundTree.loadFromFile("graphics/tree.png");
	for (int i = 0; i < 4; i++) {
		treesBackground[i].setTexture(textureBackgroundTree);
	}

	treesBackground[0].setPosition(40, 0);
	treesBackground[0].scale(Vector2f(1, 1.5));

	treesBackground[1].setPosition(420, -200);
	treesBackground[1].scale(Vector2f(0.5, 1));

	treesBackground[2].setPosition(1520, -100);
	treesBackground[2].scale(Vector2f(0.8, 1));

	treesBackground[3].setPosition(1159, -240);
	treesBackground[3].scale(Vector2f(0.4, 1));


	while (window.isOpen())
	{
		/*
		if the player presses the escape key the game will stop.....
		*/
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;
			score = 0;
			timeRemaining = 6.0f;
			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPosition[i] = side::NONE;
			}
			spriteRIP.setPosition(675, 2000);
			spritePlayer.setPosition(580, 720);
			acceptInput = true;

		}
		if (acceptInput) {


			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				playerSide = side::RIGHT;
				score++;
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				playerSide = side::LEFT;
				score++;
				timeRemaining+= (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}
		}

		if (!paused) {
			Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f) {
				paused = true;
				messageText.setString("Out of time!!");
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f
				);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				outOfTime.play();
			}

			if (!beeActive) {
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else {
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y
				);
				if (spriteBee.getPosition().x < -100) {
					beeActive = false;
				}
			}
			if (!cloudActive) {
				srand((int)time(0) * 10);
				cloudSpeed = (rand() % 200);
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud.setPosition(-200, height);
				cloudActive = true;
			}
			else {
				spriteCloud.setPosition(
					spriteCloud.getPosition().x + (cloudSpeed * dt.asSeconds()),
					spriteCloud.getPosition().y
				);
				if (spriteCloud.getPosition().x > 1920) {
					cloudActive = false;
				}
			}
			if (!cloud2Active) {
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
				);
				if (spriteCloud2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}
			if (!cloud3Active) {
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else {
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
				);
				if (spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPosition[i] == side::LEFT) {
					branches[i].setPosition(820, height);
					branches[i].setRotation(180);
				}
				else if (branchPosition[i] == side::RIGHT) {
					branches[i].setPosition(1100, height);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(3000, height);
				}
			}
			if (logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedY * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				);
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x>2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}
			if (branchPosition[5] == playerSide) {
				paused = true;
				acceptInput = false;
				spriteRIP.setPosition(525, 760);

				spritePlayer.setPosition(2000, 660);

				messageText.setString("SQUISHED");
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f
				);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();

			}

		}
		
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(treesBackground[3]);
		window.draw(treesBackground[1]);
		window.draw(treesBackground[2]);
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		window.draw(treesBackground[0]);
		window.draw(spriteTree);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(timeBar);
		if (paused) {
			window.draw(messageText);
		}
		window.display();
	}
	return 0;
}

void updateBranches(int seed) {
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPosition[j] = branchPosition[j - 1];
	}
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPosition[0] = side::LEFT;
		break;
	case 1:
		branchPosition[0] = side::RIGHT;
		break;
	default:
		branchPosition[0] = side::NONE;
		break;
	}
}