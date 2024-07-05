#ifndef SPRITES_LOADER_H
#define SPRITES_LOADER_H

#include <iostream>
#include <vector>
#include "../common/enums.h"

// Cargar manualmente frames porque estos no son de width constante.
#include <map>

struct Frame
{
    int x;
    int y;
    int width;
    int height;
};

const std::map<enum AnimationState, std::vector<Frame>> animations_frames = {
    {IDLE_JAZZ, {
                    // Cargar manualmente frames
                    {0, 0, 49, 53},   // Frame 1
                    {48, 0, 55, 53},  // Frame 2
                    {106, 0, 51, 53}, // Frame 3
                    {158, 0, 46, 53}, // Frame 4
                    {206, 0, 44, 53}, // Frame 5
                    {250, 0, 43, 53}, // Frame 6
                    {292, 0, 43, 53}, // Frame 7
                    {337, 0, 46, 53}, // Frame 8
                    {383, 0, 49, 53}, // Frame 9
                    {438, 0, 53, 53}, // Frame 10
                    {490, 0, 46, 53}, // Frame 11
                    {537, 0, 51, 53}, // Frame 12
                    {593, 0, 54, 53}, // Frame 13
                }},
    {WALKING_JAZZ, {
                       {1, 0, 56, 50},   // Frame 1
                       {56, 0, 58, 50},  // Frame 2
                       {114, 0, 57, 50}, // Frame 3
                       {170, 0, 58, 50}, // Frame 4
                       {228, 0, 57, 50}, // Frame 5
                       {284, 0, 58, 50}, // Frame 6
                       {341, 0, 58, 50}, // Frame 7
                       {398, 0, 58, 50}, // Frame 8
                   }},
    {RUNNING_JAZZ, {
                       {0, 0, 66, 41},   // Frame 1
                       {65, 0, 71, 41},  // Frame 2
                       {137, 0, 66, 41}, // Frame 3
                       {203, 0, 66, 41}, // Frame 4
                       {270, 0, 66, 41}, // Frame 5
                       {336, 0, 69, 41}, // Frame 6
                       {407, 0, 62, 41}, // Frame 7
                       {469, 0, 65, 41}, // Frame 8
                   }},
    {PREPARING_TO_DASH_JAZZ, {
                                 {0, 0, 46, 63},   // Frame 1
                                 {45, 0, 46, 63},  // Frame 2
                                 {89, 0, 46, 63},  // Frame 3
                                 {136, 0, 52, 63}, // Frame 4
                                 {188, 0, 57, 63}, // Frame 5
                                 {244, 0, 52, 63}, // Frame 6
                                 {296, 0, 62, 63}, // Frame 7
                                 {361, 0, 67, 63}, // Frame 8
                                 {427, 0, 68, 63}, // Frame 9
                                 {495, 0, 68, 63}, // Frame 10
                                 {562, 0, 68, 63}, // Frame 11
                                 {630, 0, 60, 63}, // Frame 12
                                 {689, 0, 60, 63}, // Frame 13

                             }},
    {DASHING_JAZZ, {
                       {0, 5, 72, 41},   // Frame 1
                       {71, 5, 67, 41},  // Frame 2
                       {137, 1, 71, 45}, // Frame 3
                       {207, 5, 67, 41}, // Frame 4
                   }},
    {SKIDDING_JAZZ, {
                        {0, 0, 58, 43},   // Frame 1
                        {58, 0, 57, 43},  // Frame 2
                        {114, 0, 57, 43}, // Frame 3
                        {171, 0, 68, 43}, // Frame 4
                        {239, 0, 67, 43}, // Frame 5
                        {306, 0, 68, 43}, // Frame 6
                    }},

    {TRANSITION_TO_JUMPING_JAZZ, {
                                     {0, 0, 48, 59},  // Frame 1
                                     {47, 0, 52, 59}, // Frame 2
                                     {99, 0, 53, 59}, // Frame 3
                                 }},

    {JUMPING_UP_JAZZ, {
                          {0, 0, 46, 59},  // Frame 1
                          {45, 0, 44, 59}, // Frame 2
                          {89, 0, 41, 59}, // Frame 3
                      }},

    {TRANSITION_TO_FALLING_JAZZ, {
                                     {0, 0, 50, 59},   // Frame 1
                                     {50, 0, 55, 59},  // Frame 2
                                     {104, 0, 59, 59}, // Frame 3
                                 }},

    {FALLING_JAZZ, {
                       {0, 0, 57, 59},   // Frame 1
                       {57, 0, 61, 59},  // Frame 2
                       {117, 0, 61, 59}, // Frame 3
                   }},

    {LANDING_JAZZ, {
                       {0, 0, 53, 51},   // Frame 1
                       {52, 0, 62, 51},  // Frame 2
                       {113, 0, 56, 51}, // Frame 3
                       {168, 0, 49, 51}, // Frame 4
                       {216, 0, 47, 51}, // Frame 5
                   }},
    {JUMPING_FORWARD_JAZZ, {
                               {0, 3, 53, 61},   // Frame 1
                               {53, 0, 38, 61},  // Frame 2
                               {90, 0, 43, 61},  // Frame 3
                               {132, 0, 50, 61}, // Frame 4
                               {181, 0, 48, 61}, // Frame 5
                               {228, 0, 52, 61}, // Frame 6
                               {279, 0, 52, 61}, // Frame 7
                               {330, 0, 52, 61}, // Frame 8
                               {382, 0, 45, 61}, // Frame 9
                           }},
    {FALLING_FORWARD_JAZZ, {
                               {0, 0, 38, 51},  // Frame 1
                               {37, 0, 37, 51}, // Frame 2
                               {73, 0, 39, 51}, // Frame 3
                           }},
    {SHOOTING_WHILE_FALLING_JAZZ, {
                                      {0, 0, 52, 61},  // Frame 1
                                      {52, 0, 50, 61}, // Frame 2
                                  }},
    {STOP_SHOOTING_WHILE_FALLING_JAZZ, {
                                           {0, 0, 43, 57},  // Frame 1
                                           {45, 0, 40, 57}, // Frame 2
                                       }},
    {SHOOTING_JAZZ, {
                        {0, 0, 49, 61},  // Frame 1
                        {50, 0, 48, 61}, // Frame 2
                    }},
    {STOP_SHOOTING_JAZZ, {
                             {0, 0, 42, 61},   // Frame 1
                             {42, 0, 41, 61},  // Frame 2
                             {84, 0, 40, 61},  // Frame 3
                             {126, 0, 39, 61}, // Frame 4
                         }},
    {LOOKING_UP_JAZZ, {
                          {0, 0, 54, 70},  // Frame 1
                          {56, 0, 47, 70}, // Frame 2
                      }},
    {SHOOTING_UP_JAZZ, {
                           {0, 0, 44, 70},  // Frame 1
                           {46, 0, 41, 70}, // Frame 2
                       }},
    {CROUCHING_JAZZ, {
                         {0, 0, 44, 53},  // Frame 1
                         {44, 0, 61, 53}, // Frame 2
                     }},
    {CROUCH_JAZZ, {
                      {0, 0, 70, 40}, // Frame 1
                  }},
    {CROUCH_SHOOTING_JAZZ, {
                               {0, 0, 67, 41},  // Frame 1
                               {67, 0, 67, 41}, // Frame 2
                           }},
    {STANDING_UP_JAZZ, {
                           {0, 0, 59, 53},  // Frame 1
                           {58, 0, 45, 53}, // Frame 2
                       }},
    {TRANSITION_TO_UPPERCUT_JAZZ, {
                                      {0, 0, 59, 56},   // Frame 1
                                      {58, 0, 54, 56},  // Frame 2
                                      {112, 0, 46, 56}, // Frame 3
                                      {159, 0, 42, 56}, // Frame 4
                                      {201, 0, 38, 56}, // Frame 5
                                      {238, 0, 33, 56}, // Frame 6
                                      {270, 0, 30, 56}, // Frame 7
                                  }},
    {UPPERCUT_JAZZ, {
                        {0, 0, 27, 61},  // Frame 1
                        {26, 0, 27, 61}, // Frame 2
                        {52, 0, 28, 61}, // Frame 3
                    }},
    {TRANSITION_TO_FALLING_AFTER_UPPERCUT_JAZZ, {
                                                    {0, 0, 43, 55},  // Frame 1
                                                    {42, 0, 56, 55}, // Frame 2
                                                }},
    {INTOXICATED_IDLE_JAZZ, {
                                {0, 0, 47, 52},   // Frame 1
                                {53, 0, 46, 52},  // Frame 2
                                {102, 0, 47, 52}, // Frame 3
                                {154, 0, 47, 52}, // Frame 4
                                {205, 0, 47, 52}, // Frame 5
                                {258, 0, 47, 52}, // Frame 6
                                {311, 0, 47, 52}, // Frame 7
                                {365, 0, 47, 52}, // Frame 8
                            }},
    {INTOXICATED_WALKING_JAZZ, {
                                   {0, 0, 60, 54},   // Frame 1
                                   {61, 0, 60, 54},  // Frame 2
                                   {121, 0, 60, 54}, // Frame 3
                                   {182, 0, 62, 54}, // Frame 4
                                   {243, 0, 68, 54}, // Frame 5
                                   {311, 0, 66, 54}, // Frame 6
                                   {376, 0, 62, 54}, // Frame 7
                                   {439, 0, 62, 54}, // Frame 8
                                   {501, 0, 61, 54}, // Frame 9
                                   {560, 0, 62, 54}, // Frame 10
                                   {624, 0, 62, 54}, // Frame 11
                                   {685, 0, 66, 54}, // Frame 12
                               }},
    {RECEIVE_DAMAGE_JAZZ, {
                              {0, 0, 42, 52},   // Frame 1
                              {44, 0, 37, 55},  // Frame 2
                              {84, 0, 37, 55},  // Frame 3
                              {124, 0, 46, 68}, // Frame 4
                              {174, 0, 46, 68}, // Frame 5
                              {227, 0, 61, 68}, // Frame 6
                              {293, 0, 69, 68}, // Frame 7
                              {365, 0, 74, 68}, // Frame 8
                              {445, 0, 70, 68}, // Frame 9
                          }},
    {IMPACT_JAZZ, {
                      {0, 0, 52, 74},   // Frame 1
                      {52, 0, 44, 74},  // Frame 2
                      {97, 0, 77, 74},  // Frame 3
                      {176, 0, 83, 74}, // Frame 4
                      {269, 0, 89, 74}, // Frame 5
                      {370, 0, 91, 74}, // Frame 6
                      {468, 0, 94, 74}, // Frame 7
                      {568, 0, 92, 74}, // Frame 8
                      {668, 0, 86, 74}, // Frame 9
                  }},
    {DYING_JAZZ, {
                     {0, 0, 50, 62},   // Frame 1
                     {49, 0, 50, 62},  // Frame 2
                     {100, 0, 57, 62}, // Frame 3
                     {160, 0, 65, 62}, // Frame 4
                     {229, 0, 68, 40}, // Frame 5
                     {300, 0, 62, 40}, // Frame 6
                     {368, 0, 75, 40}, // Frame 7
                     {450, 0, 84, 40}, // Frame 8
                     {541, 0, 79, 40}, // Frame 9
                     {624, 0, 68, 40}, // Frame 9
                 }},

    {IDLE_LORI, {
                    {0, 0, 44, 57},   // Frame 1
                    {44, 0, 40, 57},  // Frame 2
                    {88, 0, 44, 57},  // Frame 3
                    {135, 0, 44, 57}, // Frame 4
                    {177, 0, 44, 57}, // Frame 5
                    {221, 0, 44, 57}, // Frame 6
                    {265, 0, 44, 57}, // Frame 7
                    {308, 0, 44, 57}, // Frame 8
                }},

    {SHOOTING_FORWARD_LORI, {
                                {0, 0, 48, 59},  // Frame 1
                                {49, 0, 48, 59}, // Frame 2
                            }},

    {STOP_SHOOTING_FORWARD_LORI, {
                                     {0, 0, 40, 59},   // Frame 1
                                     {41, 0, 40, 59},  // Frame 2
                                     {82, 0, 40, 59},  // Frame 3
                                     {123, 0, 42, 59}, // Frame 4
                                 }},

    {LOOKING_UP_LORI, {
                          {0, 0, 47, 59},  // Frame 1
                          {45, 0, 47, 59}, // Frame 2
                      }},

    {SHOOTING_UP_LORI, {
                           {0, 0, 44, 59},  // Frame 1
                           {43, 0, 44, 59}, // Frame 2
                       }},

    {CROUCHING_LORI, {
                         {0, 0, 43, 52},   // Frame 1
                         {43, 0, 43, 52},  // Frame 2
                         {85, 0, 43, 52},  // Frame 3
                         {128, 0, 47, 52}, // Frame 4
                     }},

    {CROUCH_LORI, {
                      {0, 0, 49, 36}, // Frame 1
                  }},

    {CROUCH_SHOOTING_LORI, {
                               {0, 0, 51, 37},  // Frame 1
                               {50, 0, 50, 37}, // Frame 2
                           }},

    {STANDING_UP_LORI, {
                           {0, 0, 43, 39},  // Frame 1
                           {44, 0, 43, 39}, // Frame 2
                       }},

    {FLYING_KICK_LORI, {
                           {0, 0, 51, 62},   // Frame 1
                           {50, 0, 46, 62},  // Frame 2
                           {98, 0, 46, 62},  // Frame 3
                           {143, 0, 46, 62}, // Frame 4
                           {191, 0, 50, 62}, // Frame 5
                           {242, 0, 51, 62}, // Frame 6
                           {296, 0, 54, 62}, // Frame 7
                           {352, 0, 65, 62}, // Frame 8
                           {419, 0, 66, 62}, // Frame 9
                           {488, 0, 66, 62}, // Frame 10
                       }},

    {WALKING_LORI, {
                       {0, 0, 51, 53},   // Frame 1
                       {51, 0, 51, 53},  // Frame 2
                       {103, 0, 51, 53}, // Frame 3
                       {153, 0, 51, 53}, // Frame 4
                       {204, 0, 51, 53}, // Frame 5
                       {255, 0, 51, 53}, // Frame 6
                       {308, 0, 51, 53}, // Frame 7
                       {357, 0, 51, 53}, // Frame 8
                   }},

    {RUNNING_LORI, {
                       {0, 0, 54, 46},   // Frame 1
                       {53, 0, 55, 46},  // Frame 2
                       {110, 0, 55, 46}, // Frame 3
                       {166, 0, 55, 46}, // Frame 4
                       {218, 0, 55, 46}, // Frame 5
                       {271, 0, 55, 46}, // Frame 6
                       {329, 0, 55, 46}, // Frame 7
                       {383, 0, 52, 46}, // Frame 8
                   }},

    {PREPARING_TO_DASH_LORI, {
                                 {0, 0, 47, 60},   // Frame 1
                                 {45, 0, 47, 60},  // Frame 2
                                 {90, 0, 47, 60},  // Frame 3
                                 {134, 0, 47, 60}, // Frame 4
                                 {181, 0, 47, 60}, // Frame 5
                                 {230, 0, 47, 60}, // Frame 6
                                 {276, 0, 47, 60}, // Frame 7
                                 {323, 0, 59, 60}, // Frame 8
                                 {381, 0, 54, 60}, // Frame 9
                                 {438, 0, 54, 60}, // Frame 10
                                 {495, 0, 54, 60}, // Frame 11
                                 {554, 0, 65, 60}, // Frame 12
                                 {618, 0, 62, 60}, // Frame 13

                             }},

    {DASHING_LORI, {
                       {0, 0, 65, 44},   // Frame 1
                       {65, 0, 65, 44},  // Frame 2
                       {129, 0, 65, 44}, // Frame 3
                       {194, 0, 66, 44}, // Frame 4
                       {262, 0, 66, 44}, // Frame 5
                       {327, 0, 66, 44}, // Frame 6
                       {391, 0, 66, 44}, // Frame 7
                       {457, 0, 66, 44}, // Frame 8
                   }},

    {SKIDDING_LORI, {
                        {0, 0, 50, 49},   // Frame 1
                        {51, 0, 51, 49},  // Frame 2
                        {104, 0, 53, 49}, // Frame 3
                        {158, 0, 56, 49}, // Frame 4
                        {217, 0, 59, 49}, // Frame 5
                        {277, 0, 59, 49}, // Frame 6
                    }},

    {STOP_SKIDDING_LORI, {
                             {0, 0, 57, 50},   // Frame 1
                             {56, 0, 53, 50},  // Frame 2
                             {108, 0, 50, 50}, // Frame 3
                             {158, 0, 50, 50}, // Frame 4
                             {208, 0, 41, 50}, // Frame 5
                             {249, 0, 39, 50}, // Frame 6
                             {287, 0, 39, 50}, // Frame 7
                             {325, 0, 46, 50}, // Frame 8
                         }},

    {TRANSITION_TO_JUMPING_LORI, {
                                     {0, 0, 38, 60},  // Frame 1
                                     {37, 0, 41, 60}, // Frame 2
                                     {77, 0, 39, 60}, // Frame 3
                                 }},

    {JUMPING_UP_LORI, {
                          {0, 0, 42, 60},  // Frame 1
                          {42, 0, 44, 60}, // Frame 2
                          {85, 0, 45, 60}, // Frame 3
                      }},

    {TRANSITION_TO_FALLING_LORI, {
                                     {0, 0, 46, 60},  // Frame 1
                                     {45, 0, 46, 60}, // Frame 2
                                     {89, 0, 41, 60}, // Frame 3
                                 }},

    {FALLING_LORI, {
                       {0, 0, 35, 58},  // Frame 1
                       {36, 0, 35, 58}, // Frame 2
                       {72, 0, 35, 58}, // Frame 3
                   }},

    {JUMPING_FORWARD_LORI, {
                               {0, 0, 50, 60},   // Frame 1
                               {53, 0, 43, 60},  // Frame 2
                               {99, 0, 43, 60},  // Frame 3
                               {142, 0, 47, 60}, // Frame 4
                               {190, 0, 48, 60}, // Frame 5
                               {238, 0, 49, 60}, // Frame 6
                               {287, 0, 53, 60}, // Frame 7
                               {340, 0, 53, 60}, // Frame 8
                               {392, 0, 53, 60}, // Frame 9
                           }},

    {FALLING_FORWARD_LORI, {
                               {0, 0, 42, 60},   // Frame 1
                               {40, 0, 42, 60},  // Frame 2
                               {80, 0, 42, 60},  // Frame 3
                               {120, 0, 42, 60}, // Frame 4
                           }},

    {SHOOTING_WHILE_FALLING_LORI, {
                                      {0, 0, 40, 67},  // Frame 1
                                      {40, 0, 40, 67}, // Frame 2
                                  }},
    {STOP_SHOOTING_WHILE_FALLING_LORI, {
                                           {0, 0, 37, 67},  // Frame 1
                                           {36, 0, 31, 67}, // Frame 2
                                       }},

    {LANDING_LORI, {
                       {0, 0, 46, 50},   // Frame 1
                       {46, 0, 50, 50},  // Frame 2
                       {96, 0, 50, 50},  // Frame 3
                       {147, 0, 48, 50}, // Frame 4
                       {195, 0, 53, 50}, // Frame 5
                       {248, 0, 46, 50}, // Frame 6
                       {293, 0, 42, 50}, // Frame 7
                   }},

    {INTOXICATED_IDLE_LORI, {
                                {0, 0, 60, 53},   // Frame 1
                                {58, 0, 60, 53},  // Frame 2
                                {119, 0, 60, 53}, // Frame 3
                                {179, 0, 60, 53}, // Frame 4
                                {243, 0, 60, 53}, // Frame 5
                                {309, 0, 60, 53}, // Frame 6
                                {370, 0, 49, 53}, // Frame 7
                                {421, 0, 49, 53}, // Frame 8
                                {471, 0, 49, 53}, // Frame 9
                                {525, 0, 49, 53}, // Frame 10
                                {578, 0, 52, 53}, // Frame 11
                                {630, 0, 52, 53}, // Frame 12
                            }},

    {INTOXICATED_WALKING_LORI, {
                                   {0, 0, 54, 55},   // Frame 1
                                   {52, 0, 54, 55},  // Frame 2
                                   {105, 0, 54, 55}, // Frame 3
                                   {160, 0, 54, 55}, // Frame 4
                                   {212, 0, 54, 55}, // Frame 5
                                   {265, 0, 54, 55}, // Frame 6
                                   {318, 0, 54, 55}, // Frame 7
                                   {369, 0, 54, 55}, // Frame 8
                                   {421, 0, 54, 55}, // Frame 9
                                   {472, 0, 54, 55}, // Frame 10
                                   {524, 0, 54, 55}, // Frame 11
                                   {579, 0, 52, 55}, // Frame 12
                               }},

    {RECEIVE_DAMAGE_LORI, {
                              {0, 0, 53, 59},   // Frame 1
                              {51, 0, 46, 59},  // Frame 2
                              {97, 0, 38, 59},  // Frame 3
                              {137, 0, 45, 59}, // Frame 4
                              {182, 0, 53, 59}, // Frame 5
                              {238, 0, 59, 59}, // Frame 6
                              {296, 0, 56, 59}, // Frame 7
                              {351, 0, 56, 59}, // Frame 8
                              {406, 0, 48, 59}, // Frame 9
                              {452, 0, 48, 59}, // Frame 10
                              {497, 0, 44, 59}, // Frame 11
                          }},

    {IDLE_SPAZ, {
                    {0, 0, 38, 50},   // Frame 1
                    {39, 0, 38, 50},  // Frame 2
                    {76, 0, 35, 50},  // Frame 3
                    {111, 0, 38, 50}, // Frame 4
                    {147, 0, 37, 50}, // Frame 5
                }},
    {SHOOTING_FORWARD_SPAZ, {
                                {0, 0, 52, 48},  // Frame 1
                                {52, 0, 51, 48}, // Frame 2
                            }},

    {STOP_SHOOTING_FORWARD_SPAZ, {
                                     {0, 0, 50, 48},   // Frame 1
                                     {49, 0, 38, 48},  // Frame 2
                                     {87, 0, 41, 48},  // Frame 3
                                     {128, 0, 47, 48}, // Frame 4
                                 }},

    {LOOKING_UP_SPAZ, {
                          {0, 0, 48, 48},  // Frame 1
                          {50, 0, 42, 48}, // Frame 2
                      }},

    {SHOOTING_UP_SPAZ, {
                           {0, 0, 44, 62},  // Frame 1
                           {42, 0, 44, 62}, // Frame 2
                       }},

    {CROUCHING_SPAZ, {
                         {0, 0, 42, 49}, // Frame 1
                     }},

    {CROUCH_SPAZ, {
                      {0, 0, 51, 31}, // Frame 1
                  }},

    {CROUCH_SHOOTING_SPAZ, {
                               {0, 0, 53, 39},  // Frame 1
                               {55, 0, 53, 39}, // Frame 2
                           }},

    {STANDING_UP_SPAZ, {
                           {0, 0, 52, 46},   // Frame 1
                           {52, 0, 52, 46},  // Frame 2
                           {102, 0, 41, 46}, // Frame 3

                       }},

    {TRANSITION_TO_FLYING_KICK_SPAZ, {
                                         {0, 0, 50, 53},   // Frame 1
                                         {50, 0, 51, 53},  // Frame 2
                                         {102, 0, 40, 53}, // Frame 3
                                         {142, 0, 40, 53}, // Frame 4
                                         {181, 0, 45, 53}, // Frame 5
                                         {226, 0, 48, 53}, // Frame 6
                                         {274, 0, 51, 53}, // Frame 7
                                     }},
    {FLYING_KICK_SPAZ, {
                           {0, 0, 57, 53},   // Frame 1
                           {56, 0, 57, 53},  // Frame 2
                           {112, 0, 56, 53}, // Frame 3
                       }},

    {TRANSITION_AFTER_KICK_SPAZ, {
                                     {0, 0, 49, 53},  // Frame 1
                                     {50, 0, 50, 53}, // Frame 2
                                 }},

    {WALKING_SPAZ, {
                       {0, 0, 50, 50},   // Frame 1
                       {49, 0, 50, 50},  // Frame 2
                       {100, 0, 50, 50}, // Frame 3
                       {151, 0, 50, 50}, // Frame 4
                       {201, 0, 53, 50}, // Frame 5
                       {255, 0, 49, 50}, // Frame 6
                       {303, 0, 51, 50}, // Frame 7
                       {354, 0, 51, 50}, // Frame 8
                   }},
    {RUNNING_SPAZ, {
                       {0, 0, 49, 41},   // Frame 1
                       {49, 0, 57, 41},  // Frame 2
                       {107, 0, 51, 41}, // Frame 3
                       {159, 0, 51, 41}, // Frame 4
                       {208, 0, 51, 41}, // Frame 5
                       {259, 0, 56, 41}, // Frame 6
                       {316, 0, 50, 41}, // Frame 7
                       {367, 0, 50, 41}, // Frame 8
                   }},

    {PREPARING_TO_DASH_SPAZ, {
                                 {0, 0, 42, 58},   // Frame 1
                                 {42, 0, 47, 58},  // Frame 2
                                 {91, 0, 47, 58},  // Frame 3
                                 {139, 0, 49, 58}, // Frame 4
                                 {193, 0, 49, 58}, // Frame 5
                                 {248, 0, 53, 58}, // Frame 6
                                 {300, 0, 60, 58}, // Frame 7
                                 {362, 0, 65, 58}, // Frame 8
                                 {427, 0, 63, 58}, // Frame 9
                                 {489, 0, 64, 58}, // Frame 10
                                 {553, 0, 64, 58}, // Frame 11
                                 {622, 0, 62, 58}, // Frame 12
                                 {684, 0, 50, 58}, // Frame 13

                             }},

    {DASHING_SPAZ, {
                       {0, 0, 59, 43},   // Frame 1
                       {58, 0, 53, 43},  // Frame 2
                       {111, 0, 55, 43}, // Frame 3
                       {165, 0, 55, 43}, // Frame 4
                   }},

    {SKIDDING_SPAZ, {
                        {0, 0, 46, 43},   // Frame 1
                        {47, 0, 46, 43},  // Frame 2
                        {95, 0, 53, 43},  // Frame 3
                        {150, 0, 63, 43}, // Frame 4
                        {215, 0, 61, 43}, // Frame 5
                        {279, 0, 61, 43}, // Frame 6
                    }},

    {STOP_SKIDDING_SPAZ, {
                             {0, 0, 56, 50},   // Frame 1
                             {56, 0, 51, 50},  // Frame 2
                             {107, 0, 46, 50}, // Frame 3
                             {153, 0, 45, 50}, // Frame 4
                             {197, 0, 41, 50}, // Frame 5
                             {238, 0, 40, 50}, // Frame 6
                             {277, 0, 40, 50}, // Frame 7
                             {317, 0, 40, 50}, // Frame 8
                         }},

    {TRANSITION_TO_JUMPING_SPAZ, {
                                     {0, 0, 37, 58},  // Frame 1
                                     {37, 0, 41, 58}, // Frame 2
                                     {80, 0, 38, 58}, // Frame 3
                                 }},

    {JUMPING_UP_SPAZ, {
                          {0, 0, 50, 53},  // Frame 1
                          {49, 0, 45, 53}, // Frame 2
                          {93, 0, 45, 53}, // Frame 3
                      }},

    {TRANSITION_TO_FALLING_SPAZ, {
                                     {0, 0, 49, 54},   // Frame 1
                                     {48, 0, 53, 54},  // Frame 2
                                     {100, 0, 56, 54}, // Frame 3
                                 }},

    {FALLING_SPAZ, {
                       {0, 0, 55, 58},   // Frame 1
                       {56, 0, 55, 58},  // Frame 2
                       {110, 0, 55, 58}, // Frame 3
                   }},

    {JUMPING_FORWARD_SPAZ, {
                               {0, 0, 44, 52},   // Frame 1
                               {43, 0, 36, 52},  // Frame 2
                               {82, 0, 39, 52},  // Frame 3
                               {123, 0, 41, 52}, // Frame 4
                               {163, 0, 41, 52}, // Frame 5
                               {203, 0, 41, 52}, // Frame 6
                               {245, 0, 41, 52}, // Frame 7
                               {287, 0, 44, 52}, // Frame 8
                               {330, 0, 44, 52}, // Frame 9
                           }},

    {FALLING_FORWARD_SPAZ, {
                               {0, 0, 36, 52},  // Frame 1
                               {37, 0, 36, 52}, // Frame 2
                               {72, 0, 40, 52}, // Frame 3
                           }},

    {SHOOTING_WHILE_FALLING_SPAZ, {
                                      {0, 0, 46, 60},  // Frame 1
                                      {48, 0, 46, 60}, // Frame 2
                                  }},
    {STOP_SHOOTING_WHILE_FALLING_SPAZ, {
                                           {0, 0, 48, 60},  // Frame 1
                                           {45, 0, 48, 60}, // Frame 2
                                       }},

    {LANDING_SPAZ, {
                       {0, 0, 48, 48},   // Frame 1
                       {48, 0, 55, 48},  // Frame 2
                       {105, 0, 52, 48}, // Frame 3
                       {156, 0, 46, 48}, // Frame 4
                       {204, 0, 46, 48}, // Frame 5
                   }},

    {INTOXICATED_IDLE_SPAZ, {
                                {0, 0, 44, 54},   // Frame 1
                                {46, 0, 40, 54},  // Frame 2
                                {91, 0, 40, 54},  // Frame 3
                                {134, 0, 41, 54}, // Frame 4
                                {182, 0, 41, 54}, // Frame 5
                                {227, 0, 44, 54}, // Frame 6
                                {274, 0, 40, 54}, // Frame 7
                                {316, 0, 42, 54}, // Frame 8
                            }},

    {INTOXICATED_WALKING_SPAZ, {
                                   {0, 0, 40, 53},   // Frame 1
                                   {45, 0, 44, 53},  // Frame 2
                                   {89, 0, 44, 53},  // Frame 3
                                   {132, 0, 44, 53}, // Frame 4
                                   {175, 0, 44, 53}, // Frame 5
                                   {221, 0, 43, 53}, // Frame 6
                                   {264, 0, 43, 53}, // Frame 7
                                   {305, 0, 48, 53}, // Frame 8
                                   {353, 0, 47, 53}, // Frame 9
                                   {401, 0, 43, 53}, // Frame 10
                                   {444, 0, 43, 53}, // Frame 11
                                   {489, 0, 43, 53}, // Frame 12
                               }},

    {RECEIVE_DAMAGE_SPAZ, {
                              {0, 0, 49, 55},   // Frame 1
                              {51, 0, 49, 55},  // Frame 2
                              {104, 0, 52, 55}, // Frame 3
                              {159, 0, 64, 71}, // Frame 4
                              {231, 0, 74, 71}, // Frame 5
                              {315, 0, 74, 71}, // Frame 6
                              {403, 0, 74, 71}, // Frame 7
                              {487, 0, 63, 71}, // Frame 8
                              {551, 0, 63, 71}, // Frame 9
                              {617, 0, 55, 37}, // Frame 10
                              {676, 0, 49, 44}, // Frame 11
                          }},

    {WALKING_LIZARD, {
                         {3, 0, 65, 65},   // Frame 1
                         {83, 0, 56, 65},  // Frame 2
                         {150, 0, 49, 65}, // Frame 3
                         {204, 0, 72, 65}, // Frame 4
                         {284, 0, 56, 65}, // Frame 5
                         {353, 0, 56, 65}, // Frame 6
                         {419, 0, 62, 65}, // Frame 7
                         {496, 0, 63, 65}, // Frame 8
                         {582, 0, 67, 65}, // Frame 9
                         {664, 0, 67, 65}, // Frame 10
                         {738, 0, 73, 65}, // Frame 11
                         {817, 0, 77, 65}, // Frame 12
                     }},
    {FLYING_BAT, {
                     {0, 0, 68, 43},   // Frame 1
                     {69, 0, 66, 43},  // Frame 2
                     {135, 0, 67, 43}, // Frame 3
                     {204, 0, 68, 43}, // Frame 4
                     {273, 0, 64, 34}, // Frame 5
                     {337, 0, 48, 43}, // Frame 6
                     {384, 0, 32, 43}, // Frame 7
                     {419, 0, 68, 43}, // Frame 8
                 }},
    {WALKING_SKELETON, {
                           {0, 0, 57, 55},   // Frame 1
                           {62, 0, 44, 55},  // Frame 2
                           {107, 0, 44, 55}, // Frame 3
                           {151, 0, 51, 55}, // Frame 4
                           {205, 0, 62, 55}, // Frame 5
                           {266, 0, 45, 55}, // Frame 6
                           {311, 0, 35, 55}, // Frame 7
                           {346, 0, 48, 55}, // Frame 8
                           {394, 0, 55, 55}, // Frame 9
                           {449, 0, 44, 55}, // Frame 10
                           {492, 0, 41, 55}, // Frame 11
                           {534, 0, 52, 55}, // Frame 12
                           {585, 0, 62, 55}, // Frame 13
                           {648, 0, 49, 55}, // Frame 14
                           {694, 0, 37, 55}, // Frame 15
                           {730, 0, 51, 55}, // Frame 16
                       }},
    {CRAB, {
               {0, 0, 42, 35},   // Frame 1
               {42, 0, 40, 35},  // Frame 2
               {81, 0, 39, 35},  // Frame 3
               {119, 0, 43, 35}, // Frame 4
               {161, 0, 43, 35}, // Frame 5
               {203, 0, 43, 35}, // Frame 6
               {247, 0, 40, 35}, // Frame 7
               {287, 0, 44, 35}, // Frame 8
           }},
    {FISH, {
               {0, 0, 58, 48},   // Frame 1
               {57, 0, 57, 48},  // Frame 2
               {115, 0, 57, 48}, // Frame 3
               {171, 0, 57, 48}, // Frame 4
               {226, 0, 57, 48}, // Frame 5
               {282, 0, 57, 48}, // Frame 6
               //{340, 0, 57, 48}, // Frame 7
               //{397, 0, 57, 48}, // Frame 8
           }},
    {TURTLE, {
                 {0, 0, 61, 60},   // Frame 1
                 {60, 0, 49, 60},  // Frame 2
                 {108, 0, 46, 60}, // Frame 3
                 {152, 0, 46, 60}, // Frame 4
                 {197, 0, 59, 60}, // Frame 5
                 {256, 0, 56, 60}, // Frame 6
                 {311, 0, 42, 60}, // Frame 7
                 {353, 0, 41, 60}, // Frame 8
                 {394, 0, 48, 60}, // Frame 9
                 {441, 0, 67, 60}, // Frame 10
             }},
    {GEM, {
              {0, 0, 31, 32},   // Frame 1
              {31, 0, 29, 32},  // Frame 2
              {59, 0, 29, 32},  // Frame 3
              {88, 0, 29, 32},  // Frame 4
              {117, 0, 29, 32}, // Frame 5
              {146, 0, 29, 32}, // Frame 6
              {175, 0, 29, 32}, // Frame 7
              {204, 0, 32, 32}, // Frame 8
          }},
    {COIN, {
               {0, 0, 28, 29},   // Frame 1
               {27, 0, 26, 29},  // Frame 2
               {52, 0, 24, 29},  // Frame 3
               {75, 0, 20, 29},  // Frame 4
               {94, 0, 16, 29},  // Frame 5
               {109, 0, 11, 29}, // Frame 6
               {119, 0, 16, 29}, // Frame 7
               {134, 0, 20, 29}, // Frame 8
               {153, 0, 25, 29}, // Frame 9
               {177, 0, 27, 29}, // Frame 10
               {203, 0, 27, 29}, // Frame 11
               {229, 0, 27, 29}, // Frame 12
               {255, 0, 25, 29}, // Frame 13
               {279, 0, 20, 29}, // Frame 14
               {298, 0, 16, 29}, // Frame 15
               {313, 0, 11, 29}, // Frame 16
               {323, 0, 15, 29}, // Frame 17
               {337, 0, 19, 29}, // Frame 18
               {355, 0, 24, 29}, // Frame 19
               {378, 0, 25, 29}, // Frame 20
           }},
    {POISON_FRUIT, {
                         {0, 0, 30, 30},      // Frame 1
                 }},

    {FIREBALL, {
                   {0, 0, 22, 21},   // Frame 1
                   {21, 0, 16, 21},  // Frame 2
                   {36, 0, 16, 21},  // Frame 3
                   {51, 0, 16, 21},  // Frame 4
                   {66, 0, 15, 21},  // Frame 5
                   {80, 0, 14, 21},  // Frame 6
                   {93, 0, 15, 21},  // Frame 7
                   {107, 0, 16, 21}, // Frame 8
                   {122, 0, 16, 21}, // Frame 9
                   {137, 0, 22, 21}, // Frame 10
               }},
    {SHOT_FIREBALL, {
                        {0, 0, 26, 10},  // Frame 1
                        {25, 0, 26, 10}, // Frame 2
                        {49, 0, 28, 10}, // Frame 3
                    }},

    {RED_ROCKET, {
                     {3, 5, 20, 13},   // Frame 1
                     {24, 0, 23, 22},  // Frame 2
                     {46, 0, 17, 22},  // Frame 3
                     {62, 0, 17, 22},  // Frame 4
                     {78, 0, 23, 22},  // Frame 5
                     {100, 0, 24, 22}, // Frame 6
                     {123, 0, 23, 22}, // Frame 7
                     {145, 0, 17, 22}, // Frame 8
                     {161, 0, 17, 22}, // Frame 9
                     {177, 0, 26, 22}, // Frame 10
                 }},
    {SHOT_RED_ROCKET, {
                          {0, 0, 25, 15},   // Frame 1
                          {24, 0, 23, 15},  // Frame 2
                          {46, 0, 23, 15},  // Frame 3
                          {68, 0, 23, 15},  // Frame 4
                          {90, 0, 23, 15},  // Frame 5
                          {112, 0, 24, 15}, // Frame 6
                      }},

    {BULLET, {
                 {0, 0, 17, 12},  // Frame 1
                 {16, 0, 15, 12}, // Frame 2
                 {31, 0, 15, 12}, // Frame 3
             }},

    // Escenario
    {Background_AIW, {
                         {0, 0, 300, 300},
                     }},

    // Beach Level (necesario para el editor)
    {STATIC_ANIMATION, {{0, 0, 500, 500}}},
    {BEACH_LANDSCAPE, {{0, 0, 320, 96}}},
    {BEACH_FLOOR, {{0, 0, 320, 32}}},
    {BEACH_FLOATING_FLOOR, {{0, 0, 191, 63}}},
    {BEACH_PLATFORM, {{0, 0, 256, 160}}},
    {BEACH_RISE_DESCENT, {{0, 0, 324, 168}}},
    {BEACH_DESCENT, {{0, 0, 162, 161}}},
    {BEACH_RISE, {{0, 0, 158, 177}}},
    {BEACH_FLOATING_PLATFORM, {{0, 0, 90, 20}}},
    {BEACH_EXIT_SIGN, {{0, 0, 33, 22}}},
    {BEACH_ALGAE, {{0, 0, 46, 49}}},

    {SPAWN_POINT, {{0, 0, 75, 75}}},
    {Background_BEACH, {
                           {0, 0, 255, 155},
                       }},
    {DYING_INVISIBLE, {{0, 0, 0, 0}}},

    // AIW
    {ARROW, {{0, 0, 32, 32}}},
    {FLOOR_AIW, {{0, 0, 308, 100}}},
    {GUITAR, {{0, 0, 320, 128}}},
    {CHESIRE, {{5, 0, 45, 32}}},
    {DESCENT, {{0, 0, 345, 261}}},
    {RISE, {{0, 0, 211, 261}}},
    {RED_MUSHROOM, {{0, 0, 55, 65}}},
    {EXIT, {{0, 0, 32, 32}}},
    {ROCKS2_AIW, {{0, 0, 124, 163}}},
    {ROCKS, {{0, 0, 307, 200}}},
    {ROCKS3_AIW, {{0, 0, 307, 200}}},
    {FLOOR2_AIW, {{0, 0, 372, 100}}},
    {FLOOR3_AIW, {{0, 0, 372, 100}}},
    {FLOOR4_AIW, {{0, 0, 386, 100}}},
    {STONE_TOWER, {{0, 0, 227, 346}}},
    {COLUMN_STONES, {{0, 0, 392, 281}}},
    {COLUMN_STONES_RIGHT, {{0, 0, 392, 281}}},
    {COLUMN_STONES_LOWER, {{0, 0, 374, 336}}},
    {COLUMN_STONES_LOWER_RIGHT, {{0, 0, 374, 336}}},
    {FLOOR_AFTER_RAISE, {{0, 0, 136, 100}}},
    {ROCKS_AFTER_RAISE, {{0, 0, 134, 163}}},
    {FLOOR_BEFORE_DESCENT, {{0, 0, 136, 100}}},
    {ROCKS_BEFORE_DESCENT, {{0, 0, 134, 163}}},
    {FLOOR_STONE_TOWER, {{0, 0, 220, 63}}},
    {MAD_HATTER, {
                     {0, 0, 60, 60},   // Frame 1
                     {65, 0, 60, 60},  // Frame 2
                     {135, 0, 60, 60}, // Frame 3
                     {210, 0, 55, 60}, // Frame 4
                     {271, 0, 60, 60}, // Frame 5
                     {340, 0, 52, 65}, // Frame 6
                     {406, 0, 57, 65}, // Frame 7
                     {467, 0, 47, 65}, // Frame 8
                     {520, 0, 60, 65}, // Frame 9
                     {582, 0, 55, 65}, // Frame 10
                     {639, 0, 63, 65}, // Frame 11
                     {717, 0, 55, 65}, // Frame 12

                 }},
    {SKELETON, {
                   {0, 0, 45, 55},   // Frame 1
                   {65, 0, 45, 55},  // Frame 2
                   {110, 0, 35, 55}, // Frame 3
                   {150, 0, 50, 55}, // Frame 4
                   {205, 0, 58, 55}, // Frame 5
                   {265, 0, 43, 55}, // Frame 6
                   {312, 0, 30, 55}, // Frame 7
                   {350, 0, 40, 55}, // Frame 8
                   {397, 0, 50, 55}, // Frame 9
                   {450, 0, 42, 55}, // Frame 10
                   {495, 0, 35, 55}, // Frame 11
                   {535, 0, 50, 55}, // Frame 12
                   {587, 0, 58, 55}, // Frame 13
                   {654, 0, 35, 55}, // Frame 14
                   {700, 0, 27, 55}, // Frame 15
                   {735, 0, 40, 55}, // Frame 16
               }},
    {DYING_LORI, {
                     {0, 0, 50, 100},    // Frame 1
                     {75, 0, 41, 100},   // Frame 2
                     {130, 0, 75, 100},  // Frame 3
                     {613, 0, 230, 116}, // Frame 4
                     {622, 0, 242, 110}, // Frame 5
                     {875, 0, 245, 110}, // Frame 6

                     {0, 125, 85, 92},   // Frame 7
                     {173, 125, 84, 92}, // Frame 8
                     {179, 125, 84, 92}, // Frame 9
                     {292, 125, 51, 92}, // Frame 9

                     {380, 125, 55, 92}, // Frame 10
                     {451, 125, 50, 92}, // Frame 11
                     {506, 125, 55, 92}, // Frame 12
                     {567, 125, 40, 92}, // Frame 13

                     {615, 125, 55, 92}, // Frame 10
                     {670, 125, 55, 92}, // Frame 11
                     {734, 125, 50, 92}, // Frame 12
                     {793, 125, 40, 92}, // Frame 13

                     {839, 125, 40, 92},  // Frame 14
                     {890, 125, 50, 92},  // Frame 15
                     {948, 125, 50, 92},  // Frame 16
                     {1005, 125, 55, 92}, // Frame 17

                 }},
    {DYING_SPAZ, {
                     {0, 0, 70, 115},      // Frame 1
                     {100, 0, 100, 125},   // Frame 2
                     {210, 0, 106, 125},   // Frame 3
                     {310, 0, 127, 125},   // Frame 4
                     {439, 0, 106, 40},    // Frame 5
                     {545, 0, 70, 40},     // Frame 6
                     {620, 0, 20, 40},     // Frame 7
                     {655, 0, 35, 40},     // Frame 8
                     {694, 0, 45, 40},     // Frame 9
                     {740, 0, 70, 40},     // Frame 10
                     {808, 0, 100, 40},    // Frame 11
                     {912, 0, 116, 40},    // Frame 12
                     {0, 120, 120, 120},   // Frame 13
                     {125, 120, 115, 120}, // Frame 14
                     {245, 120, 81, 120},  // Frame 15
                     {335, 120, 81, 120},  // Frame 16
                     {420, 120, 55, 120},  // Frame 17

                 }},
};

