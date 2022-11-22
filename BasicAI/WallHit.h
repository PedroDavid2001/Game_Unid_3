/**********************************************************************************
// WallHit (Arquivo de Cabe�alho)
// 
// Cria��o:     03 Ago 2019
// Atualiza��o: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Efeito de explos�o usando sistema de part�culas
//
**********************************************************************************/

#ifndef _BASICAI_WALLHIT_H_
#define _BASICAI_WALLHIT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"
#include "Missile.h"

// ---------------------------------------------------------------------------------

class WallHit : public Object
{
private:
    Particles * sparks;                 // sistema de part�culas
    
public:
    WallHit(float pX, float pY);        // construtor
    ~WallHit();                         // destrutor

    int  Size();                        // quantidade de part�culas
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline int WallHit::Size()
{ return sparks->Size(); }

inline void WallHit::Draw()
{ sparks->Draw(Layer::MIDDLE, 0.0f); }

// ---------------------------------------------------------------------------------


#endif