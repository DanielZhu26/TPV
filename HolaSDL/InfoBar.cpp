#include "InfoBar.h"
#include "PlayState.h"
#include "Game.h"

InfoBar::InfoBar(int score, Texture* texturaCannon, Texture* texturaNumeros, PlayState* playState)
    : GameObject(playState)
{
    this->playState = playState;
    this->score = score;
    this->texturaCannon = texturaCannon;
    this->texturaNumeros = texturaNumeros;
}

InfoBar::~InfoBar()
{

}


void InfoBar::render() const
{
    int cannonTexPadding = 5;
    for (int i = 0; i < playState->getPlayerLives(); i++)
    {
        SDL_Rect rectDestino{(cannonTexPadding * (i + 1)) + texturaCannon->getFrameWidth() * i,
            gameState->getGame()->getHeight() - texturaCannon->getFrameHeight() - cannonTexPadding,
            texturaCannon->getFrameWidth(), texturaCannon->getFrameHeight()};
        texturaCannon->renderFrame(rectDestino, 0, 0);
    }

    int scoreTexPadding = 5;
    int aux = score;
    int digito;
    int i = 1;
    if (aux == 0)
    {
        SDL_Rect rectDestino{ gameState->getGame()->getWidth() - scoreTexPadding - texturaNumeros->getFrameWidth(),
                gameState->getGame()->getHeight() - scoreTexPadding - texturaNumeros->getFrameHeight(),
                texturaNumeros->getFrameWidth(), texturaNumeros->getFrameHeight() };
        texturaNumeros->renderFrame(rectDestino, 0, 0);
    }
    else
    {
        while ((log10(aux) + 1) > 0) {
            digito = aux % 10;
            SDL_Rect rectDestino{ gameState->getGame()->getWidth() - scoreTexPadding - (texturaNumeros->getFrameWidth() * i),
                gameState->getGame()->getHeight() - scoreTexPadding - texturaNumeros->getFrameHeight(),
                texturaNumeros->getFrameWidth(), texturaNumeros->getFrameHeight() };
            texturaNumeros->renderFrame(rectDestino, 0, digito);
            aux = aux / 10;
            i++;
        }
    }
}

void InfoBar::update()
{

}

void InfoBar::save(std::ofstream& out) const
{
    out << 7 << " " << score << endl;
}