const std::map<enum Guns, Frame> gun_position = {
    {
        GREEN_GUN,
        {0, 0, 25, 30},
    },
    {
        VIOLET_GUN,
        {0, 0, 45, 35},
    },
    {
        BLUE_GUN,
        {0, 80, 30, 40},
    },
};
/*
{PREPARING_TO_DASH_JAZZ, {
                               {5, 10, 41, 56},     // Frame 1
                               {46, 10, 43, 56},   // Frame 2
                               {91, 10, 46, 56},  // Frame 3
                               {137, 10, 52, 56},  // Frame 4
                               {188, 10, 55, 56},  // Frame 5
                               {244, 2, 51, 64},  // Frame 6
                               {296, 0, 62, 66},  // Frame 7
                       }},
{CHARGING_DASH_JAZZ, {
                                 {0, 0, 70, 49},     // Frame 1
                                 {69, 0, 67, 49},   // Frame 2
                                 {135, 0, 69, 49},  // Frame 3
                                 {203, 0, 67, 49},  // Frame 4
                         }},
{TRANSITION_TO_DASHING_JAZZ, {
                             {0, 0, 61, 49},     // Frame 1
                             {60, 0, 60, 49},   // Frame 2
                     }},
{TRANSITION_TO_SKIDDING_JAZZ, {
                               {0, 0, 58, 41},     // Frame 1
                               {58, 0, 56, 41},   // Frame 2
                               {115, 0, 57, 41},  // Frame 3
                       }},
{SKIDDING_JAZZ, {
                                              {0, 0, 70, 41},     // Frame 1
                                              {69, 0, 66, 41},   // Frame 2
                                              {135, 0, 68, 41},  // Frame 3
                                      }},

                     */

#endif // SPRITES_LOADER_H
