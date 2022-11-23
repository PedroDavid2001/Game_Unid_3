/**********************************************************************************
// Home (C�digo Fonte)
//
// Cria��o:     14 Fev 2013
// Atualiza��o: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tela de abertura do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "BasicAI.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

Scene* Home::scene = nullptr;

// ------------------------------------------------------------------------------

void Home::Init()
{
    scene = new Scene();

    // cria objeto mouse
    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    backg = new Sprite("Resources/home.jpeg");
    //title = new Sprite("Resources/title.png");

}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // atualiza objeto mouse
    mouse->Update();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    // desenha itens do menu
    scene->Draw();

    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
   // title->Draw(window->CenterX(), window->CenterY(), Layer::FRONT, GravityGuy::totalScale);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete scene;
    delete backg;
    delete title;
}

// ------------------------------------------------------------------------------