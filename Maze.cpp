#include "Maze.h"


Maze::Maze(){
	//Init tileBoard
	this->tileBoard = std::vector<std::vector<Tile>>(ROW_LENGTH, std::vector<Tile>(COLUMN_LENGTH, Tile()));
	this->numDots = 0;
	// Create text string
	std::string map_buffer[] = { 
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   1   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #234#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### " 
	};
	for (int i = 0; i < COLUMN_LENGTH; i++) {
		for (int j = 0; j < ROW_LENGTH; j++) {
			Tile newTile;
			switch (map_buffer[i][j]){
			case '#':
				newTile.set_Wall(true);
				break;
			case '.':
				newTile.setPellet(1);
				numDots++;
				break;
			case 'o':
				newTile.setPellet(2);
				numDots++;
				break;
			case 'P':
				newTile.setPSpawn(true);
				break;
			case '1':
				newTile.setGSpawn(1);
				break;
			case '2':
				newTile.setGSpawn(2);
				break;
			case '3':
				newTile.setGSpawn(3);
				break;
			case '4':
				newTile.setGSpawn(4);
				break;
			default:
				break;
			}
			this->tileBoard[i][j] = newTile;
		}
	}
}

Maze::Maze(std::string mapFileName){
	//Init tileBoard								21              22
	this->tileBoard = std::vector<std::vector<Tile>>(ROW_LENGTH, std::vector<Tile>(COLUMN_LENGTH, Tile()));

	//Read mapFile
	std::ifstream mapFile;
	std::string mapFilepath = MAP_PATH + mapFileName;
	//std::string mapFilepath = "./assets/maps/DEFAULT_MAP.txt";
	mapFile.open(mapFilepath);

	//Init Tile Board
	if (mapFile.is_open()) {
		std::string line;
		dot newDot;
		int i = 0;
		while (getline(mapFile, line)) {
			for (int j = 0; j < COLUMN_LENGTH; j++) {
				Tile newTile;
				switch (line[j]) {
				case '#':
					newTile.set_Wall(true);
					break;
				case '.':
					newDot = dot(i, j, false);
					dots.push_back(newDot);
					newTile.setPellet(1);
					numDots++;
					break;
				case 'o':
					newDot = dot(i, j, true);
					dots.push_back(newDot);
					newTile.setPellet(1);
					numDots++;
					newTile.setSuperPellet(true);
					break;
				case 'P':
					newTile.setPSpawn(true);
					break;
				case '1':
					newTile.setGSpawn(1);
					break;
				case '2':
					newTile.setGSpawn(2);
					break;
				case '3':
					newTile.setGSpawn(3);
					break;
				case '4':
					newTile.setGSpawn(4);
					break;
				default:
					break;
				}
				this->tileBoard[i][j] = newTile;
			}
			i++;
		}
		std::cout<<"number dots" << numDots << " vec len:" << dots.size()<<std::endl;
	}
}

Maze::~Maze(){
	//Insert Destructor Here
}

void Maze::drawMaze() {
	for (size_t i = 0; i < tileBoard.size(); i++) {
		for (size_t j = 0; j < tileBoard[i].size(); j++) {
			// Simple mode: draw rectangle for each cell that has a wall.
			if (tileBoard[i][j].isWall()) {
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				DrawRectangle(posX, posY, 32, 32, BLUE);
			}
			// Simple mode: draw circles for each cell that has a dot
			if (tileBoard[i][j].hasPellet() == 1) {
				int centX = (j * 8 * 4) - 8;
				int centY = (i * 8 * 4) - 8;
				DrawCircle(centX, centY, 4, WHITE);
			}
			if (tileBoard[i][j].hasPellet() == 2) {
				int centX = (j * 8 * 4) - 8;
				int centY = (i * 8 * 4) - 8;
				DrawCircle(centX, centY, 8, WHITE);
			}
		}
	}
}

void Maze::drawMazeEX() {
	Sprite map_sprites = Sprite("./assets/maps/textures/DEFAULT_TEXTURE.png");
	for (size_t i = 0; i < tileBoard.size(); i++) {
		for (size_t j = 0; j < tileBoard[i].size(); j++) {
			if (tileBoard[i][j].isWall()){
				// Check what cells have walls
				int left = j - 1;
				int right = j + 1;
				int up = i - 1;
				int down = i + 1;
				bool l = false;
				bool r = false;
				bool u = false;
				bool d = false;
				if (left >= 0) {
					if (tileBoard[i][left].isWall()){
						l = true;
					}
				}
				if (right < tileBoard[i].size()) {
					if (tileBoard[i][right].isWall()) {
						r = true;
					}
				}
				if (up >= 0) {
					if (tileBoard[up][j].isWall()) {
						u = true;
					}
				}
				if (down < tileBoard.size()) {
					if (tileBoard[down][j].isWall()) {
						d = true;
					}
				}

				// Now we determine frame
				if (!l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::SINGLE));
				}
				else if (!l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::UP_END));
				}
				else if (l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RIGHT_END));
				}
				else if (l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TR_CORNER));
				}
				else if (!l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LEFT_END));
				}
				else if (!l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TL_CORNER));
				}
				else if (l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::H_STRAIGHT));
				}
				else if (l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LDR_T));
				}
				else if (!l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DOWN_END));
				}
				else if (!l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::V_STRAIGHT));
				}
				else if (l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BR_CORNER));
				}
				else if (l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::ULD_T));
				}
				else if (!l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BL_CORNER));
				}
				else if (!l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DRU_T));
				}
				else if (l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RUL_T));
				}
				else if (l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::INTERSECTION));
				}

				// Declare offsets and Draw Sprite
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				map_sprites.drawSprite(posX + 256, posY + 32, 0, 2, WHITE);
			}
		}
	}
}

