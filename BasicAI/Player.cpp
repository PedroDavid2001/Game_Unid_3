/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "BasicAI.h"
#include "Hud.h"

Image * Player::missile = nullptr;

// -------------------------------------------------------------------------------

Player::Player()
{
    // inicializa controle
    gamepad = new Controller();
    gamepadOn = gamepad->Initialize();

    // configuração do objeto
    sprite = new Sprite("Resources/Player.png");
    cannon = new Sprite("Resources/Player_cannon.png");
    missile = new Image("Resources/Missile.png");
    speed.RotateTo(90.0f);
    speed.ScaleTo(0.0f);
    
    Point vertex[4] =
    {
        Point(-26, -27), Point(-26,27), Point(26,27), Point(26,-27)
    };

    BBox(new Poly(vertex, 4));

    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    
    tailCount = 0;

    // diparo habilitado
    firingAngle = 0.0f;
    cannonAng = 0.0f;
    keysPressed = false;
    axisCtrl = true;
    keysCtrl = true;
    start = 0;
    timer.Start();
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete missile;
    delete cannon;
    
    delete gamepad;
}

// -------------------------------------------------------------------------------

bool Player::KeysTimed(bool pressed, float time)
{
    // se já passou o tempo para o próximo disparo
    if (keysCtrl)
    {
        // se há qualquer seta pressionada
        if (pressed)
        {
            keysCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // senão aguarda o momento certo
    else if (timer.Elapsed(start, time))
    {
        keysCtrl = true;
    }

    // teclas não pressionadas ou tempo não atingido
    return false;
}

// -------------------------------------------------------------------------------

bool Player::AxisTimed(int axisX, int axisY, float time)
{
    // se já passou o tempo para o próximo disparo
    if (axisCtrl)
    {
        // a magnitude é a distância do eixo para o seu centro
        float magnitude = Point::Distance(Point(0, 0), Point(float(gamepad->Axis(axisX)), float(gamepad->Axis(axisY))));

        // se há qualquer movimento no eixo
        if (magnitude > 0)
        {
            axisCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // senão aguarda o momento certo para testar
    else if (timer.Elapsed(start, time))
    {
        axisCtrl = true;
    }

    // eixo não acionado ou tempo não atingido
    return false;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
    // soma vetor movimento (v) ao vetor velocidade
    speed.Add(v);

    // limita velocidade máxima
    if (speed.Magnitude() > 10.0f)
        speed.ScaleTo(10.0f);
}

// -------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    switch(obj->Type())
    {
    case BLUE:
    case ORANGE:
    case GREEN:
    case MAGENTA:
        BasicAI::gameOver = true;
        break;
        
    }
}

// -------------------------------------------------------------------------------


void Player::Update()
{
    
    BBox()->RotateTo(-speed.Angle() + 90.0f);

    // magnitude do vetor aceleração
    float accel = 40.0f * gameTime;

    // -----------------
    // Controle
    // -----------------

    if (gamepadOn)
    {
        // atualiza estado das teclas e eixos do controle
        gamepad->UpdateState();

        // constrói vetor com base na posição do analógico esquerdo
        float ang = Line::Angle(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));
        float mag = Point::Distance(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));

        // nenhuma direção selecionada
        if (mag == 0)
        {
            // se a velocidade estiver muita baixa
            if (speed.Magnitude() < 0.1)
            {
                // pare de se movimentar imediatamente
                speed.ScaleTo(0.0f);
            }
            else
            {
                // some um vetor no sentido contrário para frear
                Move(Vector(speed.Angle() + 180.0f, 5.0f * gameTime));
            }
        }
        else
        {
            // movimente-se para a nova direção
            Move(Vector(ang, mag * gameTime));
        }

        // dispara míssil com o analógico direito
        if (AxisTimed(AxisRX, AxisRY, 0.150f))
        {
            float ang = Line::Angle(Point(0,0), Point(float(gamepad->Axis(AxisRX)), float(gamepad->Axis(AxisRY))));
            cannonAng = ang;
            BasicAI::audio->Play(FIRE);
            BasicAI::scene->Add(new Missile(ang), STATIC);
        }
    }

    // -----------------
    // Teclado
    // -----------------

    else
    {
        // controla movimentação do jogador
        if (window->KeyDown('D') && window->KeyDown('W')) {
            Move(Vector(45.0f, accel));
        }
        else if (window->KeyDown('A') && window->KeyDown('W')) {
            Move(Vector(135.0f, accel));
        }
        else if (window->KeyDown('A') && window->KeyDown('S')) {
            Move(Vector(225.0f, accel));
        }
        else if (window->KeyDown('D') && window->KeyDown('S')) {
            Move(Vector(315.0f, accel));
        }
        else if (window->KeyDown('D')) {
            Move(Vector(0.0f, accel));
        }
        else if (window->KeyDown('A')) {
            Move(Vector(180.0f, accel));
        }
        else if (window->KeyDown('W')) {
            Move(Vector(90.0f, accel));
        }
        else if (window->KeyDown('S')) {
            Move(Vector(270.0f, accel));
        }
        else
            // se nenhuma tecla está pressionada comece a frear
            if (speed.Magnitude() > 0.1f)
                Move(Vector(speed.Angle() + 180.0f, 5.0f * gameTime));
            else
                // velocidade muita baixa, não use soma vetorial, apenas pare
                speed.ScaleTo(0.0f);

        // controla direção dos disparos
        if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 45.0f;
            cannonAng = 315.0f;
        } 
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 135.0f;
            cannonAng = 225.0f;
        }
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 225.0f;
            cannonAng = 135.0f;
        }
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 315.0f;
            cannonAng = 45.0f;
        }
        else if (window->KeyDown(VK_RIGHT)) {
            keysPressed = true;
            firingAngle = 0.0f;
            cannonAng = 0.0f;
        }
        else if (window->KeyDown(VK_LEFT)) {
            keysPressed = true;
            firingAngle = 180.0f;
            cannonAng = 180.0f;
        }
        else if (window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 90.0f;
            cannonAng = 270.0f;
        }
        else if (window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 270.0f;
            cannonAng = 90.0f;
        }
        else
        {
            keysPressed = false;
        }

        // dispara míssil
        if (KeysTimed(keysPressed, 0.150f))
        {
            BasicAI::audio->Play(FIRE);
            BasicAI::scene->Add(new Missile(firingAngle), STATIC);
        }
    }

    // movimenta objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);

    
    Hud::particles -= tailCount;
    
    Hud::particles += tailCount;

    // restringe a área do jogo
    if (x < 90)
        MoveTo(90, y);
    if (y < 90)
        MoveTo(x, 90);
    if (x > game->Width() - 90)
        MoveTo(game->Width() - 90, y);
    if (y > game->Height() - 90)
        MoveTo(x, game->Height() - 90);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed.Angle() + 90.0f);
    cannon->Draw(x, y, Layer::UPPER, 1.0f, cannonAng);
    
        
}

// -------------------------------------------------------------------------------
