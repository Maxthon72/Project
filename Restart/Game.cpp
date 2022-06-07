#include "Game.h"

std::vector<sf::Texture*> Load_Asteroid_Texture()
{
	std::regex asteroid_reg(".*(Asteroid){1}[0-9]*(.png){1}");
	std::vector<sf::Texture*> text;
	for (auto const& obj : std::filesystem::directory_iterator(Draw /= "Asteroids")) {
		sf::Texture* T = new sf::Texture;

		/*if (std::regex_match(obj.path().string(), asteroid_reg))
			std::cout << "OK" << std::endl;
		else
			std::cout << obj.path().string() << std::endl;*/
		std::cout << obj.path().string() << std::endl;
		T->loadFromFile(obj.path().string());
		text.push_back(T);
		//delete(T);
	}
	return text;
}

Game::Game()
{
	fu = std::async(Load_Asteroid_Texture);
	score = 0;
	state = 0;
	
	MG_Loop();
}

void Game::Create_SW_Thread()
{
	Status_window_point = &SW;
}

void Game::MG_Loop()
{
	
	Asteroid_Texture = fu.get();
	n_asteroide = Asteroid_Texture.size()-1;
	Create_SW_Thread();
	std::thread SWT(&Status_Window::SW_Loop, &SW);
	while (MW.W_Open()) {
		MainToThread.release();

		if (state == 0) {
			SG_Event_Loop();

		}

		else if (state == 1) {
			MG_Event_Loop();
			MP->Obj_Controlle();
			if (score_clock.getElapsedTime().asSeconds() > 0.5) {
				score++;
				score_clock.restart();
			}
			Enemy_Spawn();
			
		}

		else if (state == 2) {

			GG_Event_Loop();
		}
			

		ThreadToMain.acquire();

		MW.W_Draw();

		for (auto obj : Bullets) {

			
			if (obj->Chcek_lives()) {
				Bullets.erase(std::remove(Bullets.begin(), Bullets.end(), obj), Bullets.end());
				delete(obj);
				continue;
			}
			

			obj->Bullet_Move();
			MW.Wrap(obj->Get_Sprite());
			MW.W_Draw(obj->Get_Sprite());
		}
		
		for (auto obj : Small_Asteroids) {

			if (obj->Chcek_lives()) {
				Small_Asteroids.erase(std::remove(Small_Asteroids.begin(), Small_Asteroids.end(), obj), Small_Asteroids.end());
				delete(obj);
				score += 5;
				continue;
			}

			if (Colision(MP->Get_Sprite(), obj->Get_Sprite())) {
				MP->Minus_Live();
				MP->Colided();
				if (Check_GG()) {
					state = 2;
					continue;
				}

			}


			for (auto obj2 : Bullets) {
				if (Colision(obj2->Get_Sprite(), obj->Get_Sprite())) {
					obj->Minus_Live();
					obj2->Kill();
				}

			}


			obj->Asteroide_Move();
			MW.Wrap(obj->Get_Sprite());
			MW.W_Draw(obj->Get_Sprite());
		}

		for (auto obj : Big_Asteroids) {

			if (obj->Chcek_lives()) {
				Big_Asteroids.erase(std::remove(Big_Asteroids.begin(), Big_Asteroids.end(), obj), Big_Asteroids.end());
				Spawn_Small_Asteroide(obj);
				delete(obj);
				score += 15;
				continue;
			}

			if (Colision(MP->Get_Sprite(), obj->Get_Sprite())) {
				MP->Minus_Live();
				MP->Colided();
				if (Check_GG()) {
					state = 2;
					continue;
				}

			}

			for (auto obj2 : Bullets) {
				if (Colision(obj2->Get_Sprite(), obj->Get_Sprite())) {
					obj->Minus_Live();
					obj2->Kill();
					Spawn_Small_Asteroide(SMALL_OUT_OF_BIG);
				}

			}


			obj->Asteroide_Move();
			MW.Wrap(obj->Get_Sprite());
			MW.W_Draw(obj->Get_Sprite());
		}

		if (MP != nullptr) {

			this->Save();
			if (MP->Colided_Q()) {
				Reset();
				MW.Set_Sprite(state);
			}
				
			MP->Obj_Move();
			MW.Wrap(MP->Get_Sprite());
			MW.W_Draw(MP->Get_Sprite());
		}		
		
		
		//Status_window_point->Display();
		MW.W_Display();
	}
	SWT.join();
}

void Game::SG_Event_Loop()
{
	while (MW.Poll())
	{
		// "close requested" event: we close the window
		if (MW.Get_Eve().type == sf::Event::Closed) {

			MW.Set_Sprite(state);
			Clean();

			MW.W_CLose();
			Status_window_point->W_CLose();
			MainToThread.release();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			state = 1;
			MP = new Player();
			MW.Set_Sprite(state);
			score = 0;
			timer.restart();
			shoot.restart();
			asteroide.restart();
		}
	}
}

void Game::MG_Event_Loop()
{
	while (MW.Poll())
	{
		if (MW.Get_Eve().type == sf::Event::Closed) {

			MW.Set_Sprite(state);
			Clean();

			MW.W_CLose();
			Status_window_point->W_CLose();
			MainToThread.release();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

			state = 0;
			MW.Set_Sprite(state);
			Clean();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (shoot.getElapsedTime().asSeconds() > BULLET_COLL_DOWN) {
				Bullets.push_back(MP->Shoot());
				shoot.restart();
			}
				
		}
	}
}