void Maze::drawMazeEX(std::string textureFile){
	std::string textureFilePath = MAP_TEXTURE + textureFile;
	Sprite map_sprites = Sprite(textureFilePath);
	for (size_t i = 0; i < tileBoard.size(); i++) {
		for (size_t j = 0; j < tileBoard[i].size(); j++) {
			// Simple mode: draw rectangle at correct position
			if (tileBoard[i][j].isWall()) {
				// Check what cells have walls
				int left = j - 1;
				int right = j + 1;
				int up = i - 1;
				int down = i + 1;
				bool l = false;
				bool r = false;
				bool u = false;
				bool d = false;
				if (left >= 0) {
					if (tileBoard[i][left].isWall()) {
						l = true;
					}
				}
				if (right < tileBoard[i].size()) {
					if (tileBoard[i][right].isWall()) {
						r = true;
					}
				}
				if (up >= 0) {
					if (tileBoard[up][j].isWall()) {
						u = true;
					}
				}
				if (down < tileBoard.size()) {
					if (tileBoard[down][j].isWall()) {
						d = true;
					}
				}

				// Now we determine frame
				if (!l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::SINGLE));
				}
				else if (!l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::UP_END));
				}
				else if (l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RIGHT_END));
				}
				else if (l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TR_CORNER));
				}
				else if (!l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LEFT_END));
				}
				else if (!l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TL_CORNER));
				}
				else if (l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::H_STRAIGHT));
				}
				else if (l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LDR_T));
				}
				else if (!l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DOWN_END));
				}
				else if (!l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::V_STRAIGHT));
				}
				else if (l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BR_CORNER));
				}
				else if (l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::ULD_T));
				}
				else if (!l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BL_CORNER));
				}
				else if (!l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DRU_T));
				}
				else if (l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RUL_T));
				}
				else if (l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::INTERSECTION));
				}

				// Declare offsets and Draw Sprite
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				map_sprites.drawSprite(posX + 256, posY + 32, 0, 2, WHITE);
			}
		}
	}
}

void Maze::drawMazeEX(Sprite map_sprites){
	for (size_t i = 0; i < tileBoard.size(); i++) {
		for (size_t j = 0; j < tileBoard[i].size(); j++) {
			// Simple mode: draw rectangle at correct position
			if (tileBoard[i][j].isWall()) {
				// Check what cells have walls
				int left = j - 1;
				int right = j + 1;
				int up = i - 1;
				int down = i + 1;
				bool l = false;
				bool r = false;
				bool u = false;
				bool d = false;
				if (left >= 0) {
					if (tileBoard[i][left].isWall()) {
						l = true;
					}
				}
				if (right < tileBoard[i].size()) {
					if (tileBoard[i][right].isWall()) {
						r = true;
					}
				}
				if (up >= 0) {
					if (tileBoard[up][j].isWall()) {
						u = true;
					}
				}
				if (down < tileBoard.size()) {
					if (tileBoard[down][j].isWall()) {
						d = true;
					}
				}

				// Now we determine frame
				if (!l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::SINGLE));
				}
				else if (!l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::UP_END));
				}
				else if (l && !r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RIGHT_END));
				}
				else if (l && !r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TR_CORNER));
				}
				else if (!l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LEFT_END));
				}
				else if (!l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::TL_CORNER));
				}
				else if (l && r && !u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::H_STRAIGHT));
				}
				else if (l && r && !u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::LDR_T));
				}
				else if (!l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DOWN_END));
				}
				else if (!l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::V_STRAIGHT));
				}
				else if (l && !r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BR_CORNER));
				}
				else if (l && !r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::ULD_T));
				}
				else if (!l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::BL_CORNER));
				}
				else if (!l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::DRU_T));
				}
				else if (l && r && u && !d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::RUL_T));
				}
				else if (l && r && u && d) {
					map_sprites.changeFrame(static_cast<int>(spriteType::INTERSECTION));
				}
				// Declare offsets and Draw Sprite
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				map_sprites.drawSprite(posX + 256, posY + 32, 0, 2, WHITE);
			}
			else if(tileBoard[i][j].hasPellet() == 1) {
				map_sprites.changeFrame(static_cast<int>(spriteType::PELLET));
				// Declare offsets and Draw Sprite
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				map_sprites.drawSprite(posX + 256, posY + 32, 0, 2, WHITE);
			}
			else if (tileBoard[i][j].hasSuperPellet()) {
				map_sprites.changeFrame(static_cast<int>(spriteType::SUPER_PELLET));
				// Declare offsets and Draw Sprite
				int posX = j * 8 * 4;
				int posY = i * 8 * 4;
				map_sprites.drawSprite(posX + 256, posY + 32, 0, 2, WHITE);
			}
		}
	}
}

void Maze::setTile(int x, int y, TileType type) {
	this->tileBoard[x][y] = Tile(type);
}

std::vector<std::vector<Tile>> Maze::getTileBoard()
{
	return this->tileBoard;
}

int Maze::getColLength()
{
	return COLUMN_LENGTH;
}

int Maze::getRowLength()
{
	return ROW_LENGTH;
}

bool Maze::checkInMaze(int x, int y){
	return (x >= 0) && (y >= 0) && (x < COLUMN_LENGTH) && (y < ROW_LENGTH);
}

Tile Maze::getTile(int x, int y){
	return tileBoard[x][y];
}
