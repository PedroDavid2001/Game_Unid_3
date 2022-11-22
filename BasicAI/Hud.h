/**********************************************************************************
// Hud (Arquivo de Cabe�alho)
//
// Cria��o:     02 Ago 2019
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Heads Up Display
//
**********************************************************************************/

#ifndef _BASICAI_HUD_H_
#define _BASICAI_HUD_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>
using std::stringstream;

// --------------------------------------------------------------------------------

class Hud : public Object
{
private:
    Font * font = nullptr;              // fonte para exibi��o normal
    Font * bold = nullptr;              // fonte para exibi��o negrito
    Sprite * infoBox = nullptr;         // �rea de informa��es do jogo

    stringstream text;                  // texto tempor�rio
    uint frameCount;                    // contador de quadros por segundo
    float totalTime;                    // tempo total transcorrido 
    uint fps;                           // valor para exibi��o do fps

public:
    static uint missiles;               // n�mero de m�sseis na tela
    static uint oranges;                // n�mero de inimigos laranja
    static uint magentas;               // n�mero de inimigos rosa
    static uint blues;                  // n�mero de inimigos azul
    static uint greens;                 // n�mero de inimigos verde
    static uint particles;              // n�mero de part�culas ativas

    Hud();                              // construtor
    ~Hud();                             // destrutor

    void Update();                      // atualiza��o
    void Draw();                        // desenho
};

// ------------------------------------------------------------------------------

#endif