void Game::GG_Event_Loop()
{
	Clean();
	while (MW.Poll())
	{
		if (MW.Get_Eve().type == sf::Event::Closed) {

			MW.Set_Sprite(state);
			
			Clean();
			MW.W_CLose();
			Status_window_point->W_CLose();
			MainToThread.release();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			state = 1;
			MP = new Player();
			MW.Set_Sprite(state);
			score = 0;
			timer.restart();
			shoot.restart();
			asteroide.restart();
		}
			
	}
}

void Game::Enemy_Spawn()
{
	if (asteroide.getElapsedTime().asSeconds() > SPAWNER_TIME) {
		if (score < 25)
			Spawn_Big_Asteroide(1);
		else if (score < 50)
			Spawn_Small_Asteroide(2);
		else if (score < 75)
			Spawn_Small_Asteroide(3);
		else if (score < 100) {
			Spawn_Small_Asteroide(4);
			Spawn_Big_Asteroide(1);
		}
		else if (score < 125) {
			Spawn_Small_Asteroide(5);
			Spawn_Big_Asteroide(2);
		}
		else {
			Spawn_Small_Asteroide(6);
			Spawn_Big_Asteroide(3);
		}
		asteroide.restart();
	}
	return;
}

void Game::Spawn_Small_Asteroide(int x)
{
	for (int i = 0; i < x; i++) {
		int Spawn_x = GEt_Random(W);
		int Spawn_y = GEt_Random(H);
		int r = GEt_Random(1);
		if (r) {
			if (Spawn_x > (W / 2))
				Spawn_x = W;
			else
				Spawn_x = 0;
		}
		else {
			if (Spawn_y > (H / 2))
				Spawn_y = H;
			else
				Spawn_y = 0;
		}
		Smal_Asteroid* ast = new Smal_Asteroid(Get_Random_Texture(), Spawn_x, Spawn_y);
		ast->Obj_Rotate(GEt_Random(359));
		Small_Asteroids.push_back(ast);
	}
	
}

void Game::Spawn_Small_Asteroide(Big_Asteroid* obj)
{
	sf::Vector2f pos = obj->Get_Sprite().getPosition();

	for (int i = 0; i < SMALL_OUT_OF_BIG; i++) {
		
		Smal_Asteroid* ast = new Smal_Asteroid(Get_Random_Texture(), pos);
		ast->Obj_Rotate(GEt_Random(359));
		Small_Asteroids.push_back(ast);
	}
}

void Game::Spawn_Big_Asteroide(int x)
{
	for (int i = 0; i < x; i++) {
		int Spawn_x = GEt_Random(W);
		int Spawn_y = GEt_Random(H);
		int r = GEt_Random(1);
		if (r) {
			if (Spawn_x > (W / 2))
				Spawn_x = W;
			else
				Spawn_x = 0;
		}
		else {
			if (Spawn_y > (H / 2))
				Spawn_y = H;
			else
				Spawn_y = 0;
		}
		Big_Asteroid* ast = new Big_Asteroid(Get_Random_Texture(), Spawn_x, Spawn_y);
		ast->Obj_Rotate(GEt_Random(359));
		Big_Asteroids.push_back(ast);
	}
	
}

sf::Texture* Game::Get_Random_Texture()
{
	return Asteroid_Texture.at(GEt_Random(n_asteroide));
}

void Game::Clean()
{
	delete(MP);
	MP = nullptr;
	for (auto obj : Bullets)
		delete(obj);
	Bullets.clear();

	for (auto obj : Small_Asteroids)
		delete(obj);
	Small_Asteroids.clear();

	for (auto obj : Big_Asteroids)
		delete(obj);
	Big_Asteroids.clear();
}

void Game::Reset()
{
	MP->Reset();
	for (auto obj : Bullets)
		delete(obj);
	Bullets.clear();

	for (auto obj : Small_Asteroids)
		delete(obj);
	Small_Asteroids.clear();

	for (auto obj : Big_Asteroids)
		delete(obj);
	Big_Asteroids.clear();
	asteroide.restart();
	shoot.restart();
	score_clock.restart();
}

int Game::GEt_Random(int x)
{
	std::uniform_int_distribution<int> dist(0, x);
	return dist(randomEngine);
}

bool Game::Check_GG()
{
	if (MP->Get_Live() == 0) {
		//state = 2;
		std::cout << "GAME_OVER";
		return true;
	}
	return false;
}

void Game::Save()
{
	//ThreadToMain.acquire();
	MyFile.open("Save.txt");
	MyFile.clear();
	MyFile << MP->Get_Live()<<"\n";
	MyFile << timer.getElapsedTime().asSeconds() << "\n";
	MyFile << score;
	MyFile.close();
	//MainToThread.release();
}

bool Game::Colision(sf::Sprite& obj1, sf::Sprite& obj2)
{
	if (obj1.getGlobalBounds().intersects(obj2.getGlobalBounds()))
		return true;
	return false;
}

