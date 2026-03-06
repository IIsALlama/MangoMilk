
#include "game_render.h"
#include "game_manager.h"
#include "resource_manager.h"
#include "common.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <Windows.h>
namespace fs = std::filesystem;

import Entity;
import Transform;
import SpriteRenderer;

using std::vector;


unsigned int frameBuffer;
unsigned int renderBuffer;

namespace MangoMilk {
    namespace GameRender {
        GLsizei W = 1920;
        GLsizei H = 1080;

        float aspect;

        bool init;
        unsigned int outputTexture;

        static std::wstring getExePath() {
            wchar_t buffer[MAX_PATH]; // Buffer to store the path
            GetModuleFileNameW(NULL, buffer, MAX_PATH); // Retrieve the path
            return std::wstring(buffer); // Convert to std::wstring
        }

        void LoadShaders() {
            ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

            glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(W),
                static_cast<float>(H), 0.0f, -1.0f, 1.0f);
            ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
            ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
        }

        void LoadTextures() {
            fs::path texPath = fs::current_path() += "/textures";
            for (const auto& entry : fs::directory_iterator(texPath)) {
                std::string strPath = entry.path().string();
                ResourceManager::LoadTexture(strPath.c_str(), true, strPath.substr(strPath.find_last_of("/\\") + 1));
            }
        }

        void Initialize()
        {
            glGenFramebuffers(1, &frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

            glGenTextures(1, &outputTexture);
            glBindTexture(GL_TEXTURE_2D, outputTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, 0);

            glGenRenderbuffers(1, &renderBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, W, H);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            aspect = (float)H / (float)W;

            LoadShaders();
            LoadTextures();

            init = true;
        }

        bool IsInitialized() {
            return init;
        }

        void Terminate()
        {
            glDeleteFramebuffers(1, &frameBuffer);
            glDeleteTextures(1, &outputTexture);
            glDeleteRenderbuffers(1, &renderBuffer);

            ResourceManager::Clear();

            init = false;
        }

        void _BindFramebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        }

        void _UnbindFramebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Rescale(float width, float height)
        {
            GLsizei _w = (GLsizei)width;
            GLsizei _h = (GLsizei)height;
            glBindTexture(GL_TEXTURE_2D, outputTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _w, _h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _w, _h);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
        }

        void Render()
        {
            _BindFramebuffer();

            vector<Entity*> entities = GameManager::GetEntities();
            for (size_t i = 0; i < entities.size(); i++)
            {
                Entity* entity = entities[i];
                SpriteRenderer* renderer = entity->GetComponent<SpriteRenderer>();

                if (renderer != nullptr) {
                    Vector2 pos = entity->transform->GetWorldPosition() * 100.0f;
                    Vector2 scale = entity->transform->scale * 100.0f;
                    float rot = entity->transform->rotation;

                    renderer->DrawSprite(renderer->texture, glm::vec2(pos.x + W/2.0f - scale.x/2.0f, pos.y + H/2.0f - scale.y/2.0f), glm::vec2(scale.x, scale.y), rot, glm::vec3(renderer->colour.r, renderer->colour.g, renderer->colour.b));

                    /*glBegin(GL_TRIANGLES);
                    glVertex2f(pos.x-0.5f * scale.x, pos.y-0.5f * scale.y);
                    glVertex2f(pos.x-0.5f * scale.x, pos.y+0.5f * scale.y);
                    glVertex2f(pos.x+0.5f * scale.x, pos.y-0.5f * scale.y);
                    glEnd();

                    glBegin(GL_TRIANGLES);
                    glVertex2f(pos.x - 0.5f * scale.x, pos.y + 0.5f * scale.y);
                    glVertex2f(pos.x + 0.5f * scale.x, pos.y + 0.5f * scale.y);
                    glVertex2f(pos.x + 0.5f * scale.x, pos.y - 0.5f * scale.y);
                    glEnd();*/
                }
            }

            _UnbindFramebuffer();
        }
    }

}
