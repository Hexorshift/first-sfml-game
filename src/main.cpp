#include <cstdlib>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "headers/Player.h"
#include "headers/Bullet.h"
#include "headers/Enemy.h"

int main()
{
	srand((unsigned int)time(NULL));


	sf::RenderWindow window(sf::VideoMode(1280, 720), "Stupid Stuff", sf::Style::Default);
	// window.setFramerateLimit(120);

	// Font
	sf::Font font;
	font.loadFromFile("fonts/kenvector_future_thin.ttf") ? std::cout << "Loaded font!\n" : std::cout << "Error loading font\n";

	// FPS
	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	float dt;
	float mulitplier = 60;
	float normal_fps;

	sf::Text fps_counter;
	fps_counter.setFont(font);
	fps_counter.setCharacterSize(30);
	fps_counter.setFillColor(sf::Color::White);
	fps_counter.setPosition(sf::Vector2f(10.0f, 3.0f));

	// Textures
	sf::Texture player_texture;
	player_texture.loadFromFile("textures/SpaceShooter/PNG/playerShip1_green.png") ? std::cout << "Loaded player texture!\n" : std::cout << "Error loading player texture!\n";
	
	sf::Texture player_health_texture;
	player_health_texture.loadFromFile("textures/SpaceShooter/PNG/UI/playerLife1_green.png") ? std::cout << "Loaded player health texture!\n" : std::cout << "Error loading player health texture!\n";

	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("textures/SpaceShooter/PNG/Enemies/enemyBlack1.png") ? std::cout << "Loaded enemy texture!\n" : std::cout << "Error loading enemy texture!\n";

	sf::Texture bullet_texture;
	bullet_texture.loadFromFile("textures/SpaceShooter/PNG/Lasers/laserGreen13.png") ? std::cout << "Loaded bullet texture!\n" : std::cout << "Error loading bullet texture!\n";

	sf::Texture enemy_bullet_texture;
	enemy_bullet_texture.loadFromFile("textures/SpaceShooter/PNG/Lasers/laserRed01.png") ? std::cout << "Loaded enemy bullet texture!\n" : std::cout << "Error loading enemy bullet texture!\n";

	// Player
	Player player(player_texture);
	player.shape.setPosition(sf::Vector2f(200.0f, 500.0f));

	// Bullet
	Bullet bullet(bullet_texture);
	bullet.shape.setPosition(sf::Vector2f(300.0f, 500.0f));

	int shoot_timer = 0;

	// Player Health
	sf::Sprite player_health_sprite;
	player_health_sprite.setTexture(player_health_texture);
	std::vector<sf::Sprite> player_health_container;

	sf::RectangleShape player_health_bar(sf::Vector2f(200.0f, 30.0f));
	player_health_bar.setFillColor(sf::Color::Color(0, 255, 0, 300));

	// Player Points
	unsigned int points = 0;
	sf::Text player_points;
	player_points.setFont(font);
	player_points.setFillColor(sf::Color::White);
	player_points.setStyle(sf::Text::Bold);
	player_points.setPosition(sf::Vector2f(float(window.getSize().x - (window.getSize().x / 6)), 3.0f));
	player_points.setString("Points: " + std::to_string(points));

	for (int xy = 5; xy < 30; xy+=5)
	{
		player_health_sprite.setPosition(sf::Vector2f(float(xy * 8), 40.0f));
		player_health_container.push_back(sf::Sprite(player_health_sprite));
	}

	// Sounds
	sf::SoundBuffer laser_buffer;
	laser_buffer.loadFromFile("textures/SpaceShooter/Bonus/sfx_laser1.ogg") ? std::cout << "Loaded bullet sound!\n" : std::cout << "Error loading bullet sound!\n";

	sf::SoundBuffer enemy_laser_buffer;
	enemy_laser_buffer.loadFromFile("textures/SpaceShooter/Bonus/sfx_laser2.ogg") ? std::cout << "Loaded enemy bullet sound!\n" : std::cout << "Error loading enemy bullet sound!\n";

	sf::Sound laser_sound;
	laser_sound.setBuffer(laser_buffer);
	
	sf::Sound enemy_laser_sound;
	enemy_laser_sound.setBuffer(enemy_laser_buffer);
	
	sf::SoundBuffer player_hit_buffer;
	player_hit_buffer.loadFromFile("textures/SpaceShooter/Bonus/sfx_lose.ogg") ? std::cout << "Loaded player hit sound!\n" : std::cout << "Error loading player hit sound!\n";

	sf::Sound player_hit_sound;
	player_hit_sound.setBuffer(player_hit_buffer);

	// Enemy
	Enemy enemy(enemy_texture);
	std::vector <Enemy> enemies;

	sf::Sprite enemy_bullet;
	enemy_bullet.setTexture(enemy_bullet_texture);
	std::vector <sf::Sprite> enemy_bullets;

	int enemy_spawn_time = 0;

	// Attack Text
	int player_damages[3] = { 100, 20, 40 };

	sf::Text damage_counter;
	damage_counter.setFont(font);
	damage_counter.setFillColor(sf::Color::Red);
	damage_counter.setStyle(sf::Text::Bold);

	std::vector<sf::Text> damage_counters;
	int delete_counter_delay = 0;

	bool game_over = false;
	
	// Game over 
	sf::Text game_over_text;
	game_over_text.setFont(font);
	game_over_text.setCharacterSize(50);
	game_over_text.setFillColor(sf::Color::Red);
	game_over_text.setStyle(sf::Text::Bold);
	game_over_text.setString("Game Over!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update
		// FPS
		dt = clock.restart().asSeconds();
		normal_fps = dt * mulitplier;

		std::cout << dt << "\n";
		if (player_health_container.empty())
			game_over = true;

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); 
		previousTime = currentTime;

		fps_counter.setString("FPS: " + std::to_string(int(floor(fps))));
		
		if (!game_over)
		{
			// Player Movements
			player.movements(window, normal_fps);
			player.move_bullets(window);

			if (!damage_counters.empty())
			{
				if (delete_counter_delay < 30)
					delete_counter_delay++;

				if (delete_counter_delay >= 30)
				{
					damage_counters.pop_back();
					delete_counter_delay = 0;
				}
			}

			if (shoot_timer < 25)
				shoot_timer++;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shoot_timer >= 25 && window.hasFocus())
			{
				bullet.shape.setPosition(sf::Vector2f((player.shape.getPosition().x + ((player.shape.getLocalBounds().width / 2) - 6)), player.shape.getPosition().y));
				player.bullets.push_back(bullet);

				laser_sound.play();
				shoot_timer = 0;
			}

			if (enemy_spawn_time < 100)
				enemy_spawn_time++;

			if (enemy_spawn_time >= 100)
			{
				enemy.shape.setPosition(sf::Vector2f(float(rand() % int(window.getSize().x - enemy.shape.getLocalBounds().width) + 0), -enemy.shape.getGlobalBounds().height));
				enemies.push_back(enemy);

				enemy_bullet.setPosition(sf::Vector2f((enemy.shape.getPosition().x + (enemy.shape.getLocalBounds().width / 2)), (enemy.shape.getPosition().y) + 100));
				enemy_bullets.push_back(sf::Sprite(enemy_bullet));
				enemy_laser_sound.play();

				enemy_spawn_time = 0;
			}

			for (size_t e = 0; e < enemies.size(); e++)
			{
				enemies[e].shape.move(sf::Vector2f(0.0f, 3.0f * normal_fps));
				if (enemies[e].hp <= 0)
				{
					points++;
					player_points.setString("Points: " + std::to_string(points));
					enemies.erase(enemies.begin() + e);
					break;
				}
				if (enemies[e].shape.getPosition().y > window.getSize().y)
				{
					enemies.erase(enemies.begin() + e);
					break;
				}
			}

			for (size_t m_eb = 0; m_eb < enemy_bullets.size(); m_eb++)
			{
				enemy_bullets[m_eb].move(sf::Vector2f(0.0f, 10.0f * normal_fps));
				if (enemy_bullets[m_eb].getPosition().y > window.getSize().y)
				{
					enemy_bullets.erase(enemy_bullets.begin() + m_eb);
				}
			}

			for (int l = 0; l < player.bullets.size(); l++)
			{
				for (int k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[l].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						player.bullets.erase(player.bullets.begin() + l);
						int damage = player_damages[rand() % 3 + 0];
						enemies[k].hp = enemies[k].hp - damage;

						damage_counter.setPosition(sf::Vector2f((enemies[k].shape.getPosition().x + 10), (enemies[k].shape.getPosition().y - 20)));
						damage_counter.setString("-" + std::to_string(damage));
						damage_counters.push_back(damage_counter);

						break;
					}
				}
			}

			for (size_t t = 0; t < enemy_bullets.size(); t++)
			{
				if (enemy_bullets[t].getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemy_bullets.erase(enemy_bullets.begin() + t);
					player_health_container.pop_back();
					player_hit_sound.play();
					player_health_bar.setSize(sf::Vector2f((player_health_bar.getSize().x - 40), 30.0f));
					
					break;
				}
			}
			game_over_text.setPosition(sf::Vector2f(float((window.getSize().x / 2) - (game_over_text.getGlobalBounds().width / 2)), float(window.getSize().y / 2)));
		}

		for (int eb = 0; eb < enemy_bullets.size(); eb++)
		{
			for (int es = 0; es < enemies.size(); es++)
			{
				if (enemy_bullets[eb].getGlobalBounds().intersects(enemies[es].shape.getGlobalBounds()))
				{
					enemy_bullets.erase(enemy_bullets.begin() + eb);
					enemies.erase(enemies.begin() + es);

					break;
				}
			}
		}

		for (int x = 0; x < enemies.size(); x++)
		{
			if (enemies[x].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + x);
				player_health_container.pop_back();
				player_hit_sound.play();
				player_health_bar.setSize(sf::Vector2f((player_health_bar.getSize().x - 40), 30.0f));

				break;
			}
		}

		player_health_bar.setPosition(sf::Vector2f((player.shape.getPosition().x + (player.shape.getLocalBounds().width / 2)), player.shape.getPosition().y + 50));

		// Draw
		window.clear(sf::Color::Black);
		window.draw(fps_counter);

		if (!game_over)
		{
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].shape);
			}

			for (size_t j = 0; j < enemies.size(); j++)
			{
				window.draw(enemies[j].shape);
			}

			for (size_t e_bu = 0; e_bu < enemy_bullets.size(); e_bu++)
			{
				window.draw(enemy_bullets[e_bu]);
			}

			for (size_t dc = 0; dc < damage_counters.size(); dc++) {
				window.draw(damage_counters[dc]);
			}

			for (size_t hb = 0; hb < player_health_container.size(); hb++) {
				window.draw(player_health_container[hb]);
			}

			window.draw(player.shape);
			window.draw(player_health_bar);
			window.draw(player_points);
		} else 
		{
			window.draw(game_over_text);
		}
				
		// Display
		window.display();
	}

	return 0;
}