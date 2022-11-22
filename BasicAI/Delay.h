/**********************************************************************************
// Delay (Arquivo de Cabe�alho)
//
// Cria��o:     02 Ago 2019
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Sincroniza uma a��o
//
**********************************************************************************/

#ifndef _BASICAI_DELAY_H_
#define _BASICAI_DELAY_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

// --------------------------------------------------------------------------------

class Delay : public Object
{
private:
    Sprite * logo;          // logotipo do jogo
    Timer timer;            // medidor de tempo
    
    bool notPlayed;         // intro n�o tocada ainda
    bool fase1;             // fase 1 completada
    bool fase2;             // fase 2 completada
    bool fase3;             // fase 3 completada
    bool fase4;             // fase 4 completada

public:
    Delay();                // construtor
    ~Delay();               // destrutor

    void Update();          // atualiza��o
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
