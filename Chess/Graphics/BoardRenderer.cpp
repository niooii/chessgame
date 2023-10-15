#include "BoardRenderer.h"

BoardRenderer::BoardRenderer()
{

}

void BoardRenderer::Init(Board* target)
{
	this->target = target;

	SDL_Color green{70,160,70,200};
	SDL_Color white{ 255,255,255,255 };

	for (std::vector<Tile>& tilevec : target->Tiles())
	{
		for (Tile& tile : tilevec)
		{
			int w{ 80 };
			int h{ 80 };
			int offset{ 100 };
			rendertiles.emplace_back(&tile,
				(tile.col - 1) * w + offset, (tile.row - 1) * h + offset, w, h,
				(tile.row % 2 == (tile.col % 2 == 0 ? 0 : 1) ? green : white));
		}
	}

	for (Tile& t : target->WhiteCaptured())
	{
		int w{ 80 };
		int h{ 80 };
		int offset{ 100 };
		killedtiles.emplace_back(&t,
			(t.col - 0.5) * w/2 + offset, -0.75 * h + offset, w/2, h/2,
			white);
	}

	for (Tile& t : target->BlackCaptured())
	{
		int w{ 80 };
		int h{ 80 };
		int offset{ 100 };
		killedtiles.emplace_back(&t,
			(t.col - 0.5) * w / 2 + offset, (target->Rows() - 0.25) * h + offset, w / 2, h / 2,
			white);
	}

	for (Piece& p : target->Pieces())
	{
		SDL_Texture* tex;
		switch (p.Type())
		{
		case KING:
			if (p.Team() == WHITE)
				tex = Textures::WhiteKing;
			else
				tex = Textures::BlackKing;
			break;

		case PAWN:
			if (p.Team() == WHITE)
				tex = Textures::WhitePawn;
			else
				tex = Textures::BlackPawn;
			break;

		case QUEEN:
			if (p.Team() == WHITE)
				tex = Textures::WhiteQueen;
			else
				tex = Textures::BlackQueen;
			break;

		case BISHOP:
			if (p.Team() == WHITE)
				tex = Textures::WhiteBishop;
			else
				tex = Textures::BlackBishop;
			break;

		case ROOK:
			if (p.Team() == WHITE)
				tex = Textures::WhiteRook;
			else
				tex = Textures::BlackRook;
			break;

		case KNIGHT:
			if (p.Team() == WHITE)
				tex = Textures::WhiteKnight;
			else
				tex = Textures::BlackKnight;
			break;

		default:
			tex = nullptr;
			break;
		}

		if (tex == nullptr)
		{
			//std::cout << "TEXTURE NULL!" << '\n';
		}

		renderpieces.emplace_back(&p, tex);
			
	}

}

void BoardRenderer::Draw(SDL_Renderer* renderer)
{
	//draw colored tiles
	for (GraphicTile& gt : rendertiles)
	{
		if (gt.usetempcolor)
		{
			SDL_SetRenderDrawColor(renderer, gt.tempcolor.r, gt.tempcolor.g, gt.tempcolor.b, gt.tempcolor.a);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, gt.color.r, gt.color.g, gt.color.b, gt.color.a);
		}
		SDL_RenderFillRect(renderer, &gt.dest);
	}

	for (GraphicTile& gt : killedtiles)
	{
		SDL_SetRenderDrawColor(renderer, gt.color.r, gt.color.g, gt.color.b, gt.color.a);
		SDL_RenderFillRect(renderer, &gt.dest);
	}

	//draw pieces on top of them
	for (GraphicPiece& gp : renderpieces)
	{
		//check for optimizations later
		GraphicTile* gt = GraphicTileForTile(gp.correspondingPiece->CurrentTile());
		if (gt == nullptr)
		{
			std::cout << "corresponding graphics tile does not exist" << '\n';
		}
		else
		{
			//check if type differs from inittype:
			if (gp.correspondingPiece->Type() != gp.prevType)
			{
				gp.prevType = gp.correspondingPiece->Type();
				SDL_Texture* tex{ nullptr };
				Piece* p = gp.correspondingPiece;
				switch (p->Type())
				{
				case KING:
					if (p->Team() == WHITE)
						tex = Textures::WhiteKing;
					else
						tex = Textures::BlackKing;
					break;

				case PAWN:
					if (p->Team() == WHITE)
						tex = Textures::WhitePawn;
					else
						tex = Textures::BlackPawn;
					break;

				case QUEEN:
					if (p->Team() == WHITE)
						tex = Textures::WhiteQueen;
					else
						tex = Textures::BlackQueen;
					break;

				case BISHOP:
					if (p->Team() == WHITE)
						tex = Textures::WhiteBishop;
					else
						tex = Textures::BlackBishop;
					break;

				case ROOK:
					if (p->Team() == WHITE)
						tex = Textures::WhiteRook;
					else
						tex = Textures::BlackRook;
					break;

				case KNIGHT:
					if (p->Team() == WHITE)
						tex = Textures::WhiteKnight;
					else
						tex = Textures::BlackKnight;
					break;

				default:
					tex = nullptr;
					break;
				}
				gp.texture = tex;
			}
			if (gp.correspondingPiece->IsDead())
			{
				gp.smallDest.x = gt->dest.x + (gt->dest.w - gp.smallDest.w) / 2;
				gp.smallDest.y = gt->dest.y + (gt->dest.h - gp.smallDest.h) / 2;
				SDL_RenderCopy(renderer, gp.texture, NULL, &gp.smallDest);
			}
			else
			{
				gp.dest.x = gt->dest.x + (gt->dest.w - gp.dest.w) / 2;
				gp.dest.y = gt->dest.y + (gt->dest.h - gp.dest.h) / 2;
				SDL_RenderCopy(renderer, gp.texture, NULL, &gp.dest);
			}
		}
	}
}

Tile* BoardRenderer::TileAtClick(int x, int y)
{
	SDL_Point querypoint{ x, y };
	for (GraphicTile& gt : rendertiles)
	{
		if (SDL_PointInRect(&querypoint, &gt.dest))
		{
			return gt.correspondingTile;
		}
	}
	return nullptr;
}

GraphicTile* BoardRenderer::GraphicTileForTile(Tile* t)
{
	for (GraphicTile& gt : rendertiles)
	{
		if (gt.correspondingTile == t)
			return &gt;
	}
	for (GraphicTile& gt : killedtiles)
	{
		if (gt.correspondingTile == t)
			return &gt;
	}
	return nullptr;
}

GraphicPiece* BoardRenderer::GraphicPieceForPiece(Piece* p)
{
	for (GraphicPiece& gp : renderpieces)
	{
		if (gp.correspondingPiece == p)
			return &gp;
	}
	return nullptr;
}

void BoardRenderer::SetColor(Tile* t, SDL_Color tempcolor)
{
	GraphicTile* gt = GraphicTileForTile(t);
	if (gt == nullptr)
		return;

	gt->usetempcolor = true;
	gt->tempcolor = tempcolor;
}

void BoardRenderer::RevertColor(Tile* t)
{
	GraphicTile* gt = GraphicTileForTile(t);
	if (gt == nullptr)
		return;

	gt->usetempcolor = false;
}