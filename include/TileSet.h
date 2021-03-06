#ifndef TILESET_H_
#define TILESET_H_

#include "Sprite.h"

class TileSet {
private:
	Sprite tileSet;
	int columns;
	int rows;
	int tileWidth;
	int tileHeight;
	int adjustX;
	int adjustY;

public:
	TileSet(int tileWidth, int tileHeight, std::string file, int adjustX = 0, int ajustY = 0);
	~TileSet();
	void Render(int index, int x, int y);
	Sprite GetTileSet();
	int GetTileWidth();
	int GetTileHeight();
	int GetColumns();
	int GetRows();
};

#endif /* TILESET_H_ */
