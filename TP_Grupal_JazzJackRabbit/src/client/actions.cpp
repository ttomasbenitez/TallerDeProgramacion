#include "actions.h"
#include "constant_rate.h"
#include <iostream>

Actions::Actions(Queue<ClientAction> &queue) : actionQueue(queue)
{
}

void Actions::process_actions()
{
    SDL_Event event;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&event);
      if (event.type == SDL_WINDOWEVENT)
        {
            ClientAction action(Action::Quit, 0);
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                _keep_running = false;
                actionQueue.push(action);
                actionQueue.close();
                return;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                //resize();
                break;
            default:
                break;
            }
        }
        if(event.type == SDL_KEYUP){
            Action action;
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                case SDLK_d:
                case SDLK_LEFT:
                case SDLK_a:
                    action = Action::StopMoving;
                    break;
                case SDLK_p:
                    action = Action::StopShooting;
                    break;
                }
            ClientAction clientAction(action, 0);
            actionQueue.push(clientAction);
        }
        if (event.type == SDL_KEYDOWN /*|| event.type == SDL_KEYUP*/ )
        {
            if((keyboard_state_array[SDL_SCANCODE_S] || keyboard_state_array[SDL_SCANCODE_DOWN])&& keyboard_state_array[SDL_SCANCODE_SPACE]){
                ClientAction action(Action::Combo, 0);
                actionQueue.push(action);
            }else if ((keyboard_state_array[SDL_SCANCODE_D] || keyboard_state_array[SDL_SCANCODE_RIGHT])&& (keyboard_state_array[SDL_SCANCODE_LSHIFT]||keyboard_state_array[SDL_SCANCODE_RSHIFT]))
            {
                ClientAction action(Action::Right, 1);
                actionQueue.push(action);
            }
            else if ((keyboard_state_array[SDL_SCANCODE_A] || keyboard_state_array[SDL_SCANCODE_LEFT])&& (keyboard_state_array[SDL_SCANCODE_LSHIFT]||keyboard_state_array[SDL_SCANCODE_RSHIFT]))
            {
                ClientAction action(Action::Left, 1);
                actionQueue.push(action);
            }
            if ((keyboard_state_array[SDL_SCANCODE_LSHIFT]||keyboard_state_array[SDL_SCANCODE_RSHIFT]) && keyboard_state_array[SDL_SCANCODE_F])
            {
                ClientAction action(Action::Ammo, 0);
                actionQueue.push(action);
            }
            Action action;
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
            case SDLK_d:
                action = Action::Right;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                action = Action::Left;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                action = Action::Down;
                break;
            case SDLK_UP:
            case SDLK_w:
                action = Action::Up;
                break;
            case SDLK_p:
                action = Action::Shoot;
                break;
            case SDLK_SPACE:
                action = Action::Jump;
                break;
            case SDLK_e:
                action = Action::SwitchGun;
                break; 
            default:
                return;
                break;
            }
            ClientAction clientAction(action, 0);
            actionQueue.push(clientAction);
        
        }
}


void Actions::stop()
{
    _keep_running = false;
    _is_alive = false;
    try
    {
        actionQueue.close();
    }
    catch(const std::runtime_error& e)
    {
     
    }
}

bool Actions::is_Running(){
    return _keep_running;
}

void Actions::run()
{
    ConstantRateLooper loop(150.0, [act=this](int _){      
        try {
            act->process_actions();
        } catch(const ClosedQueue& e) {}
        return act->_keep_running.load();
    });
    loop.run();
}

 